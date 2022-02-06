#pragma once 
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "PQLToken.h"
#include "models/Query.h"

std::unordered_set<EntityType> stmtRef = {
	EntityType::STMT, EntityType::READ, EntityType::PRINT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
	EntityType::VAR, EntityType::CONST, EntityType::PROC,
	EntityType::WILD, EntityType::INT
};

std::unordered_set<EntityType> EntRef = {
	EntityType::STMT, EntityType::READ, EntityType::PRINT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
	EntityType::VAR, EntityType::CONST, EntityType::PROC,
	EntityType::WILD, EntityType::STRING
};

std::unordered_map < RelationRef, std::vector<std::unordered_set<EntityType>>> relationValidArgsTypeMap = {
	{RelationRef::USES, {stmtRef, EntRef}},
	{RelationRef::MODIFIES, {stmtRef, EntRef}},
	{RelationRef::FOLLOWS, {stmtRef, stmtRef}},
	{RelationRef::FOLLOWS_T, {stmtRef, stmtRef}},
	{RelationRef::PARENT, {stmtRef, stmtRef}},
	{RelationRef::PARENT_T, {stmtRef, stmtRef}}
};

class Parser {
	public:
		Query parse();
		Parser(std::vector<PQLToken> &PQLTokens);

	private:
		std::vector<PQLToken>::iterator current;
		std::vector<PQLToken>::iterator end;
		std::unordered_map<std::string, EntityType> Declarations;
		std::vector<QueryArgument> resultSynonyms;
		std::vector<QueryClause> QueryClauses;

		PQLToken getNextToken();
		PQLToken getNextExpectedToken(TokenType tokenType);

		void parseEndOfDeclaration();
		void parseDeclaration();
		void parseSelect();
		void parseResultSynonym(); 
		QueryArgument parseArgs(PQLToken token, std::unordered_set<std::string>& usedSynonyms);
		void parseRelationshipClause();
		void parseSuchThatClause();
		//QueryArgument parsePatternLHS(std::unordered_set<std::string>& usedSynonyms);
		//QueryArgument parsePatternRHS();
		//void parsePatternClause();
		void parseAfterSelect();
};