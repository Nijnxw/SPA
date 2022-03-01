#pragma once

#include <vector>
#include <unordered_set>
#include "OptimizerClause.h"

class OptimizerGroup {
public:
	OptimizerGroup();
	OptimizerGroup(std::vector<OptimizerClause>& clauses);

	bool addClause(OptimizerClause& clause);
	bool operator<(OptimizerGroup& other);
	std::vector<OptimizerClause> getClauses();
	bool containsSynonym(std::string& synonym) const;
	bool containsAnySynonyms(std::unordered_set<std::string> ls) const;

private:
	int totalWeight;
	std::vector<OptimizerClause> clauses;
	std::unordered_set<std::string> synonyms;
};