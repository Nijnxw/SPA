#include "DesignRelationships.h"


DesignRelationships DesignRelationships::createEmpty() {
	return DesignRelationships();
}

void DesignRelationships::addUses(std::string used) {
	uses.insert(used);
}

void DesignRelationships::addModifies(std::string modified) {
	modifies.insert(modified);
}

void DesignRelationships::addChildren(int child) {
	children.insert(child);
}

std::unordered_set<std::string> DesignRelationships::getUses() {
	return uses;
}

std::unordered_set<std::string> DesignRelationships::getModifies() {
	return modifies;
}

std::unordered_set<int> DesignRelationships::getChildren() {
	return children;
}

int DesignRelationships::getUsesSize() {
	return uses.size();
}

int DesignRelationships::getModifiesSize() {
	return modifies.size();
}

int DesignRelationships::getChildrenSize() {
	return children.size();
}

void DesignRelationships::combine(DesignRelationships other) {
	uses.merge(other.getUses());
	modifies.merge(other.getModifies());
	children.merge(other.getChildren());
}