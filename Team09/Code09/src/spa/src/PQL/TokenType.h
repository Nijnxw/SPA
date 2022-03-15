#pragma once

#include <unordered_map>
#include "models/EntityType.h"
#include "models/RelationRef.h"

enum class TokenType {
	//Lexical tokens
	SYNONYM,
	INTEGER,
	STRING,
	EXPR,

	//Puncuation tokens
	SEMICOLON,
	OPEN_PARAN,
	CLOSE_PARAN,
	OPEN_ANGLED,
	CLOSE_ANGLED,
	COMMA,
	UNDERSCORE, 
	PERIOD,

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
	CALL,

	//Select
	SELECT,
	BOOLEAN,

	//Relationship clause tokens
	SUCH,
	THAT,
	MODIFIES,
	USES,
	PARENT,
	PARENT_T,
	FOLLOWS,
	FOLLOWS_T,
	CALLS,
	CALLS_T,
	NEXT,
	NEXT_T,
	AFFECTS,
	AFFECTS_T,

	//PATTERN clause tokens
	PATTERN,

	//WITH clause
	WITH,
	EQUAL,

	//AND
	AND,

	//attr ref
	STMT_NO,
	PROC_NAME,
	VAR_NAME,
	VALUE,
};

//unordered map to map raw string tokens to the appropriate token type
static std::unordered_map<std::string, TokenType> stringTokenMap = {
	//puncuation token mapping
	{";",         TokenType::SEMICOLON},
	{"(",         TokenType::OPEN_PARAN},
	{")",         TokenType::CLOSE_PARAN},
	{"<",         TokenType::OPEN_ANGLED},
	{">",         TokenType::CLOSE_ANGLED},
	{",",         TokenType::COMMA},
	{"_",         TokenType::UNDERSCORE},
	{".",		  TokenType::PERIOD},

	//Design-entity token mapping
	{"stmt",      TokenType::STMT},
	{"read",      TokenType::READ},
	{"print",     TokenType::PRINT},
	{"while",     TokenType::WHILE},
	{"if",        TokenType::IF},
	{"assign",    TokenType::ASSIGN},
	{"variable",  TokenType::VARIABLE},
	{"constant",  TokenType::CONST},
	{"procedure", TokenType::PROC},
	{"call",	  TokenType::CALL},

	//Select
	{"Select",    TokenType::SELECT},
	{"BOOLEAN",	  TokenType::BOOLEAN},

	//Relationship clause token mapping 
	{"such",      TokenType::SUCH},
	{"that",      TokenType::THAT},
	{"Modifies",  TokenType::MODIFIES},
	{"Uses",      TokenType::USES},
	{"Parent",    TokenType::PARENT},
	{"Parent*",   TokenType::PARENT_T},
	{"Follows",   TokenType::FOLLOWS},
	{"Follows*",  TokenType::FOLLOWS_T},
	{"Calls",	  TokenType::CALLS},
	{"Calls*",	  TokenType::CALLS_T},
	{"Next",	  TokenType::NEXT},
	{"Next*",	  TokenType::NEXT_T},
	{"Affects",	  TokenType::AFFECTS},
	{"Affects*",  TokenType::AFFECTS_T},

	//Pattern clause token mapping 
	{"pattern",   TokenType::PATTERN},

	//with claue token mapping
	{"with",	  TokenType::WITH},
	{"=",		  TokenType::EQUAL},

	//And
	{"and",		  TokenType::AND},

	//attr ref
	{"stmt#",	  TokenType::STMT_NO},
	{"procName",  TokenType::PROC_NAME},
	{"varName",	  TokenType::VAR_NAME},
	{"value",	  TokenType::VALUE},



};
