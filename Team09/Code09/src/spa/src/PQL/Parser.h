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

std::unordered_map < QueryRelationType, std::vector<std::unordered_set<EntityType>>> relationValidArgsTypeMap = {
	{QueryRelationType::USES, {stmtRef, EntRef}},
	{QueryRelationType::MODIFIES, {stmtRef, EntRef}},
	{QueryRelationType::FOLLOWS, {stmtRef, stmtRef}},
	{QueryRelationType::FOLLOWS_T, {stmtRef, stmtRef}},
	{QueryRelationType::PARENT, {stmtRef, stmtRef}},
	{QueryRelationType::PARENT_T, {stmtRef, stmtRef}}
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
		std::vector<QuerySuchThatClause> suchThatClauses;
		std::vector<QueryPatternClause> PatternClauses;
		bool isPatternExactMatch = false;

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