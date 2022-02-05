#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../PKB.h"
#include "../util/PKBUtil.cpp"
#include "../../models/EntityType.h"
#include "../../models/QueryClauseTable.h"
#include "../../models/QueryClause.h"

class ModifiesEvaluator {
private:

	// Internal helper methods
	static QueryClauseTable getModifiesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryClauseTable getModifiesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryClauseTable getModifiesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType);

public:
	static QueryClauseTable
		getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
};
