#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../models/EntityType.h"
#include "../../models/QueryClauseTable.h"
#include "../stores/EntityStore.h"
#include "../util/PKBUtil.cpp"

class ModifiesStore {
private:
	// Data
	static inline std::unordered_set<int> modifiesStatements;
	static inline std::unordered_set<std::string> modifiedVariables;
	static inline std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesModified;
	static inline std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersModifiedBy;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesModified;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresModifiedBy;


public:
	ModifiesStore();

	static void clear();

	// Getters
	static std::unordered_set<int> getModifiesStatements();
	static std::unordered_set<std::string> getModifiedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersModifiedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresModifiedBy();
	static std::unordered_set<std::string> getVariablesModifiedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesModifiedByProcedure(const std::string& procName);
	static std::unordered_set<int> getStatementsModifyingVariable(const std::string& variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
		getStmtsToModifiedVariable(const std::unordered_set<int>& stmts);

	/* Setters called by SP and DE */
	static bool addModifiesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addModifiesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);

};
