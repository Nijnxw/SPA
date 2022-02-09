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

#include "StatementOnlyRelationshipEvaluator.h";

class ParentEvaluator : public StatementOnlyRelationshipEvaluator {
public:
	static QueryClauseTable
	getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			  bool isBooleanResult);
	static QueryClauseTable
	getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
};
