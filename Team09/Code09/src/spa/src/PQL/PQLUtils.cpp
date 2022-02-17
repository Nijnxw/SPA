#include <string>

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

static bool isValidString(std::string str) {
	const std::string content = str.substr(1, str.size() - 2);
	bool isInStringLiterals = str.size() >= 2 && str[0] == '"' && str[str.size() - 1] == '"';
	bool isEitherIdentOrIntButNotBoth = (isIdent(content) && !isInt(content)) || (!isIdent(content) && isInt(content));
	return isInStringLiterals && isEitherIdentOrIntButNotBoth;
}