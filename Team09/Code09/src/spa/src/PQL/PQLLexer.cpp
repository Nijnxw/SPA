#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include "PQL/PQLLexer.h"
#include "PQL/PQLUtils.cpp"
#include "util/RPN.h"

PQLLexer::PQLLexer(std::string rawQueryString) : CommonLexer(new std::stringstream(rawQueryString)) {}

void PQLLexer::processRawToken(std::string nextStr) {
	if (QPStringTokenMap.find(nextStr) != QPStringTokenMap.end()) {
		PQLTokens.push_back(new PQLToken(QPStringTokenMap[nextStr], nextStr));
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

void PQLLexer::pushToken() {
	if (nextStr.size() > 0) {
		processRawToken(nextStr);
	}
	nextStr = "";
}

void PQLLexer::pushSymbolToken(char nextChar) {
	pushToken();
	nextStr += nextChar;
	pushToken();
}

void PQLLexer::readString() {
	char nextStrChar = next();
	while (notEOF()) {
		nextStr += nextStrChar;
		if (nextStrChar == '"') { break; }
		nextStrChar = next();
	}
}

bool PQLLexer::isAllowedSymbolOutsideStringLiterals(char nextChar) {
	std::unordered_set<char> allowedSymbols = { ';','_',',','.','=','<','>','(',')' };
	return allowedSymbols.find(nextChar) != allowedSymbols.end();
}

bool PQLLexer::nextTokenIsAllowedSymbolAfterName(char nextChar) {
	std::unordered_set<char> allowedSymbols = { '#','*' };
	return allowedSymbols.find(nextChar) != allowedSymbols.end();
}


std::vector<PQLToken*> PQLLexer::tokenise() {
	try {
		char nextChar = next();
		while (notEOF()) {
			if (nextChar == '"') {
				nextStr += nextChar;
				readString();
			} else if (isspace(nextChar)) {
				pushToken();
			} else if (isalpha(nextChar)) {
				nextStr += nextChar;
				readName();
				if (nextTokenIsAllowedSymbolAfterName(peek())) { nextStr += next(); }
				pushToken();
			} else if (isdigit(nextChar)) {
				nextStr += nextChar;
				readInteger();
				pushToken();
			} else if (isAllowedSymbolOutsideStringLiterals(nextChar)) {
				pushSymbolToken(nextChar);
			} else {
				throw "invalid character detected ";
			}
			nextChar = next();
		}
		pushToken();
	}
	catch (...) {
		PQLTokens.clear();
	}
	return PQLTokens;
}