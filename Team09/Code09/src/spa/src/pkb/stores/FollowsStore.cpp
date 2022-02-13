#include "FollowsStore.h"

FollowsStore::FollowsStore() {}

void FollowsStore::clear() {
	followerToFollowee.clear();
	followeeToFollower.clear();
	followsTPairs.clear();
	followerToFolloweesT.clear();
	followeeToFollowersT.clear();
}

bool FollowsStore::addFollows(int follower, int followee) {
	return followerToFollowee.insert({ follower, followee }).second && followeeToFollower.insert({ followee, follower }).second;
}

bool FollowsStore::addFollowsT(int follower, int followee) {
	std::pair<int, int> pair;
	pair = std::make_pair(follower, followee);
	return followsTPairs.insert(pair).second && PKBUtil::addToMapWithSet(followerToFolloweesT, follower, followee) && PKBUtil::addToMapWithSet(followeeToFollowersT, followee, follower);
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

std::unordered_set<int> FollowsStore::getFollowee(int follower) {
	std::unordered_set<int> result;
	result.insert(followerToFollowee[follower]);
	return result;
}

std::unordered_set<int> FollowsStore::getFollower(int followee) {
	std::unordered_set<int> result;
	result.insert(followeeToFollower[followee]);
	return result;
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
	return PKBUtil::convertSetPairsToVectorTuple(followsTPairs);
}