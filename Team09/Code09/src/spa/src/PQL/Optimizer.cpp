#include "Optimizer.h"

std::tuple<std::vector<QueryArgument>, std::vector<QueryClause>, std::vector<OptimizerGroup>>
Optimizer::optimize(Query& query) {

	OptimizerQuery queryGraph;
	std::unordered_set<std::string> usedSynonyms;
	std::vector<QueryArgument> synNotInClauses = query.getResultSynonyms();
	std::vector<QueryClause> clausesWithoutSyn;        // each of these clauses return a boolean (should evaluate first)
	std::vector<OptimizerGroup> clauseGroups;

	std::vector<QueryClause> clauses = query.getClauses();

	for (const auto& clause: clauses) {
		std::unordered_set<std::string> clauseSynonyms = clause.getUsedSynonyms();
		usedSynonyms.insert(clauseSynonyms.begin(), clauseSynonyms.end());
		if (clauseSynonyms.empty()) {
			clausesWithoutSyn.push_back(clause);
		} else {
			queryGraph.addEdge(clause, 0);    // left as 0 until weight estimation algo is done
		}
	}

	clauseGroups = queryGraph.groupClauses();
	std::sort(clauseGroups.begin(), clauseGroups.end());

	synNotInClauses.erase(std::remove_if(synNotInClauses.begin(), synNotInClauses.end(),
										 [&](const QueryArgument& arg) {
											 return usedSynonyms.count(arg.getValue());
										 }),
						  synNotInClauses.end());

	return {synNotInClauses, clausesWithoutSyn, clauseGroups};
}
