#include "AffectsEvaluator.h"

QueryClauseResult
AffectsEvaluator::getAffects(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
							 bool isBooleanResult) {

	if (!isValidArg(LHS, LHSType) || !isValidArg(RHS, RHSType)) {
		return {};
	}
	visitedLoops.clear();
	switch (LHSType) {
		case EntityType::INT:
			return getAffectsByStmtNum(LHS, RHS, RHSType, isBooleanResult, true, affectsCache, revAffectsCache);
		case EntityType::WILD:
			return getAffectsByUnderscore(RHS, RHSType, isBooleanResult, true, affectsCache, revAffectsCache);
		case EntityType::ASSIGN:
		case EntityType::STMT:
			return getAffectsByStmt(LHS, RHS, RHSType, isBooleanResult, true, affectsCache, revAffectsCache);
		default:
			return {};
	}
}

QueryClauseResult
AffectsEvaluator::getAffectsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
							  bool isBooleanResult) {
	if (!isValidArg(LHS, LHSType) || !isValidArg(RHS, RHSType)) {
		return {};
	}
	visitedLoops.clear();
	switch (LHSType) {
		case EntityType::INT:
			return getAffectsByStmtNum(LHS, RHS, RHSType, isBooleanResult, false, affectsTCache, revAffectsTCache);
		case EntityType::WILD:
			return getAffectsByUnderscore(RHS, RHSType, isBooleanResult, false, affectsTCache, revAffectsTCache);
		case EntityType::ASSIGN:
		case EntityType::STMT:
			return getAffectsByStmt(LHS, RHS, RHSType, isBooleanResult, false, affectsCache, revAffectsCache);
		default:
			return {};
	}
}

QueryClauseResult
AffectsEvaluator::getAffectsByStmtNum(const std::string& LHS, const std::string& RHS, EntityType RHSType,
									  bool isBooleanResult, bool isAffects, Cache& cache, Cache& revCache) {
	if (RHSType == EntityType::INT) {
		if (cache.find(LHS) != cache.end()) {
			auto affected = cache.at(LHS);
			if (affected.find(RHS) != affected.end()) {
				return {true};
			}
		}

		terminateFunc = [&LHS, &RHS, cache, this](int curr) -> bool {
			if (cache.find(LHS) != cache.end()) {
				auto affected = cache.at(LHS);
				return affected.find(RHS) != affected.end();
			}
			return isProcLastStmt(curr);
		};
	} else if (RHSType == EntityType::WILD) {
		if (cache.find(LHS) != cache.end()) {
			return {true};
		}
		terminateFunc = [&LHS, cache, this](int curr) -> bool {
			if (cache.find(LHS) != cache.end()) {
				return true;
			}
			return isProcLastStmt(curr);
		};
	} else if (RHSType == EntityType::ASSIGN || RHSType == EntityType::STMT) {
		terminateFunc = [cache, this](int curr) -> bool {
			return isProcLastStmt(curr);
		};
	} else {
		return {};    // graceful handling of semantic error
	}
	if ((isAffects && !isAffectsCacheComplete) || (!isAffects && !isAffectsTCacheComplete)) {
		computeAffects(std::stoi(LHS), cfg.size() - 1, isAffects);
	}
	if (isBooleanResult) {
		return buildBoolResult(LHS, RHS, EntityType::INT, RHSType, cache, revCache);
	}
	return buildClauseResult(LHS, RHS, EntityType::INT, RHSType, cache, revCache);
}

QueryClauseResult
AffectsEvaluator::getAffectsByStmt(const std::string& LHS, const std::string& RHS, EntityType RHSType,
								   bool isBooleanResult, bool isAffects, Cache& cache, Cache& revCache) {
	if (RHSType == EntityType::INT) {
		terminateFunc = [&RHS, isBooleanResult, revCache](int curr) -> bool {
			if (isBooleanResult) {
				return revCache.find(RHS) != revCache.end();
			}
			return false;
		};
	} else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::WILD) {
		terminateFunc = [isBooleanResult, cache](int curr) -> bool {
			if (isBooleanResult) {
				return !cache.empty();
			}
			return false;
		};
	} else {
		return {};    // graceful handling of semantic error
	}
	if (isAffects && !isAffectsCacheComplete) {
		computeAffects(1, cfg.size() - 1, isAffects);
		isAffectsCacheComplete = true;
	} else if (!isAffects && !isAffectsTCacheComplete) {
		computeAffects(1, cfg.size() - 1, isAffects);
		isAffectsTCacheComplete = true;
	}
	if (isBooleanResult) {
		return buildBoolResult(LHS, RHS, EntityType::ASSIGN, RHSType, cache, revCache);
	}
	return buildClauseResult(LHS, RHS, EntityType::ASSIGN, RHSType, cache, revCache);
}

