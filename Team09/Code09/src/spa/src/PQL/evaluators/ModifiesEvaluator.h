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

class ModifiesEvaluator {
private:

	// Internal helper methods
	static QueryClauseTable getModifiesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryClauseTable getModifiesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryClauseTable getModifiesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType);

	static std::unordered_set<std::string> getVariablesModifiedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesModifiedByProcedure(const std::string& procName);
	static std::unordered_set<int> getStatementsModifyingVariable(const std::string& variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
	getStmtsToModifiedVariable(const std::unordered_set<int>& stmts);

public:
	static QueryClauseTable
	getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
				bool isBooleanResult);
};
