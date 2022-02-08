#pragma once 
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "PQLToken.h"
#include "models/Query.h"

static std::unordered_set<EntityType> stmtRef = {
	EntityType::STMT, EntityType::READ, EntityType::PRINT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
	EntityType::VAR, EntityType::CONST, EntityType::PROC,
	EntityType::WILD, EntityType::INT
};

static std::unordered_set<EntityType> EntRef = {
	EntityType::STMT, EntityType::READ, EntityType::PRINT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
	EntityType::VAR, EntityType::CONST, EntityType::PROC,
	EntityType::WILD, EntityType::STRING
};

static std::unordered_map < RelationRef, std::vector<std::unordered_set<EntityType>>> relationValidArgsTypeMap = {
	{RelationRef::USES, {stmtRef, EntRef}},
	{RelationRef::MODIFIES, {stmtRef, EntRef}},
	{RelationRef::FOLLOWS, {stmtRef, stmtRef}},
	{RelationRef::FOLLOWS_T, {stmtRef, stmtRef}},
	{RelationRef::PARENT, {stmtRef, stmtRef}},
	{RelationRef::PARENT_T, {stmtRef, stmtRef}}
};

class Parser {
public:
	Parser(std::vector<PQLToken>& PQLTokens);
	Query parse();

private:
	int current;
	int end;
	std::vector<PQLToken> tokens;
	std::unordered_map<std::string, EntityType> Declarations;
	std::vector<QueryArgument> resultSynonyms;
	std::vector<QueryClause> QueryClauses;

	PQLToken getNextToken();
	PQLToken getNextExpectedToken(TokenType tokenType);

	void parseEndOfDeclaration();
	void parseDeclaration();
	void parseSelect();
	void parseResultSynonym();
	QueryArgument parseArgs(PQLToken token);
	void parseRelationshipClause();
	void parseSuchThatClause();
	QueryArgument parsePatternLHS();
	QueryArgument parsePatternRHS();
	void parsePatternClause();
	void parseAfterSelect();
};