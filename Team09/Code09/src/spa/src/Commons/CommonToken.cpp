#include <string>
#include "Commons/CommonToken.h"

CommonToken::CommonToken(TokenType tokenType, std::string value) : type(tokenType), value(value) {}
std::string CommonToken::getValue() { return value; }

 TokenType CommonToken::getType() { return type; }