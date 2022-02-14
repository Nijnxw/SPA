#pragma once

#include <string>
#include <utility>

enum class ParserTokenType { NAME, INTEGER, OPERATOR, PUNCTUATOR, END_OF_FILE };

// Base class for SIMPLE language lexical tokens
class Token {
private:
	ParserTokenType type;
	std::string value;

public:
	Token(ParserTokenType t, std::string v);

	bool isNameToken();
	bool isIntegerToken();
	bool isOperatorToken();
	bool isPunctuatorToken();
	bool isEndOfFileToken();

	ParserTokenType getTokenType();
	std::string getValue();
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

// OPERATOR : '+' | '-' | '*' | '/' | '%' | '&&' | '||' |
//            '<' | '<=' | '>' | '>=' | '=' | '==' | '!' | '!='
class OperatorToken : public Token {
    public:
        explicit OperatorToken(std::string v);
};

// PUNCTUATOR : '(' | ')' | '{' | '}' | ';'
class PunctuatorToken : public Token {
public:
    explicit PunctuatorToken(std::string v);
};

// reached the end of the file
class EndOfFileToken : public Token {
    public:
        explicit EndOfFileToken();
};
