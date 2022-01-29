#include <ModifiesStore.h>

static std::unordered_set<int> modifiesStatements;
static std::unordered_set<std::string> modifiedVariables;
static std::unordered_map<int, unordered_set<std::string>> statementNumberToVariablesModified;
static std::unordered_map<std::string, unordered_set<int>> variableToStatementNumbersModifiedBy;
static std::unordered_map<std::string, unordered_set<std::string>> procedureToVariablesModified;
static std::unordered_map<std::string, unordered_set<std::string>> variableToProceduresModifiedBy;

ModifiesStore::ModifiesStore() {}

void ModifiesStore::clear() {
	modifiesStatements.clear();
	modifiedVariables.clear();
	statementNumberToVariablesModified.clear();
	variableToStatementNumbersModifiedBy.clear();
	procedureToVariablesModified.clear();
	variableToProceduresModifiedBy.clear();
}

bool ModifiesStore::addModifiesStatement(int statementNumber, StatementType statementType, std::unordered_set<std::string> variables) {
	return true; // TODO: Implement functionality.
}

bool ModifiesStore::addModifiesProcedure(std::string procedure, StatementType statementType, std::unordered_set<std::string> variables) {
	return true; // TODO: Implement functionality.
}