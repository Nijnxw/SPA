#pragma once 

#include <string>
#include <vector>
#include <PQL/PQLToken.h>

class Tokeniser {
public:
	Tokeniser(std::string);
	std::vector<PQLToken*> tokenise();

private:
	std::istream* rawQuery;
	std::string rawToken = "";
	std::vector<PQLToken*> PQLTokens;
	
	void processRawToken(std::string rawToken);
	void pushToken();
};

