#include "ParentEvaluator.h"

QueryClauseTable ParentEvaluator::getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	switch (LHSType) {
	case EntityType::INT:
		return getParentByStatementNumber(LHS, RHS, RHSType);
	case EntityType::STMT:
		return getParentByStatementVariable(LHS, RHS, RHSType);
	case EntityType::WILD:
		return getParentByUnderscore(RHS, RHSType);
	default:
		QueryClauseTable emptyQueryResult;
		return emptyQueryResult;
	}
}

QueryClauseTable ParentEvaluator::getParentByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent(1, 2) 
		if (PKB::isParentRelationship(std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent(1, s)
		if (PKB::isParent(std::stoi(LHS))) {
			queryResult.addColumn(RHS, PKB::getChildren(std::stoi(LHS)));
		}
		break;
	case EntityType::WILD: // Parent(1, _)
		if (PKB::isParent(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable ParentEvaluator::getParentByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent(s, 2)
		if (PKB::isChild(std::stoi(RHS))) {
			std::vector<int> parent;
			parent.push_back(PKB::getParent(std::stoi(RHS)));
			queryResult.addColumn(LHS, parent);
		}
		break;
	case EntityType::STMT: // Parent(s1, s2)
	{ // Curly brackets here to prevent error scoping C2360 from autotester.exe
		auto [parents, children] = PKB::getAllParentPairs();
		queryResult.addColumn(LHS, parents);
		queryResult.addColumn(RHS, children);
	}
	break;
	case EntityType::WILD: // Parent(s, _)
		queryResult.addColumn(LHS, PKB::getAllParents());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable ParentEvaluator::getParentByUnderscore(const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent(_, 2)
		if (PKB::isChild(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent(_, s)
		queryResult.addColumn(RHS, PKB::getAllChildren());
		break;
	case EntityType::WILD: // Parent(_, _)
		if (PKB::hasParentRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable ParentEvaluator::getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	QueryClauseTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		queryResult = getParentTByStatementNumber(LHS, RHS, RHSType);
		break;
	case EntityType::STMT:
		queryResult = getParentTByStatementVariable(LHS, RHS, RHSType);
		break;
	case EntityType::WILD:
		queryResult = getParentTByUnderscore(RHS, RHSType);
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable ParentEvaluator::getParentTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent*(1, 2) 
		if (PKB::isParentTRelationship(std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent*(1, s)
		if (PKB::isParentT(std::stoi(LHS))) {
			queryResult.addColumn(RHS, PKB::getChildrenT(std::stoi(LHS)));
		}
		break;
	case EntityType::WILD: // Parent*(1, _)
		if (PKB::isParentT(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable ParentEvaluator::getParentTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent*(s, 2)
		if (PKB::isChildT(std::stoi(RHS))) {
			queryResult.addColumn(LHS, PKB::getParentsT(std::stoi(RHS)));
		}
		break;
	case EntityType::STMT: // Parent*(s1, s2)
	{ // Curly brackets here to prevent error scoping C2360 from autotester.exe
		auto [parents, children] = PKB::getAllParentTPairs();
		queryResult.addColumn(LHS, parents);
		queryResult.addColumn(RHS, children);
	}
	break;
	case EntityType::WILD: // Parent*(s, _)
		queryResult.addColumn(LHS, PKB::getAllParentsT());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable ParentEvaluator::getParentTByUnderscore(const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent*(_, 2)
		if (PKB::isChildT(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent*(_, s)
		queryResult.addColumn(RHS, PKB::getAllChildrenT());
		break;
	case EntityType::WILD: // Parent*(_, _)
		if (PKB::hasParentTRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}