#include "PQL/PQL.h"
#include "PQL/Tokeniser.h"
#include "PQL/PQLParser.h"

#include <iostream>

const std::vector<PQLToken*> PQL::tokenise(std::string query) {
	auto tokeniser = Tokeniser(query);
	return tokeniser.tokenise();
}

Query PQL::parse(std::vector<PQLToken*> tokens) {
	auto parser = PQLParser(tokens);
	return parser.parse();
}
