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

	bool operator==(const PQLToken& other) const {
		return type == other.getType() && value == other.getValue();
	}

private:
	std::string value;
	TokenType type;
};