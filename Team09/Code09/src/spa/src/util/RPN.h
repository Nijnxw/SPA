#pragma once

#include "util/RPNToken.h"
#include <cctype>
#include <stack>
#include <sstream>
#include <string>
#include <vector>

class RPN {

private:
	RPN() {};

public:
	static std::string convertToRpn(const std::string& infix);
	static bool contains(const std::string& rpn1, const std::string& rpn2);
};
