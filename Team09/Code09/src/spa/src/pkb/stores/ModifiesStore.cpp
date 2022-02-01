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
// ============ STORE METHODS ==============

/* Add Modifies(stmt, var) relationship to PKB */
bool ModifiesStore::addModifiesStatement(int statementNumber, std::unordered_set<std::string> variables) {
	modifiesStatements.insert(statementNumber);

	if (!statementNumberToVariablesModified.emplace(statementNumber, variables).second) {
		statementNumberToVariablesModified.at(statementNumber).insert(variables.begin(), variables.end());
	}

	for (const std::string& v : variables) {
		if (!variableToStatementNumbersModifiedBy.emplace(v, std::unordered_set<int>{ statementNumber }).second) {
			variableToStatementNumbersModifiedBy.at(v).emplace(statementNumber);
		}
		modifiedVariables.emplace(v);
	}

	return true;
}

/* Add Modifies(proc, var) relationship to PKB */
bool ModifiesStore::addModifiesProcedure(std::string procedure, std::unordered_set<std::string> variables) {

	if (!procedureToVariablesModified.emplace(procedure, variables).second) {
		procedureToVariablesModified.at(procedure).insert(variables.begin(), variables.end());
	}

	for (const std::string& v : variables) {
		if (!variableToProceduresModifiedBy.emplace(v, std::unordered_set<std::string>{ procedure }).second) {
			variableToProceduresModifiedBy.at(v).emplace(procedure);
		}
	}

	return true;
}

// ============ GETTER METHOD ==============

/* Get Modifies relationship information from PKB, note that LHS and RHS types have to be specified */
QueryResultTable ModifiesStore::getModifies(std::string LHS, std::string RHS, ModifiesLHSTypeEnum LHSType, ModifiesRHSTypeEnum RHSType, bool isBooleanResult) {

	if (RHSType == VARIABLE_NAME) {
		return getModifiesByVariable(LHS, RHS, LHSType);
	}
	else if (RHSType == SYNONYM_VARIABLE) {
		return getModifiesBySynonym(LHS, RHS, LHSType);
	}
	else if (RHSType == UNDERSCORE) {
		return getModifiesByUnderscore(LHS, RHS, LHSType);
	}
	else {
		QueryResultTable emptyQueryResult;
		return emptyQueryResult;
	}
}

// ============ HELPER METHODS ==============

/* Get Uses relationship information for Uses(_, _) cases */
QueryResultTable ModifiesStore::getModifiesByUnderscore(std::string LHS, std::string RHS, ModifiesLHSTypeEnum LHSType) {
	QueryResultTable queryResult;

	switch (LHSType) {
	case STMT_NO:
		// e.g. Modifies("9", _)
		if (!getVariablesModifiedByStatement(std::stoi(LHS)).empty())
			queryResult.setBooleanResult(true);
		break;
		/* Not used in iteration 1
			case PROC_NAME:
			// e.g. Modifies("cs3203", _)
			if (!getVariablesModifiedByProcedure(LHS).empty())
				queryResult.setBooleanResult(true);
			break;
		*/
	case SYNONYM_STMT:
		// e.g. stmt s; Modifies(s, _)
		queryResult.addColumn(LHS, modifiesStatements);
		break;
	case SYNONYM_ASSIGN: {
		// e.g. assign a; Modifies(a, _)
		std::unordered_set<int> assignStmts;
		for (auto kv : EntityStore::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements, assignStmts));
		break;
	}
	case SYNONYM_READ:
		// e.g. print p; Modifies(p, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements, EntityStore::getReadStatements()));
		break;

	case SYNONYM_IF:
		// e.g. if ifs; Modifies(ifs, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements, EntityStore::getIfStatements()));
		break;

	case SYNONYM_WHILE:
		// e.g. while w; Modifies(w, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements, EntityStore::getWhileStatements()));
		break;
	}
	return queryResult;
}

