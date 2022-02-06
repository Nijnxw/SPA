#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

void ModifiesStore::clear() {
	modifiesStatements.clear();
	modifiedVariables.clear();
	statementNumberToVariablesModified.clear();
	variableToStatementNumbersModifiedBy.clear();
	procedureToVariablesModified.clear();
	variableToProceduresModifiedBy.clear();
}
// ============ STORE METHODS ==============

/* Add Modifies(stmt, var) relationship to PKB */
bool ModifiesStore::addModifiesStatement(int statementNumber, const std::unordered_set<std::string>& variables) {
	modifiesStatements.insert(statementNumber);

	if (!statementNumberToVariablesModified.emplace(statementNumber, variables).second) {
		statementNumberToVariablesModified.at(statementNumber).insert(variables.begin(), variables.end());
	}

	for (const std::string& v: variables) {
		if (!variableToStatementNumbersModifiedBy.emplace(v, std::unordered_set<int>{statementNumber}).second) {
			variableToStatementNumbersModifiedBy.at(v).insert(statementNumber);
		}
		modifiedVariables.insert(v);
	}

	return true;
}

/* Add Modifies(proc, var) relationship to PKB */
bool
ModifiesStore::addModifiesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables) {

	if (!procedureToVariablesModified.emplace(procedure, variables).second) {
		procedureToVariablesModified.at(procedure).insert(variables.begin(), variables.end());
	}

	for (const std::string& v: variables) {
		if (!variableToProceduresModifiedBy.emplace(v, std::unordered_set<std::string>{procedure}).second) {
			variableToProceduresModifiedBy.at(v).emplace(procedure);
		}
	}

	return true;
}

// ============ GETTER METHOD ==============

std::unordered_set<int> ModifiesStore::getModifiesStatements() {
	return modifiesStatements;
}

std::unordered_set<std::string> ModifiesStore::getModifiedVariables() {
	return modifiedVariables;
}

std::unordered_map<int, std::unordered_set<std::string>> ModifiesStore::getStatementNumberToVariablesModified() {
	return statementNumberToVariablesModified;
}

std::unordered_map<std::string, std::unordered_set<int>> ModifiesStore::getVariableToStatementNumbersModifiedBy() {
	return variableToStatementNumbersModifiedBy;
}

std::unordered_map<std::string, std::unordered_set<std::string>> ModifiesStore::getProcedureToVariablesModified() {
	return procedureToVariablesModified;
}

std::unordered_map<std::string, std::unordered_set<std::string>> ModifiesStore::getVariableToProceduresModifiedBy() {
	return variableToProceduresModifiedBy;
}
