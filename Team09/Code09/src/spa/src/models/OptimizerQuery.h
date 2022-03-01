#pragma once

#include <unordered_map>
#include "OptimizerClause.h"
#include "OpimizerGroup.h"

class OptimizerQuery {
public:
	OptimizerQuery();

	bool addEdge(QueryClause& clause, int weight);
	std::unordered_map<std::string, std::vector<OptimizerClause>> getAdjList();
	std::vector<OptimizerGroup> groupClauses();    // perform DFS to extract out groups of clauses
private:
	std::unordered_map<std::string, std::vector<OptimizerClause>> adjList;
};
