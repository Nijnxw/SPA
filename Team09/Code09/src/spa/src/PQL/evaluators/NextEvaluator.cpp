#include "NextEvaluator.h"

NextEvaluator::NextEvaluator()
	: StmtStmtRelationshipEvaluator() {
	isNextTCacheComplete = false;
}

QueryClauseResult NextEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
NextEvaluator::getNext(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return NextEvaluator::getRelationship(RelationRef::NEXT, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
NextEvaluator::getNextT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	QueryClauseResult emptyQueryResult;

	if (LHSType == EntityType::INT) {
		return NextEvaluator::getNextTByStatementNumber(LHS, RHS, RHSType, isBooleanResult);
	}
	else if (LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN || LHSType == EntityType::IF ||
		LHSType == EntityType::WHILE || LHSType == EntityType::PRINT || LHSType == EntityType::READ ||
		LHSType == EntityType::CALL) {
		return NextEvaluator::getNextTByStatementVariable(LHS, RHS, LHSType, RHSType, isBooleanResult);
	}
	else if (LHSType == EntityType::WILD) {
		return NextEvaluator::getNextTByUnderscore(RHS, RHSType, isBooleanResult);
	}
	else {
		return emptyQueryResult;
	}
}

QueryClauseResult NextEvaluator::getNextTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType, bool isBooleanResult) {
	QueryClauseResult queryResult;
	std::vector<std::unordered_set<int>> cfg = PKB::getCFG();

	int LHSInt = std::stoi(LHS);

	if (isNodeNotInCFG(LHSInt, cfg)) {
		return queryResult;
	}

	if (RHSType == EntityType::INT) { // Next*(1, 2)
		int RHSInt = std::stoi(RHS);

		if (isNodeNotInCFG(RHSInt, cfg)) {
			return queryResult;
		}

		if (nextTCache.count(LHSInt) > 0) {
			if (nextTCache.at(LHSInt).count(RHSInt) > 0) {
				queryResult.setBooleanResult(true);
			}
		} else {
			queryResult.setBooleanResult(isReachableFromNode(LHSInt, RHSInt, cfg, true));
		}
	} else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Next*(1, s)
		if (isNextTCacheComplete) {
			queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(nextTCache[LHSInt], RHSType, isBooleanResult));
		}
		else {
			if (isBooleanResult) {
				queryResult.setBooleanResult(hasNeighbours(LHSInt, cfg));
			}
			else {
				std::unordered_set<int> reachableNodes = getReachableNodes(LHSInt, cfg, true);

				if (reachableNodes.size() <= 0) {
					return queryResult;
				}

				queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(reachableNodes, RHSType, isBooleanResult));
			}
		}
	} else if (RHSType == EntityType::WILD) { // Next*(1, _)
		queryResult.setBooleanResult(hasNeighbours(LHSInt, cfg));
	}

	return queryResult;
}

QueryClauseResult NextEvaluator::getNextTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Next*(s, 2)
		std::vector<std::unordered_set<int>> cfg = PKB::getCFG();

		int RHSInt = std::stoi(RHS);

		if (isNodeNotInCFG(RHSInt, cfg)) {
			return queryResult;
		}

		if (isNextTCacheComplete) {
			queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(nextTCache[RHSInt], LHSType, isBooleanResult));
		}
		else {
			std::vector<std::unordered_set<int>> reversedCfg = PKB::getReversedCFG();

			if (isBooleanResult) {
				queryResult.setBooleanResult(hasNeighbours(RHSInt, reversedCfg));
			}
			else {
				std::unordered_set<int> reachableNodes = getReachableNodes(RHSInt, reversedCfg, false);
				queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(reachableNodes, LHSType, isBooleanResult));
			}
		}
	} else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Next*(s1, s2)
		std::unordered_map<int, std::unordered_set<int>> nextTPairs;

		if (isNextTCacheComplete) {
			nextTPairs = nextTCache;
		} else {
			nextTPairs = getAllNextTPairs();
		}

		auto [firstEntities, secondEntities] = PKBUtils::convertMapWithSetToVectorTuple(nextTPairs);
		auto [filteredFirst, filteredSecond] = StmtStmtRelationshipEvaluator::filterStatementPairsByType(firstEntities, secondEntities, LHSType, RHSType, isBooleanResult);

		if (LHS == RHS) {
			std::unordered_set<int> set = PKBUtils::getEqualPairs(filteredFirst, filteredSecond);
			queryResult.addColumn(LHS, set);
		}
		else {
			queryResult.addColumn(LHS, filteredFirst);
			queryResult.addColumn(RHS, filteredSecond);
		}
	} else if (RHSType == EntityType::WILD) { // Next*(s, _)
		std::unordered_set<int> statements = PKB::getAllStmtStmtFirstEntities(RelationRef::NEXT);
		queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, LHSType, isBooleanResult));
	}

	return queryResult;
}
QueryClauseResult NextEvaluator::getNextTByUnderscore(const std::string& RHS, EntityType RHSType, bool isBooleanResult) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Next*(_, 2)
		std::vector<std::unordered_set<int>> cfg = PKB::getCFG();

		int RHSInt = std::stoi(RHS);

		if (isNodeNotInCFG(RHSInt, cfg)) {
			return queryResult;
		}

		std::vector<std::unordered_set<int>> reversedCfg = PKB::getReversedCFG();

		queryResult.setBooleanResult(hasNeighbours(RHSInt, reversedCfg));
	} else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Next*(_, s)
		std::unordered_set<int> statements = PKB::getAllStmtStmtSecondEntities(RelationRef::NEXT);
		queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, RHSType, isBooleanResult));
	} else if (RHSType == EntityType::WILD) { // Next*(_, _)
		if (PKB::hasNextRelationship()) {
			queryResult.setBooleanResult(true);
		}
	}

	return queryResult;
}

