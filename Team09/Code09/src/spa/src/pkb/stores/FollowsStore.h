#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../models/EntityType.h"
#include "../../models/QueryClauseTable.h"
#include "../util/PKBUtil.cpp"

class FollowsStore {
private:
	static inline std::unordered_map<int, int> followerToFollowee;
	static inline std::unordered_map<int, int> followeeToFollower;
	static inline std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> followsTPairs;
	static inline std::unordered_map<int, std::unordered_set<int>> followerToFolloweesT;
	static inline std::unordered_map<int, std::unordered_set<int>> followeeToFollowersT;

	static bool hasFollowsRelationship();
	static bool hasFollowsTRelationship();

	static bool isFollowsRelationship(int follower, int followee);
	static bool isFollowsTRelationship(int follower, int followee);
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

	static std::tuple<std::vector<int>, std::vector<int>> getAllFollowsPairs();
	static std::tuple<std::vector<int>, std::vector<int>> getAllFollowsTPairs();

	static QueryClauseTable getFollowsByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsByUnderscore(const std::string& RHS, EntityType RHSType);

	static QueryClauseTable getFollowsTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getFollowsTByUnderscore(const std::string& RHS, EntityType RHSType);

public:
	FollowsStore();

	static void clear();

	/* Setters called by SP and DE */
	static bool addFollows(int follower, int followee);
	static bool addFollowsT(int follower, int followee);

	/* Getters called by QE */
	static QueryClauseTable getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryClauseTable getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
};