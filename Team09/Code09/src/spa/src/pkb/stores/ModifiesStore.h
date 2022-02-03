#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "models/EntityType.h"
#include "models/QueryClauseTable.h"
#include "pkb/stores/EntityStore.h"
#include "pkb/util/PKBUtil.cpp"

class ModifiesStore {
private:
	// Data
	static inline std::unordered_set<int> modifiesStatements;
	static inline std::unordered_set<std::string> modifiedVariables;
	static inline std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesModified;
	static inline std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersModifiedBy;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesModified;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresModifiedBy;

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
	ModifiesStore();

	static void clear();

	// Called by QE
	static QueryClauseTable
	getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
				bool isBooleanResult);

	// Called by SP and DE
	static bool addModifiesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addModifiesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);
};
