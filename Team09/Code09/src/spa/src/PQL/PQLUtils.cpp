#include <string>
#include <unordered_set>
#include <sstream>
#include <vector>

static std::unordered_set<std::string> exprSym = { "+" , "-", "*", "/", "%", "(" , ")"};

static bool isAlphaNum(std::string str) {
	for (const char c : str) {
		if (!isalnum(c)) {
			return false;
		}
	}
	return true;
}

static bool startsWithAlpha(std::string str) {
	if (str.empty()) {
		return false;
	}
	return isalpha(str[0]);
}

static bool isMathSym(std::string c) {
	return exprSym.find(c) != exprSym.end();
}

static bool isInt(std::string str) {
	for (const char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

static std::vector<std::string> splitExpr(const std::string& s, char delim) {
	std::vector<std::string> output;
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		output.push_back(item);
	}
	return output;
}

static bool isIdent(std::string str) {
	return startsWithAlpha(str) && isAlphaNum(str);
}

static bool isValidExpr(std::string expr) {
	std::vector<std::string> exprTokens = splitExpr(expr, ' ');
	for (std::string str : exprTokens) {
		if (!isMathSym(str) && !isIdent(str) && !isInt(str)) {
			return false;
		}
	}
	return true;
}


static bool isInStringLiteral(std::string str) {
	return str.size() >= 2 && str[0] == '"' && str[str.size() - 1] == '"';
}

