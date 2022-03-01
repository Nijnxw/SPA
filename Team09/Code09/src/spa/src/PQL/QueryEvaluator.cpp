#include "QueryEvaluator.h"
#include "models/QueryClauseResult.h"
#include "PQL/evaluators/EntityEvaluator.h"
#include "PQL/evaluators/ClauseEvaluator.h"
#include "util/QueryUtils.h"

// assume single result synonym
// assume at most 2 clauses (iter 1 req)
Table QueryEvaluator::evaluate(Query& query) {
	Table finalResult;

	bool isNoClauseQuery = query.getClauses().empty();
	bool isSingleClauseQuery = query.getClauses().size() == 1;
	bool isMultiClauseQuery = query.getClauses().size() == 2;

	if (query.getResultSynonyms().size() != 1) {
		return finalResult;
	}

	QueryArgument resultSyn = query.getResultSynonyms().front();

	if (isNoClauseQuery) {
		finalResult = EntityEvaluator::evaluate(resultSyn).getTable();
	} else if (isSingleClauseQuery) {
		QueryClause clause = query.getClauses().front();
		finalResult = evaluateSingleClause(clause, resultSyn);
	} else if (isMultiClauseQuery) {
		QueryClause firstClause = query.getClauses().at(0);
		QueryClause secondClause = query.getClauses().at(1);
		finalResult = evaluateMultiClause(firstClause, secondClause, resultSyn);
	}

	return finalResult;
}

Table QueryEvaluator::evaluateSingleClause(QueryClause& clause, QueryArgument& resultSyn) {
	bool clauseContainsResSyn = clause.containsSynonym(resultSyn);
	QueryClauseResult clauseRes = ClauseEvaluator::evaluate(clause, false);

	if (!clauseContainsResSyn && clauseRes.containsValidResult()) {
		return EntityEvaluator::evaluate(resultSyn).getTable();
	} else {
		return clauseRes.getTable();
	}
}

Table QueryEvaluator::evaluateMultiClause(QueryClause& firstClause, QueryClause& secondClause,
										  QueryArgument& resultSyn) {
	QueryClauseResult firstClauseRes = ClauseEvaluator::evaluate(firstClause, false);
	QueryClauseResult secondClauseRes = ClauseEvaluator::evaluate(secondClause, false);
	Table emptyRes;

	bool noneContainsResSyn = !firstClause.containsSynonym(resultSyn) && !secondClause.containsSynonym(resultSyn);
	bool bothContainsResSyn = firstClause.containsSynonym(resultSyn) && secondClause.containsSynonym(resultSyn);

	if (bothContainsResSyn) {
		return QueryUtils::hashJoin(firstClauseRes.getTable(), secondClauseRes.getTable());
	} else if (noneContainsResSyn) {
		bool containsResult;
		if (firstClause.containsCommonSynonym(secondClause)) {
			Table intermediateRes = QueryUtils::hashJoin(firstClauseRes.getTable(), secondClauseRes.getTable());
			containsResult = !intermediateRes.empty();
		} else {
			containsResult = firstClauseRes.containsValidResult() && secondClauseRes.containsValidResult();
		}

		if (containsResult) {
			return EntityEvaluator::evaluate(resultSyn).getTable();
		}
	} else {
		if (firstClause.containsCommonSynonym(secondClause)) {
			return QueryUtils::hashJoin(firstClauseRes.getTable(), secondClauseRes.getTable());
		}

		if (firstClause.containsSynonym(resultSyn)) {
			return secondClauseRes.containsValidResult() ? firstClauseRes.getTable() : emptyRes;
		} else {
			return firstClauseRes.containsValidResult() ? secondClauseRes.getTable() : emptyRes;
		}
	}

	return emptyRes;
}
