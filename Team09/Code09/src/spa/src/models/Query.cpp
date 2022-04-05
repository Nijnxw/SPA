#include <vector>
#include "Query.h"

Query::Query(const std::vector<QueryArgument>& resultSynonyms, const std::vector<QueryClause>& clauses, bool isBoolean)
	: resultSynonyms(resultSynonyms), clauses(clauses), isBoolean(isBoolean) {}

Query::Query(bool isBoolean, bool isSemanticErrorDetected)
	: isBoolean(isBoolean), SemanticErrorDetected(isSemanticErrorDetected) {}

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
	return resultSynonyms.empty() && clauses.empty() && !isBoolean;
}

bool Query::isSemanticErrorDetected() {
	return SemanticErrorDetected;
}