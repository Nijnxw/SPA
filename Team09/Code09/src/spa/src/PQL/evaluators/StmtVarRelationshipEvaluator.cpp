#include "StmtVarRelationshipEvaluator.h"

QueryClauseResult
	StmtVarRelationshipEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {

	switch (RHSType) {
	case EntityType::STRING:
		return getRelationshipByVariable(relationship, LHS, RHS, LHSType);
	case EntityType::VAR:
		return getRelationshipBySynonym(relationship, LHS, RHS, LHSType);
	case EntityType::WILD:
		return getRelationshipByUnderscore(relationship, LHS, RHS, LHSType);
	default:
		QueryClauseResult emptyQueryResult;
		return emptyQueryResult;
	}
}

QueryClauseResult StmtVarRelationshipEvaluator::getRelationshipByUnderscore(
	RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseResult queryResult;
	std::unordered_set<int> relationshipStmts = (relationship == RelationRef::MODIFIES)
		? PKB::getModifiesStatements()
		: PKB::getUsesStatements();
		
	switch (LHSType) {
	case EntityType::INT:
		if (relationship == RelationRef::MODIFIES && !PKB::getVariablesModifiedByStatement(std::stoi(LHS)).empty()
			|| relationship == RelationRef::USES && !PKB::getVariablesUsedByStatement(std::stoi(LHS)).empty()) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT:
		queryResult.addColumn(LHS, relationshipStmts);
		break;
	case EntityType::ASSIGN: {
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(relationshipStmts, assignStmts));
		break;
	}
	case EntityType::READ:
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(relationshipStmts,
			PKB::getStatementsWithType(EntityType::READ)));
		break;
	case EntityType::PRINT:
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(relationshipStmts,
			PKB::getStatementsWithType(EntityType::PRINT)));
		break;
	case EntityType::IF:
		queryResult.addColumn(LHS,PKBUtil::unorderedSetIntersection(relationshipStmts,
			PKB::getStatementsWithType(EntityType::IF)));
		break;
	case EntityType::WHILE:
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(relationshipStmts,
			PKB::getStatementsWithType(EntityType::WHILE)));
		break;
	case EntityType::CALL:
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(relationshipStmts,
			PKB::getStatementsWithType(EntityType::CALL)));
		break;
	case EntityType::PROC:
		if (relationship == RelationRef::USES) {
			queryResult.addColumn(LHS, PKB::getUsesProcedures());
		}
		else if (relationship == RelationRef::MODIFIES) {
			queryResult.addColumn(LHS, PKB::getModifiesProcedures());
		}
		break;
	case EntityType::STRING:
		if (relationship == RelationRef::USES && !PKB::getVariablesUsedByProcedure(LHS).empty()
			|| relationship == RelationRef::MODIFIES && !PKB::getVariablesModifiedByProcedure(LHS).empty()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		return queryResult;
	}
	return queryResult;
}

QueryClauseResult StmtVarRelationshipEvaluator::getRelationshipByVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseResult queryResult;

	std::unordered_set<int> relationshipStmts = (relationship == RelationRef::MODIFIES)
		? PKB::getStatementsModifyingVariable(RHS)
		: PKB::getStatementsUsingVariable(RHS);

	switch (LHSType) {
	case EntityType::INT:
		if (relationship == RelationRef::MODIFIES && PKB::getVariablesModifiedByStatement(std::stoi(LHS)).count(RHS)
			|| relationship == RelationRef::USES && PKB::getVariablesUsedByStatement(std::stoi(LHS)).count(RHS)) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT:
		queryResult.addColumn(LHS, relationshipStmts);
		break;
	case EntityType::ASSIGN: {
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		queryResult.addColumn(LHS, PKBUtil::unorderedSetIntersection(relationshipStmts, assignStmts));
		break;
	}
	case EntityType::PRINT:
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(relationshipStmts, PKB::getStatementsWithType(EntityType::PRINT)));
		break;
	case EntityType::READ:
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(relationshipStmts, PKB::getStatementsWithType(EntityType::READ)));
		break;
	case EntityType::IF:
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(relationshipStmts, PKB::getStatementsWithType(EntityType::IF)));
		break;
	case EntityType::WHILE:
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(relationshipStmts, PKB::getStatementsWithType(EntityType::WHILE)));
		break;
	case EntityType::CALL:
		queryResult.addColumn(LHS,
			PKBUtil::unorderedSetIntersection(relationshipStmts, PKB::getStatementsWithType(EntityType::CALL)));
		break;
	case EntityType::PROC:
		if (relationship == RelationRef::USES) {
			queryResult.addColumn(LHS, PKB::getProcedureUsingVariable(RHS));
		}
		else if (relationship == RelationRef::MODIFIES) {
			queryResult.addColumn(LHS, PKB::getProcedureModifyingVariable(RHS));
		}
		break;
	case EntityType::STRING:
		if (relationship == RelationRef::USES && PKB::getProcedureUsingVariable(RHS).count(LHS)
			|| relationship == RelationRef::MODIFIES && PKB::getProcedureModifyingVariable(RHS).count(LHS)) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		return queryResult;
	}
	return queryResult;
}

