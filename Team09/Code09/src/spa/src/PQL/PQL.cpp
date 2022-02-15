#include "PQL/PQL.h"
#include "PQL/Tokeniser.h"
#include "PQL/Parser.h"

#include <iostream>

const std::vector<PQLToken> PQL::tokenise(std::string query) {
	auto tokeniser = Tokeniser(query);
	return tokeniser.tokenise();
}

Query PQL::parse(std::vector<PQLToken> tokens) {
	auto parser = Parser(tokens);
	return parser.parse();
}
