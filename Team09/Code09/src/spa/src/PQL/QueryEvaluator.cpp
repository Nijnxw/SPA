#include "QueryEvaluator.h"
#include "models/QueryClauseResult.h"
#include "PQL/evaluators/EntityEvaluator.h"
#include "util/QueryUtils.h"
#include "Optimizer.h"

ClauseEvaluator QueryEvaluator::clauseEvaluator{};

Table QueryEvaluator::evaluate(Query& query) {
	if (query.isEmpty()) {
		return {};
	}

	auto[selectSynNotInClauses, synWithRef, clausesWithoutSyn, clauseGroups] = Optimizer::optimize(query);

	clauseEvaluator = ClauseEvaluator();

	if (query.isBooleanQuery()) {
		return evaluateBooleanQuery(clausesWithoutSyn, clauseGroups);
	}

	const std::vector<QueryArgument>& resultSyns = query.getResultSynonyms();
	std::unordered_set<std::string> resultSynSet;
	std::transform(resultSyns.begin(), resultSyns.end(), std::inserter(resultSynSet, resultSynSet.begin()),
				   [](const QueryArgument& arg) -> std::string { return arg.getValue(); });

	return evaluateNormalQuery(resultSynSet, selectSynNotInClauses, synWithRef, clausesWithoutSyn, clauseGroups);
}

Table QueryEvaluator::evaluateBooleanQuery(const std::vector<QueryClause>& clausesWithoutSyn,
										   const std::vector<OptimizerGroup>& groupsWithoutSelect) {

	if (!clausesWithoutSyn.empty() && !evaluateClausesWithoutSyn(clausesWithoutSyn)) {
		return {};
	}

	if (groupsWithoutSelect.empty()) {
		return {{"true", {"true"}}};    //returns a dummy result
	}

	for (const auto& group: groupsWithoutSelect) {
		if (!evaluateGroupWithoutSelect(group)) {
			return {};
		}
	}
	return {{"true", {"true"}}};
}

Table QueryEvaluator::evaluateNormalQuery(const std::unordered_set<std::string>& resultSynSet,
										  const std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual>& selectSynNotInClauses,
										  const std::unordered_set<QueryArgument, std::hash<QueryArgument>>& synWithRef,
										  const std::vector<QueryClause>& clausesWithoutSyn,
										  const std::vector<OptimizerGroup>& clauseGroups) {

	if (!clausesWithoutSyn.empty() && !evaluateClausesWithoutSyn(clausesWithoutSyn)) {
		return {};
	}
	const std::vector<QueryClauseResult>& entityResults = evaluateSynNotInClause(selectSynNotInClauses);
	if (!selectSynNotInClauses.empty() && entityResults.empty()) {
		return {};
	}

	std::vector<Table> groupWithSelectResults;
	for (const auto& group: clauseGroups) {
		const std::unordered_set<std::string>& synonyms = group.getUsedSynonyms();
		if (CommonUtils::containsCommon(synonyms, resultSynSet)) {
			Table intermediateRes = evaluateGroupWithSelect(group);
			if (intermediateRes.empty()) {
				return {};
			}

			filterIntermediateResults(intermediateRes, resultSynSet);
			groupWithSelectResults.push_back(intermediateRes);
			continue;
		}
		if (!evaluateGroupWithoutSelect(group)) {
			return {};
		}
	}
	Table finalResults;
	if (!groupWithSelectResults.empty() && selectSynNotInClauses.empty()) {
		finalResults = mergeGroupResults(groupWithSelectResults);
	} else if (groupWithSelectResults.empty() && !selectSynNotInClauses.empty()) {
		finalResults = mergeGroupResults(entityResults);
	} else {
		const Table& synNotInClausesResults = mergeGroupResults(entityResults);
		const Table& clausesWithSelectResults = mergeGroupResults(groupWithSelectResults);
		finalResults = QueryUtils::crossProduct(synNotInClausesResults, clausesWithSelectResults);
	}
	SelectRefEvaluator::evaluate(finalResults, synWithRef);
	return finalResults;
}

