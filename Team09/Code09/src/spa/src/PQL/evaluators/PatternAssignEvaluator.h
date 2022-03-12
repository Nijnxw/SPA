#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/AssignStatement.h"
#include "models/QueryClauseResult.h"
#include "util/RPN.h"

#include "PatternEvaluator.h"

class PatternAssignEvaluator : public PatternEvaluator {
private:
	QueryClauseResult
	getPatternBySynonym(const std::string& LHS, const std::string& RHS, EntityType RHSType, const std::string& clauseSyn,
						const std::unordered_map<int, AssignStatement> assignStatements);
	QueryClauseResult
	getPatternByVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType, const std::string& clauseSyn,
						 const std::unordered_map<int, AssignStatement> assignStatements);
	QueryClauseResult getPatternByUnderscore(const std::string& RHS, EntityType RHSType, const std::string& clauseSyn,
											 const std::unordered_map<int, AssignStatement> assignStatements);

public:
	PatternAssignEvaluator();

	QueryClauseResult getPattern(const std::string& LHS, const std::string& RHS, const std::string& clauseSyn, EntityType LHSType, EntityType RHSType,
								 bool isBooleanResult);
};