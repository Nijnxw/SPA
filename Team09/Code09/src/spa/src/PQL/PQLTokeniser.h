#pragma once 
#include <string>
#include <vector>
#include <PQL/PQL.h>

class PQLTokeniser
{
public:
	PQLTokeniser(std::string);
	
	std::vector<PQLToken> tokenise();

private:
	std::string rawQuery;

};

