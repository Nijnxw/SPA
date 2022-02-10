#pragma once

#include "QueryArgument.h"
#include "QueryClause.h"

class Query {
public:
	Query();
	Query(std::vector<QueryArgument>& resultSynonyms, std::vector<QueryClause>& clauses);
	const std::vector<QueryArgument>& getResultSynonyms() const;
	const std::vector<QueryClause>& getClauses() const;

private:
	std::vector<QueryArgument> resultSynonyms;
	std::vector<QueryClause> clauses;
};
