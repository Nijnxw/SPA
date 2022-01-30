#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../models/QueryResultTable.h"
#include "EntityStore.h"

// Typing for input arguments to getUses()
enum UsesLHSTypeEnum {
	STMT_NO,
	PROC_NAME,
	SYNONYM_STMT,
	SYNONYM_ASSIGN,
	SYNONYM_PRINT,
	SYNONYM_CALL,
	SYNONYM_IF,
	SYNONYM_WHILE,
};

enum UsesRHSTypeEnum {
	VARIABLE_NAME,
	SYNONYM_VARIABLE,
	// UNDERSCORE,
};

enum SelectEnum {
	SELECT_LEFT,
	SELECT_RIGHT,
	SELECT_BOTH
};

class UsesStore {
private:
	static std::unordered_set<int> usesStatements;
	static std::unordered_set<std::string> usedVariables;
	static std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesUsed;
	static std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersUsedBy;
	static std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesUsed;
	static std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresUsedBy;

public:
	UsesStore();

	static void clear();
	
	static bool getUsesBoolean(std::string LHS, std::string RHS);
	static QueryResultTable getUses(std::string LHS, std::string RHS, UsesLHSTypeEnum LHSType, UsesRHSTypeEnum RHSType, SelectEnum select);
	static bool addUsesStatement(int statementNumber, StatementType statementType, std::unordered_set<std::string> variables);
	static bool addUsesProcedure(std::string procedure, StatementType statementType, std::unordered_set<std::string> variables);
	
	static QueryResultTable UsesStore::getUsesByVariable(std::string LHS, std::string RHS, UsesLHSTypeEnum LHSType);
	static QueryResultTable UsesStore::getUsesBySynonym(std::string LHS, std::string RHS, UsesLHSTypeEnum LHSType, SelectEnum select);

	static std::unordered_set<std::string> getVariablesUsedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesUsedByProcedure(std::string procName);
	static std::unordered_set<int> getStatementsUsingVariable(std::string variable);
};
