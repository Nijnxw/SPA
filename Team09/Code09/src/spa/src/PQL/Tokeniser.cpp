#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include "PQL/Tokeniser.h"
#include "PQL/PQLUtils.cpp"

Tokeniser::Tokeniser(std::string rawQueryString) : rawQuery(new std::stringstream(rawQueryString)) {}

void Tokeniser::processRawToken(std::string rawToken) {
	if (stringTokenMap.find(rawToken) != stringTokenMap.end()) {
		PQLTokens.push_back(new PQLToken(stringTokenMap[rawToken], rawToken));
	}
	else if (isValidString(rawToken)) {
		const std::string ident = rawToken.substr(1, rawToken.size() - 2);
		PQLTokens.push_back(new PQLToken(TokenType::STRING, ident));
	}
	else if (isIdent(rawToken)) {
		PQLTokens.push_back(new PQLToken(TokenType::SYNONYM, rawToken));
	}
	else if (isInt(rawToken)) {
		PQLTokens.push_back(new PQLToken(TokenType::INTEGER, rawToken));
	}
	else {
		throw "Unknown syntax : " + rawToken + "\n";
	}
}

void Tokeniser::pushToken() {
	if (rawToken.size() > 0) {
		processRawToken(rawToken);
	}
	rawToken = "";
}


std::vector<PQLToken*> Tokeniser::tokenise() {
	try {
		char nextChar = rawQuery->get();
		while (!rawQuery->eof()) {
			switch (nextChar) {
			//Start of string
			case '"':
				isWithinStringLiterals = !isWithinStringLiterals;
				rawToken += nextChar;
				break;

			//White spaces
			case ' ':
			case '\t':
			case '\n':
				// ignore whitespaceif its within string literals
				if (!isWithinStringLiterals) {
					pushToken();
				}
				break;

			case '_':
			case ',':
			case '(':
			case ')':
			case ';':
				pushToken();
				rawToken += nextChar;
				pushToken();
				break;

			default:
				rawToken += nextChar;
				break;
			}
			nextChar = rawQuery->get();
		}
		pushToken();
	}
	catch (...) {
		PQLTokens.clear();
	}
	return PQLTokens;
}