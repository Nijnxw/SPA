#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/AssignStatement.h"
#include "models/QueryClauseTable.h"
#include "util/RPN.h"

#include "PatternEvaluator.h"

class PatternAEvaluator : public PatternEvaluator {
private:
	QueryClauseTable
		getPatternBySynonym(const std::string& LHS, const std::string& RHS, EntityType RHSType, 
			const std::unordered_map<int, AssignStatement> assignStatements);
	QueryClauseTable
		getPatternByVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType, 
			const std::unordered_map<int, AssignStatement> assignStatements);
	QueryClauseTable getPatternByUnderscore(const std::string& RHS, EntityType RHSType, 
		const std::unordered_map<int, AssignStatement> assignStatements);

public:
	QueryClauseTable getPattern(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
};