QueryClauseResult
AffectsEvaluator::getAffectsByUnderscore(const std::string& RHS, EntityType RHSType, bool isBooleanResult,
										 bool isAffects, Cache& cache, Cache& revCache) {
	if (RHSType == EntityType::ASSIGN || RHSType == EntityType::STMT) {
		terminateFunc = [isBooleanResult, revCache](int curr) -> bool {
			if (isBooleanResult) {
				return !revCache.empty();
			}
			return false;
		};
	} else if (RHSType == EntityType::INT) {
		if (revCache.find(RHS) != revCache.end()) {
			return {true};
		}
		terminateFunc = [&RHS, revCache](int curr) -> bool {
			return revCache.find(RHS) != revCache.end();
		};
	} else if (RHSType == EntityType::WILD) {
		if (!cache.empty()) {
			return {true};
		}
		terminateFunc = [cache](int curr) -> bool {
			return !cache.empty();
		};
	} else {
		return {};    // graceful handling of semantic error
	}
	if (isAffects && !isAffectsCacheComplete) {
		computeAffects(1, cfg.size() - 1, isAffects);
		isAffectsCacheComplete = true;
	} else if (!isAffects && !isAffectsTCacheComplete) {
		computeAffects(1, cfg.size() - 1, isAffects);
		isAffectsTCacheComplete = true;
	}
	if (isBooleanResult) {
		return buildBoolResult("_", RHS, EntityType::WILD, RHSType, cache, revCache);
	}
	return buildClauseResult("_", RHS, EntityType::WILD, RHSType, cache, revCache);
}

QueryClauseResult
AffectsEvaluator::buildBoolResult(const std::string& LHS, const std::string& RHS, EntityType LHSType,
								  EntityType RHSType, Cache& cache, Cache& revCache) {
	if (LHSType == EntityType::INT && RHSType == EntityType::INT) {
		if (cache.find(LHS) != cache.end()) {
			auto affected = cache.at(LHS);
			return {affected.find(RHS) != affected.end()};
		}
		return {false};
	} else if (LHSType == EntityType::INT) {
		return {cache.find(LHS) != cache.end()};
	} else if (RHSType == EntityType::INT) {
		return {revCache.find(LHS) != revCache.end()};
	} else {
		return {!cache.empty()};
	}
}

QueryClauseResult
AffectsEvaluator::buildClauseResult(const std::string& LHS, const std::string& RHS, EntityType LHSType,
									EntityType RHSType, Cache& cache, Cache& revCache) {
	if (LHSType == EntityType::INT && (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN)) {
		if (cache.find(LHS) != cache.end()) {
			auto affected = cache.at(LHS);
			std::vector<std::string> rowValues = {affected.begin(), affected.end()};
			return {{{RHS, rowValues}}};
		}
	} else if ((LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN) && RHSType == EntityType::INT) {
		if (revCache.find(LHS) != revCache.end()) {
			auto affectee = revCache.at(LHS);
			std::vector<std::string> rowValues = {affectee.begin(), affectee.end()};
			return {{{RHS, rowValues}}};
		}
	} else if ((LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN) &&
			   (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN)) {
		std::vector<std::string> lhsValues;
		std::vector<std::string> rhsValues;
		for (const auto& keyVal: cache) {
			for (const auto& affected: keyVal.second) {
				lhsValues.push_back(keyVal.first);
				rhsValues.push_back(affected);
			}
		}
		return {{{LHS, lhsValues}, {RHS, rhsValues}}};
	} else if (LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN) {
		std::vector<std::string> lhsValues;
		for (const auto& keyVal: cache) {
			lhsValues.push_back(keyVal.first);
		}
		return {{{LHS, lhsValues}}};
	} else {
		std::vector<std::string> rhsValues;
		for (const auto& keyVal: revCache) {
			rhsValues.push_back(keyVal.first);
		}
		return {{{RHS, rhsValues}}};
	}
	return {};
}

