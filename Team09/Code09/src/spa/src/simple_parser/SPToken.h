#pragma once

#include "Commons/CommonToken.h"

#include <string>
#include <utility>

// Base class for SIMPLE language lexical tokens
class SPToken : public CommonToken {
public:
	SPToken(TokenType t, std::string v);
};

// NAME : LETTER (LETTER | DIGIT)*
class NameToken : public SPToken {
public:
	explicit NameToken(std::string v);
};

// INTEGER : DIGIT+
class IntegerToken : public SPToken {
public:
	explicit IntegerToken(std::string v);
};

// TERMINAL : '+' | '-' | '*' | '/' | '%' | '&&' | '||' |
//            '<' | '<=' | '>' | '>=' | '=' | '==' | '!' | '!=' |
// 						'(' | ')' | '{' | '}' | ';'
class TerminalToken : public SPToken {
public:
	explicit TerminalToken(std::string v);
};

// reached the end of the file
class EndOfFileToken : public SPToken {
public:
	explicit EndOfFileToken();
};
