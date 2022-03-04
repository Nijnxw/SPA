#pragma once

#include "OptimizerGraph.h"
#include <queue>

class OptimizerGroup : public OptimizerGraph {
public:
	OptimizerGroup() = default;
	OptimizerGroup(const AdjList& adjList);

	using OptimizerGraph::addEdge;
	bool addEdge(const QueryClause& clause, int weight) override;
	std::vector<QueryClause> getClauses();
private:
	OptimizerClause startPoint;
	void setStartPoint(const OptimizerClause& clause);
	void orderingHelper(std::string& syn, std::unordered_set<std::string>& visitedSyns,
						std::unordered_set<OptimizerClause>& visitedClauses,
						std::priority_queue<OptimizerClause>& toAdd);
};
