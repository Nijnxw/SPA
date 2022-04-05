#include "AffectsEvaluator.h"

AffectsEvaluator::AffectsEvaluator() : isAffectsCacheComplete(false), isAffectsTCacheComplete(false) {
	cfg = PKB::getCFG();
}

QueryClauseResult
AffectsEvaluator::getAffects(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
							 bool isBooleanResult) {

	if (!isValidArg(LHS, LHSType) || !isValidArg(RHS, RHSType)) {
		return {};
	}
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
	switch (LHSType) {
		case EntityType::INT:
			return getAffectsByStmtNum(LHS, RHS, RHSType, isBooleanResult, false, affectsTCache, revAffectsTCache);
		case EntityType::WILD:
			return getAffectsByUnderscore(RHS, RHSType, isBooleanResult, false, affectsTCache, revAffectsTCache);
		case EntityType::ASSIGN:
		case EntityType::STMT:
			return getAffectsByStmt(LHS, RHS, RHSType, isBooleanResult, false, affectsTCache, revAffectsTCache);
		default:
			return {};
	}
}

QueryClauseResult
AffectsEvaluator::getAffectsByStmtNum(const std::string& LHS, const std::string& RHS, EntityType RHSType,
									  bool isBooleanResult, bool isAffects, Cache& cache, Cache& revCache) {
	if (RHSType == EntityType::INT) {
		if (cache.count(LHS) > 0) {
			const auto& affected = cache.at(LHS);
			if (affected.count(RHS) > 0) {
				return {true};
			}
		}
		setTermFuncAffectsByIntInt(LHS, RHS, cache);
	} else if (RHSType == EntityType::WILD || RHSType == EntityType::ASSIGN || RHSType == EntityType::STMT) {
		if (isBooleanResult && cache.count(LHS) > 0) {
			return {true};
		}
		setTermFuncAffectsByIntAny(LHS, isBooleanResult, cache);
	} else {
		return {};    // graceful handling of semantic error
	}
	if ((isAffects && !isAffectsCacheComplete) || (!isAffects && !isAffectsTCacheComplete)) {
		int lhsInt = std::stoi(LHS);
		if (lhsInt > 0 && lhsInt >= cfg.size()) {
			return {};
		}
		computeAffects(lhsInt, cfg.size() - 1, isAffects, true);
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
		int rhsInt = std::stoi(RHS);
		if (rhsInt > 0 && rhsInt >= cfg.size()) {
			return {};
		}
		setTermFuncAffectsByStmtInt(RHS, isBooleanResult, revCache);
	} else if (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN || RHSType == EntityType::WILD) {
		setTermFuncAffectsByStmt(LHS, RHS, isBooleanResult, cache);
	} else {
		return {};    // graceful handling of semantic error
	}
	if (isAffects && !isAffectsCacheComplete) {
		computeAffects(1, cfg.size() - 1, isAffects);
		isAffectsCacheComplete = !isBooleanResult;
	} else if (!isAffects && !isAffectsTCacheComplete) {
		computeAffects(1, cfg.size() - 1, isAffects);
		isAffectsTCacheComplete = !isBooleanResult;
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
		setTermFuncAffectsByWildStmt(isBooleanResult, revCache);
		if (isAffects && !isAffectsCacheComplete) {
			computeAffects(1, cfg.size() - 1, isAffects);
			isAffectsCacheComplete = !isBooleanResult;
		} else if (!isAffects && !isAffectsTCacheComplete) {
			computeAffects(1, cfg.size() - 1, isAffects);
			isAffectsTCacheComplete = !isBooleanResult;
		}
	} else {
		if (RHSType == EntityType::INT && revCache.count(RHS) > 0) {
			return {true};
		} else if (RHSType == EntityType::INT) {
			int rhsInt = std::stoi(RHS);
			if (rhsInt > 0 && rhsInt >= cfg.size()) {
				return {};
			}
			setTermFuncAffectsByWildInt(RHS, revCache);
		} else if (RHSType == EntityType::WILD && !cache.empty()) {
			return {true};
		} else if (RHSType == EntityType::WILD) {
			setTermFuncAffectsByWildWild(cache);
		} else {
			return {}; // graceful handling of semantic error
		}
		if (isAffects && !isAffectsCacheComplete) {
			computeAffects(1, cfg.size() - 1, isAffects);
		} else if (!isAffects && !isAffectsTCacheComplete) {
			computeAffects(1, cfg.size() - 1, isAffects);
		}
	}
	if (isBooleanResult) {
		return buildBoolResult("_", RHS, EntityType::WILD, RHSType, cache, revCache);
	}
	return buildClauseResult("_", RHS, EntityType::WILD, RHSType, cache, revCache);
}

