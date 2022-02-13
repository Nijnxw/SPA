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

class UsesEvaluator {
private:

	// Internal helper methods
	static QueryClauseTable getUsesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryClauseTable getUsesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryClauseTable getUsesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType);

public:
	static QueryClauseTable
	getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);

};
