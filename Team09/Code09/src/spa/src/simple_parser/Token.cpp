#include "simple_parser/Token.h"

#include <utility>

Token::Token(ParserTokenType t, std::string v) : type(t), value(std::move(v)){}
NameToken::NameToken(std::string v) : Token(ParserTokenType::NAME, std::move(v)){}
IntegerToken::IntegerToken(std::string v) : Token(ParserTokenType::INTEGER, std::move(v)){}
OperatorToken::OperatorToken(std::string v) : Token(ParserTokenType::OPERATOR, std::move(v)){}
PunctuatorToken::PunctuatorToken(std::string v) : Token(ParserTokenType::PUNCTUATOR, std::move(v)){}
EndOfFileToken::EndOfFileToken() : Token(ParserTokenType::END_OF_FILE, ""){}

bool Token::isNameToken() {
	return type == ParserTokenType::NAME;
}

bool Token::isIntegerToken() {
	return type == ParserTokenType::INTEGER;
}

bool Token::isOperatorToken() {
	return type == ParserTokenType::OPERATOR;
}

bool Token::isPunctuatorToken() {
	return type == ParserTokenType::PUNCTUATOR;
}

bool Token::isEndOfFileToken() {
	return type == ParserTokenType::END_OF_FILE;
}

ParserTokenType Token::getTokenType() {
	return type;
}

std::string Token::getValue() {
	return value;
}