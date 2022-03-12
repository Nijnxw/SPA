#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include "PQL/Tokeniser.h"
#include "PQL/PQLUtils.cpp"
#include "util/RPN.h"

Tokeniser::Tokeniser(std::string rawQueryString) : rawQuery(new std::stringstream(rawQueryString)) {}

void Tokeniser::processRawToken(std::string rawToken) {
	if (stringTokenMap.find(rawToken) != stringTokenMap.end()) {
		PQLTokens.push_back(new PQLToken(stringTokenMap[rawToken], rawToken));
	}
	else if (isInStringLiteral(rawToken)) {
		const std::string ident = trimWhitespaces(rawToken.substr(1, rawToken.size() - 2));
		PQLTokens.push_back(new PQLToken(TokenType::STRING, ident));
	} else if (isIdent(rawToken)) {
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

void Tokeniser::pushSymbolToken(char nextChar) {
	pushToken();
	rawToken += nextChar;
	pushToken();
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
				// ignore whitespace if its within string literals
				if (!isWithinStringLiterals) {
					pushToken();
				} else {
					rawToken += nextChar;
				}
				break;

			//operator symbols that only appear within string literals
			case '+':
			case '-':
			case '/':
			case '%':
				if (isWithinStringLiterals) {
					rawToken += nextChar;
				}
				break;

			//symbols that can appear in and outside string literals
			case '(':
			case ')':
				if (isWithinStringLiterals) {
					rawToken += nextChar;
				} else {
					pushSymbolToken(nextChar);
				}
				break;
			
			//symbols that does not appear in string literals at all 
			case '_':
			case ',':
			case ';':
			case '.':
			case '<':
			case '>':
			case '=':
				pushSymbolToken(nextChar);
				break;

			default:
				rawToken += nextChar;
				break;
			}
			nextChar = rawQuery->get();
		}
		if (isWithinStringLiterals) {
			throw "Unclosed string in query.";
		}
		pushToken();
	}
	catch (...) {
		PQLTokens.clear();
	}
	return PQLTokens;
}