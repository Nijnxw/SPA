#include "OptimizerGroup.h"


OptimizerGroup::OptimizerGroup() {}

bool OptimizerGroup::addEdge(QueryClause& clause, int weight) {
	const std::unordered_set<std::string>& synonyms = clause.getUsedSynonyms();

	if (synonyms.empty()) {
		return false;
	}

	if (synonyms.size() == 1) {
		std::string synonym = *synonyms.begin();
		adjList[synonym].emplace_back(synonym, synonym, weight, clause);
	} else {
		std::string firstSynonym = *synonyms.begin();
		std::string secondSynonym = *next(synonyms.begin());

		adjList[firstSynonym].emplace_back(firstSynonym, secondSynonym, weight, clause);
		adjList[secondSynonym].emplace_back(secondSynonym, firstSynonym, weight, clause);
	}
	return true;
}

std::unordered_map<std::string, std::vector<OptimizerClause>> OptimizerGroup::getAdjList() {
	return adjList;
}

// TODO: DFS to split the clauses into individual groups
std::vector<OptimizerGroup> OptimizerGroup::groupClauses() {
	return std::vector<OptimizerGroup>();
}
