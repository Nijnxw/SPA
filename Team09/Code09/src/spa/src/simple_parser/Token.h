#pragma once

#include <string>

enum class TokenType { NAME, INTEGER, OPERATOR, PUNCTUATOR, END_OF_FILE };

// Base class for SIMPLE language lexical tokens
class Token {
    public:
        TokenType type;
        std::string value;
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