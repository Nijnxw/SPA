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

bool FollowsStore::isFollows(int follower, int followee) {
	if (followerToFollowee.count(follower) <= 0) {
		return false;
	}
	return followerToFollowee.at(follower) == followee;
}

bool FollowsStore::isFollowsStar(int follower, int followee) {
	if (followerToFolloweesT.count(follower) <= 0) {
		return false;
	}
	std::unordered_set<int> followees = followerToFolloweesT[follower];
	return followees.count(followee) > 0;
}

int FollowsStore::getFollowee(int follower) {
	return followerToFollowee[follower];
}

int FollowsStore::getFollower(int followee) {
	return followeeToFollower[followee];
}

std::unordered_set<int> FollowsStore::getAllFollowees(int follower) {
	return PKBUtil::getKeySetFromMap(followeeToFollower);
}

std::unordered_set<int> FollowsStore::getAllFollowers(int followee) {
	return PKBUtil::getKeySetFromMap(followerToFollowee);
}

std::unordered_set<int> FollowsStore::getFolloweesT(int follower) {
	return followerToFolloweesT[follower];
}

std::unordered_set<int> FollowsStore::getFollowersT(int followee) {
	return followeeToFollowersT[followee];
}

std::unordered_set<int> FollowsStore::getAllFolloweesT(int follower) {
	return PKBUtil::getKeySetFromMap(followeeToFollowersT);
}

std::unordered_set<int> FollowsStore::getAllFollowersT(int followee) {
	return PKBUtil::getKeySetFromMap(followerToFolloweesT);
}

QueryResultTable FollowsStore::getFollows(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	if (LHS == RHS && LHSType != EntityType::WILD) {
		// Empty table, Follows(var, var) is invalid. 
	}
}

QueryResultTable FollowsStore::getFollowsT(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{

}