#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "PQL/Tokeniser.h"


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

bool isValidString(std::string str) {
	return str.size() >= 2 && str[0] == '"' && str[str.size() - 1];
}

bool isIdent(std::string str) {
	return startsWithAlpha(str) && isAlphaNum(str);
}

Tokeniser::Tokeniser(std::string rawQueryString) { this->rawQuery = rawQueryString; }

void Tokeniser::pushRawToken() {
	if (currentRawToken.size() > 0) {
		rawTokens.push_back(currentRawToken);
		currentRawToken = "";
	}
}

void Tokeniser::split() {
	for (const char c : rawQuery) {
		switch (c) {

		//Case 1 - whitespace detected 
		case ' ':
		case '\n':
		case '\t':
			Tokeniser::pushRawToken();
			continue;

		//Case 2 - special characters 
		case '_':
		case ',':
		case '(':
		case ')':
		case ';':
			Tokeniser::pushRawToken();
			rawTokens.push_back(std::string(1,c));
			continue;

		default:
			break;
		}
		currentRawToken.push_back(c);
	}
	Tokeniser::pushRawToken();
}

std::vector<PQLToken*> Tokeniser::tokenise() {
	
}