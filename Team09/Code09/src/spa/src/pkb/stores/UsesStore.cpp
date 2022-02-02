//TODO: Possible optimisation by early termination given isBooleanResult argument, currently boolean is not used
#include "UsesStore.h"

UsesStore::UsesStore() {}

void UsesStore::clear() {
	usesStatements.clear();
	usedVariables.clear();
	statementNumberToVariablesUsed.clear();
	variableToStatementNumbersUsedBy.clear();
	procedureToVariablesUsed.clear();
	variableToProceduresUsedBy.clear();
}

// ============ STORE METHODS ==============

/* Add Uses(stmt, var) relationship to PKB */
bool UsesStore::addUsesStatement(int statementNumber, const std::unordered_set<std::string>& variables) {
	usesStatements.insert(statementNumber);

	if (!statementNumberToVariablesUsed.emplace(statementNumber, variables).second) {
		statementNumberToVariablesUsed.at(statementNumber).insert(variables.begin(), variables.end());
	}

	for (const std::string& v : variables) {
		if (!variableToStatementNumbersUsedBy.emplace(v, std::unordered_set<int>{ statementNumber }).second) {
			variableToStatementNumbersUsedBy.at(v).emplace(statementNumber);
		}
		usedVariables.emplace(v);
	}

	return true;
}

/* Add Uses(proc, var) relationship to PKB */
bool UsesStore::addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables) {

	if (!procedureToVariablesUsed.emplace(procedure, variables).second) {
		procedureToVariablesUsed.at(procedure).insert(variables.begin(), variables.end());
	}

	for (const std::string& v : variables) {
		if (!variableToProceduresUsedBy.emplace(v, std::unordered_set<std::string>{ procedure }).second) {
			variableToProceduresUsedBy.at(v).emplace(procedure);
		}
	}

	return true;
}

// ============ GETTER METHOD ==============

/* Get Uses relationship information from PKB, note that LHS and RHS types have to be specified */
QueryResultTable UsesStore::getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {

	if (RHSType == EntityType::STRING) {
		return getUsesByVariable(LHS, RHS, LHSType);
	}
	else if (RHSType == EntityType::VAR) {
		return getUsesBySynonym(LHS, RHS, LHSType);
	}
	else if (RHSType == EntityType::WILD) {
		return getUsesByUnderscore(LHS, RHS, LHSType);
	}
	else {
		QueryResultTable emptyQueryResult;
		return emptyQueryResult;
	}
}

// ============ HELPER METHODS ==============

/* Get Uses relationship information for Uses(_, _) cases */
QueryResultTable UsesStore::getUsesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryResultTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		// e.g. Uses("9", _)
		if (!getVariablesUsedByStatement(std::stoi(LHS)).empty())
			queryResult.setBooleanResult(true);
		break;
		/* Not used in iteration 1
			case PROC_NAME:
			// e.g. Uses("cs3203", _)
			if (!getVariablesUsedByProcedure(LHS).empty())
				queryResult.setBooleanResult(true);
			break;
		*/
	case EntityType::STMT:
		// e.g. stmt s; Uses(s, _)
		queryResult.addColumn(LHS, usesStatements);
		break;
	case EntityType::ASSIGN: {
		// e.g. assign a; Uses(a, _)
		std::unordered_set<int> assignStmts;
		for (auto kv : EntityStore::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(usesStatements, assignStmts));
		break;
	}
	case EntityType::PRINT:
		// e.g. print p; Uses(p, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(usesStatements, EntityStore::getPrintStatements()));
		break;

	case EntityType::IF:
		// e.g. if ifs; Uses(ifs, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(usesStatements, EntityStore::getIfStatements()));
		break;

	case EntityType::WHILE:
		// e.g. while w; Uses(w, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(usesStatements, EntityStore::getWhileStatements()));
		break;
	}
	return queryResult;
}

