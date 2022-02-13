#include "UMEvaluator.h"

QueryClauseTable
	UMEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {

	switch (RHSType) {
	case EntityType::STRING:
		return getRelationshipByVariable(relationship, LHS, RHS, LHSType);
	case EntityType::VAR:
		return getRelationshipBySynonym(relationship, LHS, RHS, LHSType);
	case EntityType::WILD:
		return getRelationshipByUnderscore(relationship, LHS, RHS, LHSType);
	default:
		QueryClauseTable emptyQueryResult;
		return emptyQueryResult;
	}
}

QueryClauseTable UMEvaluator::getRelationshipByUnderscore(
	RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;
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

	default:
		return queryResult;
	}
	return queryResult;
}

QueryClauseTable UMEvaluator::getRelationshipByVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;

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
	default:
		return queryResult;
	}
	return queryResult;
}

QueryClauseTable UMEvaluator::getRelationshipBySynonym(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType) {
	QueryClauseTable queryResult;
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
	default:
		return queryResult;
	}
	}
	queryResult.addColumn(LHS, stmts);
	queryResult.addColumn(RHS, vars);
	return queryResult;
}
