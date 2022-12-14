#pragma once 
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "PQLToken.h"
#include "models/Query.h"

static std::unordered_set<TokenType> keywords = {
	//declaration entity
	TokenType::STMT, TokenType::READ, TokenType::PRINT,
	TokenType::WHILE, TokenType::IF, TokenType::ASSIGN,
	TokenType::VARIABLE, TokenType::CONST, TokenType::PROC,
	TokenType::CALL,
	//clauses keyword
	TokenType::SUCH, TokenType::THAT, TokenType::USES, 
	TokenType::MODIFIES, TokenType::FOLLOWS, TokenType::PARENT,
	TokenType::PATTERN, TokenType::SELECT, TokenType::BOOLEAN,
	TokenType::CALLS, TokenType::NEXT, TokenType::AFFECTS, TokenType::WITH,
	TokenType::AND,
};

static std::unordered_map<TokenType, RelationRef> relationTypeMapping = {
	{TokenType::PARENT, RelationRef::PARENT},
	{TokenType::PARENT_T, RelationRef::PARENT_T},
	{TokenType::FOLLOWS, RelationRef::FOLLOWS},
	{TokenType::FOLLOWS_T, RelationRef::FOLLOWS_T},
	{TokenType::MODIFIES, RelationRef::MODIFIES},
	{TokenType::USES, RelationRef::USES},
	{TokenType::CALLS, RelationRef::CALLS},
	{TokenType::CALLS_T, RelationRef::CALLS_T},
	{TokenType::NEXT, RelationRef::NEXT},
	{TokenType::NEXT_T, RelationRef::NEXT_T},
	{TokenType::AFFECTS, RelationRef::AFFECTS},
	{TokenType::AFFECTS_T, RelationRef::AFFECTS_T},
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
	{TokenType::CALL, EntityType::CALL},
	{TokenType::BOOLEAN, EntityType::BOOL},
	{TokenType::UNDERSCORE, EntityType::WILD},
	{TokenType::INTEGER, EntityType::INT},
	{TokenType::STRING, EntityType::STRING},
};

static std::unordered_map<TokenType, AttributeRef> attrRefMapping = {
	{TokenType::STMT_NO, AttributeRef::STMT_NO},
	{TokenType::PROC_NAME, AttributeRef::PROC_NAME},
	{TokenType::VAR_NAME, AttributeRef::VAR_NAME},
	{TokenType::VALUE, AttributeRef::VALUE},
};

static std::unordered_set<AttributeRef> nameAttr = {
	AttributeRef::PROC_NAME, AttributeRef::VAR_NAME,
};

static std::unordered_set<AttributeRef> numberAttr = {
	AttributeRef::VALUE, AttributeRef::STMT_NO
};

static std::unordered_map <TokenType, std::unordered_set<EntityType>> attrRefEntityTypeMap = {
	{TokenType::PROC_NAME, {EntityType::CALL, EntityType::PROC}},
	{TokenType::VAR_NAME, {EntityType::READ, EntityType::PRINT, EntityType::VAR, }},
	{TokenType::VALUE, {EntityType::CONST}},
	{TokenType::STMT_NO, {EntityType::READ,EntityType::PRINT,EntityType::WHILE,EntityType::IF,EntityType::ASSIGN,EntityType::CALL,EntityType::STMT}},
};

static std::unordered_set<EntityType> stmtRef = {
	EntityType::STMT, EntityType::READ, EntityType::PRINT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
	EntityType::WILD, EntityType::INT, EntityType::CALL,
};

static std::unordered_set<EntityType> UsesFristArgTypes = {
	EntityType::STMT, EntityType::PRINT, EntityType::INT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
    EntityType::PROC, EntityType::STRING, EntityType::CALL
};

static std::unordered_set<EntityType> VarArgTypes = {
	EntityType::VAR, EntityType::WILD, EntityType::STRING, 
};

