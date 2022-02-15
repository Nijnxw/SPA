#pragma once 
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "PQLToken.h"
#include "models/Query.h"

static std::unordered_set<TokenType> keywords = {
	TokenType::STMT, TokenType::READ, TokenType::PRINT,
	TokenType::WHILE, TokenType::IF, TokenType::ASSIGN,
	TokenType::VARIABLE, TokenType::CONST, TokenType::PROC,
	TokenType::SUCH, TokenType::THAT, TokenType::USES, 
	TokenType::MODIFIES, TokenType::FOLLOWS, TokenType::PARENT,
	TokenType::PATTERN, TokenType::SELECT
};

static std::unordered_map<TokenType, RelationRef> relationTypeMapping = {
	{TokenType::PARENT, RelationRef::PARENT},
	{TokenType::PARENT_T, RelationRef::PARENT_T},
	{TokenType::FOLLOWS, RelationRef::FOLLOWS},
	{TokenType::FOLLOWS_T, RelationRef::FOLLOWS_T},
	{TokenType::MODIFIES, RelationRef::MODIFIES},
	{TokenType::USES, RelationRef::USES},
};

static std::unordered_map<TokenType, EntityType> entityTypeMapping = {
	{TokenType::STMT, EntityType::STMT},
	{TokenType::READ, EntityType::READ},
	{TokenType::PRINT, EntityType::PRINT},
	{TokenType::WHILE, EntityType::WHILE},
	{TokenType::IF, EntityType::IF},
	{TokenType::ASSIGN, EntityType::ASSIGN},
	{TokenType::VARIABLE, EntityType::VAR},
	{TokenType::CONST, EntityType::CONST},
	{TokenType::PROC, EntityType::PROC},

	{TokenType::UNDERSCORE, EntityType::WILD},
	{TokenType::INTEGER, EntityType::INT},
	{TokenType::STRING, EntityType::STRING},
};

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

static std::unordered_set<EntityType> UsesFristArgTypes = {
	EntityType::STMT, EntityType::PRINT, EntityType::INT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
    EntityType::PROC,
};

static std::unordered_set<EntityType> VarSecondArgTypes = {
	EntityType::VAR, EntityType::WILD, EntityType::STRING, 
};

static std::unordered_set<EntityType> ModifiesFristArgTypes = {
	EntityType::STMT, EntityType::READ, EntityType::INT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
	 EntityType::PROC,
};


static std::unordered_map < RelationRef, std::vector<std::unordered_set<EntityType>>> relationValidArgsTypeMap = {
	{RelationRef::USES, {UsesFristArgTypes, VarSecondArgTypes}},
	{RelationRef::MODIFIES, {ModifiesFristArgTypes, VarSecondArgTypes}},
	{RelationRef::FOLLOWS, {stmtRef, stmtRef}},
	{RelationRef::FOLLOWS_T, {stmtRef, stmtRef}},
	{RelationRef::PARENT, {stmtRef, stmtRef}},
	{RelationRef::PARENT_T, {stmtRef, stmtRef}}
};

class PQLParser {
public:
	PQLParser(std::vector<PQLToken*> PQLTokens);
	Query parse();

private:
	int current;
	int end;
	std::vector<PQLToken*> tokens;
	std::unordered_map<std::string, EntityType> Declarations;
	std::vector<QueryArgument> resultSynonyms;
	std::vector<QueryClause> QueryClauses;

	PQLToken* getNextToken();
	PQLToken* getNextExpectedToken(TokenType tokenType);
	PQLToken* getValidSynonymToken();

	void parseEndOfDeclaration();
	void parseDeclaration();
	void parseSelect();
	void parseResultSynonym();
	QueryArgument parseArgs(PQLToken* token);
	void parseRelationshipClause();
	void parseSuchThatClause();
	QueryArgument parsePatternLHS();
	QueryArgument parsePatternRHS();
	void parsePatternClause();
	void parseAfterSelect();
};