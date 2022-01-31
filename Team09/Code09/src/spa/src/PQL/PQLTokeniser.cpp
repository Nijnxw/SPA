#include <PQL/PQLTokeniser.h>
#include <PQL/PQL.h>
#include <string>

//Checkers to check if each token follows the grammer rules of the PQL

bool isAlphaNum(std::string str) {
	for (const char c : str) {
		if (!isalnum(c)) {
			return false;
		}
	}
	return true;
}

bool startsWithAlpha(std::string str) {
	if (str.empty()) {
		return false;
	}
	return isalpha(str[0]);
}

bool isInt(std::string str) {
	for (const char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool isString(std::string str) {
	return str.size() >= 2 && str.at(0) == '"' && str[str.size() - 1];
}

bool isIdent(std::string str) {
	return startsWithAlpha(str) && isAlphaNum(str);
}

PQLTokeniser::PQLTokeniser(std::string rawQueryString) { this->rawQuery = rawQueryString; }

//std::vector<PQLToken> PQLTokeniser::tokenise() {
//	// TODO - Delimits raw query 
//
//	// TODO - Split raw query from the delimiter
//
//	// TODO - Tokenise 
//	return NULL;
//}