void
AffectsEvaluator::setTermFuncAffectsByIntInt(const std::string& LHS, const std::string& RHS, Cache& cache) {
	terminateFunc = [&LHS, &RHS, &cache](int curr) -> bool {
		if (cache.count(LHS) > 0) {
			const auto& affected = cache.at(LHS);
			return affected.count(RHS) > 0;
		}
		return false;
	};
}

void AffectsEvaluator::setTermFuncAffectsByIntAny(const std::string& LHS, bool isBooleanResult, Cache& cache) {
	terminateFunc = [&LHS, isBooleanResult, &cache](int curr) -> bool {
		if (isBooleanResult && cache.count(LHS) > 0) {
			return true;
		}
		return false;
	};
}

void AffectsEvaluator::setTermFuncAffectsByStmtInt(const std::string& RHS, bool isBooleanResult, Cache& revCache) {
	terminateFunc = [&RHS, isBooleanResult, &revCache](int curr) -> bool {
		if (isBooleanResult) {
			return revCache.count(RHS) > 0;
		}
		return false;
	};
}

void AffectsEvaluator::setTermFuncAffectsByStmt(const std::string& LHS, const std::string& RHS, bool isBooleanResult,
												Cache& cache) {
	terminateFunc = [LHS, RHS, isBooleanResult, &cache](int curr) -> bool {
		std::string currString = std::to_string(curr);
		if (isBooleanResult && LHS != RHS) {
			return !cache.empty();
		} else if (isBooleanResult && cache.count(currString) > 0) {
			auto affected = cache.at(currString);
			return affected.count(currString) > 0;
		}
		return false;
	};
}

void AffectsEvaluator::setTermFuncAffectsByWildStmt(bool isBooleanResult, Cache& revCache) {
	terminateFunc = [isBooleanResult, &revCache](int curr) -> bool {
		if (isBooleanResult) {
			return !revCache.empty();
		}
		return false;
	};
}

void AffectsEvaluator::setTermFuncAffectsByWildInt(const std::string& RHS, Cache& revCache) {
	terminateFunc = [&RHS, &revCache](int curr) -> bool {
		return revCache.count(RHS) > 0;
	};
}

void AffectsEvaluator::setTermFuncAffectsByWildWild(Cache& cache) {
	terminateFunc = [&cache](int curr) -> bool {
		return !cache.empty();
	};
}

QueryClauseResult
AffectsEvaluator::buildBoolResult(const std::string& LHS, const std::string& RHS, EntityType LHSType,
								  EntityType RHSType, Cache& cache, Cache& revCache) {
	if (LHSType == EntityType::INT && RHSType == EntityType::INT) {
		if (cache.count(LHS) > 0) {
			const auto& affected = cache.at(LHS);
			return {affected.count(RHS) > 0};
		}
		return {false};
	} else if (LHSType == EntityType::INT) {
		return {cache.count(LHS) > 0};
	} else if (RHSType == EntityType::INT) {
		return {revCache.count(RHS) > 0};
	} else {
		return {!cache.empty()};
	}
}

QueryClauseResult
AffectsEvaluator::buildClauseResult(const std::string& LHS, const std::string& RHS, EntityType LHSType,
									EntityType RHSType, Cache& cache, Cache& revCache) {
	if (LHSType == EntityType::INT && (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN)) {
		return buildClauseResultIntStmt(LHS, RHS, cache);
	} else if ((LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN) && RHSType == EntityType::INT) {
		return buildClauseResultIntStmt(RHS, LHS, revCache);
	} else if ((LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN) &&
			   (RHSType == EntityType::STMT || RHSType == EntityType::ASSIGN)) {
		return buildClauseResultStmtStmt(LHS, RHS, cache);
	} else if (LHSType == EntityType::STMT || LHSType == EntityType::ASSIGN) {
		return buildClauseResultStmtWild(LHS, cache);
	} else {
		return buildClauseResultStmtWild(RHS, revCache);
	}
	return {};
}

QueryClauseResult
AffectsEvaluator::buildClauseResultIntStmt(const std::string& num, const std::string& syn, Cache& cache) {
	if (cache.count(num) > 0) {
		const auto& affected = cache.at(num);
		const std::vector<std::string>& rowValues = {affected.begin(), affected.end()};
		return {{{syn, rowValues}}};
	}
	return {};
}

