#pragma once

#include <string>

enum class TokenType { NAME, INTEGER, SYMBOL, END_OF_FILE };

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

// SYMBOL : '(' | ')' | '{' | '}' | '+' | '-' | '*' | '/' | '%' | ';' |
//          '&&' | '||' | '<' | '<=' | '>' | '>=' | '=' | '==' | '!' | '!='
class SymbolToken : public Token {
    public:
        explicit SymbolToken(std::string v);
};

// reached the end of the file
class EndOfFileToken : public Token {
    public:
        explicit EndOfFileToken();
};
