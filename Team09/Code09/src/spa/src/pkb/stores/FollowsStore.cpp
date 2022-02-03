#include "FollowsStore.h"

std::unordered_map<int, int> FollowsStore::followerToFollowee; 
std::unordered_map<int, int> FollowsStore::followeeToFollower; 
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
	return PKBUtil::addToMapWithSet(followerToFolloweesT, follower, followee) && PKBUtil::addToMapWithSet(followeeToFollowersT, followee, follower);
}

QueryResultTable FollowsStore::getFollows(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	QueryResultTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		queryResult = getFollowsByStatementNumber(LHS, RHS, RHSType);
		break;
	case EntityType::STMT:
		queryResult = getFollowsByStatementVariable(LHS, RHS, RHSType);
		break;
	case EntityType::WILD:
		queryResult = getFollowsByUnderscore(RHS, RHSType);
		break;
	default:
		break;
	}

	return queryResult;
}

QueryResultTable FollowsStore::getFollowsByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(1, 2) 
		if (isFollows(LHS, RHS)) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(1, s)
		if (isFollower(std::stoi(LHS))) {
			queryResult.addColumn(RHS, getFollowee(LHS));
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

QueryResultTable FollowsStore::getFollowsByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(s, 2)
		if (isFollowee(std::stoi(RHS))) {
			queryResult.addColumn(LHS, getFollower(RHS));
		}
		break;
	case EntityType::STMT: // Follows(s1, s2)
		auto [followers, followees] = getAllFollows();
		queryResult.addColumn(LHS, followers);
		queryResult.addColumn(RHS, followees);
		break;
	case EntityType::WILD: // Follows(s, _)
		queryResult.addColumn(LHS, getAllFollowers());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryResultTable FollowsStore::getFollowsByUnderscore(std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows(_, 2)
		if (isFollowee(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows(_, s)
		queryResult.addColumn(LHS, getAllFollowees());
		break;
	case EntityType::WILD: // Follows(_, _)
		if (hasFollows()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryResultTable FollowsStore::getFollowsT(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	QueryResultTable queryResult;

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

QueryResultTable FollowsStore::getFollowsTByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(1, 2) 
		if (isFollowsT(LHS, RHS)) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows*(1, s)
		if (isFollowerT(std::stoi(LHS))) {
			queryResult.addColumn(RHS, getFolloweesT(LHS));
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

QueryResultTable FollowsStore::getFollowsTByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(s, 2)
		if (isFollowee(std::stoi(RHS))) {
			queryResult.addColumn(LHS, getFollowersT(RHS));
		}
		break;
	case EntityType::STMT: // Follows*(s1, s2)
		auto [followers, followees] = getAllFollowsT();
		queryResult.addColumn(LHS, followers);
		queryResult.addColumn(RHS, followees);
		break;
	case EntityType::WILD: // Follows*(s, _)
		queryResult.addColumn(LHS, getAllFollowersT());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryResultTable FollowsStore::getFollowsTByUnderscore(std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Follows*(_, 2)
		if (isFolloweeT(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Follows*(_, s)
		queryResult.addColumn(LHS, getAllFolloweesT());
		break;
	case EntityType::WILD: // Follows*(_, _)
		if (hasFollowsT()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

bool FollowsStore::isFollows(int follower, int followee) {
	if (followerToFollowee.count(follower) <= 0) {
		return false;
	}
	return followerToFollowee.at(follower) == followee;
}

bool FollowsStore::isFollowsT(int follower, int followee) {
	if (followerToFolloweesT.count(follower) <= 0) {
		return false;
	}
	std::unordered_set<int> followees = followerToFolloweesT[follower];
	return followees.count(followee) > 0;
}

bool FollowsStore::hasFollows() {
	return followerToFollowee.size() > 0;
}

bool FollowsStore::hasFollowsT() {
	return followerToFolloweesT.size() > 0;
}

bool FollowsStore::isFollowee(int followee) {
	return followeeToFollower.count(followee) > 0;
}

bool FollowsStore::isFollower(int follower) {
	return followerToFollowee.count(follower) > 0;
}

bool FollowsStore::isFollowee(int followee) {
	return followeeToFollower.count(followee) > 0;
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

std::tuple<std::vector<int>, std::vector<int>> FollowsStore::getAllFollows() {
	return PKBUtil::convertMapToVectorTuple(followerToFollowee);
}

std::tuple<std::vector<int>, std::vector<int>> FollowsStore::getAllFollowsT() {
	return PKBUtil::convertMapToVectorTuple(followerToFolloweesT);
}