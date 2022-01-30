#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class FollowsStore {
private:
	static std::unordered_map<int, int> followerToFollowee;
	static std::unordered_map<int, int> followeeToFollower;
	static std::unordered_map<int, std::unordered_set<int>> followerToFolloweesT;
	static std::unordered_map<int, std::unordered_set<int>> followeeToFollowersT;

public:
	FollowsStore();

	static void clear();

	static bool addFollows(int follower, int followee);
	static bool addFollowsT(int follower, int followee);
};