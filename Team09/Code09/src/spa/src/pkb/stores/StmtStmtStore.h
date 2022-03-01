#pragma once

#include "pkb/stores/Store.h"

class StmtStmtStore : public Store {
private:
	std::unordered_map<int, std::unordered_set<int>> firstStatementToSecondStatements;
	std::unordered_map<int, int> secondStatementToFirstStatement;
	std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> relationshipPairs;
	std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> relationshipTPairs;
	std::unordered_map<int, std::unordered_set<int>> firstStatementToSecondStatementsT;
	std::unordered_map<int, std::unordered_set<int>> secondStatementToFirstStatementsT;
public:
	void clear();

	/* Setters called by SP and DE */
	bool addRelationship(int firstStatement, int secondStatement);
	bool addRelationshipT(int firstStatement, int secondStatement);

	/* Getters called by QE */
	bool hasRelationship();
	bool hasTRelationship();

	bool isRelationship(int firstStatement, int secondStatement);
	bool isTRelationship(int firstStatement, int secondStatement);
	bool isFirstStatement(int firstStatement);
	bool isSecondStatement(int secondStatement);
	bool isFirstStatementT(int firstStatement);
	bool isSecondStatementT(int secondStatement);

	std::unordered_set<int> getFirstStatements(int secondStatement);
	std::unordered_set<int> getSecondStatements(int firstStatement);
	std::unordered_set<int> getAllFirstStatements();
	std::unordered_set<int> getAllSecondStatements();

	std::unordered_set<int> getFirstStatementsT(int secondStatement);
	std::unordered_set<int> getSecondStatementsT(int firstStatement);
	std::unordered_set<int> getAllFirstStatementsT();
	std::unordered_set<int> getAllSecondStatementsT();

	std::tuple<std::vector<int>, std::vector<int>> getAllRelationshipPairs();
	std::tuple<std::vector<int>, std::vector<int>> getAllRelationshipTPairs();
};