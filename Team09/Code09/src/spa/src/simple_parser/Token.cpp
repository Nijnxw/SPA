#include "simple_parser/Token.h"

#include <utility>

Token::Token(RPNTokenType t, std::string v) : type(t), value(std::move(v)){}
NameToken::NameToken(std::string v) : Token(RPNTokenType::NAME, std::move(v)){}
IntegerToken::IntegerToken(std::string v) : Token(RPNTokenType::INTEGER, std::move(v)){}
OperatorToken::OperatorToken(std::string v) : Token(RPNTokenType::OPERATOR, std::move(v)){}
PunctuatorToken::PunctuatorToken(std::string v) : Token(RPNTokenType::PUNCTUATOR, std::move(v)){}
EndOfFileToken::EndOfFileToken() : Token(RPNTokenType::END_OF_FILE, ""){}