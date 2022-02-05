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

/* Get Uses relationship information for Uses(_, _) cases */
QueryClauseTable UsesEvaluator::getUsesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		// e.g. Uses("9", _)
		if (!UsesStore::getVariablesUsedByStatement(std::stoi(LHS)).empty())
			queryResult.setBooleanResult(true);
		break;
		/* Not used in iteration 1
			case PROC_NAME:
			// e.g. Uses("cs3203", _)
			if (!UsesStore::getVariablesUsedByProcedure(LHS).empty())
				queryResult.setBooleanResult(true);
			break;
		*/
	case EntityType::STMT:
		// e.g. stmt s; Uses(s, _)
		queryResult.addColumn(LHS, UsesStore::getUsesStatements());
		break;
	case EntityType::ASSIGN: {
		// e.g. assign a; Uses(a, _)
		std::unordered_set<int> assignStmts;
		for (auto kv : EntityStore::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(UsesStore::getUsesStatements(), assignStmts));
		break;
	}
	case EntityType::PRINT:
		// e.g. print p; Uses(p, _)
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(UsesStore::getUsesStatements(), EntityStore::getStatementsWithType(EntityType::PRINT)));
		break;

	case EntityType::IF:
		// e.g. if ifs; Uses(ifs, _)
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(UsesStore::getUsesStatements(), EntityStore::getStatementsWithType(EntityType::IF)));
		break;

	case EntityType::WHILE:
		// e.g. while w; Uses(w, _)
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(UsesStore::getUsesStatements(), EntityStore::getStatementsWithType(EntityType::WHILE)));
		break;
	default:
		return queryResult;
	}
	return queryResult;
}

/* Get Uses relationship information for Uses(_, "x") cases */
QueryClauseTable UsesEvaluator::getUsesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	std::unordered_set<int> stmtsUsingVar = UsesStore::getStatementsUsingVariable(RHS);
	switch (LHSType) {
	case EntityType::INT:
		// e.g. Uses("9", "x")
		if (UsesStore::getVariablesUsedByStatement(std::stoi(LHS)).count(RHS))
			queryResult.setBooleanResult(true);
		break;
		/* Not used in iteration 1
			case PROC_NAME:
			// e.g. Uses("cs3203", "x")
			if (UsesStore::getVariablesUsedByProcedure(LHS).count(RHS))
				queryResult.setBooleanResult(true);
			break;
		*/
	case EntityType::STMT:
		// e.g. stmt s; Uses(s, "x")
		queryResult.addColumn(LHS, UsesStore::getStatementsUsingVariable(RHS));
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
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getStatementsWithType(EntityType::PRINT)));
		break;

	case EntityType::IF:
		// e.g. if ifs; Uses(ifs, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getStatementsWithType(EntityType::IF)));
		break;

	case EntityType::WHILE:
		// e.g. while w; Uses(w, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, EntityStore::getStatementsWithType(EntityType::WHILE)));
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
		queryResult.addColumn(RHS, UsesStore::getVariablesUsedByStatement(std::stoi(LHS)));
		return queryResult;
		/* Not used in iteration 1
	case EntityType::STRING:
		// e.g. Uses("cs3203", v)
		queryResult.addColumn(RHS, UsesStore::getVariablesUsedByProcedure(LHS));
		break;
		*/
	case EntityType::STMT: {
		// e.g. stmt s; Uses(s, v)
		std::tie(stmts, vars) = UsesStore::getStmtsToUsedVariable(UsesStore::getUsesStatements());
		break;
	}
	case EntityType::ASSIGN: {
		// e.g. assign a; Uses(a, v)
		std::unordered_set<int> assignStmts;
		for (auto kv : EntityStore::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		std::tie(stmts, vars) = UsesStore::getStmtsToUsedVariable(
			PKBUtil::unorderedSetIntersection(UsesStore::getUsesStatements(), assignStmts));
		break;
	}
	case EntityType::PRINT: {
		// e.g. print p; Uses(p, v)
		std::tie(stmts, vars) = UsesStore::getStmtsToUsedVariable(EntityStore::getStatementsWithType(EntityType::PRINT));
		break;
	}
	case EntityType::IF: {
		// e.g. if ifs; Uses(ifs, v)
		std::tie(stmts, vars) = UsesStore::getStmtsToUsedVariable(EntityStore::getStatementsWithType(EntityType::IF));
		break;
	}
	case EntityType::WHILE: {
		// e.g. while w; Uses(w, v)
		std::tie(stmts, vars) = UsesStore::getStmtsToUsedVariable(EntityStore::getStatementsWithType(EntityType::WHILE));
		break;
	default:
		return queryResult;
	}
	}
	queryResult.addColumn(LHS, stmts);
	queryResult.addColumn(RHS, vars);
	return queryResult;
}
