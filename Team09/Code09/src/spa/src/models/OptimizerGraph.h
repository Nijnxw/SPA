#pragma once

#include <unordered_map>
#include "OptimizerClause.h"

class OptimizerGraph {
public:
	OptimizerGraph();

	bool addEdge(const OptimizerClause& clause);
	bool addEdge(const QueryClause& clause, int weight);
	std::unordered_map<std::string, std::vector<OptimizerClause>> getAdjList();

protected:
	std::unordered_set<QueryClause> clauses;    // to prevent duplicate clauses
	std::unordered_map<std::string, std::vector<OptimizerClause>> adjList;
};
