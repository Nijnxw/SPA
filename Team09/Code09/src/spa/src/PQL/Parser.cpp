#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

#include "PQL/Parser.h"

Parser::Parser(std::vector<PQLToken>& PQLTokens) : current(0), end(PQLTokens.size()), tokens(PQLTokens) {}

PQLToken Parser::getNextToken() {
	if (current == end) {
		throw "Runtime error : no more tokens to parse";
	}
	const auto token = tokens.at(current);
	current++;
	return token;
}

PQLToken Parser::getNextExpectedToken(TokenType tokenType) {
	const PQLToken token = getNextToken();
	if (token.getType() != tokenType) {
		throw "unexpected token type.";
	}
	return token;
}

void Parser::parseEndOfDeclaration() {
	getNextExpectedToken(TokenType::SEMICOLON);
}

void Parser::parseDeclaration() {
	auto nextToken = getNextToken();
	const auto entityType = entityTypeMapping.find(nextToken.getType());
	if (entityType == entityTypeMapping.end()) {
		throw "invalid entity type.";
	}
	const auto expectedSynonym = getNextExpectedToken(TokenType::SYNONYM);
	if (Declarations.find(expectedSynonym.getValue()) != Declarations.end()) {
		throw "Duplicated declarations detected";
	}
	Declarations[expectedSynonym.getValue()] = entityType->second;

	while (current != end && tokens.at(current).getType() == TokenType::COMMA) {
		getNextExpectedToken(TokenType::COMMA);
		nextToken = getNextExpectedToken(TokenType::SYNONYM);
		if (Declarations.find(nextToken.getValue()) != Declarations.end()) {
			throw "Duplicated declarations detected";
		}
		Declarations[nextToken.getValue()] = entityType->second;
	}

	parseEndOfDeclaration();
}

void Parser::parseSelect() {
	getNextExpectedToken(TokenType::SELECT);
	parseResultSynonym();
}

void Parser::parseResultSynonym() {
	const auto nextToken = getNextExpectedToken(TokenType::SYNONYM);
	if (Declarations.find(nextToken.getValue()) == Declarations.end()) {
		throw "Result synonym is not declared";
	}
	resultSynonyms.push_back(QueryArgument(std::string(nextToken.getValue()), Declarations[nextToken.getValue()]));
}

QueryArgument Parser::parseArgs(PQLToken token) {
	switch (token.getType()) {
	case TokenType::STRING:
	case TokenType::UNDERSCORE:
	case TokenType::INTEGER:
		return QueryArgument(std::string(token.getValue()), entityTypeMapping[token.getType()]);
		break;
	case TokenType::SYNONYM:
		if (Declarations.find(token.getValue()) != Declarations.end()) {
			return QueryArgument(std::string(token.getValue()), Declarations[token.getValue()]);
			break;
		}
	default:
		throw "Invalid argument";
	}
}

void Parser::parseRelationshipClause() {
	const auto nextToken = getNextToken();
	const auto relationType = relationTypeMapping.find(nextToken.getType());
	if (relationType == relationTypeMapping.end()) {
		throw "invalid relation type.";
	}
	const auto validArgTypes = relationValidArgsTypeMap.at(relationType->second);
	getNextExpectedToken(TokenType::OPEN_PARAN);
	std::vector<QueryArgument> relArgs;
	std::unordered_set<std::string> usedSynonyms;
	for (int i = 0; i < validArgTypes.size(); i++) {
		const auto validArgs = validArgTypes[i];
		const auto nextToken = getNextToken();
		if (validArgs.find(entityTypeMapping[nextToken.getType()]) == validArgs.end()) {
			throw "Invalid arguments for relationship clause.";
		}
		auto validArg = parseArgs(nextToken);

		if (nextToken.getType() == TokenType::SYNONYM) {
			usedSynonyms.insert(nextToken.getValue());
		}

		relArgs.push_back(validArg);
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

void Parser::parseSuchThatClause() {
	getNextExpectedToken(TokenType::SUCH);
	getNextExpectedToken(TokenType::THAT);

	parseRelationshipClause();
}

QueryArgument Parser::parsePatternLHS() {
	return parseArgs(getNextToken());
}

QueryArgument Parser::parsePatternRHS() {
	const auto nextToken = getNextToken();
	switch (nextToken.getType()) {
	case TokenType::UNDERSCORE: {
		const auto followingToken = getNextToken();
		switch (followingToken.getType()) {
		case TokenType::STRING:
			getNextExpectedToken(TokenType::UNDERSCORE);
			getNextExpectedToken(TokenType::CLOSE_PARAN);
			return QueryArgument(std::string("_" + followingToken.getValue() + "_"), entityTypeMapping[TokenType::STRING]);
		case TokenType::CLOSE_PARAN:
			return QueryArgument(std::string(""), entityTypeMapping[TokenType::UNDERSCORE]);
		}
	}
	case TokenType::STRING:
		getNextExpectedToken(TokenType::CLOSE_PARAN);
		return QueryArgument(std::string(nextToken.getValue()), entityTypeMapping[TokenType::STRING]);
	default:
		throw "Invalid Argument.";
	};
}

void Parser::parsePatternClause() {
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> usedSynonyms;

	getNextExpectedToken(TokenType::PATTERN);
	const auto synonymToken = getNextExpectedToken(TokenType::SYNONYM);
	usedSynonyms.insert(synonymToken.getValue());
	getNextExpectedToken(TokenType::OPEN_PARAN);
	QueryArgument LHS = parsePatternLHS();
	if (LHS.getType() != EntityType::INT && LHS.getType() != EntityType::WILD) {
		usedSynonyms.insert(LHS.getValue());
	}
	patternArgs.push_back(LHS);
	getNextExpectedToken(TokenType::COMMA);
	patternArgs.push_back(parsePatternRHS());

	QueryClauses.push_back(QueryClause(RelationRef::PATTERN, patternArgs, usedSynonyms, synonymToken.getValue()));
}

void Parser::parseAfterSelect() {
	while (current != end) {
		switch (tokens.at(current).getType()) {
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

Query Parser::parse() {
	try {
		while (current != end && entityTypeMapping.find(tokens.at(current).getType()) != entityTypeMapping.end()) {
			parseDeclaration();
		}
		parseSelect();
		parseAfterSelect();
		return Query(resultSynonyms, QueryClauses);
	} catch (...) {
		return Query();
	}
}
