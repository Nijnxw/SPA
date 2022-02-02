#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "pkb/util/PKBUtil.cpp"
#include <models/QueryResultTable.h>
#include <models/EntityType.h>

class FollowsStore {
private:
	static std::unordered_map<int, int> followerToFollowee;
	static std::unordered_map<int, int> followeeToFollower;
	static std::unordered_map<int, std::unordered_set<int>> followerToFolloweesT;
	static std::unordered_map<int, std::unordered_set<int>> followeeToFollowersT;

	static bool isFollows(int follower, int followee);
	static bool isFollowsStar(int follower, int followee);

	static int getFollowee(int follower);
	static int getFollower(int followee);
	static std::unordered_set<int> getAllFollowees(int follower);
	static std::unordered_set<int> getAllFollowers(int followee);

	static std::unordered_set<int> getFolloweesT(int follower);
	static std::unordered_set<int> getFollowersT(int followee);
	static std::unordered_set<int> getAllFolloweesT(int follower);
	static std::unordered_set<int> getAllFollowersT(int followee);

public:
	FollowsStore();

	static void clear();

	// Called by SP and DE
	static bool addFollows(int follower, int followee);
	static bool addFollowsT(int follower, int followee);

	// Called by QE
	static QueryResultTable getFollows(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryResultTable getFollowsT(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
};