QueryClauseResult
AffectsEvaluator::buildClauseResultStmtStmt(const std::string& LHS, const std::string& RHS, Cache& cache) {
	std::vector<std::string> lhsValues;
	std::vector<std::string> rhsValues;
	if (LHS == RHS) {
		for (const auto& keyVal: cache) {
			const auto& affected = keyVal.second;
			if (affected.count(keyVal.first) > 0) {
				lhsValues.push_back(keyVal.first);
			}
		}
		return {{{LHS, lhsValues}}};
	}

	for (const auto& keyVal: cache) {
		for (const auto& affected: keyVal.second) {
			lhsValues.push_back(keyVal.first);
			rhsValues.push_back(affected);
		}
	}
	return {{{LHS, lhsValues}, {RHS, rhsValues}}};
}

QueryClauseResult AffectsEvaluator::buildClauseResultStmtWild(const std::string& syn, Cache& cache) {
	std::vector<std::string> rowValues;
	for (const auto& keyVal: cache) {
		rowValues.push_back(keyVal.first);
	}
	return {{{syn, rowValues}}};
}

void AffectsEvaluator::computeAffects(int start, int end, bool isAffects, bool cannotGoPastProc) {    // start point
	canTerminate = false;
	const std::vector<int>& allProcFirstStmt = PKB::getProcStatementNumbers();
	auto it = allProcFirstStmt.begin();

	while ((it + 1) != allProcFirstStmt.end()) {
		int intervalStart = *it;
		it++;
		int intervalEnd = (*it) - 1;

		if (start <= intervalEnd && intervalStart <= end) { // overlap
			LMT lmt;
			computeAffectsStmtList(intervalStart, intervalEnd, lmt, isAffects);
			if (cannotGoPastProc || canTerminate) {
				return;
			}
		}
	}
	LMT lmt;
	computeAffectsStmtList(*it, end, lmt, isAffects);
}

void AffectsEvaluator::computeAffectsStmtList(int start, int end, LMT& currLMT, bool isAffects) {
	int currStmtNum = start;
	while (currStmtNum <= end) {
		EntityType currStmtType = PKB::getStatementType(currStmtNum);
		switch (currStmtType) {
			case EntityType::IF:
				computeAffectsIfElse(currLMT, currStmtNum, isAffects);
				currStmtNum = getNextForBlock(currStmtNum);
				break;
			case EntityType::WHILE:
				computeAffectsWhile(currLMT, currStmtNum, isAffects);
				currStmtNum = getNextForBlock(currStmtNum);
				break;
			default:
				computeAffectsStmt(currLMT, currStmtNum, currStmtType, isAffects);
				currStmtNum++;
				break;
		}
		if (terminateFunc(currStmtNum) || canTerminate) {
			canTerminate = true;
			return;
		}
	}
}

void AffectsEvaluator::computeAffectsIfElse(LMT& lmt, int start, bool isAffects) {
	int firstIfStmt = start + 1;
	int firstElseStmt = getNextBigger(start);
	int lastIfStmt = firstElseStmt - 1;
	int lastElseStmt = getBiggestChild(start);

	LMT lmtElse(lmt);
	computeAffectsStmtList(firstIfStmt, lastIfStmt, lmt, isAffects);
	if (canTerminate) {
		return;
	}
	computeAffectsStmtList(firstElseStmt, lastElseStmt, lmtElse, isAffects);
	if (canTerminate) {
		return;
	}

	mergeLMT(lmt, lmtElse);
}

void AffectsEvaluator::computeAffectsWhile(LMT& prevLMT, int start, bool isAffects) {
	int end = getBiggestChild(start);

	LMT lmtLoop(prevLMT);
	bool changed;
	do {
		changed = false;
		computeAffectsStmtList(start + 1, end, lmtLoop, isAffects);
		if (canTerminate) {
			return;
		}
		changed = mergeLMT(prevLMT, lmtLoop);
	} while (changed);
}

