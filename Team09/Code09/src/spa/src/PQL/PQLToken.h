#pragma once

#include <string>
#include "PQLTokenType.h"

class PQLToken {
public:
	PQLToken();
	PQLToken(std::string& value, PQLTokenType type);

	const std::string& getValue() const;
	PQLTokenType getType();

private:
	std::string value;
	PQLTokenType type;
};