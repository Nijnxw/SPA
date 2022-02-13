#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseTable.h"
#include "models/QueryClause.h"

#include "UMEvaluator.h"

class ModifiesEvaluator : public UMEvaluator {
public:
	static QueryClauseTable
	getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
				bool isBooleanResult);
};
