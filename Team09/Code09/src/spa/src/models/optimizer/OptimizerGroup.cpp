#include "OptimizerGroup.h"

OptimizerGroup::OptimizerGroup(AdjList adjList) : OptimizerGraph(adjList) {}

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

bool OptimizerGroup::operator==(const OptimizerGroup& other) const {
	return adjList == other.adjList && startPoint == other.startPoint;
}
