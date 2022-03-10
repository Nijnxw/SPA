#pragma once

#include "pkb/stores/Store.h"

class NextStore : public Store {
private:
	const std::vector<std::unordered_set<int>>* cfg;

public:
	/* Getters called by QE */
	//std::unordered_set<std::string> getNext();

	/* Setters called by DE */
	bool addCFG(const std::vector<std::unordered_set<int>>* cfg);
	void clear();
};
