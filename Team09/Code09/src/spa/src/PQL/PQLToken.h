#pragma once

#include <string>
#include "TokenType.h"

class PQLToken {
public:
	PQLToken();
	PQLToken(std::string value, TokenType type);

	const std::string& getValue() const;
	TokenType getType();

	bool PQLToken::operator==(const PQLToken& other) const {
		return type == other.type && value == other.value;
	}

private:
	std::string value;
	TokenType type;
};