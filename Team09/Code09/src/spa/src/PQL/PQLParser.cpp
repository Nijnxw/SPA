#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

#include "PQL/PQLParser.h"
#include "PQL/PQLUtils.cpp"

PQLParser::PQLParser(std::vector<PQLToken*> PQLTokens) : current(0), end(PQLTokens.size()), tokens(PQLTokens) {}

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
	if (token->getType() == TokenType::SYNONYM || keywords.find(token->getType()) != keywords.end()) {
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
	if (Declarations.find(expectedSynonym->getValue()) != Declarations.end()) {
		throw "Duplicated declarations detected";
	}
	Declarations[expectedSynonym->getValue()] = entityType->second;

	while (current != end && (tokens.at(current))->getType() == TokenType::COMMA) {
		getNextExpectedToken(TokenType::COMMA);
		nextToken = getValidSynonymToken();
		if (Declarations.find(nextToken->getValue()) != Declarations.end()) {
			throw "Duplicated declarations detected";
		}
		Declarations[nextToken->getValue()] = entityType->second;
	}

	parseEndOfDeclaration();
}

void PQLParser::parseSelect() {
	getNextExpectedToken(TokenType::SELECT);
	parseResultSynonym();
}

void PQLParser::parseResultSynonym() {
	auto nextToken = getValidSynonymToken();;
	if (Declarations.find(nextToken->getValue()) == Declarations.end()) {
		throw "Result synonym is not declared";
	}
	resultSynonyms.push_back(QueryArgument(std::string(nextToken->getValue()), Declarations[nextToken->getValue()]));
}

QueryArgument PQLParser::parseArgs(PQLToken* token) {
	switch (token->getType()) {
	case TokenType::STRING:
	case TokenType::UNDERSCORE:
	case TokenType::INTEGER:
		return QueryArgument(std::string(token->getValue()), entityTypeMapping[token->getType()]);
		break;
	default:
		if (Declarations.find(token->getValue()) != Declarations.end()) {
			return QueryArgument(std::string(token->getValue()), Declarations[token->getValue()]);
			break;
		}
		throw "Invalid argument";
	}
}

void PQLParser::parseRelationshipClause() {
	auto nextToken = getNextToken();
	auto relationType = relationTypeMapping.find(nextToken->getType());
	if (relationType == relationTypeMapping.end()) {
		throw "invalid relation type.";
	}
	auto validArgTypes = relationValidArgsTypeMap.at(relationType->second);
	getNextExpectedToken(TokenType::OPEN_PARAN);
	std::vector<QueryArgument> relArgs;
	std::unordered_set<std::string> usedSynonyms;
	for (int i = 0; i < validArgTypes.size(); i++) {
		auto validArgs = validArgTypes[i];
		auto nextToken = getNextToken();
		auto arg = parseArgs(nextToken);

		if (validArgs.find(arg.getType()) == validArgs.end()) {
			throw "Invalid arguments for relationship clause.";
		}

		if (isIdent(nextToken->getValue())) {
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

void PQLParser::parseSuchThatClause() {
	getNextExpectedToken(TokenType::SUCH);
	getNextExpectedToken(TokenType::THAT);

	parseRelationshipClause();
}

QueryArgument PQLParser::parsePatternLHS() {
	auto nextToken = getNextToken();
	auto arg = parseArgs(nextToken);
	if (VarArgTypes.find(arg.getType()) == VarArgTypes.end()) {
		throw "Invalid arguments for pattern clause.";
	}
	return arg;
}

QueryArgument PQLParser::parsePatternRHS() {
	auto nextToken = getNextToken();
	switch (nextToken->getType()) {
	case TokenType::UNDERSCORE: {
		auto followingToken = getNextToken();
		switch (followingToken->getType()) {
		case TokenType::STRING:
			getNextExpectedToken(TokenType::UNDERSCORE);
			getNextExpectedToken(TokenType::CLOSE_PARAN);
			return QueryArgument(std::string("_" + followingToken->getValue() + "_"), entityTypeMapping[TokenType::STRING]);
		case TokenType::CLOSE_PARAN:
			return QueryArgument(std::string("_"), entityTypeMapping[TokenType::UNDERSCORE]);
		}
	}
	case TokenType::STRING:
		getNextExpectedToken(TokenType::CLOSE_PARAN);
		return QueryArgument(std::string(nextToken->getValue()), entityTypeMapping[TokenType::STRING]);
	default:
		throw "Invalid Argument.";
	};
}

void PQLParser::parsePatternClause() {
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> usedSynonyms;

	getNextExpectedToken(TokenType::PATTERN);
	auto synonymToken = getValidSynonymToken();
	if (Declarations.find(synonymToken->getValue()) == Declarations.end()) {
		throw "invalid syn-assign";
	}
	usedSynonyms.insert(synonymToken->getValue());
	getNextExpectedToken(TokenType::OPEN_PARAN);
	QueryArgument LHS = parsePatternLHS();
	if (LHS.getType() != EntityType::STRING && LHS.getType() != EntityType::WILD) {
		usedSynonyms.insert(LHS.getValue());
	}
	patternArgs.push_back(LHS);
	getNextExpectedToken(TokenType::COMMA);
	patternArgs.push_back(parsePatternRHS());

	QueryClauses.push_back(QueryClause(RelationRef::PATTERN, patternArgs, usedSynonyms, synonymToken->getValue()));
}

void PQLParser::parseAfterSelect() {
	while (current != end) {
		switch (tokens.at(current)->getType()) {
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
		while (current != end && entityTypeMapping.find(tokens.at(current)->getType()) != entityTypeMapping.end()) {
			parseDeclaration();
		}
		parseSelect();
		parseAfterSelect();
		return Query(resultSynonyms, QueryClauses);
	} catch (...) {
		return Query();
	}
}


