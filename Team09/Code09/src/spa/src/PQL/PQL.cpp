#include "PQL/PQL.h"
#include "PQL/PQLLexer.h"
#include "PQL/PQLParser.h"
#include "PQL/QueryEvaluator.h"
#include "QueryResultProjector.h"

const std::vector<PQLToken*> PQL::tokenise(std::string query) {
	auto tokeniser = PQLLexer(query);
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


