#include "simple_parser/Token.h"

#include <utility>

Token::Token(TokenType t, std::string v) : type(t), value(std::move(v)){}
NameToken::NameToken(std::string v) : Token(TokenType::NAME, std::move(v)){}
IntegerToken::IntegerToken(std::string v) : Token(TokenType::INTEGER, std::move(v)){}
OperatorToken::OperatorToken(std::string v) : Token(TokenType::OPERATOR, std::move(v)){}
PunctuatorToken::PunctuatorToken(std::string v) : Token(TokenType::PUNCTUATOR, std::move(v)){}
EndOfFileToken::EndOfFileToken() : Token(TokenType::END_OF_FILE, ""){}