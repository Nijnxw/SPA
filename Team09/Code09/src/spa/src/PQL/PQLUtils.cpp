#include <string>
#include <unordered_set>

static std::unordered_set<char> exprSym = { '+' , '-', '*', '/', '%', '(' , ')'};

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

static bool isBinaryOp(char c) {
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

static bool isIdent(std::string str) {
	return startsWithAlpha(str) && isAlphaNum(str);
}

static bool isInStringLiteral(std::string str) {
	return str.size() >= 2 && str[0] == '"' && str[str.size() - 1] == '"';
}

