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
	static Table evaluateBooleanQuery(const std::vector<QueryClause>& clausesWithoutSyn,
									  const std::vector<OptimizerGroup>& groupsWithoutSelect);
	static Table evaluateNormalQuery(const std::vector<QueryArgument>& selectSynNotInClauses,
									 const std::vector<QueryClause>& clausesWithoutSyn,
									 const std::vector<OptimizerGroup>& groupsWithoutSelect,
									 const std::vector<OptimizerGroup>& groupsWithSelect);

	static bool evaluateBooleanClauses(const std::vector<QueryClause>& clauses);
	static std::vector<QueryClauseResult> evaluateSynWithoutClause(const std::vector<QueryArgument>& syns);
	static std::vector<std::vector<QueryClauseResult>>
	evaluateGroupsWithoutSelect(const std::vector<OptimizerGroup>& groups);
	static std::vector<std::vector<QueryClauseResult>>
	evaluateGroupsWithSelect(const std::vector<OptimizerGroup>& groups);
	static Table mergeSynNotInClauseResults(const std::vector<QueryClauseResult>& synResults);
	static bool mergeGroupWithoutSelectResults(const std::vector<std::vector<QueryClauseResult>>& groupResults);
	static Table mergeGroupWithSelectResults(const std::vector<std::vector<QueryClauseResult>>& groupResults);
};

/*
 * std::vector<QueryArgument> synNotInClauses;
	std::vector<QueryClause> clausesWithoutSyn;
	std::vector<OptimizerGroup> groupsWithSelect;
	std::vector<OptimizerGroup> groupsWithoutSelect;
 */
