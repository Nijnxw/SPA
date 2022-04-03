#pragma once

#include "models/QueryClause.h"
#include "models/Query.h"
#include "util/CommonUtils.cpp"

class WeightOptimizer {
public:
	static int estimateWeight(QueryClause clause);
};
