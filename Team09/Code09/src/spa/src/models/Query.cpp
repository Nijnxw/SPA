#include <vector>
#include "Query.h"

Query::Query(std::vector<QueryArgument>& resultSynonyms, std::vector<QueryClause>& clauses) : resultSynonyms(
	resultSynonyms), clauses(clauses) {}
Query::Query() {}

const std::vector<QueryArgument>& Query::getResultSynonyms() const {
	return resultSynonyms;
}

const std::vector<QueryClause>& Query::getClauses() const {
	return clauses;
}

bool Query::isEmpty() {
	return resultSynonyms.empty() && clauses.empty();
}