#include "FollowsStore.h"

std::unordered_map<int, int> FollowsStore::followerToFollowee; 
std::unordered_map<int, int> FollowsStore::followeeToFollower; 
std::unordered_map<int, int> FollowsStore::followsTPairs;
std::unordered_map<int, std::unordered_set<int>> FollowsStore::followerToFolloweesT; 
std::unordered_map<int, std::unordered_set<int>> FollowsStore::followeeToFollowersT;

FollowsStore::FollowsStore() {}

void FollowsStore::clear() {
	followerToFollowee.clear();
	followeeToFollower.clear();
	followerToFolloweesT.clear();
	followeeToFollowersT.clear();
}

bool FollowsStore::addFollows(int follower, int followee) {
	return followerToFollowee.insert({ follower, followee }).second && followeeToFollower.insert({ followee, follower }).second;
}

bool FollowsStore::addFollowsT(int follower, int followee) {
	return followsTPairs.insert({ follower, followee }).second && PKBUtil::addToMapWithSet(followerToFolloweesT, follower, followee) && PKBUtil::addToMapWithSet(followeeToFollowersT, followee, follower);
}

QueryClauseTable FollowsStore::getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
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

QueryClauseTable FollowsStore::getFollowsByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(1, 2) 
		if (isFollowsRelationship(std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(1, s)
		if (isFollower(std::stoi(LHS))) {
			std::vector<int> followee;
			followee.push_back(getFollowee(std::stoi(LHS)));
			queryResult.addColumn(RHS, followee);
		}
		break;
	case EntityType::WILD: // Follows(1, _)
		if (isFollower(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable FollowsStore::getFollowsByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(s, 2)
		if (isFollowee(std::stoi(RHS))) {
			std::vector<int> follower;
			follower.push_back(getFollower(std::stoi(RHS)));
			queryResult.addColumn(LHS, follower);
		}
		break;
	case EntityType::STMT: // Follows(s1, s2)
	{ // Curly brackets here to prevent error scoping C2360 from autotester.exe
		auto [followers, followees] = getAllFollowsPairs();
		queryResult.addColumn(LHS, followers);
		queryResult.addColumn(RHS, followees);
	}
		break;
	case EntityType::WILD: // Follows(s, _)
		queryResult.addColumn(LHS, getAllFollowers());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable FollowsStore::getFollowsByUnderscore(const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(_, 2)
		if (isFollowee(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(_, s)
		queryResult.addColumn(RHS, getAllFollowees());
		break;
	case EntityType::WILD: // Follows(_, _)
		if (hasFollowsRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable FollowsStore::getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
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

QueryClauseTable FollowsStore::getFollowsTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(1, 2) 
		if (isFollowsTRelationship(std::stoi(LHS), std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows*(1, s)
		if (isFollowerT(std::stoi(LHS))) {
			queryResult.addColumn(RHS, getFolloweesT(std::stoi(LHS)));
		}
		break;
	case EntityType::WILD: // Follows*(1, _)
		if (isFollowerT(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable FollowsStore::getFollowsTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(s, 2)
		if (isFollowee(std::stoi(RHS))) {
			queryResult.addColumn(LHS, getFollowersT(std::stoi(RHS)));
		}
		break;
	case EntityType::STMT: // Follows*(s1, s2)
	{ // Curly brackets here to prevent error scoping C2360 from autotester.exe
		auto [followers, followees] = getAllFollowsTPairs();
		queryResult.addColumn(LHS, followers);
		queryResult.addColumn(RHS, followees);
	}
		break;
	case EntityType::WILD: // Follows*(s, _)
		queryResult.addColumn(LHS, getAllFollowersT());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable FollowsStore::getFollowsTByUnderscore(const std::string& RHS, EntityType RHSType) {
	QueryClauseTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(_, 2)
		if (isFolloweeT(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows*(_, s)
		queryResult.addColumn(RHS, getAllFolloweesT());
		break;
	case EntityType::WILD: // Follows*(_, _)
		if (hasFollowsTRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

bool FollowsStore::hasFollowsRelationship() {
	return followerToFollowee.size() > 0;
}

bool FollowsStore::hasFollowsTRelationship() {
	return followerToFolloweesT.size() > 0;
}

bool FollowsStore::isFollowsRelationship(int follower, int followee) {
	if (followerToFollowee.count(follower) <= 0) {
		return false;
	}
	return followerToFollowee.at(follower) == followee;
}

bool FollowsStore::isFollowsTRelationship(int follower, int followee) {
	if (followerToFolloweesT.count(follower) <= 0) {
		return false;
	}
	std::unordered_set<int> followees = followerToFolloweesT[follower];
	return followees.count(followee) > 0;
}

bool FollowsStore::isFollowee(int followee) {
	return followeeToFollower.count(followee) > 0;
}

bool FollowsStore::isFollower(int follower) {
	return followerToFollowee.count(follower) > 0;
}

bool FollowsStore::isFollowerT(int follower) {
	return followerToFolloweesT.count(follower) > 0;
}

bool FollowsStore::isFolloweeT(int followee) {
	return followeeToFollowersT.count(followee) > 0;
}

int FollowsStore::getFollowee(int follower) {
	return followerToFollowee[follower];
}

int FollowsStore::getFollower(int followee) {
	return followeeToFollower[followee];
}

std::unordered_set<int> FollowsStore::getAllFollowees() {
	return PKBUtil::getKeySetFromMap(followeeToFollower);
}

std::unordered_set<int> FollowsStore::getAllFollowers() {
	return PKBUtil::getKeySetFromMap(followerToFollowee);
}

std::unordered_set<int> FollowsStore::getFolloweesT(int follower) {
	return followerToFolloweesT[follower];
}

std::unordered_set<int> FollowsStore::getFollowersT(int followee) {
	return followeeToFollowersT[followee];
}

std::unordered_set<int> FollowsStore::getAllFolloweesT() {
	return PKBUtil::getKeySetFromMap(followeeToFollowersT);
}

std::unordered_set<int> FollowsStore::getAllFollowersT() {
	return PKBUtil::getKeySetFromMap(followerToFolloweesT);
}

std::tuple<std::vector<int>, std::vector<int>> FollowsStore::getAllFollowsPairs() {
	return PKBUtil::convertMapToVectorTuple(followerToFollowee);
}

std::tuple<std::vector<int>, std::vector<int>> FollowsStore::getAllFollowsTPairs() {
	return PKBUtil::convertMapToVectorTuple(followsTPairs);
}