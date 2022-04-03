#include "Optimizer.h"

std::tuple<std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual>, std::unordered_set<QueryArgument, std::hash<QueryArgument>>, std::vector<QueryClause>, std::vector<OptimizerGroup>>
Optimizer::optimize(Query& query) {

	OptimizerQuery queryGraph;
	std::unordered_set<std::string> usedSynonyms;
	std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual> synNotInClauses;
	std::unordered_set<QueryArgument, std::hash<QueryArgument>> synWithRef;
	std::vector<QueryClause> clausesWithoutSyn;        // each of these clauses return a boolean (should evaluate first)
	std::vector<OptimizerGroup> clauseGroups;

	const std::vector<QueryClause>& clauses = query.getClauses();

	for (const auto& clause: clauses) {
		const std::unordered_set<std::string>& clauseSynonyms = clause.getUsedSynonyms();
		usedSynonyms.insert(clauseSynonyms.begin(), clauseSynonyms.end());
		if (clauseSynonyms.empty()) {
			clausesWithoutSyn.push_back(clause);
		} else {
			queryGraph.addEdge(clause, 0);    // left as 0 until weight estimation algo is done
		}
	}

	clauseGroups = queryGraph.groupClauses();
	std::sort(clauseGroups.begin(), clauseGroups.end());

	for (const auto& syn: query.getResultSynonyms()) {
		if (usedSynonyms.find(syn.getValue()) == usedSynonyms.end()) {
			synNotInClauses.insert(syn);
		}
	}

	for (const auto& syn: query.getResultSynonyms()) {
		if (syn.getAttrRef() != AttributeRef::NONE) {
			synWithRef.insert(syn);
		}
	}

	return {synNotInClauses, synWithRef, clausesWithoutSyn, clauseGroups};
}
