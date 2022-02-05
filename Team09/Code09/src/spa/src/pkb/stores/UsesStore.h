#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../models/EntityType.h"

class UsesStore {
private:
	// Data
	static inline std::unordered_set<int> usesStatements;
	static inline std::unordered_set<std::string> usedVariables;
	static inline std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesUsed;
	static inline std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersUsedBy;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesUsed;
	static inline std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresUsedBy;

public:
	UsesStore();

	static void clear();

	/* Getters */
	static std::unordered_set<int> getUsesStatements();
	static std::unordered_set<std::string> getUsedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersUsedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresUsedBy();

	/* Setters called by SP and DE */
	static bool addUsesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);
};
