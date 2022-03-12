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

Tokeniser::Tokeniser(std::string rawQueryString) : CommonLexer(new std::stringstream(rawQueryString)) {}

void Tokeniser::processRawToken(std::string nextStr) {
	if (stringTokenMap.find(nextStr) != stringTokenMap.end()) {
		PQLTokens.push_back(new PQLToken(stringTokenMap[nextStr], nextStr));
	}
	else if (isInStringLiteral(nextStr)) {
		const std::string ident = trimWhitespaces(nextStr.substr(1, nextStr.size() - 2));
		PQLTokens.push_back(new PQLToken(TokenType::STRING, ident));
	} else if (isIdent(nextStr)) {
		PQLTokens.push_back(new PQLToken(TokenType::SYNONYM, nextStr));
	}
	else if (isInt(nextStr)) {
		PQLTokens.push_back(new PQLToken(TokenType::INTEGER, nextStr));
	}
	else {
		throw "Unknown syntax : " + nextStr + "\n";
	}
}

void Tokeniser::pushToken() {
	if (nextStr.size() > 0) {
		processRawToken(nextStr);
	}
	nextStr = "";
}

void Tokeniser::pushSymbolToken(char nextChar) {
	pushToken();
	nextStr += nextChar;
	pushToken();
}


std::vector<PQLToken*> Tokeniser::tokenise() {
	try {
		char nextChar = next();
		while (notEOF()) {
			switch (nextChar) {
			//Start of string
			case '"':
				isWithinStringLiterals = !isWithinStringLiterals;
				nextStr += nextChar;
				break;

			//White spaces
			case ' ':
			case '\t':
			case '\n':
				// ignore whitespace if its within string literals
				if (!isWithinStringLiterals) {
					pushToken();
				} else {
					nextStr += nextChar;
				}
				break;

			//operator symbols that only appear within string literals
			case '+':
			case '-':
			case '/':
			case '%':
				if (isWithinStringLiterals) {
					nextStr += nextChar;
				}
				break;

			//symbols that can appear in and outside string literals
			case '(':
			case ')':
				if (isWithinStringLiterals) {
					nextStr += nextChar;
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
				nextStr += nextChar;
				break;
			}
			nextChar = next();
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