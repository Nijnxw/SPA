#pragma once 

#include <string>
#include <vector>
#include <PQL/PQLToken.h>

class Tokeniser {
public:
	Tokeniser(std::string);
	
	std::vector<PQLToken> tokenise();

private:
	std::string rawQuery;
	std::string currentRawToken = "";
	std::vector<std::string> rawTokens;
	
	/**
	 * @brief Split string into raw tokens
	 * @return vector of strings 
	*/
	void split();

	void pushRawToken();

};

