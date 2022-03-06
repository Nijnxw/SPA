#pragma once

#include <vector>
#include <unordered_map>
#include "models/Query.h"
#include "models/QueryClauseResult.h"
#include "pkb/stores/ModifiesStore.h"
#include "pkb/stores/UsesStore.h"
#include "models/optimizer/OptimizerGroup.h"

class QueryEvaluator {
public:
	static Table evaluate(Query& query);

private:
	static bool evaluateBooleanClauses(std::vector<QueryClause>& clauses);
	static std::vector<QueryClauseResult> evaluateSynWithoutClause(std::vector<QueryArgument> syns);
	static std::vector<std::vector<QueryClauseResult>> evaluateGroupsWithoutSelect(std::vector<OptimizerGroup> groups);
	static std::vector<std::vector<QueryClauseResult>> evaluateGroupsWithSelect(std::vector<OptimizerGroup> groups);
	static Table mergeSynNotInClauseResults(const std::vector<QueryClauseResult>& synResults);
	static bool mergeGroupWithoutSelectResults(const std::vector<std::vector<QueryClauseResult>>& groupResults);
	static Table mergeGroupWithSelectResults(const std::vector<std::vector<QueryClauseResult>>& groupResults);
};
