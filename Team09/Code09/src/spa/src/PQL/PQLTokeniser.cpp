#include <PQL/PQLTokeniser.h>
#include <PQL/PQL.h>
#include <string>

  
PQLTokeniser::PQLTokeniser(std::string rawQueryString) { this->rawQuery = rawQueryString; }

std::vector<PQLToken> PQLTokeniser::tokenise() {
}