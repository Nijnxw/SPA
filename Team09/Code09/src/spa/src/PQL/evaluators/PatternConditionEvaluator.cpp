#include "PatternConditionEvaluator.h"

QueryClauseResult
PatternConditionEvaluator::getPattern(EntityType patternType, const std::string& LHS, const std::string& clauseSyn,
									  EntityType LHSType, bool isBooleanResult) {
	std::unordered_map<int, std::unordered_set<std::string>> statementNumbersToConditionalVariables;

	if (patternType == EntityType::IF) {
		statementNumbersToConditionalVariables = PKB::getIfStatementsToConditionalVariables();
	} else if (patternType == EntityType::WHILE) {
		statementNumbersToConditionalVariables = PKB::getWhileStatementsToConditionalVariables();
	} else {
		return {};
	}

	switch (LHSType) {
		case EntityType::VAR: // ifs(v, _, _) or w(v, _)
			return PatternConditionEvaluator::getPatternBySynonym(LHS, clauseSyn,
																  statementNumbersToConditionalVariables);
		case EntityType::STRING: // ifs("x", _, _) or w("x", _)
			return PatternConditionEvaluator::getPatternByVariable(LHS, clauseSyn,
																   statementNumbersToConditionalVariables);
		case EntityType::WILD: // ifs(_, _, _) or w(_, _)
			return PatternConditionEvaluator::getPatternByUnderscore(clauseSyn, statementNumbersToConditionalVariables);
		default:
			return {};
	}
}

QueryClauseResult
PatternConditionEvaluator::getPatternBySynonym(const std::string& LHS, const std::string& clauseSyn,
											   const std::unordered_map<int, std::unordered_set<std::string>>& statementNumbersToConditionalVariables) {
	QueryClauseResult queryResult;
	std::vector<int> statementNumbers;
	std::vector<std::string> variables;

	for (auto const& pair: statementNumbersToConditionalVariables) {
		int statementNum = pair.first;
		const std::unordered_set<std::string>& conditionalVariables = pair.second;

		for (const auto& conditionalVariable: conditionalVariables) {
			statementNumbers.push_back(statementNum);
			variables.push_back(conditionalVariable);
		}
	}

	queryResult.addColumn(clauseSyn, statementNumbers);
	queryResult.addColumn(LHS, variables);

	return queryResult;
}

QueryClauseResult
PatternConditionEvaluator::getPatternByVariable(const std::string& LHS, const std::string& clauseSyn,
												const std::unordered_map<int, std::unordered_set<std::string>>& statementNumbersToConditionalVariables) {
	QueryClauseResult queryResult;
	std::vector<int> statementNumbers;

	for (const auto& pair: statementNumbersToConditionalVariables) {
		int statementNum = pair.first;
		const std::unordered_set<std::string>& conditionalVariables = pair.second;

		if (conditionalVariables.count(LHS) > 0) {
			statementNumbers.push_back(statementNum);
		}
	}

	queryResult.addColumn(clauseSyn, statementNumbers);

	return queryResult;
}

QueryClauseResult
PatternConditionEvaluator::getPatternByUnderscore(const std::string& clauseSyn,
												  const std::unordered_map<int, std::unordered_set<std::string>>& statementNumbersToConditionalVariables) {
	QueryClauseResult queryResult;
	std::vector<int> statementNumbers;

	for (const auto& pair: statementNumbersToConditionalVariables) {
		int statementNum = pair.first;
		if (!pair.second.empty()) { // Only if the if/while has variables
			statementNumbers.push_back(statementNum);
		}
	}

	queryResult.addColumn(clauseSyn, statementNumbers);

	return queryResult;
}
