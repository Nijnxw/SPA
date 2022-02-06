#include <string>
#include "PQLToken.h"

PQLToken::PQLToken() : type(TokenType::STRING), value("") {}
PQLToken::PQLToken(TokenType tokenType, std::string value) : type(tokenType), value(value) {}


const std::string PQLToken::getValue() const { return value; }

const TokenType PQLToken::getType() const { return type; }