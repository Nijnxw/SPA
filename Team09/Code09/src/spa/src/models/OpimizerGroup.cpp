#include "OpimizerGroup.h"

OptimizerGroup::OptimizerGroup() = default;

OptimizerGroup::OptimizerGroup(std::vector<OptimizerClause>& clauses) : clauses(clauses) {
	totalWeight = 0;
	for (const auto& clause: clauses) {
		totalWeight += clause.getWeight();
	}
}

bool OptimizerGroup::addClause(OptimizerClause& clause) {
	totalWeight += clause.getWeight();
	clauses.push_back(clause);
	QueryClause queryClause = clause.getClause();
	std::unordered_set<std::string> usedSynonyms = queryClause.getUsedSynonyms();
	synonyms.insert(usedSynonyms.begin(), usedSynonyms.end());
	return true;
}

bool OptimizerGroup::operator<(OptimizerGroup& other) {
	size_t numClauses = clauses.size();
	size_t otherNumClauses = other.clauses.size();
	if (numClauses == otherNumClauses) {
		return totalWeight < other.totalWeight;
	}
	return numClauses < otherNumClauses;
}

std::vector<OptimizerClause> OptimizerGroup::getClauses() {
	std::sort(clauses.begin(), clauses.end());
	return {clauses.begin(), clauses.end()};
}

bool OptimizerGroup::containsSynonym(std::string& synonym) const {
	return synonyms.count(synonym) != 0;
}

bool OptimizerGroup::containsAnySynonyms(std::unordered_set<std::string> ls) const {
	for (const auto& synonym: ls) {
		if (synonyms.count(synonym) != 0) {
			return true;
		}
	}
	return false;
}


