#pragma once

#include "OptimizerGraph.h"
#include "OptimizerGroup.h"

class OptimizerQuery : public OptimizerGraph {
public:
	std::vector<OptimizerGroup> groupClauses();    // perform DFS to extract out groups of clauses
private:
	OptimizerGroup groupingHelper(const std::string& synonym, std::unordered_set<std::string>& visited);
};
