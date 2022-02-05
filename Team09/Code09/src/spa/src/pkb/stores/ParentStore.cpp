#include "ParentStore.h"

ParentStore::ParentStore() {}

void ParentStore::clear() {
	parentToChildren.clear();
	childToParent.clear();
	parentPairs.clear();
	parentTPairs.clear();
	parentToChildrenT.clear();
	childToParentsT.clear();
}

bool ParentStore::addParent(int parent, int child) {
	std::pair<int, int> pair;
	pair = std::make_pair(parent, child);
	return parentPairs.insert(pair).second && PKBUtil::addToMapWithSet(parentToChildren, parent, child) && childToParent.insert({child, parent}).second;
}

bool ParentStore::addParentT(int parent, int child) {
	std::pair<int, int> pair;
	pair = std::make_pair(parent, child);
	return parentTPairs.insert(pair).second && PKBUtil::addToMapWithSet(parentToChildrenT, parent, child) && PKBUtil::addToMapWithSet(childToParentsT, child, parent);
}

bool ParentStore::hasParentRelationship() {
	return parentToChildren.size() > 0;
}

bool ParentStore::hasParentTRelationship() {
	return parentToChildrenT.size() > 0;
}

bool ParentStore::isParentRelationship(int parent, int child) {
	if (parentToChildren.count(parent) <= 0) {
		return false;
	}
	std::unordered_set<int> children = parentToChildren[parent];
	return children.count(child) > 0;
}

bool ParentStore::isParentTRelationship(int parent, int child) {
	if (parentToChildrenT.count(parent) <= 0) {
		return false;
	}
	std::unordered_set<int> children = parentToChildrenT[parent];
	return children.count(child) > 0;
}

bool ParentStore::isParent(int parent) {
	return parentToChildren.count(parent) > 0;
}

bool ParentStore::isChild(int child) {
	return childToParent.count(child) > 0;
}

bool ParentStore::isParentT(int parent) {
	return parentToChildrenT.count(parent) > 0;
}

bool ParentStore::isChildT(int child) {
	return childToParentsT.count(child) > 0;
}

std::unordered_set<int> ParentStore::getChildren(int parent) {
	return parentToChildren[parent];
}

int ParentStore::getParent(int child) {
	return childToParent[child];
}

std::unordered_set<int> ParentStore::getAllChildren() {
	return PKBUtil::getKeySetFromMap(childToParent);
}

std::unordered_set<int> ParentStore::getAllParents() {
	return PKBUtil::getKeySetFromMap(parentToChildren);
}

std::unordered_set<int> ParentStore::getChildrenT(int parent) {
	return parentToChildrenT[parent];
}

std::unordered_set<int> ParentStore::getParentsT(int child) {
	return childToParentsT[child];
}

std::unordered_set<int> ParentStore::getAllChildrenT() {
	return PKBUtil::getKeySetFromMap(childToParentsT);
}

std::unordered_set<int> ParentStore::getAllParentsT() {
	return PKBUtil::getKeySetFromMap(parentToChildrenT);
}

std::tuple<std::vector<int>, std::vector<int>> ParentStore::getAllParentPairs() {
	return PKBUtil::convertSetPairsToVectorTuple(parentPairs);
}

std::tuple<std::vector<int>, std::vector<int>> ParentStore::getAllParentTPairs() {
	return PKBUtil::convertSetPairsToVectorTuple(parentTPairs);
}