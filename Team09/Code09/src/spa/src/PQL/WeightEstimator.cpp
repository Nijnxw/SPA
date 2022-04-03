#include "WeightEstimator.h"

const std::unordered_map<RelationRef, int> WeightEstimator::heuristicsToWeight = {
	{RelationRef::WITH, WeightEstimator::WITH_WEIGHT},
	{RelationRef::PATTERN_ASSIGN, WeightEstimator::PATTERN_ASSIGN_WEIGHT},
	{RelationRef::PATTERN_IF, WeightEstimator::PATTERN_IF_WEIGHT},
	{RelationRef::PATTERN_WHILE, WeightEstimator::PATTERN_WHILE_WEIGHT},
	{RelationRef::CALLS, WeightEstimator::CALLS_WEIGHT},
	{RelationRef::CALLS_T, WeightEstimator::CALLS_T_WEIGHT},
	{RelationRef::AFFECTS, WeightEstimator::AFFECTS_WEIGHT},
	{RelationRef::AFFECTS_T, WeightEstimator::AFFECTS_T_WEIGHT},
	{RelationRef::FOLLOWS, WeightEstimator::FOLLOWS_WEIGHT},
	{RelationRef::PARENT, WeightEstimator::PARENT_WEIGHT},
	{RelationRef::NEXT, WeightEstimator::NEXT_WEIGHT},
	{RelationRef::FOLLOWS_T, WeightEstimator::FOLLOWS_T_WEIGHT},
	{RelationRef::PARENT_T, WeightEstimator::PARENT_T_WEIGHT},
	{RelationRef::NEXT_T, WeightEstimator::NEXT_T_WEIGHT},
	{RelationRef::MODIFIES, WeightEstimator::MODIFIES_WEIGHT},
	{RelationRef::USES, WeightEstimator::USES_WEIGHT}
};

int WeightEstimator::estimateWeight(QueryClause clause) {
	int heuristicsWeight = getHeuristicsWeight(clause);
	int statisticsWeight = getStatisticsWeight(clause);

	return (heuristicsWeight * statisticsWeight) + heuristicsWeight;
}

int WeightEstimator::getHeuristicsWeight(QueryClause clause) {
	return heuristicsToWeight.at(clause.getClauseType());
}

int WeightEstimator::getStatisticsWeight(QueryClause clause) {
	std::vector<QueryArgument> clauseSynonyms = clause.getArguments();

	int statisticsWeight = 0;
	for (const auto& synonym : clauseSynonyms) {
		statisticsWeight += PKB::getNumSynonymsWithType(synonym.getType());
	}

	return statisticsWeight;
}