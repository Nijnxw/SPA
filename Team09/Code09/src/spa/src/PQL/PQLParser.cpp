#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

#include "PQL/PQLParser.h"
#include "PQL/PQLUtils.cpp"
#include "util/RPN.h"

PQLParser::PQLParser(std::vector<PQLToken*> PQLTokens) : current(0), end(PQLTokens.size()), tokens(PQLTokens) {}

bool PQLParser::isValidSynonym(PQLToken* token) {
	return token->getType() == TokenType::SYNONYM || keywords.find(token->getType()) != keywords.end();
}

bool PQLParser::isDeclaredSynonym(std::string syn) {
	return Declarations.find(syn) != Declarations.end();
}

PQLToken* PQLParser::peekNextToken() {
	if (current == end) {
		throw "Runtime error : no more tokens to parse";
	}
	return tokens[current];
}

bool PQLParser::nextIsComma() {
	return (peekNextToken())->getType() == TokenType::COMMA;
}


PQLToken* PQLParser::getNextToken() {
	if (current == end) {
		throw "Runtime error : no more tokens to parse";
	}
	PQLToken* token = tokens[current];
	current++;
	return token;
}

PQLToken* PQLParser::getNextExpectedToken(TokenType TokenType) {
	PQLToken* token = getNextToken();
	if (token->getType() != TokenType) {
		throw "unexpected token type.";
	}
	return token;
}

PQLToken* PQLParser::getValidSynonymToken() {
	PQLToken* token = getNextToken();
	if (isValidSynonym(token)) {
		return token;
	}
	throw "unexpected token type.";
}

void PQLParser::parseEndOfDeclaration() {
	getNextExpectedToken(TokenType::SEMICOLON);
}

void PQLParser::parseDeclaration() {
	auto nextToken = getNextToken();
	auto entityType = entityTypeMapping.find(nextToken->getType());

	if (entityType == entityTypeMapping.end()) {
		throw "invalid entity type.";
	}

	auto expectedSynonym = getValidSynonymToken();

	if (isDeclaredSynonym(expectedSynonym->getValue())) {
		throw "Duplicated declarations detected";
	}

	Declarations[expectedSynonym->getValue()] = entityType->second;

	while (current != end && nextIsComma()) {
		getNextExpectedToken(TokenType::COMMA);
		nextToken = getValidSynonymToken();
		if (isDeclaredSynonym(nextToken->getValue()) ) {
			throw "Duplicated declarations detected";
		}
		Declarations[nextToken->getValue()] = entityType->second;
	}

	parseEndOfDeclaration();
}

void PQLParser::parseSelect() {
	getNextExpectedToken(TokenType::SELECT);
	parseResultClause(); 
}

void PQLParser::parseResultTuple() {
	getNextExpectedToken(TokenType::OPEN_ANGLED);
	parseResultSynonym();
	while (current != end && peekNextToken()->getType() != TokenType::CLOSE_ANGLED) {
		getNextExpectedToken(TokenType::COMMA);
		parseResultSynonym();
	}
	getNextExpectedToken(TokenType::CLOSE_ANGLED);
}

void PQLParser::parseResultBoolean() {
	getNextExpectedToken(TokenType::BOOLEAN);
	isBooleanQuery = true;
}

void PQLParser::parseResultClause() {
	PQLToken* currToken = peekNextToken();
	if (currToken->getType() == TokenType::BOOLEAN && !isDeclaredSynonym(currToken->getValue())) {
		parseResultBoolean();
	} else if (currToken->getType() == TokenType::OPEN_ANGLED) {
		parseResultTuple();
	} else if (isValidSynonym(currToken)) {
		parseResultSynonym();
	}else {
		throw "invalid result clause";
	}
}

void PQLParser::parseResultSynonym() {
	auto nextToken = getValidSynonymToken();;
	if (!isDeclaredSynonym(nextToken->getValue())) {
		throw "Result synonym is not declared";
	}
	resultSynonyms.push_back(QueryArgument(std::string(nextToken->getValue()), Declarations[nextToken->getValue()]));
}

