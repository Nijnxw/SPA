#pragma once

#include <vector>
#include <unordered_map>
#include "models/Query.h"
#include "models/QueryClauseResult.h"
#include "pkb/stores/ModifiesStore.h"
#include "pkb/stores/UsesStore.h"
#include "models/optimizer/OptimizerGroup.h"
#include "PQL/evaluators/ClauseEvaluator.h"
#include "PQL/evaluators/SelectRefEvaluator.h"

class QueryEvaluator {
public:
	static Table evaluate(Query& query);

private:
	static ClauseEvaluator clauseEvaluator;

	static Table evaluateBooleanQuery(const std::vector<QueryClause>& clausesWithoutSyn,
									  const std::vector<OptimizerGroup>& groupsWithoutSelect);
	static Table evaluateNormalQuery(const std::unordered_set<std::string>& resultSynSet,
									 const std::unordered_set<QueryArgument, std::hash<QueryArgument>>& selectSynNotInClauses,
									 const std::unordered_set<QueryArgument, std::hash<QueryArgument>>& refInClauses,
									 const std::vector<QueryClause>& clausesWithoutSyn,
									 const std::vector<OptimizerGroup>& clauseGroups);

	static Table mergeGroupResults(const std::vector<Table>& results);
	static Table mergeGroupResults(const std::vector<QueryClauseResult>& results);
	static Table mergeRelatedClauseResults(const std::vector<QueryClauseResult>& results);

	static void filterIntermediateResults(Table& results, const std::unordered_set<std::string>& resultSynSet);

	static bool evaluateClausesWithoutSyn(const std::vector<QueryClause>& clauses);
	static std::vector<QueryClauseResult>
	evaluateSynNotInClause(const std::unordered_set<QueryArgument, std::hash<QueryArgument>>& syns);
	static bool evaluateGroupWithoutSelect(const OptimizerGroup& group);
	static Table evaluateGroupWithSelect(const OptimizerGroup& group);
};
