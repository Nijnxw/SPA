#include "simple_parser/Token.h"

#include <utility>

Token::Token(TokenType t, std::string v) : type(t), value(std::move(v)){}
NameToken::NameToken(std::string v) : Token(TokenType::NAME, std::move(v)){}
IntegerToken::IntegerToken(std::string v) : Token(TokenType::INTEGER, std::move(v)){}
SymbolToken::SymbolToken(std::string v) : Token(TokenType::SYMBOL, std::move(v)){}
EndOfFileToken::EndOfFileToken() : Token(TokenType::END_OF_FILE, ""){}