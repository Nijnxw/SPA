#include "StatementOnlyRelationshipEvaluator.h"

QueryClauseTable StatementOnlyRelationshipEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	switch (LHSType) {
	case EntityType::INT:
		return StatementOnlyRelationshipEvaluator::getRelationshipByStatementNumber(relationship, LHS, RHS, RHSType);
	case EntityType::STMT:
		return StatementOnlyRelationshipEvaluator::getRelationshipByStatementVariable(relationship, LHS, RHS, RHSType);
	case EntityType::WILD:
		return StatementOnlyRelationshipEvaluator::getRelationshipByUnderscore(relationship, RHS, RHSType);
	default:
		QueryClauseTable emptyQueryResult;
		return emptyQueryResult;
	}
}

QueryClauseTable StatementOnlyRelationshipEvaluator::getRelationshipByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(1, 2) 
		if (PKB::isRelationship(relationship, std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(1, s)
		if (PKB::isFirstEntity(relationship, std::stoi(LHS))) {
			queryResult.addColumn(RHS, PKB::getSecondEntities(relationship, std::stoi(LHS)));
		}
		break;
	case EntityType::WILD: // Follows(1, _)
		if (PKB::isFirstEntity(relationship, std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable StatementOnlyRelationshipEvaluator::getRelationshipByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(s, 2)
		if (PKB::isSecondEntity(relationship, std::stoi(RHS))) {
			queryResult.addColumn(LHS, PKB::getFirstEntities(relationship, std::stoi(RHS)));
		}
		break;
	case EntityType::STMT: // Follows(s1, s2)
	{ // Curly brackets here to prevent error scoping C2360 from autotester.exe
		auto [firstEntities, secondEntities] = PKB::getAllRelationshipPairs(relationship);
		queryResult.addColumn(LHS, firstEntities);
		queryResult.addColumn(RHS, secondEntities);
	}
	break;
	case EntityType::WILD: // Follows(s, _)
		queryResult.addColumn(LHS, PKB::getAllFirstEntities(relationship));
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable StatementOnlyRelationshipEvaluator::getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(_, 2)
		if (PKB::isSecondEntity(relationship, std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(_, s)
		queryResult.addColumn(RHS, PKB::getAllSecondEntities(relationship));
		break;
	case EntityType::WILD: // Follows(_, _)
		if (PKB::hasRelationship(relationship)) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}
