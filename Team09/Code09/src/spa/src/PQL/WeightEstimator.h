#pragma once

#include <unordered_map>
#include <unordered_set>
#include "pkb/PKB.h"
#include "models/QueryClause.h"
#include "models/Query.h"
#include "models/RelationRef.h"

class WeightEstimator {
private: 
	static const int WITH_WEIGHT = 1;
	static const int PATTERN_ASSIGN_WEIGHT = 2;
	static const int PATTERN_IF_WEIGHT = 3;
	static const int PATTERN_WHILE_WEIGHT = 3;
	static const int CALLS_WEIGHT = 4;
	static const int CALLS_T_WEIGHT = 5;
	static const int AFFECTS_WEIGHT = 6;
	static const int AFFECTS_T_WEIGHT = 7;
	static const int FOLLOWS_WEIGHT = 8;
	static const int PARENT_WEIGHT = 8;
	static const int NEXT_WEIGHT = 8;
	static const int FOLLOWS_T_WEIGHT = 9;
	static const int PARENT_T_WEIGHT = 9;
	static const int NEXT_T_WEIGHT = 9;
	static const int MODIFIES_WEIGHT = 10;
	static const int USES_WEIGHT = 11;

	static const std::unordered_map<RelationRef, int> heuristicsToWeight;

	static int getHeuristicsWeight(QueryClause clause);
	static int getStatisticsWeight(QueryClause clause);
public:
	static int estimateWeight(QueryClause clause);
};