bool QueryEvaluator::evaluateClausesWithoutSyn(const std::vector<QueryClause>& clauses) {
	for (const auto& clause: clauses) {
		const QueryClauseResult& clauseRes = clauseEvaluator.evaluate(clause, true);
		if (!clauseRes.containsValidResult()) {
			return false;
		}
	}
	return true;
}

std::vector<QueryClauseResult>
QueryEvaluator::evaluateSynNotInClause(
	const std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual>& syns) {
	std::vector<QueryClauseResult> results;
	for (const auto& syn: syns) {
		const QueryClauseResult& entityResult = EntityEvaluator::evaluate(syn);
		if (!entityResult.containsValidResult()) {
			return {};
		}
		results.push_back(entityResult);
	}
	return results;
}

bool QueryEvaluator::evaluateGroupWithoutSelect(const OptimizerGroup& group) {
	const std::vector<QueryClause>& groupClauses = group.getClauses();
	std::vector<QueryClauseResult> results;
	if (groupClauses.size() == 1) {
		const QueryClauseResult& clauseRes = clauseEvaluator.evaluate(groupClauses.front(), true);
		if (!clauseRes.containsValidResult()) {
			return false;
		}
		return true;
	}

	for (const auto& clause: groupClauses) {
		const QueryClauseResult& clauseRes = clauseEvaluator.evaluate(clause, false);
		if (!clauseRes.containsValidResult()) {
			return false;
		}
		results.push_back(clauseRes);
	}

	if (mergeRelatedClauseResults(results).empty()) {
		return false;
	}
	return true;
}

Table QueryEvaluator::evaluateGroupWithSelect(const OptimizerGroup& group) {
	const std::vector<QueryClause>& groupClauses = group.getClauses();
	std::vector<QueryClauseResult> results;

	for (const auto& clause: groupClauses) {
		const QueryClauseResult& clauseRes = clauseEvaluator.evaluate(clause, false);
		if (!clauseRes.containsValidResult()) {
			return {};
		}
		results.push_back(clauseRes);
	}

	return mergeRelatedClauseResults(results);
}

Table QueryEvaluator::mergeGroupResults(const std::vector<QueryClauseResult>& results) {
	Table finalResults;

	if (results.empty()) {
		return finalResults;
	}

	finalResults = (*results.begin()).getTable();
	for (auto it = next(results.begin()); it != results.end(); it++) {
		finalResults = QueryUtils::crossProduct(finalResults, it->getTable());
	}
	return finalResults;
}


Table QueryEvaluator::mergeGroupResults(const std::vector<Table>& results) {
	Table finalResults;

	if (results.empty()) {
		return finalResults;
	}

	finalResults = *results.begin();
	for (auto it = next(results.begin()); it != results.end(); it++) {
		finalResults = QueryUtils::crossProduct(finalResults, *it);
	}
	return finalResults;
}

Table QueryEvaluator::mergeRelatedClauseResults(const std::vector<QueryClauseResult>& results) {
	Table finalResults;

	if (results.empty()) {
		return finalResults;
	}

	finalResults = (*results.begin()).getTable();
	for (auto it = next(results.begin()); it != results.end(); it++) {
		finalResults = QueryUtils::hashJoin(finalResults, it->getTable());
	}
	if (finalResults.empty()) {
		return {};
	}

	const std::vector<std::string>& firstCol = (*finalResults.begin()).second;
	if (firstCol.empty()) {
		return {};
	}

	return finalResults;
}

void QueryEvaluator::filterIntermediateResults(Table& results, const std::unordered_set<std::string>& resultSynSet) {
	for (auto it = results.begin(); it != results.end();) {
		if (resultSynSet.find(it->first) == resultSynSet.end()) {
			it = results.erase(it);
		} else {
			it++;
		}
	}

}
