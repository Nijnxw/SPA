#include "NextEvaluator.h"

NextEvaluator::NextEvaluator()
	: StmtStmtRelationshipEvaluator() {}

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
		return NextEvaluator::getNextTByStatementNumber(LHS, RHS, RHSType);
	}
	else if (LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN || LHSType == EntityType::IF ||
		LHSType == EntityType::WHILE || LHSType == EntityType::PRINT || LHSType == EntityType::READ ||
		LHSType == EntityType::CALL) {
		return NextEvaluator::getNextTByStatementVariable(LHS, RHS, LHSType, RHSType);
	}
	else if (LHSType == EntityType::WILD) {
		return NextEvaluator::getNextTByUnderscore(RHS, RHSType);
	}
	else {
		return emptyQueryResult;
	}
}

QueryClauseResult NextEvaluator::getNextTByStatementNumber(const std::string& LHS, const std::string& RHS, EntityType RHSType) {
	QueryClauseResult queryResult;
	std::vector<std::unordered_set<int>> cfg = PKB::getCFG();

	int LHSInt = std::stoi(LHS);

	if (LHSInt < 1 || LHSInt > cfg.size() - 1) {
		return queryResult;
	}

	std::unordered_set<int> reachableNodes = getReachableNodes(LHSInt, cfg);

	if (reachableNodes.size() <= 0) {
		return queryResult;
	}

	if (RHSType == EntityType::INT) { // Next*(1, 2)
		int RHSInt = std::stoi(RHS);
		if (RHSInt < 1 || RHSInt > cfg.size() - 1) {
			return queryResult;
		} 
		queryResult.setBooleanResult(reachableNodes.count(RHSInt) > 0);
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Next*(1, s)
		queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(reachableNodes, RHSType));
	}
	else if (RHSType == EntityType::WILD) { // Next*(1, _)
		queryResult.setBooleanResult(reachableNodes.size() > 0);
	}

	return queryResult;
}

QueryClauseResult NextEvaluator::getNextTByStatementVariable(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Next*(s, 2)
		std::vector<std::unordered_set<int>> cfg = PKB::getCFG();

		int RHSInt = std::stoi(RHS);

		if (RHSInt < 1 || RHSInt > cfg.size() - 1) {
			return queryResult;
		}

		std::unordered_set<int> reachableNodes = getReachableNodes(RHSInt, PKB::getReversedCFG());
		queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(reachableNodes, LHSType));
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Next*(s1, s2)
		std::unordered_map<int, std::unordered_set<int>> nextTPairs = getAllNextTPairs();

		auto [firstEntities, secondEntities] = PKBUtil::convertMapWithSetToVectorTuple(nextTPairs);
		auto [filteredFirst, filteredSecond] = StmtStmtRelationshipEvaluator::filterStatementPairsByType(firstEntities, secondEntities, LHSType, RHSType);

		if (LHS == RHS) {
			std::unordered_set<int> set = PKBUtil::getEqualPairs(filteredFirst, filteredSecond);
			queryResult.addColumn(LHS, set);
		}
		else {
			queryResult.addColumn(LHS, filteredFirst);
			queryResult.addColumn(RHS, filteredSecond);
		}
	}
	else if (RHSType == EntityType::WILD) { // Next*(s, _)
		std::unordered_map<int, std::unordered_set<int>> nextTPairs = getAllNextTPairs();
		std::unordered_set<int> statements = PKBUtil::getKeySetFromMap(nextTPairs);
		queryResult.addColumn(LHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, LHSType));
	}

	return queryResult;
}
QueryClauseResult NextEvaluator::getNextTByUnderscore(const std::string& RHS, EntityType RHSType) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::INT) { // Next*(_, 2)
		std::vector<std::unordered_set<int>> cfg = PKB::getCFG();

		int RHSInt = std::stoi(RHS);

		if (RHSInt < 1 || RHSInt > cfg.size() - 1) {
			return queryResult;
		}

		std::vector<std::unordered_set<int>> reversedCfg = PKB::getReversedCFG();

		std::unordered_set<int> reachableNodes = getReachableNodes(RHSInt, reversedCfg);
		queryResult.setBooleanResult(reachableNodes.size() > 0);
	}
	else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::IF ||
		RHSType == EntityType::WHILE || RHSType == EntityType::PRINT || RHSType == EntityType::READ ||
		RHSType == EntityType::CALL) { // Next*(_, s)
		std::unordered_map<int, std::unordered_set<int>> nextTPairs = getAllNextTPairs();
		std::unordered_set<int> statements = PKBUtil::getValueSetFromMapWithSet(nextTPairs);
		queryResult.addColumn(RHS, StmtStmtRelationshipEvaluator::filterStatementsByType(statements, RHSType));
	}
	else if (RHSType == EntityType::WILD) { // Next*(_, _)
		if (PKB::hasNextRelationship()) {
			queryResult.setBooleanResult(true);
		}
	}

	return queryResult;
}

std::unordered_set<int> NextEvaluator::getReachableNodes(int startNode, std::vector<std::unordered_set<int>>& cfg) {
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

	return nextTPairs;
}

void NextEvaluator::modifiedDFS(int currNode, const std::vector<std::unordered_set<int>>& reversedCfg, std::unordered_set<int>& reachableNodes, std::unordered_map<int, std::unordered_set<int>>& nextTPairs) {
	int numPairs = nextTPairs[currNode].size();
	
	for (const auto& reachableNode : reachableNodes) {
		PKBUtil::addToMapWithSet(nextTPairs, currNode, reachableNode);
	}

	if (nextTPairs[currNode].size() == numPairs) {
		if (!reachableNodes.empty()) {
			return;
		}
	}

	for (const auto& neighbour : reversedCfg.at(currNode)) {
		std::unordered_set<int> nextReachableNodes = reachableNodes;
		nextReachableNodes.insert(currNode);
		modifiedDFS(neighbour, reversedCfg, nextReachableNodes, nextTPairs);
	}
}