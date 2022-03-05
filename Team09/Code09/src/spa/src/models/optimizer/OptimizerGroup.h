#pragma once

#include "OptimizerGraph.h"
#include <queue>

class OptimizerGroup : public OptimizerGraph {
public:
	OptimizerGroup() = default;
	OptimizerGroup(AdjList adjList);
	std::vector<QueryClause> getClauses() const;
	bool operator==(const OptimizerGroup& other) const;
protected:
	void setStartPoint(const OptimizerClause& clause) override;
private:
	OptimizerClause startPoint;
	void orderingHelper(std::string& syn, std::unordered_set<std::string>& visitedSyns,
						std::unordered_set<OptimizerClause>& visitedClauses,
						std::priority_queue<OptimizerClause>& toAdd) const;
};
