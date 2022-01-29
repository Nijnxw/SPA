#include "ModifiesStore.h"

std::unordered_set<int> modifiesStatements;
std::unordered_set<std::string> modifiedVariables;
std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesModified;
std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersModifiedBy;
std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesModified;
std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresModifiedBy;

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