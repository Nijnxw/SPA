#pragma once

#include "pkb/stores/StmtStmtStore.h"

class NextStore : public StmtStmtStore {
private:
	std::vector<std::unordered_set<int>> cfg;
	std::vector<std::unordered_set<int>> reversedCfg;

	std::vector<std::unordered_set<int>> reverseCFG(const std::vector<std::unordered_set<int>>& cfg);

	bool selfPopulateRelationships();
public:
	void clear();

	/* Setters called by DE */
	bool addCFG(const std::vector<std::unordered_set<int>>& cfg);

	/* Getters */
	std::vector<std::unordered_set<int>> getCFG();
	std::vector<std::unordered_set<int>> getReversedCFG();
};
