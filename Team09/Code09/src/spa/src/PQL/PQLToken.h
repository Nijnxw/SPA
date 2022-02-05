#pragma once

#include <string>
#include "TokenType.h"

/**
 * @brief represent a PQL token
 */

class PQLToken {
public:
	PQLToken();
	PQLToken(TokenType type, std::string value = "");

	const std::string getValue() const;
	const TokenType getType() const ;

	bool PQLToken::operator==(const PQLToken& other) const {
		return type == other.type && value == other.value;
	}

private:
	std::string value;
	TokenType type;
};