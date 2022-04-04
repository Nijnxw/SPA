#pragma once

#include "QueryArgument.h"
#include "QueryClause.h"

class Query {
public:
	Query();
	Query(const std::vector<QueryArgument>& resultSynonyms, const std::vector<QueryClause>& clauses, bool isBoolean);
	const std::vector<QueryArgument>& getResultSynonyms() const;
	const std::vector<QueryClause>& getClauses() const;
	bool isBooleanQuery();
	bool isEmpty();
	void setSemanticErrorFlag(bool detected);
	bool isSemanticErrorDetected();

private:
	std::vector<QueryArgument> resultSynonyms;
	std::vector<QueryClause> clauses;
	bool isBoolean = false;
	bool SemanticErrorDetected = false;
};
