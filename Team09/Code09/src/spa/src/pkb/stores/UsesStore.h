#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class UsesStore {
private:
	static std::unordered_set<int> usesStatements;
	static std::unordered_set<std::string> usedVariables;
	static std::unordered_map<int, unordered_set<std::string>> statementNumberToVariablesUsed;
	static std::unordered_map<std::string, unordered_set<int>> variableToStatementNumbersUsedBy;
	static std::unordered_map<std::string, unordered_set<std::string>> procedureToVariablesUsed;
	static std::unordered_map<std::string, unordered_set<std::string>> variableToProceduresUsedBy;

public:
	UsesStore();

	static void clear();

	static bool addUsesStatement(int statementNumber, StatementType statementType, std::unordered_set<std::string> variables);
	static bool addUsesProcedure(std::string procedure, StatementType statementType, std::unordered_set<std::string> variables);
}
