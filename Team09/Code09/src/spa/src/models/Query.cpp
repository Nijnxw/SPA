#include <vector>
#include "Query.h"

Query::Query(const std::vector<QueryArgument>& resultSynonyms, const std::vector<QueryClause>& clauses, bool isBoolean)
	: resultSynonyms(resultSynonyms), clauses(clauses), isBoolean(isBoolean) {}

Query::Query() {}

const std::vector<QueryArgument>& Query::getResultSynonyms() const {
	return resultSynonyms;
}

const std::vector<QueryClause>& Query::getClauses() const {
	return clauses;
}

bool Query::isBooleanQuery() {
	return isBoolean;
}

bool Query::isEmpty() {
	return resultSynonyms.empty() && clauses.empty();
}

void Query::setSemanticErrorFlag() {
	SemanticErrorDetected = !SemanticErrorDetected;
}

bool Query::isSemanticErrorDetected() {
	return SemanticErrorDetected;
}