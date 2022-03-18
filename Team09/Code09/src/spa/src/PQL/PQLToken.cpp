#include <string>
#include "PQLToken.h"
#include "Commons/CommonToken.h"

PQLToken::PQLToken(TokenType tokenType, std::string value) : CommonToken(tokenType, value) {}
