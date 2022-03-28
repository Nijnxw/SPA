#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "util/PKBUtils.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"

#include "StmtStmtRelationshipEvaluator.h"

class NextEvaluator : public StmtStmtRelationshipEvaluator {
private:
	using Cache = std::unordered_map<int, std::unordered_set<int>>;

	bool isNextTCacheComplete;
	Cache nextTCache;
	Cache revNextTCache;

	QueryClauseResult getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);

	QueryClauseResult
		getNextTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseResult
		getNextTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType);
	QueryClauseResult getNextTByUnderscore(const std::string& RHS, EntityType RHSType);

	bool isNodeNotInCFG(int node, std::vector<std::unordered_set<int>>& cfg);

	bool hasNeighbours(int startNode, std::vector<std::unordered_set<int>>& cfg);
	bool isReachableFromNode(int startNode, int endNode, std::vector<std::unordered_set<int>>& cfg, bool isForwardCfg);
	std::unordered_set<int> getReachableNodes(int startNode, std::vector<std::unordered_set<int>>& cfg, bool isForwardCfg);

	std::unordered_map<int, std::unordered_set<int>> getAllNextTPairs();
	void modifiedDFS(int currNode, const std::vector<std::unordered_set<int>>& reversedCfg, std::unordered_set<int>& reachableNodes, std::unordered_map<int, std::unordered_set<int>>& nextTPairs);
public:
	NextEvaluator();

	QueryClauseResult
	getNext(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			  bool isBooleanResult);
	QueryClauseResult
	getNextT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
};