QueryArgument PQLParser::parseArgs(PQLToken* token) {
	switch (token->getType()) {
		case TokenType::UNDERSCORE:
		case TokenType::INTEGER:
			return QueryArgument(std::string(token->getValue()), entityTypeMapping[token->getType()]);
			break;
		case TokenType::STRING:
			if (isIdent(token->getValue())) {
				return QueryArgument(std::string(token->getValue()), entityTypeMapping[token->getType()]);
				break;
			}
			throw "invalid string";
		default:
			if (isDeclaredSynonym(token->getValue())) {
				return QueryArgument(std::string(token->getValue()), Declarations[token->getValue()]);
				break;
			}
			throw "Invalid argument";
	}
}

void PQLParser::parseSingleRelationshipClause() {
	auto nextToken = getNextToken();
	auto relationType = relationTypeMapping.find(nextToken->getType());
	if (relationType == relationTypeMapping.end()) {
		throw "invalid relation type.";
	}

	getNextExpectedToken(TokenType::OPEN_PARAN);

	auto validArgTypes = relationValidArgsTypeMap.at(relationType->second);
	std::vector<QueryArgument> relArgs;
	std::unordered_set<std::string> usedSynonyms;
	for (int i = 0; i < validArgTypes.size(); i++) {
		auto validArgs = validArgTypes[i];
		auto nextToken = getNextToken();
		auto arg = parseArgs(nextToken);

		if (validArgs.find(arg.getType()) == validArgs.end()) {
			throw "Invalid arguments for relationship clause.";
		}

		if (isValidSynonym(nextToken)) {
			usedSynonyms.insert(nextToken->getValue());
		}

		relArgs.push_back(arg);
		if (i != validArgTypes.size() - 1) {
			getNextExpectedToken(TokenType::COMMA);
		}
	}

	getNextExpectedToken(TokenType::CLOSE_PARAN);

	if (relArgs.size() != validArgTypes.size()) {
		throw "Invalid number of arguments.";
	}

	QueryClauses.push_back(QueryClause(relationType->second, relArgs, usedSynonyms));
}

void PQLParser::parseRelationshipClause() {
	parseSingleRelationshipClause();
	while (current != end && peekNextToken()->getType() == TokenType::AND) {
		getNextExpectedToken(TokenType::AND);
		parseSingleRelationshipClause();
	}
}

void PQLParser::parseSuchThatClause() {
	getNextExpectedToken(TokenType::SUCH);
	getNextExpectedToken(TokenType::THAT);

	parseRelationshipClause();
}

QueryArgument PQLParser::parsePatternArgStmtList() {
	getNextExpectedToken(TokenType::UNDERSCORE);
	return QueryArgument(std::string("_"), entityTypeMapping[TokenType::UNDERSCORE]);
}


QueryArgument PQLParser::parsePatternVarArgs() {
	auto nextToken = getNextToken();
	auto arg = parseArgs(nextToken);
	if (VarArgTypes.find(arg.getType()) == VarArgTypes.end()) {
		throw "Invalid arguments for pattern clause.";
	}
	return arg;
}

void PQLParser::parseWhilePattern(PQLToken* synonymToken) {
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> usedSynonyms;
	usedSynonyms.insert(synonymToken->getValue());
	QueryArgument arg1 = parsePatternVarArgs();
	if (arg1.getType() != EntityType::STRING && arg1.getType() != EntityType::WILD) {
		usedSynonyms.insert(arg1.getValue());
	}
	patternArgs.emplace_back(arg1);
	getNextExpectedToken(TokenType::COMMA);
	patternArgs.emplace_back(parsePatternArgStmtList());
	getNextExpectedToken(TokenType::CLOSE_PARAN);
	QueryClauses.push_back(QueryClause(RelationRef::PATTERN_WHILE, patternArgs, usedSynonyms, synonymToken->getValue()));
}

