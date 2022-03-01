#include "StmtStmtStore.h"

void StmtStmtStore::clear() {
	firstStatementToSecondStatements.clear();
	secondStatementToFirstStatement.clear();
	relationshipPairs.clear();
	relationshipTPairs.clear();
	firstStatementToSecondStatementsT.clear();
	secondStatementToFirstStatementsT.clear();
}

bool StmtStmtStore::addRelationship(int firstStatement, int secondStatement) {
	std::pair<int, int> pair;
	pair = std::make_pair(firstStatement, secondStatement);
	return relationshipPairs.insert(pair).second && PKBUtil::addToMapWithSet(firstStatementToSecondStatements, firstStatement, secondStatement) 
		&& secondStatementToFirstStatement.insert({ secondStatement, firstStatement }).second;
}

bool StmtStmtStore::addRelationshipT(int firstStatement, int secondStatement) {
	std::pair<int, int> pair;
	pair = std::make_pair(firstStatement, secondStatement);
	return relationshipTPairs.insert(pair).second && PKBUtil::addToMapWithSet(firstStatementToSecondStatementsT, firstStatement, secondStatement) 
		&& PKBUtil::addToMapWithSet(secondStatementToFirstStatementsT, secondStatement, firstStatement);
}

bool StmtStmtStore::hasRelationship() {
	return firstStatementToSecondStatements.size() > 0;
}

bool StmtStmtStore::hasTRelationship() {
	return firstStatementToSecondStatementsT.size() > 0;
}

bool StmtStmtStore::isRelationship(int firstStatement, int secondStatement) {
	if (firstStatementToSecondStatements.count(firstStatement) <= 0) {
		return false;
	}
	std::unordered_set<int> secondStatements = firstStatementToSecondStatements[firstStatement];
	return secondStatements.count(secondStatement) > 0;
}

bool StmtStmtStore::isTRelationship(int firstStatement, int secondStatement) {
	if (firstStatementToSecondStatementsT.count(firstStatement) <= 0) {
		return false;
	}
	std::unordered_set<int> secondStatements = firstStatementToSecondStatementsT[firstStatement];
	return secondStatements.count(secondStatement) > 0;
}

bool StmtStmtStore::isFirstStatement(int firstStatement) {
	return firstStatementToSecondStatements.count(firstStatement) > 0;
}

bool StmtStmtStore::isSecondStatement(int secondStatement) {
	return secondStatementToFirstStatement.count(secondStatement) > 0;
}

bool StmtStmtStore::isFirstStatementT(int firstStatement) {
	return firstStatementToSecondStatementsT.count(firstStatement) > 0;
}

bool StmtStmtStore::isSecondStatementT(int secondStatement) {
	return secondStatementToFirstStatementsT.count(secondStatement) > 0;
}

std::unordered_set<int> StmtStmtStore::getFirstStatements(int secondStatement) {
	std::unordered_set<int> result;
	result.insert(secondStatementToFirstStatement[secondStatement]);
	return result;
}

std::unordered_set<int> StmtStmtStore::getSecondStatements(int firstStatement) {
	return firstStatementToSecondStatements[firstStatement];
}

std::unordered_set<int> StmtStmtStore::getAllFirstStatements() {
	return PKBUtil::getKeySetFromMap(firstStatementToSecondStatements);
}

std::unordered_set<int> StmtStmtStore::getAllSecondStatements() {
	return PKBUtil::getKeySetFromMap(secondStatementToFirstStatement);
}

std::unordered_set<int> StmtStmtStore::getFirstStatementsT(int secondStatement) {
	return secondStatementToFirstStatementsT[secondStatement];
}

std::unordered_set<int> StmtStmtStore::getSecondStatementsT(int firstStatement) {
	return firstStatementToSecondStatementsT[firstStatement];
}

std::unordered_set<int> StmtStmtStore::getAllFirstStatementsT() {
	return PKBUtil::getKeySetFromMap(firstStatementToSecondStatementsT);
}

std::unordered_set<int> StmtStmtStore::getAllSecondStatementsT() {
	return PKBUtil::getKeySetFromMap(secondStatementToFirstStatementsT);
}

std::tuple<std::vector<int>, std::vector<int>> StmtStmtStore::getAllRelationshipPairs() {
	return PKBUtil::convertSetPairsToVectorTuple(relationshipPairs);
}

std::tuple<std::vector<int>, std::vector<int>> StmtStmtStore::getAllRelationshipTPairs() {
	return PKBUtil::convertSetPairsToVectorTuple(relationshipTPairs);
}