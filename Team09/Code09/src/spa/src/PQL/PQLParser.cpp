#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

#include "PQL/PQLParser.h"
#include "PQL/PQLUtils.cpp"
#include "util/RPN.h"

PQLParser::PQLParser(std::vector<PQLToken*> PQLTokens) : current(0), end(PQLTokens.size()), tokens(PQLTokens) {}

void PQLParser::setSemanticErrorFlag() {
	isSemanticErrorDetected = true;
}

bool PQLParser::isValidSynonym(PQLToken* token) {
	return token->getType() == TokenType::SYNONYM || keywords.find(token->getType()) != keywords.end();
}

bool PQLParser::isAttributeRef(PQLToken* token) {
	return attrRefMapping.find(token->getType()) != attrRefMapping.end();
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

bool PQLParser::isWithArgNameType(QueryArgument arg) {
	return arg.getType() == EntityType::STRING || nameAttr.find(arg.getAttrRef()) != nameAttr.end();
}

bool PQLParser::isWithArgNumberType(QueryArgument arg) {
	return arg.getType() == EntityType::INT || numberAttr.find(arg.getAttrRef()) != numberAttr.end();
}

bool PQLParser::isWithArgsSameType(QueryArgument arg1, QueryArgument arg2) {
	return (isWithArgNameType(arg1) && isWithArgNameType(arg2)) || (isWithArgNumberType(arg1) && isWithArgNumberType(arg2));
}

bool PQLParser::isValidAttributeRefSynPair(EntityType synonym, TokenType attributeRef) {
	bool isValidAttr = attrRefMapping.find(attributeRef) != attrRefMapping.end();
	auto attrRefSynTypeMap = attrRefEntityTypeMap.find(attributeRef);
	bool isValidattrRefSynTypeMap = attrRefSynTypeMap != attrRefEntityTypeMap.end() && attrRefEntityTypeMap[attributeRef].find(synonym) != attrRefEntityTypeMap[attributeRef].end();
	return isValidAttr && isValidattrRefSynTypeMap;
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
		setSemanticErrorFlag();
	}

	Declarations[expectedSynonym->getValue()] = entityType->second;

	while (current != end && nextIsComma()) {
		getNextExpectedToken(TokenType::COMMA);
		nextToken = getValidSynonymToken();
		if (isDeclaredSynonym(nextToken->getValue())) {
			setSemanticErrorFlag();
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
	auto synonymToken = getValidSynonymToken();;
	if (!isDeclaredSynonym(synonymToken->getValue()) && !isSemanticErrorDetected) {
		setSemanticErrorFlag();
	}	
	if (current != end && peekNextToken()->getType() == TokenType::PERIOD) {
		getNextExpectedToken(TokenType::PERIOD);
		auto attrRefToken = getNextToken();
		if (!isAttributeRef(attrRefToken)) {
			throw "invalid attribute ref";
		}
		if (!isValidAttributeRefSynPair(Declarations[synonymToken->getValue()], attrRefToken->getType())) { 
			setSemanticErrorFlag();
			return;
		}
		resultSynonyms.emplace_back(
			QueryArgument(std::string(synonymToken->getValue()), Declarations[synonymToken->getValue()], attrRefMapping[attrRefToken->getType()])
		);
	} else {
		if (isSemanticErrorDetected) { return; }
		resultSynonyms.emplace_back(QueryArgument(std::string(synonymToken->getValue()), Declarations[synonymToken->getValue()]));
	}
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
			} else if (isValidSynonym(token)) {
				setSemanticErrorFlag();
				return QueryArgument(std::string(token->getValue()), EntityType::NONE);
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
			setSemanticErrorFlag();
		}

		if (isValidSynonym(nextToken)) {
			usedSynonyms.insert(nextToken->getValue());
		}

		relArgs.emplace_back(arg);
		if (i != validArgTypes.size() - 1) {
			getNextExpectedToken(TokenType::COMMA);
		}
	}

	getNextExpectedToken(TokenType::CLOSE_PARAN);

	if (relArgs.size() != validArgTypes.size()) {
		throw "Invalid number of arguments.";
	}

	QueryClauses.emplace_back(QueryClause(relationType->second, relArgs, usedSynonyms));
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
		setSemanticErrorFlag();
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
	QueryClauses.emplace_back(QueryClause(RelationRef::PATTERN_ASSIGN, patternArgs, usedSynonyms, synonymToken->getValue()));
}

void PQLParser::parseSinglePatternClause() {
	auto synonymToken = getValidSynonymToken();
	auto synonymType = Declarations.find(synonymToken->getValue());
	if (synonymType == Declarations.end() && !isSemanticErrorDetected) {
		setSemanticErrorFlag();
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
			setSemanticErrorFlag();
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

QueryArgument PQLParser::parseWithArgs() {
	auto token = getNextToken();
	switch (token->getType()) {
	case TokenType::STRING:
		if (!isIdent(token->getValue())) { throw "invalid string"; }
		return QueryArgument(token->getValue(), entityTypeMapping[token->getType()]);
	case TokenType::INTEGER:
		return QueryArgument(token->getValue(), entityTypeMapping[token->getType()]);
	case TokenType::SYNONYM : {
		getNextExpectedToken(TokenType::PERIOD);
		auto nextToken = getNextToken();
		if (!isAttributeRef(nextToken)) { throw "invalid attribute ref token"; }
		if (!isValidAttributeRefSynPair(Declarations[token->getValue()],nextToken->getType())) {
			setSemanticErrorFlag();
			return QueryArgument(token->getValue(), EntityType::NONE);
		}
		return QueryArgument(token->getValue(), Declarations[token->getValue()], attrRefMapping[nextToken->getType()]);
	}
	default :
		throw "invalid with argument";
	}

}

void PQLParser::parseSignleWithClause() {
	std::vector<QueryArgument> withArgs;
	std::unordered_set<std::string> usedSynonyms;
	QueryArgument LHS = parseWithArgs();
	if (LHS.getType() != EntityType::STRING && LHS.getType() != EntityType::INT) {
		usedSynonyms.insert(LHS.getValue());
	}
	getNextExpectedToken(TokenType::EQUAL);
	QueryArgument RHS = parseWithArgs();
	if (RHS.getType() != EntityType::STRING && RHS.getType() != EntityType::INT) {
		usedSynonyms.insert(RHS.getValue());
	}
	if (!isWithArgsSameType(LHS, RHS)) { 
		setSemanticErrorFlag();
	}
	withArgs.emplace_back(LHS);
	withArgs.emplace_back(RHS);
	QueryClauses.emplace_back(QueryClause(RelationRef::WITH, withArgs, usedSynonyms));
}

void PQLParser::parseWithClause() {
	getNextExpectedToken(TokenType::WITH);
	parseSignleWithClause();
	while (current != end && peekNextToken()->getType() == TokenType::AND) {
		getNextExpectedToken(TokenType::AND);
		parseSignleWithClause();
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
			case TokenType::WITH:
				parseWithClause();
				break;
			default:
				throw "Expected such that or pattern or with";
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
		if (isSemanticErrorDetected) {
			return Query(isBooleanQuery, isSemanticErrorDetected);
		}
		return Query(resultSynonyms, QueryClauses, isBooleanQuery);
	} catch (...) {
		return Query();
	}
}