void PQLParser::parseIfPattern(PQLToken* synonymToken) {
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> usedSynonyms;
	usedSynonyms.insert(synonymToken->getValue());
	QueryArgument arg1 = parsePatternVarArgs();
	if (arg1.getType() != EntityType::STRING && arg1.getType() != EntityType::WILD) {
		usedSynonyms.insert(arg1.getValue());
	}
	patternArgs.emplace_back(arg1);
	getNextExpectedToken(TokenType::COMMA);
	patternArgs.emplace_back(parsePatternArgStmtList());
	getNextExpectedToken(TokenType::COMMA);
	patternArgs.emplace_back(parsePatternArgStmtList());
	getNextExpectedToken(TokenType::CLOSE_PARAN);
	QueryClauses.push_back(QueryClause(RelationRef::PATTERN_IF, patternArgs, usedSynonyms, synonymToken->getValue()));
}

QueryArgument PQLParser::parseAssignPatternRHS() {
	auto nextToken = getNextToken();
	std::string infix;
	switch (nextToken->getType()) {
		case TokenType::UNDERSCORE: {
			auto followingToken = getNextToken();
			switch (followingToken->getType()) {
				case TokenType::STRING:
					getNextExpectedToken(TokenType::UNDERSCORE);
					getNextExpectedToken(TokenType::CLOSE_PARAN);
					if (!isValidExpr(followingToken->getValue())) { throw "invalid expression"; }
					infix = RPN::convertToRpn(followingToken->getValue());
					return QueryArgument(std::string("_" + infix + "_"), entityTypeMapping[followingToken->getType()]);
				case TokenType::CLOSE_PARAN:
					return QueryArgument(std::string("_"), entityTypeMapping[nextToken->getType()]);
				default:
					throw "unexpected Token encountered";
			}
		}
		case TokenType::STRING:
			getNextExpectedToken(TokenType::CLOSE_PARAN);
			if (!isValidExpr(nextToken->getValue())) { throw "invalid expression"; }
			infix = RPN::convertToRpn(nextToken->getValue());
			return QueryArgument(infix, entityTypeMapping[TokenType::STRING]);
		default:
			throw "Invalid Argument.";
	};
}

void PQLParser::parseAssignPattern(PQLToken* synonymToken) {
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> usedSynonyms;
	usedSynonyms.insert(synonymToken->getValue());
	QueryArgument LHS = parsePatternVarArgs();
	if (LHS.getType() != EntityType::STRING && LHS.getType() != EntityType::WILD) {
		usedSynonyms.insert(LHS.getValue());
	}
	patternArgs.emplace_back(LHS);
	getNextExpectedToken(TokenType::COMMA);
	patternArgs.emplace_back(parseAssignPatternRHS());
	QueryClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, patternArgs, usedSynonyms, synonymToken->getValue()));
}

void PQLParser::parseSinglePatternClause() {
	auto synonymToken = getValidSynonymToken();
	auto synonymType = Declarations.find(synonymToken->getValue());
	if (synonymType == Declarations.end()) {
		throw "invalid syn-assign";
	}
	getNextExpectedToken(TokenType::OPEN_PARAN);
	switch (synonymType->second) {
		case (EntityType::ASSIGN):
			parseAssignPattern(synonymToken);
			break;
		case (EntityType::IF):
			parseIfPattern(synonymToken);
			break;
		case (EntityType::WHILE):
			parseWhilePattern(synonymToken);
			break;
		default:
			throw "invalid pattern syn";
			break;
	}
}

void PQLParser::parsePatternClause() {
	getNextExpectedToken(TokenType::PATTERN);
	parseSinglePatternClause();
	while (current != end && peekNextToken()->getType() == TokenType::AND) {
		getNextExpectedToken(TokenType::AND);
		parseSinglePatternClause();
	}
}


void PQLParser::parseAfterSelect() {
	while (current != end) {
		switch (peekNextToken()->getType()) {
			case TokenType::SUCH:
				parseSuchThatClause();
				break;
			case TokenType::PATTERN:
				parsePatternClause();
				break;
			default:
				throw "Expected such that or pattern";
		}
	}
}

Query PQLParser::parse() {
	try {
		while (current != end && entityTypeMapping.find(peekNextToken()->getType()) != entityTypeMapping.end()) {
			parseDeclaration();
		}
		parseSelect();
		parseAfterSelect();
		return Query(resultSynonyms, QueryClauses, isBooleanQuery);
	} catch (...) {
		return Query();
	}
}


