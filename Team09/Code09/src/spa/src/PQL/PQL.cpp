#include "PQL/PQL.h"
#include "PQL/Tokeniser.h"
#include "PQL/PQLParser.h"
#include "PQL/QueryEvaluator.h"
#include "QueryResultProjector.h"

#include <iostream>

const std::vector<PQLToken*> PQL::tokenise(std::string query) {
	auto tokeniser = Tokeniser(query);
	return tokeniser.tokenise();
}

Query PQL::parse(std::vector<PQLToken*> tokens) {
	auto parser = PQLParser(tokens);
	return parser.parse();
}

Table PQL::evaluate(Query& query) {
	return QueryEvaluator::evaluate(query);
}

std::unordered_set<std::string> PQL::getResults(Table& res, Query& query) {
	return QueryResultProjector::formatResult(res, query);
}


