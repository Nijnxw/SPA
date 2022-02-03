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

/* Get Modifies relationship information from PKB, note that LHS and RHS types have to be specified */
QueryClauseTable
ModifiesStore::getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
						   bool isBooleanResult) {

	switch (RHSType) {
		case EntityType::STRING:
			return getModifiesByVariable(LHS, RHS, LHSType);
		case EntityType::VAR:
			return getModifiesBySynonym(LHS, RHS, LHSType);
		case EntityType::WILD:
			return getModifiesByUnderscore(LHS, RHS, LHSType);
		default:
			QueryClauseTable emptyQueryResult;
			return emptyQueryResult;
	}
}

// ============ HELPER METHODS ==============

/* Get Uses relationship information for Uses(_, _) cases */
QueryClauseTable
ModifiesStore::getModifiesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	switch (LHSType) {
		case EntityType::INT:
			// e.g. Modifies("9", _)
			if (!getVariablesModifiedByStatement(std::stoi(LHS)).empty())
				queryResult.setBooleanResult(true);
			break;
			/* Not used in iteration 1
				case EntityType::STRING:
				// e.g. Modifies("cs3203", _)
				if (!getVariablesModifiedByProcedure(LHS).empty())
					queryResult.setBooleanResult(true);
				break;
			*/
		case EntityType::STMT:
			// e.g. stmt s; Modifies(s, _)
			queryResult.addColumn(LHS, modifiesStatements);
			break;
		case EntityType::ASSIGN: {
			// e.g. assign a; Modifies(a, _)
			std::unordered_set<int> assignStmts;
			for (auto kv: EntityStore::getAssignStatements()) {
				assignStmts.insert(kv.first);
			}
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements, assignStmts));
			break;
		}
		case EntityType::READ:
			// e.g. read r; Modifies(r, _)
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements,
																		 EntityStore::getStatementsByType(EntityType::READ)));
			break;

		case EntityType::IF:
			// e.g. if ifs; Modifies(ifs, _)
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements,
																		 EntityStore::getStatementsByType(EntityType::IF)));
			break;

		case EntityType::WHILE:
			// e.g. while w; Modifies(w, _)
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(modifiesStatements,
																		 EntityStore::getStatementsByType(EntityType::WHILE)));
			break;

		default:
			return queryResult;
	}
	return queryResult;
}

/* Get Modifies relationship information for Modifies(_, "x") cases */
QueryClauseTable
ModifiesStore::getModifiesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	std::unordered_set<int> stmtsUsingVar = getStatementsModifyingVariable(RHS);
	switch (LHSType) {
		case EntityType::INT:
			// e.g. Modifies("9", "x")
			if (getVariablesModifiedByStatement(std::stoi(LHS)).count(RHS))
				queryResult.setBooleanResult(true);
			break;
			/* Not used in iteration 1
		case EntityType::STRING:
			// e.g. Modifies("cs3203", "x")
			if (getVariablesModifiedByProcedure(LHS).count(RHS))
				queryResult.setBooleanResult(true);
			break;
			*/
		case EntityType::STMT:
			// e.g. stmt s; Modifies(s, "x")
			queryResult.addColumn(LHS, getStatementsModifyingVariable(RHS));
			break;
		case EntityType::ASSIGN: {
			// e.g. assign a; Modifies(a, "x")
			std::unordered_set<int> assignStmts;
			for (auto kv: EntityStore::getAssignStatements()) {
				assignStmts.insert(kv.first);
			}
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, assignStmts));
			break;
		}
		case EntityType::READ:
			// e.g. read r; Modifies(r, "x")
			queryResult.addColumn(LHS,
								  PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getStatementsByType(EntityType::READ)));
			break;

		case EntityType::IF:
			// e.g. if ifs; Modifies(ifs, "x")
			queryResult.addColumn(LHS,
								  PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getStatementsByType(EntityType::IF)));
			break;

		case EntityType::WHILE:
			// e.g. while w; Modifies(w, "x")
			queryResult.addColumn(LHS,
								  PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getStatementsByType(EntityType::WHILE)));
			break;

		default:
			return queryResult;
	}
	return queryResult;
}