void AffectsEvaluator::computeAffects(int start, int end, bool isAffects) {
	computeAffects(start, end, {}, isAffects);
}

AffectsEvaluator::LMT
AffectsEvaluator::computeAffects(int start, int end, LMT currLMT, bool isAffects) {
	int currStmtNum = start;

	while (currStmtNum <= end) {
		EntityType currStmtType = PKB::getStatementType(currStmtNum);
		LMT stmtLMT;
		switch (currStmtType) {
			case EntityType::IF:
				currLMT = computeAffectsIfElse(currLMT, currStmtNum, PKB::getFollower(currStmtNum), isAffects);
				currStmtNum = PKB::getFollower(currStmtNum);
				break;
			case EntityType::WHILE:
				visitedLoops.insert(currStmtNum);
				computeAffectsWhile(currLMT, currStmtNum, PKB::getFollower(currStmtNum), isAffects);
				if (terminateFunc(currStmtNum)) {
					return {};
				}
				currStmtNum = PKB::getFollower(currStmtNum);
				break;
			default:
				if (isAffects) {
					computeAffectsStmt(currLMT, currStmtNum, currStmtType);
				} else {
					computeAffectsTStmt(currLMT, currStmtNum, currStmtType);
				}
				int next = getNextSmaller(
					currStmtNum); // check for last statement in while loop to prevent infinite recursion
				if (PKB::getStatementType(next) == EntityType::WHILE && visitedLoops.find(next) != visitedLoops.end()) {
					visitedLoops.insert(next);
					computeAffectsWhile(currLMT, next, currStmtNum, isAffects);
				}
				if (terminateFunc(currStmtNum)) {
					return {};
				}
				currStmtNum++;
				break;
		}
	}

	return currLMT;
}

AffectsEvaluator::LMT
AffectsEvaluator::computeAffectsIfElse(const LMT& prevLMT, int start, int end, bool isAffects) {
	int firstIfStmt = start + 1;
	int firstElseStmt = getNextBigger(start);
	int lastIfStmt = firstElseStmt - 1;
	int lastElseStmt = end - 1;

	LMT newIfLMT = computeAffects(firstIfStmt, lastIfStmt, prevLMT, isAffects);
	LMT newElseLMT = computeAffects(firstElseStmt, lastElseStmt, prevLMT, isAffects);

	return mergeLMT(newIfLMT, newElseLMT);
}

AffectsEvaluator::LMT
AffectsEvaluator::computeAffectsWhile(const LMT& prevLMT, int start, int end, bool isAffects) {
	std::stack<LMT> LMS;
	LMT currLMT = computeAffects(start + 1, end - 1, prevLMT, isAffects);

	while (LMS.top() != currLMT) {
		currLMT = computeAffects(start + 1, end - 1, currLMT, isAffects);;
		if (LMS.top() != currLMT) {
			LMT temp = mergeLMT(LMS.top(), currLMT);
			LMS.pop();
			LMS.push(temp);
		}
	}

	return LMS.top();
}

void AffectsEvaluator::computeAffectsStmt(LMT& currLMT, int currStmtNum, EntityType currStmtType) {
	switch (currStmtType) {
		case EntityType::ASSIGN:
			computeAffectsAssign(currLMT, currStmtNum);
			break;
		case EntityType::CALL:
			computeAffectsCall(currLMT, currStmtNum);
			break;
		case EntityType::READ:
			computeAffectsRead(currLMT, currStmtNum);
			break;
		default:
			return;
	}
}

void AffectsEvaluator::computeAffectsTStmt(LMT& currLMT, int currStmtNum, EntityType currStmtType) {
	switch (currStmtType) {
		case EntityType::ASSIGN:
			computeAffectsTAssign(currLMT, currStmtNum);
			break;
		case EntityType::CALL:
			computeAffectsTCall(currLMT, currStmtNum);
			break;
		case EntityType::READ:
			computeAffectsTRead(currLMT, currStmtNum);
			break;
		default:
			return;
	}
}

