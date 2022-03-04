#include "OptimizerGraph.h"

#include <utility>

OptimizerGraph::OptimizerGraph(AdjList adjList) : adjList(std::move(adjList)) {}

bool OptimizerGraph::addEdge(const OptimizerClause& clause) {
	return addEdge(clause.getClause(), clause.getWeight());
}

bool OptimizerGraph::addEdge(const QueryClause& clause) {
	return addEdge(clause, 0);
}

bool OptimizerGraph::addEdge(const QueryClause& clause, int weight) {
	const std::unordered_set<std::string>& synonyms = clause.getUsedSynonyms();

	if (synonyms.empty() || clauses.count(clause) != 0) {
		return false;
	}

	if (synonyms.size() == 1) {
		std::string synonym = *synonyms.begin();
		adjList[synonym].emplace(synonym, synonym, weight, clause);
		setStartPoint({synonym, synonym, weight, clause});
	} else {
		std::string firstSynonym = *synonyms.begin();
		std::string secondSynonym = *next(synonyms.begin());

		adjList[firstSynonym].emplace(firstSynonym, secondSynonym, weight, clause);
		adjList[secondSynonym].emplace(secondSynonym, firstSynonym, weight, clause);
		setStartPoint({firstSynonym, secondSynonym, weight, clause});
	}
	usedSynonyms.insert(synonyms.begin(), synonyms.end());
	clauses.insert(clause);
	return true;
}

void OptimizerGraph::setStartPoint(const OptimizerClause& clause) {}


std::unordered_set<std::string> OptimizerGraph::getUsedSynonyms() const {
	return usedSynonyms;
}

AdjList OptimizerGraph::getAdjList() const {
	return adjList;
}

bool OptimizerGraph::operator==(const OptimizerGraph& other) const {
	return adjList == other.adjList;
}
