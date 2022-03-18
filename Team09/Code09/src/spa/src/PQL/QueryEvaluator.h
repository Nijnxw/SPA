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
	static Table evaluateNormalQuery(const std::unordered_set<std::string>& resultSynSet,
									 const std::vector<QueryArgument>& selectSynNotInClauses,
									 const std::vector<QueryClause>& clausesWithoutSyn,
									 const std::vector<OptimizerGroup>& clauseGroups);

	static Table mergeGroupResults(const std::vector<Table>& results);
	static Table mergeGroupResults(const std::vector<QueryClauseResult>& results);
	static Table mergeRelatedClauseResults(const std::vector<QueryClauseResult>& results);

	static bool evaluateClausesWithoutSyn(const std::vector<QueryClause>& clauses);
	static std::vector<QueryClauseResult> evaluateSynNotInClause(const std::vector<QueryArgument>& syns);
	static bool evaluateGroupWithoutSelect(const OptimizerGroup& group);
	static Table evaluateGroupWithSelect(const OptimizerGroup& group);
};
