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

bool isIdent(std::string str) {
	return startsWithAlpha(str) && isAlphaNum(str);
}

bool isValidString(std::string str) {
	const std::string content = str.substr(1, str.size() - 2);
	bool isInStringLiterals = str.size() >= 2 && str[0] == '"' && str[str.size() - 1] == '"';
	bool isEitherIdentOrIntButNotBoth = (isIdent(content) && !isInt(content)) || (!isIdent(content) && isInt(content));
	return isInStringLiterals && isEitherIdentOrIntButNotBoth;
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

std::vector<PQLToken> Tokeniser::tokenise() {
	Tokeniser::split();
	std::vector<PQLToken> PQLTokens;
	for (const auto token : rawTokens) {
		if (stringTokenMap.find(token) != stringTokenMap.end()) {
			PQLTokens.push_back(PQLToken( "", stringTokenMap[token] )); 
		} else if (isValidString(token)) {
			const std::string ident = token.substr(1, token.size() - 2);
			PQLTokens.push_back(PQLToken( ident, TokenType::STRING));
		} else if (isIdent(token)) {
			PQLTokens.push_back(PQLToken(token, TokenType::SYNONYM));
		} else if (isInt(token)) {
			PQLTokens.push_back(PQLToken(token, TokenType::INTEGER));
		} else {
			throw std::runtime_error("Unknown syntax : " + token + "\n");
		}
	}
	return PQLTokens;
}