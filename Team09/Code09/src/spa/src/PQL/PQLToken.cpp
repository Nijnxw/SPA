#include <string>
#include "PQLToken.h"

PQLToken::PQLToken() : value(""), type(PQLTokenType::STRING) {}
PQLToken::PQLToken(std::string& value, PQLTokenType type) : value(value), type(type) {}

const std::string& PQLToken::getValue() const { return value; }

PQLTokenType PQLToken::getType() { return type; }