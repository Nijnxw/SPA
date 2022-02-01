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

class UsesStore {
private:
	// Data
	static std::unordered_set<int> usesStatements;
	static std::unordered_set<std::string> usedVariables;
	static std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesUsed;
	static std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersUsedBy;
	static std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesUsed;
	static std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresUsedBy;

	// Internal helper methods
	static QueryResultTable getUsesByVariable(std::string LHS, std::string RHS, EntityType LHSType);
	static QueryResultTable getUsesBySynonym(std::string LHS, std::string RHS, EntityType LHSType);
	static QueryResultTable getUsesByUnderscore(std::string LHS, std::string RHS, EntityType LHSType);
	static std::unordered_set<std::string> getVariablesUsedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesUsedByProcedure(std::string procName);
	static std::unordered_set<int> getStatementsUsingVariable(std::string variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>> getStmtsToUsedVariable(std::unordered_set<int> stmts);

public:
	UsesStore();

	static void clear();
	
	// Called by QE
	static QueryResultTable getUses(std::string LHS, std::string RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);

	// Called by SP and DE
	static bool addUsesStatement(int statementNumber, std::unordered_set<std::string> variables);
	static bool addUsesProcedure(std::string procedure, std::unordered_set<std::string> variables);

};
