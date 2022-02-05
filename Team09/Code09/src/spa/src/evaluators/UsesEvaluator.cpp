#include "UsesEvaluator.h"

/* Get Uses relationship information from PKB, note that LHS and RHS types have to be specified */
QueryClauseTable
UsesEvaluator::getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {

	switch (RHSType) {
	case EntityType::STRING:
		return getUsesByVariable(LHS, RHS, LHSType);
	case EntityType::VAR:
		return getUsesBySynonym(LHS, RHS, LHSType);
	case EntityType::WILD:
		return getUsesByUnderscore(LHS, RHS, LHSType);
	default:
		QueryClauseTable emptyQueryResult;
		return emptyQueryResult;
	}
}

// ============ HELPER METHODS ==============

/* Get variables used by statement */
std::unordered_set<std::string> UsesEvaluator::getVariablesUsedByStatement(int stmtNo) {
	if (!PKB::getStatementNumberToVariablesUsed().count(stmtNo))
		return {};
	return PKB::getStatementNumberToVariablesUsed().at(stmtNo);
}

/* Get variables used by procedure */
std::unordered_set<std::string> UsesEvaluator::getVariablesUsedByProcedure(const std::string& procName) {
	if (!PKB::getProcedureToVariablesUsed().count(procName))
		return {};
	return PKB::getProcedureToVariablesUsed().at(procName);
}

/* Get statements using a particular variable */
std::unordered_set<int> UsesEvaluator::getStatementsUsingVariable(const std::string& variable) {
	if (!PKB::getVariableToStatementNumbersUsedBy().count(variable))
		return {};
	return PKB::getVariableToStatementNumbersUsedBy().at(variable);
}

/* Returns a mapping of each statement in the input statement set to the variables its using.
	Mapping is represented as a tuple of vectors to preserve ordering */
std::tuple<std::vector<std::string>, std::vector<std::string>>
UsesEvaluator::getStmtsToUsedVariable(const std::unordered_set<int>& stmts) {
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

/* Get Uses relationship information for Uses(_, _) cases */
QueryClauseTable UsesEvaluator::getUsesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		// e.g. Uses("9", _)
		if (!getVariablesUsedByStatement(std::stoi(LHS)).empty())
			queryResult.setBooleanResult(true);
		break;
		/* Not used in iteration 1
			case PROC_NAME:
			// e.g. Uses("cs3203", _)
			if (!PKB::getVariablesUsedByProcedure(LHS).empty())
				queryResult.setBooleanResult(true);
			break;
		*/
	case EntityType::STMT:
		// e.g. stmt s; Uses(s, _)
		queryResult.addColumn(LHS, PKB::getUsesStatements());
		break;
	case EntityType::ASSIGN: {
		// e.g. assign a; Uses(a, _)
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(PKB::getUsesStatements(), assignStmts));
		break;
	}
	case EntityType::PRINT:
		// e.g. print p; Uses(p, _)
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(PKB::getUsesStatements(), PKB::getStatementsWithType(EntityType::PRINT)));
		break;

	case EntityType::IF:
		// e.g. if ifs; Uses(ifs, _)
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(PKB::getUsesStatements(), PKB::getStatementsWithType(EntityType::IF)));
		break;

	case EntityType::WHILE:
		// e.g. while w; Uses(w, _)
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(PKB::getUsesStatements(), PKB::getStatementsWithType(EntityType::WHILE)));
		break;
	default:
		return queryResult;
	}
	return queryResult;
}

/* Get Uses relationship information for Uses(_, "x") cases */
QueryClauseTable UsesEvaluator::getUsesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	std::unordered_set<int> stmtsUsingVar = getStatementsUsingVariable(RHS);
	switch (LHSType) {
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
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, assignStmts));
		break;
	}
	case EntityType::PRINT:
		// e.g. print p; Uses(p, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, PKB::getStatementsWithType(EntityType::PRINT)));
		break;

	case EntityType::IF:
		// e.g. if ifs; Uses(ifs, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, PKB::getStatementsWithType(EntityType::IF)));
		break;

	case EntityType::WHILE:
		// e.g. while w; Uses(w, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, PKB::getStatementsWithType(EntityType::WHILE)));
		break;
	default:
		return queryResult;
	}
	return queryResult;
}

/* Get Uses relationship information for Uses(_, v) cases */
QueryClauseTable UsesEvaluator::getUsesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;
	std::vector<std::string> stmts;
	std::vector<std::string> vars;

	switch (LHSType) {
	case EntityType::INT:
		// e.g. Uses("9", v)
		queryResult.addColumn(RHS, getVariablesUsedByStatement(std::stoi(LHS)));
		return queryResult;
		/* Not used in iteration 1
	case EntityType::STRING:
		// e.g. Uses("cs3203", v)
		queryResult.addColumn(RHS, getVariablesUsedByProcedure(LHS));
		break;
		*/
	case EntityType::STMT: {
		// e.g. stmt s; Uses(s, v)
		std::tie(stmts, vars) = getStmtsToUsedVariable(PKB::getUsesStatements());
		break;
	}
	case EntityType::ASSIGN: {
		// e.g. assign a; Uses(a, v)
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		std::tie(stmts, vars) = getStmtsToUsedVariable(
			PKBUtil::unorderedSetIntersection(PKB::getUsesStatements(), assignStmts));
		break;
	}
	case EntityType::PRINT: {
		// e.g. print p; Uses(p, v)
		std::tie(stmts, vars) = getStmtsToUsedVariable(PKB::getStatementsWithType(EntityType::PRINT));
		break;
	}
	case EntityType::IF: {
		// e.g. if ifs; Uses(ifs, v)
		std::tie(stmts, vars) = getStmtsToUsedVariable(PKB::getStatementsWithType(EntityType::IF));
		break;
	}
	case EntityType::WHILE: {
		// e.g. while w; Uses(w, v)
		std::tie(stmts, vars) = getStmtsToUsedVariable(PKB::getStatementsWithType(EntityType::WHILE));
		break;
	default:
		return queryResult;
	}
	}
	queryResult.addColumn(LHS, stmts);
	queryResult.addColumn(RHS, vars);
	return queryResult;
}
