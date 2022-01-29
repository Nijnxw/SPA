#include "UsesStore.h"

std::unordered_set<int> usesStatements;
std::unordered_set<std::string> usedVariables;
std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesUsed;
std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersUsedBy;
std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesUsed;
std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresUsedBy;

UsesStore::UsesStore() {}

void UsesStore::clear() {
	usesStatements.clear();
	usedVariables.clear();
	statementNumberToVariablesUsed.clear();
	variableToStatementNumbersUsedBy.clear();
	procedureToVariablesUsed.clear();
	variableToProceduresUsedBy.clear();
}

bool UsesStore::addUsesStatement(int statementNumber, StatementType statementType, std::unordered_set<std::string> variables) {
	return true; // TODO: Implement functionality.
}

bool UsesStore::addUsesProcedure(std::string procedure, StatementType statementType, std::unordered_set<std::string> variables) {
	return true; // TODO: Implement functionality.
}