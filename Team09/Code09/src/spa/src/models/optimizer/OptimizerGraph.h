#pragma once

#include <unordered_map>
#include "OptimizerClause.h"

typedef std::unordered_map<std::string, std::vector<OptimizerClause>> AdjList;

class OptimizerGraph {
public:
	OptimizerGraph() = default;
	OptimizerGraph(const AdjList& adjList);

	bool addEdge(const OptimizerClause& clause);
	virtual bool addEdge(const QueryClause& clause, int weight);
	AdjList getAdjList();
	bool operator==(const OptimizerGraph& other) const;

protected:
	std::unordered_set<QueryClause, std::hash<QueryClause>> clauses;    // to prevent duplicate clauses
	AdjList adjList;
};
