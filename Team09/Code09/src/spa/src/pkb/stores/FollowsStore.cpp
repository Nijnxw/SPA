#include <FollowsStore.h>

static std::unordered_set<int> FollowsStore::followerStatements;
static std::unordered_set<int> FollowsStore::followeeStatements;
static std::unordered_map<int, int> FollowsStore::followerToFollowee;
static std::unordered_map<int, int> FollowsStore::followeeToFollower;
static std::unordered_map<int, std::unordered_set<int>> FollowsStore::followerToFolloweesT;
static std::unordered_map<int, std::unordered_set<int>> FollowsStore::followeeToFollowersT;

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