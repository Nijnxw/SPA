#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "PQL/Parser.h"

Parser::Parser(std::vector<PQLToken> &PQLTokens) {
	current = PQLTokens.begin();
	end = PQLTokens.end();
}

PQLToken Parser::getNextToken() {
	if (current == end) {
		throw "Runtime error : no more tokens to parse";
	}
	const auto token = *current;
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
	const auto nextToken = getNextToken();
	const auto entityType = entityTypeMapping.find(nextToken.getType());
	if (entityType == entityTypeMapping.end()) {
		throw "invalid entity type.";
	}
	Declarations[nextToken.getValue()] = entityType->second;
	while (current != end && current->getType() == TokenType::COMMA) {
		getNextExpectedToken(TokenType::COMMA); 
		const auto nextToken = getNextExpectedToken(TokenType::SYNONYM);
		if (Declarations.find(nextToken.getValue()) != Declarations.end()) {
			throw "Duplicated declarations detected";
		}
		Declarations[nextToken.getValue()] = entityType->second;
	}
	parseEndOfDeclaration();
}

void Parser::parseSelect() {
	getNextExpectedToken(TokenType::SELECT);
}

void Parser::parseResultSynonym() {
	const auto nextToken = getNextExpectedToken(TokenType::SYNONYM);
	if (Declarations.find(nextToken.getValue()) == Declarations.end()) {
		throw "Result synonym is not declared";
	}
	resultSynonyms.push_back(QueryArgument(std::string(nextToken.getValue()), Declarations[nextToken.getValue()]));
}

QueryArgument Parser::parseRelationshipArgs(PQLToken token) {
	switch(token.getType()) {
	case TokenType::STRING : 
	case TokenType::UNDERSCORE:
	case TokenType::INTEGER:
		return QueryArgument(std::string(token.getValue()), entityTypeMapping[token.getType()]);
		break;
	case TokenType::SYNONYM:
		if (Declarations.find(token.getValue()) != Declarations.end()) {
			return QueryArgument(std::string(token.getValue()), entityTypeMapping[token.getType()]);
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

	for (int i = 0; i < validArgTypes.size(); i++) {
		const auto validArgs = validArgTypes[i];
		const auto nextToken = getNextToken();
		if (validArgs.find(entityTypeMapping[nextToken.getType()]) == validArgs.end()) {
			throw "Invalid arguments for relationship clause.";
		}
		auto validArg = parseRelationshipArgs(nextToken);
		relArgs.push_back(validArg);
		if (i != validArgTypes.size() - 1) {
			getNextExpectedToken(TokenType::COMMA);
		}
	}

	getNextExpectedToken(TokenType::CLOSE_PARAN);

	if (relArgs.size() != 2) {
		throw "Invalid number of arguments.";
	}
	suchThatClauses.push_back(QuerySuchThatClause(relationType->second, relArgs));
}

void Parser::parseSuchThatClause() {
	getNextExpectedToken(TokenType::SUCH);
	getNextExpectedToken(TokenType::THAT);
	
	parseRelationshipClause();
}

void Parser::parsePatternClause() {

}

void Parser::parseAfterSelect() {
	while (current != end) {
		switch (current->getType()) {
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

//Query Parser::parse() {
//	while (current != end && entityTypeMapping.find(current->getType()) != entityTypeMapping.end()) {
//		parseDeclaration();
//	}
//	parseSelect();
//	parseResultSynonym();
//	parseAfterSelect();
//	//return Query(resultSynonyms, )
//}

