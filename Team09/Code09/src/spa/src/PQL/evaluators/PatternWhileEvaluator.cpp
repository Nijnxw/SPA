#include "PatternWhileEvaluator.h"

PatternWhileEvaluator::PatternWhileEvaluator()
	: PatternConditionEvaluator() {}

QueryClauseResult PatternWhileEvaluator::getWhilePattern(const std::string& LHS, const std::string& clauseSyn, EntityType LHSType, bool isBooleanResult)
{
	return PatternConditionEvaluator::getPattern(EntityType::WHILE, LHS, clauseSyn, LHSType, isBooleanResult);
}