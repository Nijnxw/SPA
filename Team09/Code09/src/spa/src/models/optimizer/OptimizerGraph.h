#pragma once

#include <unordered_map>
#include "OptimizerClause.h"

typedef std::unordered_map<std::string, std::unordered_set<OptimizerClause, std::hash<OptimizerClause>>> AdjList;

class OptimizerGraph {
public:
	OptimizerGraph() = default;
	OptimizerGraph(AdjList adjList);

	AdjList getAdjList() const;
	std::unordered_set<std::string> getUsedSynonyms() const;

	virtual bool addEdge(const OptimizerClause& clause);
	virtual bool addEdge(const QueryClause& clause);
	virtual bool addEdge(const QueryClause& clause, int weight);
	bool operator==(const OptimizerGraph& other) const;

protected:
	AdjList adjList;
	std::unordered_set<std::string> usedSynonyms;
	std::unordered_set<QueryClause, std::hash<QueryClause>> clauses;    // to prevent duplicate clauses

	virtual void setStartPoint(const OptimizerClause& clause);
};