/* Get Modifies relationship information for Modifies(_, v) cases */
QueryClauseTable
ModifiesStore::getModifiesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;
	std::vector<std::string> stmts;
	std::vector<std::string> vars;

	switch (LHSType) {
		case EntityType::INT:
			// e.g. Modifies("9", v)
			queryResult.addColumn(RHS, getVariablesModifiedByStatement(std::stoi(LHS)));
			return queryResult;
			/* Not used in iteration 1
		case EntityType::STRING:
			// e.g. Modifies("cs3203", v)
			queryResult.addColumn(RHS, getVariablesModifiedByProcedure(LHS));
			break;
			*/
		case EntityType::STMT: {
			// e.g. stmt s; Modifies(s, v)
			std::tie(stmts, vars) = getStmtsToModifiedVariable(modifiesStatements);
			break;
		}
		case EntityType::ASSIGN: {
			// e.g. assign a; Modifies(a, v)
			std::unordered_set<int> assignStmts;
			for (auto kv: EntityStore::getAssignStatements()) {
				assignStmts.insert(kv.first);
			}
			std::tie(stmts, vars) = getStmtsToModifiedVariable(
				PKBUtil::unorderedSetIntersection(modifiesStatements, assignStmts));
			break;
		}
		case EntityType::READ: {
			// e.g. read r; Modifies(r, v)
			std::tie(stmts, vars) = getStmtsToModifiedVariable(EntityStore::getStatementsByType(EntityType::READ));
			break;
		}
		case EntityType::IF: {
			// e.g. if ifs; Modifies(ifs, v)
			std::tie(stmts, vars) = getStmtsToModifiedVariable(EntityStore::getStatementsByType(EntityType::IF));
			break;
		}
		case EntityType::WHILE: {
			// e.g. while w; Modifies(w, v)
			std::tie(stmts, vars) = getStmtsToModifiedVariable(EntityStore::getStatementsByType(EntityType::WHILE));
			break;
		}
		default:
			return queryResult;
	}
	queryResult.addColumn(LHS, stmts);
	queryResult.addColumn(RHS, vars);
	return queryResult;
}

/* Get variables Modfies by statement */
std::unordered_set<std::string> ModifiesStore::getVariablesModifiedByStatement(int stmtNo) {
	if (!statementNumberToVariablesModified.count(stmtNo))
		return {};
	return statementNumberToVariablesModified.at(stmtNo);
}

/* Get variables Modfies by procedure */
std::unordered_set<std::string> ModifiesStore::getVariablesModifiedByProcedure(const std::string& procName) {
	if (!procedureToVariablesModified.count(procName))
		return {};
	return procedureToVariablesModified.at(procName);
}

/* Get statements using a particular variable */
std::unordered_set<int> ModifiesStore::getStatementsModifyingVariable(const std::string& variable) {
	if (!variableToStatementNumbersModifiedBy.count(variable))
		return {};
	return variableToStatementNumbersModifiedBy.at(variable);
}

/* Returns a mapping of each statement in the input statement set to the variables its using.
	Mapping is represented as a tuple of vectors to preserve ordering */
std::tuple<std::vector<std::string>, std::vector<std::string>>
ModifiesStore::getStmtsToModifiedVariable(const std::unordered_set<int>& stmts) {
	std::vector<std::string> resultStmts;
	std::vector<std::string> resultVars;
	for (int stmt: stmts) {
		for (const std::string& var: getVariablesModifiedByStatement(stmt)) {
			resultStmts.push_back(std::to_string(stmt));
			resultVars.push_back(var);
		}
	}
	return {resultStmts, resultVars};
}