/* Get Uses relationship information for Uses(_, "x") cases */
QueryResultTable UsesStore::getUsesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryResultTable queryResult;
	
	std::unordered_set<int> stmtsUsingVar = getStatementsUsingVariable(RHS);
	switch(LHSType) {
		case EntityType::INT:
			// e.g. Uses("9", "x")
			if (getVariablesUsedByStatement(std::stoi(LHS)).count(RHS))
				queryResult.setBooleanResult(true);
			break;
		/* Not used in iteration 1
			case PROC_NAME:
			// e.g. Uses("cs3203", "x")
			if (getVariablesUsedByProcedure(LHS).count(RHS))
				queryResult.setBooleanResult(true);
			break;
		*/
		case EntityType::STMT:
			// e.g. stmt s; Uses(s, "x")
			queryResult.addColumn(LHS, getStatementsUsingVariable(RHS));
			break;
		case EntityType::ASSIGN: {
			// e.g. assign a; Uses(a, "x")
			std::unordered_set<int> assignStmts;
			for (auto kv : EntityStore::getAssignStatements()) {
				assignStmts.insert(kv.first);
			}
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, assignStmts));
			break;
		}
		case EntityType::PRINT:
			// e.g. print p; Uses(p, "x")
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getPrintStatements()));
			break;

		case EntityType::IF:
			// e.g. if ifs; Uses(ifs, "x")
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getIfStatements()));
			break;

		case EntityType::WHILE:
			// e.g. while w; Uses(w, "x")
			queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getWhileStatements()));
			break;
	}
	return queryResult;
}

/* Get Uses relationship information for Uses(_, v) cases */
QueryResultTable UsesStore::getUsesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryResultTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		// e.g. Uses("9", v)
		queryResult.addColumn(RHS, getVariablesUsedByStatement(std::stoi(LHS)));
		break;
		/* Not used in iteration 1
	case EntityType::STRING:
		// e.g. Uses("cs3203", v)
		queryResult.addColumn(RHS, getVariablesUsedByProcedure(LHS));
		break;
		*/
	case EntityType::STMT: {
		// e.g. stmt s; Uses(s, v)
		auto [stmts, vars] = getStmtsToUsedVariable(usesStatements);
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case EntityType::ASSIGN: {
		// e.g. assign a; Uses(a, v)
		std::unordered_set<int> assignStmts;
		for (auto kv : EntityStore::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		auto [stmts, vars] = getStmtsToUsedVariable(PKBUtil::unorderedSetIntersection(usesStatements, assignStmts));
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case EntityType::PRINT: {
		// e.g. print p; Uses(p, v)
		auto [stmts, vars] = getStmtsToUsedVariable(EntityStore::getPrintStatements());
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case EntityType::IF: {
		// e.g. if ifs; Uses(ifs, v)
		auto [stmts, vars] = getStmtsToUsedVariable(EntityStore::getIfStatements());
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case EntityType::WHILE: {
		// e.g. while w; Uses(w, v)
		auto [stmts, vars] = getStmtsToUsedVariable(EntityStore::getWhileStatements());
		queryResult.addColumn(LHS, stmts);
		queryResult.addColumn(RHS, vars);
		break;
	}}
	return queryResult;
}

/* Get variables used by statement */
std::unordered_set<std::string> UsesStore::getVariablesUsedByStatement(int stmtNo) {
	if (!statementNumberToVariablesUsed.count(stmtNo))
		return {};
	return statementNumberToVariablesUsed.at(stmtNo);
}

/* Get variables used by procedure */
std::unordered_set<std::string> UsesStore::getVariablesUsedByProcedure(const std::string& procName) {
	if (!procedureToVariablesUsed.count(procName))
		return {};
	return procedureToVariablesUsed.at(procName);
}

/* Get statements using a particular variable */
std::unordered_set<int> UsesStore::getStatementsUsingVariable(const std::string& variable) {
	if (!variableToStatementNumbersUsedBy.count(variable))
		return {};
	return variableToStatementNumbersUsedBy.at(variable);
}

/* Returns a mapping of each statement in the input statement set to the variables its using.
	Mapping is represented as a tuple of vectors to preserve ordering */
std::tuple<std::vector<std::string>, std::vector<std::string>> UsesStore::getStmtsToUsedVariable(const std::unordered_set<int>& stmts) {
	std::vector<std::string> resultStmts;
	std::vector<std::string> resultVars;
	for (int stmt : stmts) {
		for (const std::string& var : getVariablesUsedByStatement(stmt)) {
			resultStmts.push_back(std::to_string(stmt));
			resultVars.push_back(var);
		}
	}
	return { resultStmts, resultVars };
}
