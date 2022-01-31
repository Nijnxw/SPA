#pragma once

enum class PQLTokenType {
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
	CONSTANT,
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
	FOLLOWS_T
};