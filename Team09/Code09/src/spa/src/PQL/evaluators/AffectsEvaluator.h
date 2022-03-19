#pragma once

#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "pkb/PKB.h"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"
#include "simple_parser/CFGExtractor.h"

class AffectsEvaluator {
public:
	AffectsEvaluator();

	QueryClauseResult
	getAffects(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			   bool isBooleanResult);
	QueryClauseResult
	getAffectsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
				bool isBooleanResult);
private:
	using LMT = std::unordered_map<std::string, std::unordered_set<int>>;
	using Cache = std::unordered_map<std::string, std::unordered_set<std::string>>;

	QueryClauseResult
	getAffectsByStmtNum(const std::string& LHS, const std::string& RHS, EntityType RHSType, bool isBooleanResult,
						bool isAffects, Cache& cache, Cache& revCache);
	QueryClauseResult
	getAffectsByStmt(const std::string& LHS, const std::string& RHS, EntityType RHSType, bool isBooleanResult,
					 bool isAffects, Cache& cache, Cache& revCache);
	QueryClauseResult
	getAffectsByUnderscore(const std::string& RHS, EntityType RHSType, bool isBooleanResult, bool isAffects,
						   Cache& cache, Cache& revCache);

	QueryClauseResult
	buildBoolResult(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
					Cache& cache, Cache& revCache);
	QueryClauseResult
	buildClauseResult(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
					  Cache& cache, Cache& revCache);

	void computeAffects(int start, int end, bool isAffects);
	LMT computeAffects(int start, int end, LMT prevLMT, bool isAffects);
	LMT computeAffectsIfElse(const LMT& prevLMT, int start, bool isAffects);
	LMT computeAffectsWhile(const LMT& prevLMT, int start, int end, bool isAffects);
	void computeAffectsStmt(LMT& currLMT, int currStmtNum, EntityType currStmtType, bool isAffects);
	void computeAffectsAssign(LMT& currLMT, int currStmtNum);
	void computeAffectsTAssign(LMT& currLMT, int currStmtNum);
	void computeAffectsCall(LMT& currLMT, int currStmtNum);
	void computeAffectsRead(LMT& currLMT, int currStmtNum);

	int getNextSmaller(int currStmtNum);
	int getNextBigger(int currStmtNum);
	int getLastStmtOfBlock(int currStmtNum);
	int getNextForIf(int currStmtNum);
	int getNextForWhile(int currStmtNum);
	bool isProcLastStmt(int currStmtNum);

	static bool isValidArg(const std::string& argValue, EntityType argType);
	static LMT mergeLMT(const LMT& first, const LMT& second);

	CFG cfg;
	bool isAffectsCacheComplete;
	bool isAffectsTCacheComplete;
	std::function<bool(int)> terminateFunc;
	std::unordered_set<int> visitedLoops;    // prevent infinite recursion
	Cache affectsCache;
	Cache revAffectsCache;
	Cache affectsTCache;
	Cache revAffectsTCache;
};