/* Get Modifies relationship information for Modifies(_, "x") cases */
QueryResultTable ModifiesStore::getModifiesByVariable(std::string LHS, std::string RHS, ModifiesLHSTypeEnum LHSType) {
	QueryResultTable queryResult;

	std::unordered_set<int> stmtsUsingVar = getStatementsModifyingVariable(RHS);
	switch (LHSType) {
	case STMT_NO:
		// e.g. Modifies("9", "x")
		if (getVariablesModifiedByStatement(std::stoi(LHS)).count(RHS))
			queryResult.setBooleanResult(true);
		break;
	case PROC_NAME:
		// e.g. Modifies("cs3203", "x")
		if (getVariablesModifiedByProcedure(LHS).count(RHS))
			queryResult.setBooleanResult(true);
		break;
	case SYNONYM_STMT:
		// e.g. stmt s; Modifies(s, "x")
		queryResult.addColumn(LHS, getStatementsModifyingVariable(RHS));
		break;
	case SYNONYM_ASSIGN: {
		// e.g. assign a; Modifies(a, "x")
		std::unordered_set<int> assignStmts;
		for (auto kv : EntityStore::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, assignStmts));
		break;
	}
	case SYNONYM_READ:
		// e.g. read p; Modifies(p, "x")
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getPrintStatements()));
		break;

	case SYNONYM_IF:
		// e.g. if ifs; Modifies(ifs, "x")
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getIfStatements()));
		break;

	case SYNONYM_WHILE:
		// e.g. while w; Modifies(w, "x")
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getWhileStatements()));
		break;
	}
	return queryResult;
}

/* Get Modifies relationship information for Modifies(_, v) cases */
QueryResultTable ModifiesStore::getModifiesBySynonym(std::string LHS, std::string RHS, ModifiesLHSTypeEnum LHSType) {
	QueryResultTable queryResult;

	switch (LHSType) {
	case STMT_NO:
		// e.g. Modifies("9", v)
		queryResult.addColumn(RHS, getVariablesModifiedByStatement(std::stoi(LHS)));
		break;
	case PROC_NAME:
		// e.g. Modifies("cs3203", v)
		queryResult.addColumn(RHS, getVariablesModifiedByProcedure(LHS));
		break;
	case SYNONYM_STMT: {
		// e.g. stmt s; Modifies(s, v)
		auto [stmts, vars] = getStmtsToModifiedVariable(modifiesStatements);
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case SYNONYM_ASSIGN: {
		// e.g. assign a; Modifies(a, v)
		std::unordered_set<int> assignStmts;
		for (auto kv : EntityStore::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		auto [stmts, vars] = getStmtsToModifiedVariable(PKBUtil::unorderedSetIntersection(modifiesStatements, assignStmts));
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case SYNONYM_READ: {
		// e.g. read p; Modifies(p, v)
		auto [stmts, vars] = getStmtsToModifiedVariable(EntityStore::getPrintStatements());
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case SYNONYM_IF: {
		// e.g. if ifs; Modifies(ifs, v)
		auto [stmts, vars] = getStmtsToModifiedVariable(EntityStore::getIfStatements());
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case SYNONYM_WHILE: {
		// e.g. while w; Modifies(w, v)
		auto [stmts, vars] = getStmtsToModifiedVariable(EntityStore::getWhileStatements());
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	}
	return queryResult;
}

/* Get variables Modfies by statement */
std::unordered_set<std::string> ModifiesStore::getVariablesModifiedByStatement(int stmtNo) {
	if (!statementNumberToVariablesModified.count(stmtNo))
		return {};
	return statementNumberToVariablesModified.at(stmtNo);
}

/* Get variables Modfies by procedure */
std::unordered_set<std::string> ModifiesStore::getVariablesModifiedByProcedure(std::string procName) {
	if (!procedureToVariablesModified.count(procName))
		return {};
	return procedureToVariablesModified.at(procName);
}

/* Get statements using a particular variable */
std::unordered_set<int> ModifiesStore::getStatementsModifyingVariable(std::string variable) {
	if (!variableToStatementNumbersModifiedBy.count(variable))
		return {};
	return variableToStatementNumbersModifiedBy.at(variable);
}

/* Returns a mapping of each statement in the input statement set to the variables its using.
	Mapping is represented as a tuple of vectors to preserve ordering */
std::tuple<std::vector<std::string>, std::vector<std::string>> ModifiesStore::getStmtsToModifiedVariable(std::unordered_set<int> stmts) {
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
