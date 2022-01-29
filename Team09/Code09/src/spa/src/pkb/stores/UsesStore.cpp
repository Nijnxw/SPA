#include <UsesStore.h>

static std::unordered_set<int> usesStatements;
static std::unordered_set<std::string> usedVariables;
static std::unordered_map<int, unordered_set<std::string>> statementNumberToVariablesUsed;
static std::unordered_map<std::string, unordered_set<int>> variableToStatementNumbersUsedBy;
static std::unordered_map<std::string, unordered_set<std::string>> procedureToVariablesUsed;
static std::unordered_map<std::string, unordered_set<std::string>> variableToProceduresUsedBy;

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