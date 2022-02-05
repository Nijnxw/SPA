#include "FollowsEvaluator.h"

QueryClauseTable FollowsEvaluator::getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	switch (LHSType) {
	case EntityType::INT:
		return getFollowsByStatementNumber(LHS, RHS, RHSType);
	case EntityType::STMT:
		return getFollowsByStatementVariable(LHS, RHS, RHSType);
	case EntityType::WILD:
		return getFollowsByUnderscore(RHS, RHSType);
	default:
		QueryClauseTable emptyQueryResult;
		return emptyQueryResult;
	}
}

QueryClauseTable FollowsEvaluator::getFollowsByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(1, 2) 
		if (PKB::isFollowsRelationship(std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(1, s)
		if (PKB::isFollower(std::stoi(LHS))) {
			std::vector<int> followee;
			followee.push_back(PKB::getFollowee(std::stoi(LHS)));
			queryResult.addColumn(RHS, followee);
		}
		break;
	case EntityType::WILD: // Follows(1, _)
		if (PKB::isFollower(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable FollowsEvaluator::getFollowsByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(s, 2)
		if (PKB::isFollowee(std::stoi(RHS))) {
			std::vector<int> follower;
			follower.push_back(PKB::getFollower(std::stoi(RHS)));
			queryResult.addColumn(LHS, follower);
		}
		break;
	case EntityType::STMT: // Follows(s1, s2)
	{ // Curly brackets here to prevent error scoping C2360 from autotester.exe
		auto [followers, followees] = PKB::getAllFollowsPairs();
		queryResult.addColumn(LHS, followers);
		queryResult.addColumn(RHS, followees);
	}
	break;
	case EntityType::WILD: // Follows(s, _)
		queryResult.addColumn(LHS, PKB::getAllFollowers());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable FollowsEvaluator::getFollowsByUnderscore(const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(_, 2)
		if (PKB::isFollowee(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(_, s)
		queryResult.addColumn(RHS, PKB::getAllFollowees());
		break;
	case EntityType::WILD: // Follows(_, _)
		if (PKB::hasFollowsRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable FollowsEvaluator::getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	QueryClauseTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		queryResult = getFollowsTByStatementNumber(LHS, RHS, RHSType);
		break;
	case EntityType::STMT:
		queryResult = getFollowsTByStatementVariable(LHS, RHS, RHSType);
		break;
	case EntityType::WILD:
		queryResult = getFollowsTByUnderscore(RHS, RHSType);
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable FollowsEvaluator::getFollowsTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(1, 2) 
		if (PKB::isFollowsTRelationship(std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows*(1, s)
		if (PKB::isFollowerT(std::stoi(LHS))) {
			queryResult.addColumn(RHS, PKB::getFolloweesT(std::stoi(LHS)));
		}
		break;
	case EntityType::WILD: // Follows*(1, _)
		if (PKB::isFollowerT(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable FollowsEvaluator::getFollowsTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(s, 2)
		if (PKB::isFollowee(std::stoi(RHS))) {
			queryResult.addColumn(LHS, PKB::getFollowersT(std::stoi(RHS)));
		}
		break;
	case EntityType::STMT: // Follows*(s1, s2)
	{ // Curly brackets here to prevent error scoping C2360 from autotester.exe
		auto [followers, followees] = PKB::getAllFollowsTPairs();
		queryResult.addColumn(LHS, followers);
		queryResult.addColumn(RHS, followees);
	}
	break;
	case EntityType::WILD: // Follows*(s, _)
		queryResult.addColumn(LHS, PKB::getAllFollowersT());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable FollowsEvaluator::getFollowsTByUnderscore(const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(_, 2)
		if (PKB::isFolloweeT(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows*(_, s)
		queryResult.addColumn(RHS, PKB::getAllFolloweesT());
		break;
	case EntityType::WILD: // Follows*(_, _)
		if (PKB::hasFollowsTRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}