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

	static bool hasFollows();
	static bool hasFollowsT();

	static bool isFollows(int follower, int followee);
	static bool isFollowsT(int follower, int followee);
	static bool isFollower(int follower);
	static bool isFollowee(int followee);
	static bool isFollowerT(int follower);
	static bool isFolloweeT(int followee);

	static int getFollowee(int follower);
	static int getFollower(int followee);
	static std::unordered_set<int> getAllFollowees();
	static std::unordered_set<int> getAllFollowers();

	static std::unordered_set<int> getFolloweesT(int follower);
	static std::unordered_set<int> getFollowersT(int followee);
	static std::unordered_set<int> getAllFolloweesT();
	static std::unordered_set<int> getAllFollowersT();

	static std::tuple<std::vector<int>, std::vector<int>> FollowsStore::getAllFollows();
	static std::tuple<std::vector<int>, std::vector<int>> FollowsStore::getAllFollowsT();

	static QueryResultTable getFollowsByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getFollowsByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getFollowsByUnderscore(std::string& RHS, EntityType RHSType);

	static QueryResultTable getFollowsTByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getFollowsTByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getFollowsTByUnderscore(std::string& RHS, EntityType RHSType);

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