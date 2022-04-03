#include "StmtStmtRelationshipEvaluator.h"

QueryClauseResult StmtStmtRelationshipEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	QueryClauseResult emptyQueryResult;
	if (LHSType != EntityType::WILD && LHSType == RHSType && LHS == RHS) { // Same statements which are not wildcards
		return emptyQueryResult;
	}
	else if (LHSType == EntityType::INT) {
		return StmtStmtRelationshipEvaluator::getRelationshipByStatementNumber(relationship, LHS, RHS, RHSType, isBooleanResult);
	}
	else if (LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN || LHSType == EntityType::IF ||
		LHSType == EntityType::WHILE || LHSType == EntityType::PRINT || LHSType == EntityType::READ ||
		LHSType == EntityType::CALL) {
		return StmtStmtRelationshipEvaluator::getRelationshipByStatementVariable(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
	}
	else if (LHSType == EntityType::WILD) {
		return StmtStmtRelationshipEvaluator::getRelationshipByUnderscore(relationship, RHS, RHSType, isBooleanResult);
	}
	else {
		return emptyQueryResult;
	}
}

QueryClauseResult StmtStmtRelationshipEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult StmtStmtRelationshipEvaluator::getRelationshipByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType, bool isBooleanResult) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Follows(1, 2)
		if (PKB::isStmtStmtRelationship(relationship, std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Follows(1, s)
		if (PKB::isStmtStmtFirstEntity(relationship, std::stoi(LHS))) {
			std::unordered_set<int> statements = PKB::getStmtStmtSecondEntities(relationship, std::stoi(LHS));
			queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, RHSType, isBooleanResult));
		}
	}
	else if (RHSType == EntityType::WILD) { // Follows(1, _)
		if (PKB::isStmtStmtFirstEntity(relationship, std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
	}
	
	return queryResult;
}

QueryClauseResult StmtStmtRelationshipEvaluator::getRelationshipByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	QueryClauseResult queryResult;

	if ((relationship == RelationRef::PARENT && LHSType == EntityType::READ) ||
		(relationship == RelationRef::PARENT && LHSType == EntityType::PRINT) ||
		(relationship == RelationRef::PARENT && LHSType == EntityType::ASSIGN) ||
		(relationship == RelationRef::PARENT && LHSType == EntityType::CALL) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::READ) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::PRINT) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::ASSIGN) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::CALL)) { // If it's Parent, these cannot be Parent container statements.
		return queryResult;
	}
	else if (RHSType == EntityType::INT) { // Follows(s, 2)
		if (PKB::isStmtStmtSecondEntity(relationship, std::stoi(RHS))) {
			std::unordered_set<int> statements = PKB::getStmtStmtFirstEntities(relationship, std::stoi(RHS));
			queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, LHSType, isBooleanResult));
		}
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Follows(s1, s2)
		auto [firstEntities, secondEntities] = PKB::getAllStmtStmtRelationshipPairs(relationship);
		auto [filteredFirst, filteredSecond] = StmtStmtRelationshipEvaluator::filterStatementPairsByType(firstEntities, secondEntities, LHSType, RHSType, isBooleanResult);
		queryResult.addColumn(LHS, filteredFirst);
		queryResult.addColumn(RHS, filteredSecond);
	}
	else if (RHSType == EntityType::WILD) { // Follows(s, _)
		std::unordered_set<int> statements = PKB::getAllStmtStmtFirstEntities(relationship);
		queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, LHSType, isBooleanResult));
	}

	return queryResult;
}
QueryClauseResult StmtStmtRelationshipEvaluator::getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType, bool isBooleanResult) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Follows(_, 2)
		if (PKB::isStmtStmtSecondEntity(relationship, std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Follows(_, s)
		std::unordered_set<int> statements = PKB::getAllStmtStmtSecondEntities(relationship);
		queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, RHSType, isBooleanResult));
	}
	else if (RHSType == EntityType::WILD) { // Follows(_, _)
		if (PKB::hasStmtStmtRelationship(relationship)) {
			queryResult.setBooleanResult(true);
		}
	}

	return queryResult;
}

