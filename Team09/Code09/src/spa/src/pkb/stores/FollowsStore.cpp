#include "FollowsStore.h"

std::unordered_set<int> FollowsStore::followerStatements;
std::unordered_set<int> FollowsStore::followeeStatements;
std::unordered_map<int, int> FollowsStore::followerToFollowee;
std::unordered_map<int, int> FollowsStore::followeeToFollower;
std::unordered_map<int, std::unordered_set<int>> FollowsStore::followerToFolloweesT;
std::unordered_map<int, std::unordered_set<int>> FollowsStore::followeeToFollowersT;

FollowsStore::FollowsStore() {}

void FollowsStore::clear() {
	followerStatements.clear();
	followeeStatements.clear();
	followerToFollowee.clear();
	followeeToFollower.clear();
	followerToFolloweesT.clear();
	followeeToFollowersT.clear();
}

bool FollowsStore::addFollows(int follower, int followee) {
	return true; // TODO: Implement functionality.
}

bool FollowsStore::addFollowsT(int follower, int followee) {
	return true; // TODO: Implement functionality.
}