void AffectsEvaluator::computeAffectsAssign(LMT& currLMT, int currStmtNum) {
	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByStatement(currStmtNum);
	std::unordered_set<std::string> usedVars = PKB::getVariablesUsedByStatement(currStmtNum);

	for (const auto& var: usedVars) {
		if (currLMT.find(var) == currLMT.end()) {
			continue;
		}
		for (auto stmt: currLMT.at(var)) {
			if (PKB::isAssignmentStmt(stmt)) {
				affectsCache[std::to_string(stmt)].emplace(std::to_string(currStmtNum));
				revAffectsCache[std::to_string(currStmtNum)].emplace(std::to_string(stmt));
			}
		}
	}
	for (const auto& var: modVars) {
		currLMT[var] = {currStmtNum};
	}
}

void AffectsEvaluator::computeAffectsTAssign(LMT& currLMT, int currStmtNum) {
	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByStatement(currStmtNum);
	std::unordered_set<std::string> usedVars = PKB::getVariablesUsedByStatement(currStmtNum);

	for (const auto& var: usedVars) {
		if (currLMT.find(var) == currLMT.end()) {
			continue;
		}
		for (auto stmt: currLMT.at(var)) {
			if (PKB::isAssignmentStmt(stmt)) {
				affectsCache[std::to_string(stmt)].emplace(std::to_string(currStmtNum));
				revAffectsCache[std::to_string(currStmtNum)].emplace(std::to_string(stmt));
			}
		}
	}
	for (const auto& var: modVars) {
		currLMT[var].emplace(currStmtNum);
	}
}

void AffectsEvaluator::computeAffectsCall(LMT& currLMT, int currStmtNum) {
	std::string procName = PKB::getCalledProcName(currStmtNum);

	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByProcedure(procName);

	for (const auto& var: modVars) {
		currLMT[var] = {currStmtNum};
	}
}

void AffectsEvaluator::computeAffectsTCall(LMT& currLMT, int currStmtNum) {
	std::string procName = PKB::getCalledProcName(currStmtNum);

	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByProcedure(procName);

	for (const auto& var: modVars) {
		currLMT[var].emplace(currStmtNum);
	}
}

void AffectsEvaluator::computeAffectsRead(LMT& currLMT, int currStmtNum) {
	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByStatement(currStmtNum);

	for (const auto& var: modVars) {
		currLMT[var] = {currStmtNum};
	}
}

void AffectsEvaluator::computeAffectsTRead(LMT& currLMT, int currStmtNum) {
	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByStatement(currStmtNum);

	for (const auto& var: modVars) {
		currLMT[var].emplace(currStmtNum);
	}
}

bool AffectsEvaluator::isValidArg(const std::string& argValue, EntityType argType) {
	if (argType == EntityType::INT && PKB::isAssignmentStmt(std::stoi(argValue))) {
		return true;
	} else {
		return argType == EntityType::ASSIGN || argType == EntityType::STMT || argType == EntityType::WILD;
	}
}

AffectsEvaluator::LMT AffectsEvaluator::mergeLMT(const LMT& first, const LMT& second) {
	LMT merged;

	for (const auto& keyVal: first) {
		merged[keyVal.first].insert(keyVal.second.begin(), keyVal.second.end());
	}
	for (const auto& keyVal: second) {
		merged[keyVal.first].insert(keyVal.second.begin(), keyVal.second.end());
	}

	return merged;
}

int AffectsEvaluator::getNextSmaller(int currStmtNum) {
	auto possibleNext = cfg.at(currStmtNum);
	int smallestNext = *possibleNext.begin();
	for (auto it = next(possibleNext.begin()); it != possibleNext.end(); it++) {
		smallestNext = std::min(smallestNext, *it);
	}
	return smallestNext;
}

int AffectsEvaluator::getNextBigger(int currStmtNum) {
	auto possibleNext = cfg.at(currStmtNum);
	int biggestNext = *possibleNext.begin();
	for (auto it = next(possibleNext.begin()); it != possibleNext.end(); it++) {
		biggestNext = std::max(biggestNext, *it);
	}
	return biggestNext;
}

bool AffectsEvaluator::isProcLastStmt(int currStmtNum) {
	EntityType stmtType = PKB::getStatementType(currStmtNum);
	auto nextStmts = cfg.at(currStmtNum);
	if (stmtType == EntityType::WHILE) {
		return nextStmts.size() == 1;
	}
	return nextStmts.empty();
}
