#include "PatternIfEvaluator.h"

PatternIfEvaluator::PatternIfEvaluator()
	: PatternConditionEvaluator() {}

QueryClauseResult PatternIfEvaluator::getIfPattern(const std::string& LHS, const std::string& clauseSyn, EntityType LHSType, bool isBooleanResult)
{
	return PatternConditionEvaluator::getPattern(EntityType::IF, LHS, clauseSyn, LHSType, isBooleanResult);
}