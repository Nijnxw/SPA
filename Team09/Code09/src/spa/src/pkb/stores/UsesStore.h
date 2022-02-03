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
	static inline std::unordered_set<int> usesStatements;
	static inline std::unordered_set<std::string> usedVariables;
	static inline std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesUsed;
	static inline std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersUsedBy;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesUsed;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresUsedBy;

	// Internal helper methods
	static QueryResultTable getUsesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryResultTable getUsesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static QueryResultTable getUsesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType);
	static std::unordered_set<std::string> getVariablesUsedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesUsedByProcedure(const std::string& procName);
	static std::unordered_set<int> getStatementsUsingVariable(const std::string& variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>> getStmtsToUsedVariable(const std::unordered_set<int>& stmts);

public:
	UsesStore();

	static void clear();
	
	// Called by QE
	static QueryResultTable getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);

	// Called by SP and DE
	static bool addUsesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);

};
