#include "OptimizerGroup.h"

OptimizerGroup::OptimizerGroup(const AdjList& adjList) : OptimizerGraph(adjList) {}

bool OptimizerGroup::addEdge(const QueryClause& clause, int weight) {
	const std::unordered_set<std::string>& synonyms = clause.getUsedSynonyms();

	if (synonyms.empty() || clauses.count(clause) != 0) {
		return false;
	}

	if (synonyms.size() == 1) {
		std::string synonym = *synonyms.begin();
		adjList[synonym].emplace_back(synonym, synonym, weight, clause);
		setStartPoint({synonym, synonym, weight, clause});
	} else {
		std::string firstSynonym = *synonyms.begin();
		std::string secondSynonym = *next(synonyms.begin());

		adjList[firstSynonym].emplace_back(firstSynonym, secondSynonym, weight, clause);
		adjList[secondSynonym].emplace_back(secondSynonym, firstSynonym, weight, clause);
		setStartPoint({firstSynonym, secondSynonym, weight, clause});
	}
	clauses.insert(clause);
	return true;
}

void OptimizerGroup::setStartPoint(const OptimizerClause& clause) {
	if (clauses.empty()) {
		startPoint = clause;
	} else if (clause.getWeight() < startPoint.getWeight()) {
		startPoint = clause;
	}
}

std::vector<QueryClause> OptimizerGroup::getClauses() {
	std::vector<QueryClause> orderedClauses;
	std::unordered_set<OptimizerClause, std::hash<OptimizerClause>> visitedClauses;
	std::unordered_set<std::string> visitedSyns;

	if (clauses.empty()) {
		return orderedClauses;
	}

	std::priority_queue<OptimizerClause> toAdd;
	toAdd.push(startPoint);
	visitedClauses.insert(startPoint);

	while (!toAdd.empty()) {
		OptimizerClause currClause = toAdd.top();
		toAdd.pop();

		orderedClauses.push_back(currClause.getClause());

		std::string fromSyn = currClause.getFrom();
		std::string toSyn = currClause.getTo();

		if (visitedSyns.find(fromSyn) == visitedSyns.end()) {
			orderingHelper(fromSyn, visitedSyns, visitedClauses, toAdd);
		}

		if (visitedSyns.find(toSyn) == visitedSyns.end()) {
			orderingHelper(toSyn, visitedSyns, visitedClauses, toAdd);
		}
	}

	return orderedClauses;
}

void OptimizerGroup::orderingHelper(std::string& syn, std::unordered_set<std::string>& visitedSyns,
									std::unordered_set<OptimizerClause>& visitedClauses,
									std::priority_queue<OptimizerClause>& toAdd) {
	visitedSyns.insert(syn);
	for (const auto& clause: adjList.at(syn)) {
		if (visitedClauses.find(clause) == visitedClauses.end()) {
			toAdd.push(clause);
			visitedClauses.insert(clause);
		}
	}
}

