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

class ModifiesEvaluator : public StmtVarRelationshipEvaluator {
public:
	ModifiesEvaluator();

	QueryClauseResult
	getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
				bool isBooleanResult);
};
