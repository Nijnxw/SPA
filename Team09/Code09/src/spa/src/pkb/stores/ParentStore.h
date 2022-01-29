#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class ParentStore {
private:
	static std::unordered_set<int> parentStatements;
	static std::unordered_set<int> childStatements;
	static std::unordered_map<int, unordered_set<int>> parentToChildren;
	static std::unordered_map<int, int> childToParent;
	static std::unordered_map<int, unordered_set<int>> parentToChildrenT;
	static std::unordered_map<int, unordered_set<int>> childToParentsT;

public: 
	ParentStore();

	static void clear();

	static bool addParent(int parent, int child);
	static bool addParentT(int parent, int child);
}