#include "DesignRelationships.h"

DesignRelationships::DesignRelationships() {
	uses = std::unordered_set<std::string>{};
	modifies = std::unordered_set<std::string>{};
}


DesignRelationships DesignRelationships::createEmpty() {
	return DesignRelationships();
}

void DesignRelationships::addUses(std::string used) {
	uses.insert(used);
}

void DesignRelationships::addModifies(std::string modified) {
	modifies.insert(modified);
}

std::unordered_set<std::string> DesignRelationships::getUses() {
	return uses;
}

std::unordered_set<std::string> DesignRelationships::getModifies() {
	return modifies;
}

int DesignRelationships::getUsesSize() {
	return uses.size();
}

int DesignRelationships::getModifiesSize() {
	return modifies.size();
}

void DesignRelationships::combine(DesignRelationships other) {
	uses.merge(other.getUses());
	modifies.merge(other.getModifies());
}