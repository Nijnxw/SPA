#include <ParentStore.h>

static std::unordered_set<int> parentStatements;
static std::unordered_set<int> childStatements;
static std::unordered_map<int, unordered_set<int>> parentToChildren;
static std::unordered_map<int, int> childToParent;
static std::unordered_map<int, unordered_set<int>> parentToChildrenT;
static std::unordered_map<int, unordered_set<int>> childToParentsT;

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