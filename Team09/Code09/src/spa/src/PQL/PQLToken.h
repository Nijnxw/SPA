#pragma once

#include <string>
#include "TokenType.h"

class PQLToken {
public:
	PQLToken();
	PQLToken(std::string value, TokenType type);

	const std::string& getValue() const;
	TokenType getType();

private:
	std::string value;
	TokenType type;
};