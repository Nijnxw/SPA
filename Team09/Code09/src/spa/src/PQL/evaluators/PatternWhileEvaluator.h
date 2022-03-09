#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"

#include "PatternConditionEvaluator.h"

class PatternWhileEvaluator : public PatternConditionEvaluator {
public:
	PatternWhileEvaluator();

	QueryClauseResult getWhilePattern(const std::string& LHS, const std::string& clauseSyn, EntityType LHSType,
		bool isBooleanResult);
};

