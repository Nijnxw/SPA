#pragma once
#include <unordered_map>
#include "models/EntityType.h"
#include "models/QueryRelationType.h"

enum class TokenType {
	//Lexical tokens
	SYNONYM,
	INTEGER,
	STRING,

	//Puncuation tokens
	SEMICOLON,
	OPEN_PARAN,
	CLOSE_PARAN,
	COMMA,
	UNDERSCORE, //if underscore is in quotes (within string literals)

	//Design-entity tokens
	STMT,
	READ,
	PRINT,
	WHILE,
	IF,
	ASSIGN,
	VARIABLE,
	CONST,
	PROC,

	//Such that clause tokens
	SELECT,
	SUCH,
	THAT,

	//Relationship clause tokens
	MODIFIES,
	USES,
	PARENT,
	PARENT_T,
	FOLLOWS,
	FOLLOWS_T,

	//PATTERN clause tokens
	PATTERN
};

//unordered map to map raw string tokens to the appropriate token type
static std::unordered_map<std::string, TokenType> stringTokenMap = {
	//puncuation token mapping
	{";", TokenType::SEMICOLON},
	{"(", TokenType::OPEN_PARAN},
	{")", TokenType::CLOSE_PARAN},
	{",", TokenType::COMMA},
	{"_", TokenType::UNDERSCORE},

	//Design-entity token mapping
	{"stmt", TokenType::STMT},
	{"read", TokenType::READ},
	{"print", TokenType::PRINT},
	{"while", TokenType::WHILE},
	{"if", TokenType::IF},
	{"assign", TokenType::ASSIGN},
	{"variable", TokenType::VARIABLE},
	{"constant", TokenType::CONST},
	{"procedure", TokenType::PROC},

	{"Select", TokenType::SELECT},
	
	//such that clauses token mapping
	{"such", TokenType::SUCH},
	{"that", TokenType::THAT},

	//Relationship clause token mapping 
	{"Modifies", TokenType::MODIFIES},
	{"Uses", TokenType::USES},
	{"Parent", TokenType::PARENT},
	{"Parent*", TokenType::PARENT_T},
	{"Follows", TokenType::FOLLOWS},
	{"Follows*", TokenType::FOLLOWS_T},

	//Pattern clause token mapping 
	{"pattern", TokenType::PATTERN},
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

static std::unordered_map<TokenType, QueryRelationType> relationTypeMapping = {
	{TokenType::PARENT, QueryRelationType::PARENT},
	{TokenType::PARENT_T, QueryRelationType::PARENT_T},
	{TokenType::FOLLOWS, QueryRelationType::FOLLOWS},
	{TokenType::FOLLOWS_T, QueryRelationType::FOLLOWS_T},
	{TokenType::MODIFIES, QueryRelationType::MODIFIES},
	{TokenType::USES, QueryRelationType::USES},
};