QueryClauseResult StmtVarRelationshipEvaluator::getRelationshipBySynonym(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseResult queryResult;
	std::vector<std::string> stmts;
	std::vector<std::string> vars;

	switch (LHSType) {
	case EntityType::INT:
		if (relationship == RelationRef::MODIFIES) {
			queryResult.addColumn(RHS, PKB::getVariablesModifiedByStatement(std::stoi(LHS)));
		}
		else if (relationship == RelationRef::USES) {
			queryResult.addColumn(RHS, PKB::getVariablesUsedByStatement(std::stoi(LHS)));
		}
		return queryResult;
	case EntityType::STMT: {
		std::tie(stmts, vars) = (relationship == RelationRef::MODIFIES)
			? PKB::getStmtsToModifiedVariable(PKB::getModifiesStatements())
			: PKB::getStmtsToUsedVariable(PKB::getUsesStatements());
		break;
	}
	case EntityType::ASSIGN: {
		std::unordered_set<int> assignStmts;
		for (auto kv : PKB::getAssignStatements()) {
			assignStmts.insert(kv.first);
		}
		std::tie(stmts, vars) = (relationship == RelationRef::MODIFIES)
			? PKB::getStmtsToModifiedVariable(
				PKBUtil::unorderedSetIntersection(PKB::getModifiesStatements(), assignStmts))
			: PKB::getStmtsToUsedVariable(
				PKBUtil::unorderedSetIntersection(PKB::getUsesStatements(), assignStmts));
		break;
	}
	case EntityType::PRINT: {
		std::tie(stmts, vars) = PKB::getStmtsToUsedVariable(PKB::getStatementsWithType(EntityType::PRINT));
		break;
	}
	case EntityType::READ: {
		std::tie(stmts, vars) = PKB::getStmtsToModifiedVariable(PKB::getStatementsWithType(EntityType::READ));
		break;
	}
	case EntityType::IF: {
		std::tie(stmts, vars) = (relationship == RelationRef::MODIFIES)
			? PKB::getStmtsToModifiedVariable(PKB::getStatementsWithType(EntityType::IF))
			: PKB::getStmtsToUsedVariable(PKB::getStatementsWithType(EntityType::IF));
		break;
	}
	case EntityType::WHILE: {
		std::tie(stmts, vars) = (relationship == RelationRef::MODIFIES)
			? PKB::getStmtsToModifiedVariable(PKB::getStatementsWithType(EntityType::WHILE))
			: PKB::getStmtsToUsedVariable(PKB::getStatementsWithType(EntityType::WHILE));
		break;
	}
	case EntityType::CALL: {
		std::tie(stmts, vars) = (relationship == RelationRef::MODIFIES)
			? PKB::getStmtsToModifiedVariable(PKB::getStatementsWithType(EntityType::CALL))
			: PKB::getStmtsToUsedVariable(PKB::getStatementsWithType(EntityType::CALL));
		break;
	}
	case EntityType::PROC: {
		auto [procs, vars] = (relationship == RelationRef::MODIFIES)
			? PKB::getProcsToModifiedVariable(PKB::getModifiesProcedures())
			: PKB::getProcsToUsedVariable(PKB::getUsesProcedures());
		queryResult.addColumn(LHS, procs);
		queryResult.addColumn(RHS, vars);
		break;
	}
	case EntityType::STRING:
		if (relationship == RelationRef::USES) {
			queryResult.addColumn(RHS, PKB::getVariablesUsedByProcedure(LHS));
		}
		else if (relationship == RelationRef::MODIFIES) {
			queryResult.addColumn(RHS, PKB::getVariablesModifiedByProcedure(LHS));
		}
		break;
	default:
		return queryResult;
	}
	queryResult.addColumn(LHS, stmts);
	queryResult.addColumn(RHS, vars);
	return queryResult;
}
