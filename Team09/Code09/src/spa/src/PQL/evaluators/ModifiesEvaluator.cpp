#include "ModifiesEvaluator.h"

/* Get Modifies relationship information from PKB, note that LHS and RHS types have to be specified */
QueryClauseTable
ModifiesEvaluator::getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {

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
QueryClauseTable
ModifiesEvaluator::getModifiesByUnderscore(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		// e.g. Modifies("9", _)
		if (!PKB::getVariablesModifiedByStatement(std::stoi(LHS)).empty())
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
		queryResult.addColumn(LHS, PKB::getModifiesStatements());
		break;
	case EntityType::ASSIGN: {
		// e.g. assign a; Modifies(a, _)
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(PKB::getModifiesStatements(), assignStmts));
		break;
	}
	case EntityType::READ:
		// e.g. read r; Modifies(r, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(PKB::getModifiesStatements(),
			PKB::getStatementsWithType(EntityType::READ)));
		break;

	case EntityType::IF:
		// e.g. if ifs; Modifies(ifs, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(PKB::getModifiesStatements(),
			PKB::getStatementsWithType(EntityType::IF)));
		break;

	case EntityType::WHILE:
		// e.g. while w; Modifies(w, _)
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(PKB::getModifiesStatements(),
			PKB::getStatementsWithType(EntityType::WHILE)));
		break;

	default:
		return queryResult;
	}
	return queryResult;
}

/* Get Modifies relationship information for Modifies(_, "x") cases */
QueryClauseTable
ModifiesEvaluator::getModifiesByVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

	std::unordered_set<int> stmtsUsingVar = PKB::getStatementsModifyingVariable(RHS);
	switch (LHSType) {
	case EntityType::INT:
		// e.g. Modifies("9", "x")
		if (PKB::getVariablesModifiedByStatement(std::stoi(LHS)).count(RHS))
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
		queryResult.addColumn(LHS, PKB::getStatementsModifyingVariable(RHS));
		break;
	case EntityType::ASSIGN: {
		// e.g. assign a; Modifies(a, "x")
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(stmtsUsingVar, assignStmts));
		break;
	}
	case EntityType::READ:
		// e.g. read r; Modifies(r, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, PKB::getStatementsWithType(EntityType::READ)));
		break;

	case EntityType::IF:
		// e.g. if ifs; Modifies(ifs, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, PKB::getStatementsWithType(EntityType::IF)));
		break;

	case EntityType::WHILE:
		// e.g. while w; Modifies(w, "x")
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(stmtsUsingVar, PKB::getStatementsWithType(EntityType::WHILE)));
		break;

	default:
		return queryResult;
	}
	return queryResult;
}

/* Get Modifies relationship information for Modifies(_, v) cases */
QueryClauseTable
ModifiesEvaluator::getModifiesBySynonym(const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;
	std::vector<std::string> stmts;
	std::vector<std::string> vars;

	switch (LHSType) {
	case EntityType::INT:
		// e.g. Modifies("9", v)
		queryResult.addColumn(RHS, PKB::getVariablesModifiedByStatement(std::stoi(LHS)));
		return queryResult;
		/* Not used in iteration 1
	case EntityType::STRING:
		// e.g. Modifies("cs3203", v)
		queryResult.addColumn(RHS, getVariablesModifiedByProcedure(LHS));
		break;
		*/
	case EntityType::STMT: {
		// e.g. stmt s; Modifies(s, v)
		std::tie(stmts, vars) = PKB::getStmtsToModifiedVariable(PKB::getModifiesStatements());
		break;
	}
	case EntityType::ASSIGN: {
		// e.g. assign a; Modifies(a, v)
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		std::tie(stmts, vars) = PKB::getStmtsToModifiedVariable(
			PKBUtil::unorderedSetIntersection(PKB::getModifiesStatements(), assignStmts));
		break;
	}
	case EntityType::READ: {
		// e.g. read r; Modifies(r, v)
		std::tie(stmts, vars) = PKB::getStmtsToModifiedVariable(PKB::getStatementsWithType(EntityType::READ));
		break;
	}
	case EntityType::IF: {
		// e.g. if ifs; Modifies(ifs, v)
		std::tie(stmts, vars) = PKB::getStmtsToModifiedVariable(PKB::getStatementsWithType(EntityType::IF));
		break;
	}
	case EntityType::WHILE: {
		// e.g. while w; Modifies(w, v)
		std::tie(stmts, vars) = PKB::getStmtsToModifiedVariable(PKB::getStatementsWithType(EntityType::WHILE));
		break;
	}
	default:
		return queryResult;
	}
	queryResult.addColumn(LHS, stmts);
	queryResult.addColumn(RHS, vars);
	return queryResult;
}
