#include "ParentStore.h"

std::unordered_set<int> parentStatements;
std::unordered_set<int> childStatements;
std::unordered_map<int, std::unordered_set<int>> parentToChildren;
std::unordered_map<int, int> childToParent;
std::unordered_map<int, std::unordered_set<int>> parentToChildrenT;
std::unordered_map<int, std::unordered_set<int>> childToParentsT;

ParentStore::ParentStore() {}

void ParentStore::clear() {
	parentStatements.clear();
	childStatements.clear();
	parentToChildren.clear();
	childToParent.clear();
	parentToChildrenT.clear();
	childToParentsT.clear();
}

bool ParentStore::addParent(int parent, int child) {
	return true; // TODO: Implement functionality.
}

bool ParentStore::addParentT(int parent, int child) {
	return true; // TODO: Implement functionality.
}