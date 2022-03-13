#pragma once

#include "OptimizerGraph.h"
#include <queue>
#include <utility>

class OptimizerGroup : public OptimizerGraph {
public:
	OptimizerGroup() = default;
	OptimizerGroup(AdjList adjList);
	std::vector<QueryClause> getClauses() const;
	bool addEdge(const OptimizerClause& clause) override;
	bool addEdge(const QueryClause& clause) override;
	bool addEdge(const QueryClause& clause, int weight) override;
	bool operator==(const OptimizerGroup& other) const;
	bool operator<(const OptimizerGroup& other) const;
protected:
	void setStartPoint(const OptimizerClause& clause) override;
private:
	int totalWeight = 0;
	int numClauses = 0;
	OptimizerClause startPoint;
	void orderingHelper(std::string& syn, std::unordered_set<std::string>& visitedSyns,
						std::unordered_set<OptimizerClause>& visitedClauses,
						std::priority_queue<OptimizerClause>& toAdd) const;
};
