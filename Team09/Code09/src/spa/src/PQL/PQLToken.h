#pragma once

#include <string>
#include "Commons/CommonToken.h"

/**
 * @brief represent a PQL token
 */

class PQLToken: public CommonToken {
public:
	PQLToken(TokenType type, std::string value);
};