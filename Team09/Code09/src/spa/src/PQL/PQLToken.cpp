#include <string>
#include "PQLToken.h"

PQLToken::PQLToken() : value(""), type(TokenType::STRING) {}
PQLToken::PQLToken(std::string& value, TokenType type) : value(value), type(type) {}

const std::string& PQLToken::getValue() const { return value; }

TokenType PQLToken::getType() { return type; }