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

	static std::unordered_set<std::string> getVariablesUsedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesUsedByProcedure(const std::string& procName);
	static std::unordered_set<int> getStatementsUsingVariable(const std::string& variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
	getStmtsToUsedVariable(const std::unordered_set<int>& stmts);

public:
	static QueryClauseTable
	getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);

};
