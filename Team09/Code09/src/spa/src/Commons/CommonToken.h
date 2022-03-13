#pragma once

#include <string>
#include <unordered_map>

enum class TokenType {
	// Lexical tokens
	SYNONYM, NAME,
	INTEGER,
	STRING,
	EXPR,

	// Operator tokens
	PLUS,
	MINUS,
	TIMES,
	DIVIDE,
	MODULO,
	MORE_THAN_EQUALS,
	LESS_THAN_EQUALS,
	EQUAL,
	ASSIGNMENT_EQUAL,
	NOT_EQUAL,
	NOT,
	OR,

	// Punctuation tokens
	SEMICOLON,
	OPEN_PARAN,
	CLOSE_PARAN,
	OPEN_CURLY,
	CLOSE_CURLY,
	OPEN_ANGLED, LESS_THAN,
	CLOSE_ANGLED, MORE_THAN,
	COMMA,
	UNDERSCORE,
	PERIOD,

	// Design-entity tokens
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

	// Select
	SELECT,
	BOOLEAN,

	// Relationship clause tokens
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

	// PATTERN clause tokens
	PATTERN,

	// WITH clause
	WITH,

	// AND
	AND,

	// End Of File token
	END_OF_FILE,
};

static std::unordered_map<std::string, TokenType> SPStringTokenMap = {
	//Operator token mapping
	{"<",       TokenType::LESS_THAN},
	{">",       TokenType::MORE_THAN},
	{"<=",      TokenType::LESS_THAN_EQUALS},
	{">=",      TokenType::MORE_THAN_EQUALS},
	{"+",       TokenType::PLUS},
	{"-",       TokenType::MINUS},
	{"*",       TokenType::TIMES},
	{"/",       TokenType::DIVIDE},
	{"%",       TokenType::MODULO},
	{"=",       TokenType::ASSIGNMENT_EQUAL},
	{"==",      TokenType::EQUAL},
	{"!=",      TokenType::NOT_EQUAL},
	{"!",       TokenType::NOT},
	{"&&",      TokenType::AND},
	{"||",      TokenType::OR},

	//Punctuation token mapping
	{";",         TokenType::SEMICOLON},
	{"(",         TokenType::OPEN_PARAN},
	{")",         TokenType::CLOSE_PARAN},
	{"{",         TokenType::OPEN_CURLY},
	{"}",         TokenType::CLOSE_CURLY},
};

static std::unordered_map<std::string, TokenType> QPStringTokenMap = {
	//Punctuation token mapping
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
};

class CommonToken {
public:
	explicit CommonToken(TokenType type, std::string value = "");

	std::string getValue();
	TokenType getType();

	bool operator==(CommonToken& other) {
		return type == other.getType() && value == other.getValue();
	}

protected:
	std::string value;
	TokenType type;
};