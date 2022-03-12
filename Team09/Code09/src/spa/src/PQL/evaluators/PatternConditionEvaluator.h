#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/AssignStatement.h"
#include "models/QueryClauseResult.h"

class PatternConditionEvaluator {
private:
	QueryClauseResult
		getPatternBySynonym(const std::string& LHS, const std::string& clauseSyn, const std::unordered_map<int, std::unordered_set<std::string>> statementNumbersToConditionalVariables);
	QueryClauseResult
		getPatternByVariable(const std::string& LHS, const std::string& clauseSyn, const std::unordered_map<int, std::unordered_set<std::string>> statementNumbersToConditionalVariables);
	QueryClauseResult getPatternByUnderscore(const std::string& clauseSyn, const std::unordered_map<int, std::unordered_set<std::string>> statementNumbersToConditionalVariables);

public:
	PatternConditionEvaluator();

	QueryClauseResult getPattern(EntityType patternType, const std::string& LHS, const std::string& clauseSyn, EntityType LHSType,
		bool isBooleanResult);
};