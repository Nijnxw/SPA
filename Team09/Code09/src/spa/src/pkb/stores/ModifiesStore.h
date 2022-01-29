#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class ModifiesStore {
private:
	static std::unordered_set<int> modifiesStatements;
	static std::unordered_set<std::string> modifiedVariables;
	static std::unordered_map<int, unordered_set<std::string>> statementNumberToVariablesModified;
	static std::unordered_map<std::string, unordered_set<int>> variableToStatementNumbersModifiedBy;
	static std::unordered_map<std::string, unordered_set<std::string>> procedureToVariablesModified;
	static std::unordered_map<std::string, unordered_set<std::string>> variableToProceduresModifiedBy;

public: 
	ModifiesStore();

	static void clear();

	static bool addModifiesStatement(int statementNumber, StatementType statementType, std::unordered_set<std::string> variables);
	static bool addModifiesProcedure(std::string procedure, StatementType statementType, std::unordered_set<std::string> variables);
}
