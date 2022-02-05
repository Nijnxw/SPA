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

class ParentStore {
private:
	static inline std::unordered_map<int, std::unordered_set<int>> parentToChildren;
	static inline std::unordered_map<int, int> childToParent;
	static inline std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> parentPairs;
	static inline std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> parentTPairs;
	static inline std::unordered_map<int, std::unordered_set<int>> parentToChildrenT;
	static inline std::unordered_map<int, std::unordered_set<int>> childToParentsT;

public:
	ParentStore();

	static void clear();

	/* Setters called by SP and DE */
	static bool addParent(int parent, int child);
	static bool addParentT(int parent, int child);

	/* Getters called by QE */
	static bool hasParentRelationship();
	static bool hasParentTRelationship();

	static bool isParentRelationship(int parent, int child);
	static bool isParentTRelationship(int parent, int child);
	static bool isParent(int parent);
	static bool isChild(int child);
	static bool isParentT(int parent);
	static bool isChildT(int child);

	static std::unordered_set<int> getChildren(int parent);
	static int getParent(int child);
	static std::unordered_set<int> getAllChildren();
	static std::unordered_set<int> getAllParents();

	static std::unordered_set<int> getChildrenT(int parent);
	static std::unordered_set<int> getParentsT(int child);
	static std::unordered_set<int> getAllChildrenT();
	static std::unordered_set<int> getAllParentsT();

	static std::tuple<std::vector<int>, std::vector<int>> getAllParentPairs();
	static std::tuple<std::vector<int>, std::vector<int>> getAllParentTPairs();
};