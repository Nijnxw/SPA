#include "OptimizerGraph.h"

OptimizerGraph::OptimizerGraph() {}

bool OptimizerGraph::addEdge(const OptimizerClause& clause) {
	return addEdge(clause.getClause(), clause.getWeight());
}

bool OptimizerGraph::addEdge(const QueryClause& clause, int weight) {
	const std::unordered_set<std::string>& synonyms = clause.getUsedSynonyms();

	if (synonyms.empty() || clauses.count(clause) != 0) {
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

std::unordered_map<std::string, std::vector<OptimizerClause>> OptimizerGraph::getAdjList() {
	return adjList;
}
