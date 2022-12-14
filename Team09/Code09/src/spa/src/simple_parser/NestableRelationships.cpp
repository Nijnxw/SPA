#include "NestableRelationships.h"


NestableRelationships NestableRelationships::createEmpty() {
	return NestableRelationships();
}

void NestableRelationships::addUses(std::string used) {
	uses.insert(used);
}

void NestableRelationships::addModifies(std::string modified) {
	modifies.insert(modified);
}

void NestableRelationships::addCalls(std::string procedure) {
	calls.insert(procedure);
}

void NestableRelationships::addChildren(int child) {
	children.insert(child);
}

void NestableRelationships::removeChildren(std::unordered_set<int> unwantedChildren) {
	for (int unwantedChild : unwantedChildren) {
		children.erase(unwantedChild);
	}
}

std::unordered_set<std::string> NestableRelationships::getUses() {
	return uses;
}

std::unordered_set<std::string> NestableRelationships::getModifies() {
	return modifies;
}

std::unordered_set<std::string> NestableRelationships::getCalls() {
	return calls;
}

std::unordered_set<int> NestableRelationships::getChildren() {
	return children;
}

int NestableRelationships::getUsesSize() {
	return uses.size();
}

int NestableRelationships::getModifiesSize() {
	return modifies.size();
}

int NestableRelationships::getCallsSize() {
	return calls.size();
}

int NestableRelationships::getChildrenSize() {
	return children.size();
}

void NestableRelationships::combine(NestableRelationships other) {
	uses.merge(other.getUses());
	modifies.merge(other.getModifies());
	children.merge(other.getChildren());
	calls.merge(other.getCalls());
}