#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "util/PKBUtils.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"

#include "PatternConditionEvaluator.h"

class PatternIfEvaluator : public PatternConditionEvaluator {
public:
	PatternIfEvaluator();

	QueryClauseResult getIfPattern(const std::string& LHS, const std::string& clauseSyn, EntityType LHSType,
		bool isBooleanResult);
};