bool NextEvaluator::isNodeNotInCFG(int node, std::vector<std::unordered_set<int>>& cfg) {
	return node < 1 || node > cfg.size() - 1;
}

bool NextEvaluator::hasNeighbours(int startNode, std::vector<std::unordered_set<int>>& cfg) {
	return cfg.at(startNode).size() > 0;
}

bool NextEvaluator::isReachableFromNode(int startNode, int endNode, std::vector<std::unordered_set<int>>& cfg, bool isForwardCfg) {
	int numNodes = cfg.size();
	bool* visited = new bool[numNodes];

	// Take note that index 0 is never used.
	for (int i = 0; i < numNodes; i++) {
		visited[i] = false;
	}

	std::list<int> queue;
	queue.push_back(startNode);

	while (!queue.empty()) {
		int currNode = queue.front();
		queue.pop_front();

		for (const auto& neighbour : cfg.at(currNode)) {
			
			if (isForwardCfg) {
				nextTCache[currNode].emplace(neighbour);
			} else {
				revNextTCache[currNode].emplace(neighbour);
			}

			if (neighbour == endNode) {
				return true;
			}

			if (!visited[neighbour]) {
				visited[neighbour] = true;
				queue.push_back(neighbour);
			}
		}
	}

	return false;
}

std::unordered_set<int> NextEvaluator::getReachableNodes(int startNode, std::vector<std::unordered_set<int>>& cfg, bool isForwardCfg) {
	int numNodes = cfg.size();
	bool* visited = new bool[numNodes];

	// Take note that index 0 is never used.
	for (int i = 0; i < numNodes; i++) {
		visited[i] = false;
	}

	std::list<int> queue;
	queue.push_back(startNode);

	std::unordered_set<int> reachableNodes;

	while (!queue.empty()) {
		int currNode = queue.front();
		queue.pop_front();

		for (const auto& neighbour : cfg.at(currNode)) {
			if (isForwardCfg) {
				nextTCache[currNode].emplace(neighbour);
			} else {
				revNextTCache[currNode].emplace(neighbour);
			}

			if (!visited[neighbour]) {
				visited[neighbour] = true;
				queue.push_back(neighbour);
				reachableNodes.insert(neighbour);
			}
		}
	}

	return reachableNodes;
}

std::unordered_map<int, std::unordered_set<int>> NextEvaluator::getAllNextTPairs() {
	std::unordered_map<std::string, std::unordered_set<int>> procToLastNodes = PKB::getProcedureNameToLastCFGNode();
	std::vector<std::unordered_set<int>> reversedCfg = PKB::getReversedCFG();

	std::unordered_map<int, std::unordered_set<int>> nextTPairs;

	for (const auto& pair : procToLastNodes) {
		std::unordered_set<int> lastNodes = pair.second;
		for (const auto& lastNode : lastNodes) {
			std::unordered_set<int> reachableNodes;
			modifiedDFS(lastNode, reversedCfg, reachableNodes, nextTPairs);
		}
	}

	isNextTCacheComplete = true;

	return nextTPairs;
}

void NextEvaluator::modifiedDFS(int currNode, const std::vector<std::unordered_set<int>>& reversedCfg, std::unordered_set<int>& reachableNodes, std::unordered_map<int, std::unordered_set<int>>& nextTPairs) {
	int numPairs;
	if (nextTPairs.count(currNode) <= 0) {
		numPairs = 0;
	} else {
		numPairs = nextTPairs[currNode].size();
	}
	
	for (const auto& reachableNode : reachableNodes) {
		nextTCache[currNode].emplace(reachableNode);
		revNextTCache[reachableNode].emplace(currNode);
		PKBUtils::addToMapWithSet(nextTPairs, currNode, reachableNode);
	}

	if (nextTPairs.count(currNode) > 0) {
		if (nextTPairs[currNode].size() == numPairs) {
			if (!reachableNodes.empty()) {
				return;
			}
		}
	}

	for (const auto& neighbour : reversedCfg.at(currNode)) {
		std::unordered_set<int> nextReachableNodes = reachableNodes;
		nextReachableNodes.insert(currNode);
		modifiedDFS(neighbour, reversedCfg, nextReachableNodes, nextTPairs);
	}
}