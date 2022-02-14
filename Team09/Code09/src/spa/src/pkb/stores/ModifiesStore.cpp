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

/* Get variables modified by statement */
std::unordered_set<std::string> ModifiesStore::getVariablesModifiedByStatement(int stmtNo) {
	if (!getStatementNumberToVariablesModified().count(stmtNo))
		return {};
	return getStatementNumberToVariablesModified().at(stmtNo);
}

/* Get variables modified by procedure */
std::unordered_set<std::string> ModifiesStore::getVariablesModifiedByProcedure(const std::string& procName) {
	if (!getProcedureToVariablesModified().count(procName))
		return {};
	return getProcedureToVariablesModified().at(procName);
}

/* Get statements using a particular variable */
std::unordered_set<int> ModifiesStore::getStatementsModifyingVariable(const std::string& variable) {
	if (!getVariableToStatementNumbersModifiedBy().count(variable))
		return {};
	return getVariableToStatementNumbersModifiedBy().at(variable);
}

/* Returns a mapping of each statement in the input statement set to the variables its using.
	Mapping is represented as a tuple of vectors to preserve ordering */
std::tuple<std::vector<std::string>, std::vector<std::string>>
ModifiesStore::getStmtsToModifiedVariable(const std::unordered_set<int>& stmts) {
	std::vector<std::string> resultStmts;
	std::vector<std::string> resultVars;
	for (int stmt : stmts) {
		for (const std::string& var : getVariablesModifiedByStatement(stmt)) {
			resultStmts.push_back(std::to_string(stmt));
			resultVars.push_back(var);
		}
	}
	return { resultStmts, resultVars };
}
