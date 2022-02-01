#pragma once
#include <unordered_map>

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
std::unordered_map<std::string, TokenType> stringTokenMap = {
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

	//such that clauses token mapping
	{"such", TokenType::SUCH},
	{"that", TokenType::THAT},

	//Relationship clause token mapping 
	{"Modifies", TokenType::MODIFIES},
	{"Uses", TokenType::USES},
	{"Parent", TokenType::PARENT},
	{"Parent*", TokenType::PARENT_T},
	{"Follow", TokenType::FOLLOWS},
	{"Follow*", TokenType::PARENT_T},

	//Pattern clause token mapping 
	{"pattern", TokenType::PATTERN},
};