std::unordered_set<int> StmtStmtRelationshipEvaluator::filterStatementsByType(std::unordered_set<int> statements, EntityType type, bool isBooleanResult) {
	if (type == EntityType::STMT) {
		return statements;
	}

	std::unordered_set<int> typeStatements;

	switch (type) {
	case EntityType::ASSIGN:
		typeStatements = PKB::getStatementsWithType(EntityType::ASSIGN);
		break;
	case EntityType::IF:
		typeStatements = PKB::getStatementsWithType(EntityType::IF);
		break;
	case EntityType::WHILE:
		typeStatements = PKB::getStatementsWithType(EntityType::WHILE);
		break;
	case EntityType::READ:
		typeStatements = PKB::getStatementsWithType(EntityType::READ);
		break;
	case EntityType::PRINT:
		typeStatements = PKB::getStatementsWithType(EntityType::PRINT);
		break;
	case EntityType::CALL:
		typeStatements = PKB::getStatementsWithType(EntityType::CALL);
		break;
	}

	return PKBUtils::unorderedSetIntersection(statements, typeStatements, isBooleanResult);
}

std::tuple<std::vector<int>, std::vector<int>> StmtStmtRelationshipEvaluator::filterStatementPairsByType(std::vector<int> firstEntities,
	std::vector<int> secondEntities, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> statementPairs = PKBUtils::convertVectorTupleToSetPairs(firstEntities, secondEntities);

	std::unordered_set<int> firstTypeStatements;
	std::unordered_set<int> secondTypeStatements;

	switch (LHSType) {
	case EntityType::STMT:
		for (const auto& statement : firstEntities) {
			firstTypeStatements.insert(statement);
		}
	break;
	case EntityType::ASSIGN:
		firstTypeStatements = PKB::getStatementsWithType(EntityType::ASSIGN);
		break;
	case EntityType::IF:
		firstTypeStatements = PKB::getStatementsWithType(EntityType::IF);
		break;
	case EntityType::WHILE:
		firstTypeStatements = PKB::getStatementsWithType(EntityType::WHILE);
		break;
	case EntityType::READ:
		firstTypeStatements = PKB::getStatementsWithType(EntityType::READ);
		break;
	case EntityType::PRINT:
		firstTypeStatements = PKB::getStatementsWithType(EntityType::PRINT);
		break;
	case EntityType::CALL:
		firstTypeStatements = PKB::getStatementsWithType(EntityType::CALL);
		break;
	}

	std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> firstFilteredStatementPairs;
	for (const auto& statement : firstTypeStatements) {
		for (const auto& pair : statementPairs) {
			if (pair.first == statement) {
				firstFilteredStatementPairs.insert(pair);
			}
		}
	}

	switch (RHSType) {
	case EntityType::STMT:
		for (const auto& statement : secondEntities) {
			secondTypeStatements.insert(statement);
		}
		break;
	case EntityType::ASSIGN:
		secondTypeStatements = PKB::getStatementsWithType(EntityType::ASSIGN);
		break;
	case EntityType::IF:
		secondTypeStatements = PKB::getStatementsWithType(EntityType::IF);
		break;
	case EntityType::WHILE:
		secondTypeStatements = PKB::getStatementsWithType(EntityType::WHILE);
		break;
	case EntityType::READ:
		secondTypeStatements = PKB::getStatementsWithType(EntityType::READ);
		break;
	case EntityType::PRINT:
		secondTypeStatements = PKB::getStatementsWithType(EntityType::PRINT);
		break;
	case EntityType::CALL:
		secondTypeStatements = PKB::getStatementsWithType(EntityType::CALL);
		break;
	}

	std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> secondFilteredStatementPairs;
	for (const auto& statement : secondTypeStatements) {
		for (const auto& pair : firstFilteredStatementPairs) {
			if (pair.second != statement) {
				continue;
			}

			secondFilteredStatementPairs.insert(pair);
			if (isBooleanResult) {
				break;
			}
		}
	}

	return PKBUtils::convertSetPairsToVectorTuple(secondFilteredStatementPairs);
}