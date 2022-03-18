#include "NextStore.h"

/*
Source
1 x = x + 1;
2 while (y = true) {
3	y = y + 1;
4	if (z = false) then {
5		z = z + 1;
	}
	else {
6		z = z - 1;
	}}
CFG, vector is 1-indexed
1 -> {2}
2 -> {3}
3 -> {4}
4 -> {5,6}
5 -> {2}
6 -> {2}
Reverse CFG, vector is 1-indexed
1 -> {}
2 -> {1, 5, 6}
3 -> {2}
4 -> {3}
5 -> {4}
6 -> {4}
*/

void NextStore::clear() {
	StmtStmtStore::clear();
	this->cfg.clear();
	this->reversedCfg.clear();
	this->procedureNameToLastCFGNodes.clear();
}

bool NextStore::addCFG(const std::vector<std::unordered_set<int>>& cfg) {
	this->cfg = cfg;
	this->reversedCfg = reverseCFG(cfg);
	return selfPopulateRelationships();
}

bool NextStore::addProcedureNameToLastCFGNode(const std::string procedure, const std::unordered_set<int> lastNodes) {
	return this->procedureNameToLastCFGNodes.insert({ procedure, lastNodes }).second;
}

std::vector<std::unordered_set<int>> NextStore::getCFG() {
	return cfg;
}

std::vector<std::unordered_set<int>> NextStore::getReversedCFG() {
	return reversedCfg;
}

std::unordered_map<std::string, std::unordered_set<int>> NextStore::getProcedureNameToLastCFGNode() {
	return procedureNameToLastCFGNodes;
}

std::vector<std::unordered_set<int>> NextStore::reverseCFG(const std::vector<std::unordered_set<int>>& cfg) {
	std::vector<std::unordered_set<int>> reversedCfg;

	// Populating indices with empty sets
	for (int statementNum = 0; statementNum < cfg.size(); statementNum++) {
		std::unordered_set<int> set;
		reversedCfg.push_back(set);
	}

	// For each next node, map next node as indice -> statementNum in the set
	for (int statementNum = 1; statementNum < cfg.size(); statementNum++) {
		for (const auto& nextNode : cfg[statementNum]) {
			reversedCfg[nextNode].insert(statementNum);
		}
	}

	return reversedCfg;
}

/* For each statement number, we add all the possible Next nodes in its unordered set. */
bool NextStore::selfPopulateRelationships() {
	for (int statementNum = 1; statementNum < cfg.size(); statementNum++) {
		for (const auto& nextNode : cfg[statementNum]) {
			StmtStmtStore::addRelationship(statementNum, nextNode);
		}
	}

	return true;
}
