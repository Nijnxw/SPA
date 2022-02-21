#pragma once

#include <vector>
#include <unordered_map>
#include "models/Query.h"
#include "models/QueryClauseResult.h"
#include "pkb/stores/ModifiesStore.h"
#include "pkb/stores/UsesStore.h"

class QueryEvaluator {
public:
	static Table evaluate(Query& query);

private:
	static Table evaluateSingleClause(QueryClause& clause, QueryArgument& resultSyn);
	static Table evaluateMultiClause(QueryClause& firstClause, QueryClause& secondClause, QueryArgument& resultSyn);
};
