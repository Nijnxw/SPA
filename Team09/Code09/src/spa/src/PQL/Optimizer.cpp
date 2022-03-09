#include "Optimizer.h"

std::tuple<std::vector<QueryArgument>, std::vector<QueryClause>, std::vector<OptimizerGroup>, std::vector<OptimizerGroup>>
Optimizer::optimize(Query& query) {

	OptimizerQuery queryGraph;
	std::vector<QueryArgument> synNotInClauses = query.getResultSynonyms();
	std::vector<QueryClause> clausesWithoutSyn;            // each of these clauses return a boolean
	std::vector<OptimizerGroup> groupsWithSelect;        // clause groups of related clauses (each contain the select syn)
	std::vector<OptimizerGroup> groupsWithoutSelect;    // clause groups of related clauses (each don't contain select syn)

	std::vector<QueryClause> clauses = query.getClauses();

	for (const auto& clause: clauses) {
		std::unordered_set<std::string> usedSyns = clause.getUsedSynonyms();
		if (usedSyns.empty()) {
			clausesWithoutSyn.push_back(clause);
		} else {
			queryGraph.addEdge(clause, 0);    // left as 0 until weight estimation algo is done
		}
	}

	std::vector<OptimizerGroup> groups = queryGraph.groupClauses();
	splitGroups(synNotInClauses, groupsWithSelect, groupsWithoutSelect, groups, query);

	return {synNotInClauses, clausesWithoutSyn, groupsWithSelect, groupsWithoutSelect};
}

void
Optimizer::splitGroups(std::vector<QueryArgument>& synNotInClauses, std::vector<OptimizerGroup>& groupsWithSelect,
					   std::vector<OptimizerGroup>& groupsWithoutSelect, std::vector<OptimizerGroup>& allGroups,
					   Query& query) {
	std::unordered_set<std::string> usedSynonyms;

	std::vector<QueryArgument> resultSyns = query.getResultSynonyms();
	std::unordered_set<std::string> resultSynSet;
	std::transform(resultSyns.begin(), resultSyns.end(), std::inserter(resultSynSet, resultSynSet.begin()),
				   [](const QueryArgument& arg) -> std::string { return arg.getValue(); });

	for (const auto& group: allGroups) {
		std::unordered_set<std::string> synonyms = group.getUsedSynonyms();
		if (CommonUtils::containsCommon(synonyms, resultSynSet)) {
			groupsWithSelect.push_back(group);
		} else {
			groupsWithoutSelect.push_back(group);
		}
		usedSynonyms.insert(synonyms.begin(), synonyms.end());
	}

	synNotInClauses.erase(std::remove_if(synNotInClauses.begin(), synNotInClauses.end(),
										 [&](const QueryArgument& arg) {
											 return usedSynonyms.count(arg.getValue());
										 }),
						  synNotInClauses.end());
}
