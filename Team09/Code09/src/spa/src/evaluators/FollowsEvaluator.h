#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "../models/EntityType.h"
#include "../models/QueryClauseTable.h"
#include "../models/QueryClause.h"

class FollowsEvaluator {
private:

	// Internal helper methods
	static QueryClauseTable getFollowsByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsByUnderscore(const std::string& RHS, EntityType RHSType);

	static QueryClauseTable getFollowsTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsTByUnderscore(const std::string& RHS, EntityType RHSType);

public:
	static QueryClauseTable getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryClauseTable getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
};
