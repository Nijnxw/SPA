#pragma once

#include "OptimizerGraph.h"

class OptimizerGroup : public OptimizerGraph {
public:
	OptimizerGroup();
	OptimizerGroup(const AdjList& adjList);
	//TODO: algo for retrieving order of evaluation
private:

};
