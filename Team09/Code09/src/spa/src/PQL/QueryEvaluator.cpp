#include "QueryEvaluator.h"
#include "models/QueryClauseResult.h"
#include "PQL/evaluators/EntityEvaluator.h"
#include "PQL/evaluators/ClauseEvaluator.h"
#include "util/QueryUtils.h"
#include "Optimizer.h"

Table QueryEvaluator::evaluate(Query& query) {
	std::vector<QueryArgument> synNotInClauses;
	std::vector<QueryClause> clausesWithoutSyn;
	std::vector<OptimizerGroup> groupsWithSelect;
	std::vector<OptimizerGroup> groupsWithoutSelect;

	std::tie(synNotInClauses, clausesWithoutSyn, groupsWithSelect, groupsWithoutSelect) = Optimizer::optimize(query);

	if (!clausesWithoutSyn.empty() && !evaluateBooleanClauses(clausesWithoutSyn)) {
		return {};
	}
	std::vector<QueryClauseResult> entityResults = evaluateSynWithoutClause(synNotInClauses);
	if (!synNotInClauses.empty() && entityResults.empty()) {
		return {};
	}
	std::vector<std::vector<QueryClauseResult>> groupsWithoutSelectRes = evaluateGroupsWithoutSelect(
		groupsWithoutSelect);
	if (!groupsWithoutSelect.empty() && groupsWithoutSelectRes.empty()) {
		return {};
	}
	std::vector<std::vector<QueryClauseResult>> groupsWithSelectRes = evaluateGroupsWithSelect(groupsWithSelect);
	if (!groupsWithSelect.empty() && groupsWithSelectRes.empty()) {
		return {};
	}

	if (!groupsWithoutSelect.empty() && !mergeGroupWithoutSelectResults(groupsWithoutSelectRes)) {
		return {};
	}

	if (!groupsWithSelect.empty() && synNotInClauses.empty()) {
		return mergeGroupWithSelectResults(groupsWithSelectRes);
	} else if (groupsWithSelect.empty() && !synNotInClauses.empty()) {
		return mergeSynNotInClauseResults(entityResults);
	} else {
		Table selectClauseResults = mergeGroupWithSelectResults(groupsWithSelectRes);
		Table synNotInClauseResults = mergeSynNotInClauseResults(entityResults);

		return QueryUtils::crossProduct(selectClauseResults, synNotInClauseResults);
	}
}

bool QueryEvaluator::evaluateBooleanClauses(std::vector<QueryClause>& clauses) {
	for (const auto& clause: clauses) {
		QueryClauseResult clauseRes = ClauseEvaluator::evaluate(clause, true);
		if (!clauseRes.containsValidResult()) {
			return false;
		}
	}
	return true;
}

std::vector<QueryClauseResult> QueryEvaluator::evaluateSynWithoutClause(std::vector<QueryArgument> syns) {
	std::vector<QueryClauseResult> results;
	for (const auto& syn: syns) {
		QueryClauseResult entityResult = EntityEvaluator::evaluate(syn);
		if (!entityResult.containsValidResult()) {
			return {};
		}
		results.push_back(entityResult);
	}
	return results;
}

std::vector<std::vector<QueryClauseResult>>
QueryEvaluator::evaluateGroupsWithoutSelect(std::vector<OptimizerGroup> groups) {
	std::vector<std::vector<QueryClauseResult>> groupResults;

	for (const auto& group: groups) {
		std::vector<QueryClause> groupClauses = group.getClauses();
		std::vector<QueryClauseResult> results;
		if (groupClauses.size() == 1) {
			QueryClauseResult clauseRes = ClauseEvaluator::evaluate(groupClauses.front(), true);

			if (!clauseRes.containsValidResult()) {
				return {};
			}
			results.push_back(clauseRes);
			groupResults.push_back(results);
			continue;
		}

		for (const auto& clause: groupClauses) {
			QueryClauseResult clauseRes = ClauseEvaluator::evaluate(clause, false);
			if (!clauseRes.containsValidResult()) {
				return {};
			}
			results.push_back(clauseRes);
		}
		groupResults.push_back(results);
	}

	return groupResults;
}

std::vector<std::vector<QueryClauseResult>>
QueryEvaluator::evaluateGroupsWithSelect(std::vector<OptimizerGroup> groups) {
	std::vector<std::vector<QueryClauseResult>> groupResults;

	for (const auto& group: groups) {
		std::vector<QueryClause> groupClauses = group.getClauses();
		std::vector<QueryClauseResult> results;

		for (const auto& clause: groupClauses) {
			QueryClauseResult clauseRes = ClauseEvaluator::evaluate(clause, false);
			if (!clauseRes.containsValidResult()) {
				return {};
			}
			results.push_back(clauseRes);
		}
		groupResults.push_back(results);
	}

	return groupResults;
}

Table QueryEvaluator::mergeSynNotInClauseResults(const std::vector<QueryClauseResult>& synResults) {
	Table finalResults = (*synResults.begin()).getTable();
	for (auto it = next(synResults.begin()); it != synResults.end(); it++) {
		finalResults = QueryUtils::crossProduct(finalResults, it->getTable());
	}
	return finalResults;
}

bool QueryEvaluator::mergeGroupWithoutSelectResults(const std::vector<std::vector<QueryClauseResult>>& groupResults) {
	for (const auto& group: groupResults) {
		Table result = (*group.begin()).getTable();
		for (auto it = next(group.begin()); it != group.end(); it++) {
			result = QueryUtils::hashJoin(result, it->getTable());
		}
		std::vector<std::string> firstCol = (*result.begin()).second;
		if (firstCol.empty()) {
			return false;
		}
	}
	return true;
}

Table QueryEvaluator::mergeGroupWithSelectResults(const std::vector<std::vector<QueryClauseResult>>& groupResults) {
	Table finalResults;
	std::vector<Table> tempResults;

	for (const auto& group: groupResults) {
		Table result = (*group.begin()).getTable();
		for (auto it = next(group.begin()); it != group.end(); it++) {
			result = QueryUtils::hashJoin(result, it->getTable());
		}
		std::vector<std::string> firstCol = (*result.begin()).second;
		if (firstCol.empty()) {
			return {};
		}
		tempResults.push_back(result);
	}

	finalResults = tempResults.front();
	for (auto it = next(tempResults.begin()); it != tempResults.end(); it++) {
		finalResults = QueryUtils::crossProduct(finalResults, *it);
	}

	return finalResults;
}
