#include "NextStore.h"

// ============ GETTER METHODS ==============



// ============ STORE METHODS ==============

bool NextStore::addCFG(const std::vector<std::unordered_set<int>>* cfg) {
	this->cfg = cfg;
	return true;
}

// ============ OTHER METHODS ==============

void NextStore::clear() {
	this->cfg = NULL;
}