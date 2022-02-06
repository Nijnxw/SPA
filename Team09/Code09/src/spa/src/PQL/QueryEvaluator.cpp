#include <unordered_set>
#include "QueryEvaluator.h"
#include "models/QueryClauseTable.h"
#include "PQL/evaluators/EntityEvaluator.h"
#include "PQL/evaluators/ClauseEvaluator.h"
#include "util/QueryUtils.h"

Table QueryEvaluator::evaluate(Query& query) {
	Table results;

	QueryArgument resultSynonym = query.getResultSynonyms().front();
	std::unordered_set<std::string> selectRelatedSynonyms = {resultSynonym.getValue()};    // for iter 1 (1 select)
	std::vector<QueryClauseTable> relatedResults;

	// for iteration 1, just check the 2 clauses, in future iteration, need to group clauses
	if (query.getClauses().empty()) {
		results = EntityEvaluator::evaluate(resultSynonym).getTable();
	} else if (query.getClauses().size() == 1) {
		QueryClause clause = query.getClauses().at(0);
		bool clauseContainsSelect = clause.getUsedSynonyms().count(resultSynonym.getValue()) > 0;

		if (clauseContainsSelect) {
			results = ClauseEvaluator::evaluate(clause, false).getTable();
		} else {
			results = EntityEvaluator::evaluate(resultSynonym).getTable();
		}
	} else {
		QueryClause firstClause = query.getClauses().at(0);
		QueryClause secondClause = query.getClauses().at(1);
		bool eitherClauseContainsSelect =
			firstClause.containsSynonym(resultSynonym) || secondClause.containsSynonym(resultSynonym);

		if (eitherClauseContainsSelect) {
			if (firstClause.containsCommonSynonym(secondClause)) {
				Table firstTable = ClauseEvaluator::evaluate(firstClause, false).getTable();
				Table secondTable = ClauseEvaluator::evaluate(secondClause, false).getTable();

				results = QueryUtils::hashJoin(firstTable, secondTable);
			} else if (firstClause.containsSynonym(resultSynonym)) {
				Table firstTable = ClauseEvaluator::evaluate(firstClause, false).getTable();
				Table secondTable = ClauseEvaluator::evaluate(secondClause, true).getTable();

				if (!secondTable.empty()) {
					results = firstTable;
				}
			} else {
				Table firstTable = ClauseEvaluator::evaluate(firstClause, true).getTable();
				Table secondTable = ClauseEvaluator::evaluate(secondClause, false).getTable();

				if (!firstTable.empty()) {
					results = secondTable;
				}
			}
		} else {
			results = EntityEvaluator::evaluate(resultSynonym).getTable();
		}
	}

	return results;
}
