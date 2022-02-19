#include "StmtStmtRelationshipEvaluator.h"

QueryClauseResult StmtStmtRelationshipEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	if (LHSType == EntityType::INT) {
		return StmtStmtRelationshipEvaluator::getRelationshipByStatementNumber(relationship, LHS, RHS, RHSType);
	}
	else if (LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN || LHSType == EntityType::IF ||
		LHSType == EntityType::WHILE || LHSType == EntityType::PRINT || LHSType == EntityType::READ ||
		LHSType == EntityType::CALL) {
		return StmtStmtRelationshipEvaluator::getRelationshipByStatementVariable(relationship, LHS, RHS, LHSType, RHSType);
	}
	else if (LHSType == EntityType::WILD) {
		return StmtStmtRelationshipEvaluator::getRelationshipByUnderscore(relationship, RHS, RHSType);
	}
	else {
		QueryClauseResult emptyQueryResult;
		return emptyQueryResult;
	}
}

QueryClauseResult StmtStmtRelationshipEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult StmtStmtRelationshipEvaluator::getRelationshipByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Follows(1, 2)
		if (PKB::isRelationship(relationship, std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Follows(1, s)
		if (PKB::isFirstEntity(relationship, std::stoi(LHS))) {
			std::unordered_set<int> statements = PKB::getSecondEntities(relationship, std::stoi(LHS));
			queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, RHSType));
		}
	}
	else if (RHSType == EntityType::WILD) { // Follows(1, _)
		if (PKB::isFirstEntity(relationship, std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
	}
	
	return queryResult;
}

QueryClauseResult StmtStmtRelationshipEvaluator::getRelationshipByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType) {
	QueryClauseResult queryResult;

	if ((relationship == RelationRef::PARENT && LHSType == EntityType::READ) ||
		(relationship == RelationRef::PARENT && LHSType == EntityType::PRINT) ||
		(relationship == RelationRef::PARENT && LHSType == EntityType::ASSIGN) ||
		(relationship == RelationRef::PARENT && LHSType == EntityType::CALL) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::READ) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::PRINT) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::ASSIGN) ||
		(relationship == RelationRef::PARENT_T && LHSType == EntityType::CALL)) {
		return queryResult;
	}
	else if (RHSType == EntityType::INT) { // Follows(s, 2)
		if (PKB::isSecondEntity(relationship, std::stoi(RHS))) {
			std::unordered_set<int> statements = PKB::getFirstEntities(relationship, std::stoi(RHS));
			queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, LHSType));
		}
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Follows(s1, s2)
		auto [firstEntities, secondEntities] = PKB::getAllRelationshipPairs(relationship);
		auto [filteredFirst, filteredSecond] = StmtStmtRelationshipEvaluator::filterStatementPairsByType(firstEntities, secondEntities, LHSType, RHSType);
		queryResult.addColumn(LHS, filteredFirst);
		queryResult.addColumn(RHS, filteredSecond);
	}
	else if (RHSType == EntityType::WILD) { // Follows(s, _)
		std::unordered_set<int> statements = PKB::getAllFirstEntities(relationship);
		queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, LHSType));
	}

	return queryResult;
}
QueryClauseResult StmtStmtRelationshipEvaluator::getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Follows(_, 2)
		if (PKB::isSecondEntity(relationship, std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Follows(_, s)
		std::unordered_set<int> statements = PKB::getAllSecondEntities(relationship);
		queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, RHSType));
	}
	else if (RHSType == EntityType::WILD) { // Follows(_, _)
		if (PKB::hasRelationship(relationship)) {
			queryResult.setBooleanResult(true);
		}
	}

	return queryResult;
}

std::unordered_set<int> StmtStmtRelationshipEvaluator::filterStatementsByType(std::unordered_set<int> statements, EntityType type) {
	if (type == EntityType::STMT) {
		return statements;
	}

	std::unordered_set<int> typeStatements;

	switch (type) {
	case EntityType::ASSIGN:
		for (auto kv : PKB::getAssignStatements()) {
			typeStatements.insert(kv.first);
		}
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

	return PKBUtil::unorderedSetIntersection(statements, typeStatements);
}

std::tuple<std::vector<int>, std::vector<int>> StmtStmtRelationshipEvaluator::filterStatementPairsByType(std::vector<int> firstEntities,
	std::vector<int> secondEntities, EntityType LHSType, EntityType RHSType) {
	std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> statementPairs = PKBUtil::convertVectorTupleToSetPairs(firstEntities, secondEntities);

	std::unordered_set<int> firstTypeStatements;
	std::unordered_set<int> secondTypeStatements;

	switch (LHSType) {
	case EntityType::STMT:
		for (const auto& statement : firstEntities) {
			firstTypeStatements.insert(statement);
		}
	break;
	case EntityType::ASSIGN:
		for (auto kv : PKB::getAssignStatements()) {
			firstTypeStatements.insert(kv.first);
		}
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

	std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> firstFilteredStatementPairs;
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
		for (auto kv : PKB::getAssignStatements()) {
			secondTypeStatements.insert(kv.first);
		}
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

	std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> secondFilteredStatementPairs;
	for (const auto& statement : secondTypeStatements) {
		for (const auto& pair : firstFilteredStatementPairs) {
			if (pair.second == statement) {
				secondFilteredStatementPairs.insert(pair);
			}
		}
	}

	return PKBUtil::convertSetPairsToVectorTuple(secondFilteredStatementPairs);
}