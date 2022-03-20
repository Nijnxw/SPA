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

#include "StmtVarRelationshipEvaluator.h"

class UsesEvaluator : public StmtVarRelationshipEvaluator {
public:
	UsesEvaluator();

	QueryClauseResult
	getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
};
