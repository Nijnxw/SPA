#pragma once 

#include <string>
#include <vector>
#include "PQL/PQLToken.h"
#include "Commons/CommonLexer.h"

class Tokeniser:CommonLexer {
public:
	Tokeniser(std::string);
	std::vector<PQLToken*> tokenise();

private:
	bool isWithinStringLiterals = false;
	std::vector<PQLToken*> PQLTokens;
	void processRawToken(std::string rawToken);
	void pushToken();
	void pushSymbolToken(char nextChar);
};