static std::unordered_set<EntityType> ModifiesFristArgTypes = {
	EntityType::STMT, EntityType::READ, EntityType::INT,
	EntityType::WHILE, EntityType::IF, EntityType::ASSIGN,
	EntityType::PROC, EntityType::STRING, EntityType::CALL
};

static std::unordered_set<EntityType> callsArgTypes = {
	EntityType::STRING, EntityType::PROC, EntityType::WILD
};

static std::unordered_set<EntityType> AffectsArgTypes = {
	EntityType::INT, EntityType::ASSIGN, EntityType::WILD, EntityType::STMT
};

static std::unordered_map < RelationRef, std::vector<std::unordered_set<EntityType>>> relationValidArgsTypeMap = {
	{RelationRef::USES, {UsesFristArgTypes, VarArgTypes}},
	{RelationRef::MODIFIES, {ModifiesFristArgTypes, VarArgTypes}},
	{RelationRef::FOLLOWS, {stmtRef, stmtRef}},
	{RelationRef::FOLLOWS_T, {stmtRef, stmtRef}},
	{RelationRef::PARENT, {stmtRef, stmtRef}},
	{RelationRef::PARENT_T, {stmtRef, stmtRef}},
	{RelationRef::CALLS, {callsArgTypes, callsArgTypes}},
	{RelationRef::CALLS_T, {callsArgTypes, callsArgTypes}},
	{RelationRef::NEXT, {stmtRef, stmtRef}},
	{RelationRef::NEXT_T, {stmtRef, stmtRef}},
	{RelationRef::AFFECTS, {AffectsArgTypes, AffectsArgTypes}},
	{RelationRef::AFFECTS_T, {AffectsArgTypes, AffectsArgTypes}},
};

class PQLParser {
public:
	PQLParser(std::vector<PQLToken*> PQLTokens);
	Query parse();

private:
	int current;
	int end;
	bool isBooleanQuery = false;
	bool isSemanticErrorDetected = false;
	std::vector<PQLToken*> tokens;
	std::unordered_map<std::string, EntityType> Declarations;
	std::vector<QueryArgument> resultSynonyms;
	std::vector<QueryClause> QueryClauses;

	//flag setters
	void setSemanticErrorFlag();

	//Token Checkers
	bool isValidSynonym(PQLToken* token);
	bool isAttributeRef(PQLToken* token);
	bool isDeclaredSynonym(std::string syn);
	bool nextIsComma();
	bool isWithArgNameType(QueryArgument arg);
	bool isWithArgNumberType(QueryArgument arg);
	bool isWithArgsSameType(QueryArgument arg1, QueryArgument arg2);
	bool isValidAttributeRefSynPair(EntityType synType, TokenType attributeRef);
	
	//getters + checkers
	PQLToken* peekNextToken();
	PQLToken* getNextToken();
	PQLToken* getNextExpectedToken(TokenType tokenType);
	PQLToken* getValidSynonymToken();

	void parseEndOfDeclaration();
	void parseDeclaration();

	void parseSelect();
	void parseResultClause();
	void parseResultSynonym();
	void parseResultTuple();
	void parseResultBoolean();

	QueryArgument parseArgs(PQLToken* token);

	void parseSingleRelationshipClause();
	void parseRelationshipClause();
	void parseSuchThatClause();


	QueryArgument parsePatternArgStmtList();
	QueryArgument parsePatternVarArgs();
	QueryArgument parseWhilePatternArg1();
	void parseWhilePattern(PQLToken* synonymToken);
	QueryArgument parseIfPatternArg1();
	void parseIfPattern(PQLToken* synonymToken);
	QueryArgument parseAssignPatternRHS();
	void parseAssignPattern(PQLToken* synonymToken);
	void parseSinglePatternClause();
	void parsePatternClause();

	QueryArgument parseWithArgs();
	void parseSignleWithClause();
	void parseWithClause();

	void parseAfterSelect();
};