void AffectsEvaluator::computeAffectsStmt(LMT& currLMT, int currStmtNum, EntityType currStmtType, bool isAffects) {
	switch (currStmtType) {
		case EntityType::ASSIGN:
			if (isAffects) {
				computeAffectsAssign(currLMT, currStmtNum);
			} else {
				computeAffectsTAssign(currLMT, currStmtNum);
			}
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

void AffectsEvaluator::computeAffectsAssign(LMT& currLMT, int currStmtNum) {
	std::string modVar = *(PKB::getVariablesModifiedByStatement(currStmtNum).begin());
	const std::unordered_set<std::string>& usedVars = PKB::getVariablesUsedByStatement(currStmtNum);

	for (const auto& var: usedVars) {
		if (currLMT.count(var) == 0) {
			continue;
		}
		for (auto stmt: currLMT.at(var)) {
			if (PKB::isAssignmentStmt(stmt)) {
				affectsCache[std::to_string(stmt)].emplace(std::to_string(currStmtNum));
				revAffectsCache[std::to_string(currStmtNum)].emplace(std::to_string(stmt));
			}
		}
	}
	currLMT[modVar] = {currStmtNum};
}

void AffectsEvaluator::computeAffectsTAssign(LMT& currLMT, int currStmtNum) {
	std::string modVar = *(PKB::getVariablesModifiedByStatement(currStmtNum).begin());
	const std::unordered_set<std::string>& usedVars = PKB::getVariablesUsedByStatement(currStmtNum);

	if (usedVars.count(modVar) == 0) {
		currLMT[modVar].clear();
	}
	for (const auto& var: usedVars) {
		if (currLMT.count(var) == 0) {
			continue;
		}
		for (auto stmt: currLMT.at(var)) {
			if (PKB::isAssignmentStmt(stmt)) {
				affectsTCache[std::to_string(stmt)].emplace(std::to_string(currStmtNum));
				revAffectsTCache[std::to_string(currStmtNum)].emplace(std::to_string(stmt));
				currLMT[modVar].emplace(stmt);
			}
		}
	}
	currLMT[modVar].emplace(currStmtNum);
}

void AffectsEvaluator::computeAffectsCall(LMT& currLMT, int currStmtNum) {
	const std::string& procName = PKB::getCalledProcName(currStmtNum);

	const std::unordered_set<std::string>& modVars = PKB::getVariablesModifiedByProcedure(procName);

	for (const auto& var: modVars) {
		currLMT[var].clear();
	}
}

void AffectsEvaluator::computeAffectsRead(LMT& currLMT, int currStmtNum) {
	const std::unordered_set<std::string>& modVars = PKB::getVariablesModifiedByStatement(currStmtNum);

	for (const auto& var: modVars) {
		currLMT[var].clear();
	}
}

bool AffectsEvaluator::isValidArg(const std::string& argValue, EntityType argType) {
	if (argType == EntityType::INT && PKB::isAssignmentStmt(std::stoi(argValue))) {
		return true;
	} else {
		return argType == EntityType::ASSIGN || argType == EntityType::STMT || argType == EntityType::WILD;
	}
}

bool AffectsEvaluator::mergeLMT(LMT& first, const LMT& second) {
	LMT merged;

	bool changed = false;
	for (const auto& keyVal: second) {
		if (first.count(keyVal.first) > 0) {
			for (const auto& element: keyVal.second) {
				auto& modified = first.at(keyVal.first);
				if (modified.count(element) > 0) {
					continue;
				}
				modified.insert(element);
				changed = true;
			}
			continue;
		}
		first[keyVal.first] = keyVal.second;
		changed = true;
	}

	return changed;
}

int AffectsEvaluator::getNextBigger(int currStmtNum) {
	const auto& possibleNext = cfg.at(currStmtNum);
	if (possibleNext.empty()) {
		return 0;
	}
	int biggestNext = *possibleNext.begin();
	for (auto it = next(possibleNext.begin()); it != possibleNext.end(); it++) {
		biggestNext = std::max(biggestNext, *it);
	}
	return biggestNext;
}

int AffectsEvaluator::getBiggestChild(int currStmtNum) {
	const auto& children = PKB::getChildrenT(currStmtNum);
	int maxChild = 0;
	for (const auto& child: children) {
		maxChild = std::max(child, maxChild);
	}
	return maxChild;
}

int AffectsEvaluator::getNextForBlock(int currStmtNum) {
	int followee = PKB::getFollowee(currStmtNum);
	if (followee != 0) {    // if block is not last stmt of list
		return followee;
	}

	const auto& parents = PKB::getParent(currStmtNum);
	if (!parents.empty()) {
		int parent = *parents.begin();
		return getNextForBlock(parent);
	} else {
		return getBiggestChild(currStmtNum) + 1;
	}
}
