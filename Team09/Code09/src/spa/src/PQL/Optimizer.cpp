#include "Optimizer.h"

std::tuple<std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual>, std::unordered_set<QueryArgument, std::hash<QueryArgument>>, std::vector<QueryClause>, std::vector<OptimizerGroup>>
Optimizer::optimize(Query& query) {

	OptimizerQuery queryGraph;
	std::unordered_set<std::string> usedSynonyms;
	std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual> synNotInClauses;
	std::unordered_set<QueryArgument, std::hash<QueryArgument>> synWithRef;
	std::vector<QueryClause> clausesWithoutSyn;        // each of these clauses return a boolean (should evaluate first)
	std::vector<OptimizerGroup> clauseGroups;

	std::vector<QueryClause> clauses = query.getClauses();

	for (const auto& clause: clauses) {
		std::unordered_set<std::string> clauseSynonyms = clause.getUsedSynonyms();
		usedSynonyms.insert(clauseSynonyms.begin(), clauseSynonyms.end());
		if (clauseSynonyms.empty()) {
			clausesWithoutSyn.push_back(clause);
		} else {
			int clauseWeight = WeightEstimator::estimateWeight(clause); // Weight estimation algo, revert if wrong
			queryGraph.addEdge(clause, clauseWeight);    // Change clauseWeight back to 0 if weight estimation fails
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
