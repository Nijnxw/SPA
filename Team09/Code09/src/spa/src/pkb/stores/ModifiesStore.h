#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "models/EntityType.h"
#include "models/QueryResultTable.h"
#include "pkb/stores/EntityStore.h"
#include "pkb/util/PKBUtil.cpp"

// Typing for input arguments to getModfies()
enum ModifiesLHSTypeEnum {
	STMT_NO,
	PROC_NAME,
	SYNONYM_STMT,
	SYNONYM_ASSIGN,
	SYNONYM_READ,
	SYNONYM_IF,
	SYNONYM_WHILE,
};

enum ModifiesRHSTypeEnum {
	VARIABLE_NAME,
	SYNONYM_VARIABLE,
	UNDERSCORE
};

class ModifiesStore {
private:
	// Data
	static std::unordered_set<int> modifiesStatements;
	static std::unordered_set<std::string> modifiedVariables;
	static std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesModified;
	static std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersModifiedBy;
	static std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesModified;
	static std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresModifiedBy;

	// Internal helper methods
	static QueryResultTable getModifiesByVariable(std::string LHS, std::string RHS, ModifiesLHSTypeEnum LHSType);
	static QueryResultTable getModifiesBySynonym(std::string LHS, std::string RHS, ModifiesLHSTypeEnum LHSType);
	static QueryResultTable getModifiesByUnderscore(std::string LHS, std::string RHS, ModifiesLHSTypeEnum  LHSType);
	static std::unordered_set<std::string> getVariablesModifiedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesModifiedByProcedure(std::string procName);
	static std::unordered_set<int> getStatementsModifyingVariable(std::string variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>> getStmtsToModifiedVariable(std::unordered_set<int> stmts);

public:
	ModifiesStore();

	static void clear();

	// Called by QE
	static QueryResultTable getModifies(std::string LHS, std::string RHS, ModifiesLHSTypeEnum LHSType, ModifiesRHSTypeEnum RHSType, bool isBooleanResult);

	// Called by SP and DE
	static bool addModifiesStatement(int statementNumber, std::unordered_set<std::string> variables);
	static bool addModifiesProcedure(std::string procedure, std::unordered_set<std::string> variables);
};
