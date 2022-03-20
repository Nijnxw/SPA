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
			return getAffectsByStmt(LHS, RHS, RHSType, isBooleanResult, false, affectsTCache, revAffectsTCache);
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
		setTermFuncAffectsByIntInt(LHS, RHS, cache);
	} else if (RHSType == EntityType::WILD) {
		if (cache.find(LHS) != cache.end()) {
			return {true};
		}
		setTermFuncAffectsByIntWild(LHS, cache);
	} else if (RHSType == EntityType::ASSIGN || RHSType == EntityType::STMT) {
		setTermFuncAffectsByIntStmt();
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
		if (RHSType == EntityType::INT && revCache.find(RHS) != revCache.end()) {
			return {true};
		} else if (RHSType == EntityType::INT) {
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
	terminateFunc = [&LHS, &RHS, &cache, this](int curr) -> bool {
		if (cache.find(LHS) != cache.end()) {
			auto affected = cache.at(LHS);
			return affected.find(RHS) != affected.end();
		}
		return isProcLastStmt(curr);
	};
}

void AffectsEvaluator::setTermFuncAffectsByIntWild(const std::string& LHS, Cache& cache) {
	terminateFunc = [&LHS, &cache, this](int curr) -> bool {
		if (cache.find(LHS) != cache.end()) {
			return true;
		}
		return isProcLastStmt(curr);
	};
}

void AffectsEvaluator::setTermFuncAffectsByIntStmt() {
	terminateFunc = [this](int curr) -> bool {
		return isProcLastStmt(curr);
	};
}

void AffectsEvaluator::setTermFuncAffectsByStmtInt(const std::string& RHS, bool isBooleanResult, Cache& revCache) {
	terminateFunc = [&RHS, isBooleanResult, &revCache](int curr) -> bool {
		if (isBooleanResult) {
			return revCache.find(RHS) != revCache.end();
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
		} else if (isBooleanResult && cache.find(currString) != cache.end()) {
			auto affected = cache.at(currString);
			return affected.find(currString) != affected.end();
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
		return revCache.find(RHS) != revCache.end();
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
		if (cache.find(LHS) != cache.end()) {
			auto affected = cache.at(LHS);
			return {affected.find(RHS) != affected.end()};
		}
		return {false};
	} else if (LHSType == EntityType::INT) {
		return {cache.find(LHS) != cache.end()};
	} else if (RHSType == EntityType::INT) {
		bool test = revCache.find(RHS) != revCache.end();
		return {revCache.find(RHS) != revCache.end()};
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
	if (cache.find(num) != cache.end()) {
		auto affected = cache.at(num);
		std::vector<std::string> rowValues = {affected.begin(), affected.end()};
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
			auto affected = keyVal.second;
			if (affected.find(keyVal.first) != affected.end()) {
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

void AffectsEvaluator::computeAffects(int start, int end, bool isAffects) {    // start point
	computeAffects(start, end, {}, isAffects);
}

AffectsEvaluator::LMT
AffectsEvaluator::computeAffects(int start, int end, LMT currLMT, bool isAffects) {
	int currStmtNum = start;
	int prevStmtNum = start;

	while (currStmtNum <= end) {
		prevStmtNum = currStmtNum;
		EntityType currStmtType = PKB::getStatementType(currStmtNum);
		switch (currStmtType) {
			case EntityType::IF:
				currLMT = computeAffectsIfElse(currLMT, currStmtNum, isAffects);
				currStmtNum = getNextForIf(currStmtNum);
				break;
			case EntityType::WHILE:
				if (visitedLoops.find(currStmtNum) == visitedLoops.end()) {
					visitedLoops.insert(currStmtNum);
					currLMT = computeAffectsWhile(currLMT, currStmtNum, getNextForWhile(currStmtNum), isAffects);
				}
				currStmtNum = getNextForWhile(currStmtNum);
				break;
			default:
				computeAffectsStmt(currLMT, currStmtNum, currStmtType, isAffects);
				currStmtNum = getNextForStmt(currStmtNum);
				break;
		}
		if (terminateFunc(prevStmtNum)) {
			return {};
		}
		if (isProcLastStmt(prevStmtNum)) {
			currLMT.clear();
		}
	}

	return currLMT;
}

AffectsEvaluator::LMT
AffectsEvaluator::computeAffectsIfElse(const LMT& prevLMT, int start, bool isAffects) {
	int firstIfStmt = start + 1;
	int firstElseStmt = getNextBigger(start);
	int lastIfStmt = getLastStmtOfBlock(firstIfStmt);
	int lastElseStmt = getLastStmtOfBlock(firstElseStmt);

	LMT newIfLMT = computeAffects(firstIfStmt, lastIfStmt, prevLMT, isAffects);
	LMT newElseLMT = computeAffects(firstElseStmt, lastElseStmt, prevLMT, isAffects);

	return mergeLMT(newIfLMT, newElseLMT);
}

AffectsEvaluator::LMT
AffectsEvaluator::computeAffectsWhile(const LMT& prevLMT, int start, int end, bool isAffects) {
	LMT lmt = prevLMT;
	LMT currLMT = computeAffects(start + 1, end - 1, prevLMT, isAffects);

	while (lmt != currLMT) {
		lmt = currLMT;
		currLMT = computeAffects(start + 1, end - 1, currLMT, isAffects);
	}

	return mergeLMT(currLMT, prevLMT);
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
	currLMT[modVar] = {currStmtNum};
}

void AffectsEvaluator::computeAffectsTAssign(LMT& currLMT, int currStmtNum) {
	std::string modVar = *(PKB::getVariablesModifiedByStatement(currStmtNum).begin());
	std::unordered_set<std::string> usedVars = PKB::getVariablesUsedByStatement(currStmtNum);

	if (usedVars.find(modVar) == usedVars.end()) {
		currLMT[modVar].clear();
	}
	for (const auto& var: usedVars) {
		if (currLMT.find(var) == currLMT.end()) {
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
	std::string procName = PKB::getCalledProcName(currStmtNum);

	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByProcedure(procName);

	for (const auto& var: modVars) {
		currLMT[var].clear();
	}
}

void AffectsEvaluator::computeAffectsRead(LMT& currLMT, int currStmtNum) {
	std::unordered_set<std::string> modVars = PKB::getVariablesModifiedByStatement(currStmtNum);

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

int AffectsEvaluator::getNextBigger(int currStmtNum) {
	auto possibleNext = cfg.at(currStmtNum);
	if (possibleNext.empty()) {
		return 0;
	}
	int biggestNext = *possibleNext.begin();
	for (auto it = next(possibleNext.begin()); it != possibleNext.end(); it++) {
		biggestNext = std::max(biggestNext, *it);
	}
	return biggestNext;
}

int AffectsEvaluator::getLastStmtOfBlock(int currStmtNum) {
	int stmtNum = currStmtNum;
	while (PKB::getFollowee(stmtNum) != 0) {
		stmtNum = PKB::getFollowee(stmtNum);
	}
	return stmtNum;
}

bool AffectsEvaluator::isProcLastStmt(int currStmtNum) {
	EntityType stmtType = PKB::getStatementType(currStmtNum);

	if (stmtType == EntityType::IF) {
		int lastStmtOfElse = getLastStmtOfBlock(getNextBigger(currStmtNum));
		auto nextStmts = cfg.at(lastStmtOfElse);
		return nextStmts.empty();
	} else {
		auto nextStmts = cfg.at(currStmtNum);
		if (stmtType == EntityType::WHILE) {
			return nextStmts.size() == 1;
		}
		return nextStmts.empty();
	}
}

int AffectsEvaluator::getNextForStmt(int currStmtNum) {
	auto possibleNext = cfg.at(currStmtNum);
	if (possibleNext.empty()) {
		return currStmtNum + 1;
	}

	int next = *possibleNext.begin();
	if (PKB::getStatementType(next) == EntityType::WHILE) {
		if (visitedLoops.find(next) == visitedLoops.end()) {
			return next;
		} else {
			return getNextForWhile(next);
		}
	} else {
		return next;
	}
}

int AffectsEvaluator::getNextForIf(int currStmtNum) {
	int lastStmtOfElse = getLastStmtOfBlock(getNextBigger(currStmtNum));
	EntityType stmtType = PKB::getStatementType(lastStmtOfElse);

	if (stmtType == EntityType::WHILE) {
		return getNextForWhile(lastStmtOfElse);
	} else if (stmtType == EntityType::IF) {
		return getNextForIf(lastStmtOfElse);
	} else {
		return lastStmtOfElse + 1;
	}
}

int AffectsEvaluator::getNextForWhile(int currStmtNum) {
	auto possibleNext = cfg.at(currStmtNum);
	if (possibleNext.size() == 2) {
		return getNextBigger(currStmtNum);
	}
	int lastStmtOfWhile = getLastStmtOfBlock(currStmtNum + 1);
	EntityType stmtType = PKB::getStatementType(lastStmtOfWhile);
	if (stmtType == EntityType::WHILE) {
		return getNextForWhile(lastStmtOfWhile);
	} else if (stmtType == EntityType::IF) {
		return getNextForIf(lastStmtOfWhile);
	} else {
		return lastStmtOfWhile + 1;
	}
}
