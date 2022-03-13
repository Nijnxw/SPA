#pragma once

#include "Commons/CommonToken.h"

#include <string>
#include <utility>

// Base class for SIMPLE language lexical tokens
class Token : public CommonToken {
public:
	Token(TokenType t, std::string v);
};

// NAME : LETTER (LETTER | DIGIT)*
class NameToken : public Token {
public:
	explicit NameToken(std::string v);
};

// INTEGER : DIGIT+
class IntegerToken : public Token {
public:
	explicit IntegerToken(std::string v);
};

// TERMINAL : '+' | '-' | '*' | '/' | '%' | '&&' | '||' |
//            '<' | '<=' | '>' | '>=' | '=' | '==' | '!' | '!=' |
// 						'(' | ')' | '{' | '}' | ';'
class TerminalToken : public Token {
public:
	explicit TerminalToken(std::string v);
};

// reached the end of the file
class EndOfFileToken : public Token {
public:
	explicit EndOfFileToken();
};
