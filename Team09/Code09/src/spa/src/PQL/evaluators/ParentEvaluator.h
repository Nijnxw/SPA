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

class ParentEvaluator {
private:

	// Internal helper methods
	static QueryClauseTable
	getParentByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable
	getParentByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getParentByUnderscore(const std::string& RHS, EntityType RHSType);

	static QueryClauseTable
	getParentTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable
	getParentTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getParentTByUnderscore(const std::string& RHS, EntityType RHSType);

public:
	static QueryClauseTable
	getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			  bool isBooleanResult);
	static QueryClauseTable
	getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			   bool isBooleanResult);
};
