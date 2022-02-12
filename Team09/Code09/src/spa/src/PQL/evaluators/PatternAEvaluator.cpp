#include "PatternAEvaluator.h"

QueryClauseTable PatternAEvaluator::getPattern(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {

	std::unordered_map<int, AssignStatement> assignStatements = PKB::getAssignStatements();

	switch (LHSType) {
	case EntityType::VAR:
		return PatternAEvaluator::getPatternBySynonym(LHS, RHS, RHSType, assignStatements);
	case EntityType::STRING:
		return PatternAEvaluator::getPatternByVariable(LHS, RHS, RHSType, assignStatements);
	case EntityType::WILD:
		return PatternAEvaluator::getPatternByUnderscore(RHS, RHSType, assignStatements);
	default:
		QueryClauseTable emptyQueryResult;
		return emptyQueryResult;
	}
}

QueryClauseTable PatternAEvaluator::getPatternBySynonym(const std::string& LHS, const std::string& RHS, EntityType RHSType, 
const std::unordered_map<int, AssignStatement> assignStatements) {
	QueryClauseTable queryResult;
	std::vector<int> statementNumbers;
	std::vector<std::string> variables;

	switch (RHSType) {
	case EntityType::STRING: 
		if (RHS[0] == '_') { // a(v, _"x"_)
			std::string trimmedRHS = RHS.substr(1, RHS.length() - 2);

			for (auto const& pair : assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				if (RPN::contains(statementRHS, trimmedRHS)) {
					statementNumbers.push_back(statementNum);
					variables.push_back(statementLHS);
				}
			}

			queryResult.addColumn("a", statementNumbers);
			queryResult.addColumn(LHS, variables);
		}
		else { // a(v, ”x + 1”) 
			for (auto const& pair : assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				if (statementRHS == RHS) {
					statementNumbers.push_back(statementNum);
					variables.push_back(statementLHS);
				}
			}

			queryResult.addColumn("a", statementNumbers);
			queryResult.addColumn(LHS, variables);
		}
		break;
	case EntityType::WILD: // a(v, _)
		for (auto const& pair : assignStatements) {
			int statementNum = pair.first;
			AssignStatement statement = pair.second;
			std::string statementLHS = statement.getLeftHandSide();
			std::string statementRHS = statement.getRightHandSide();

			statementNumbers.push_back(statementNum);
			variables.push_back(statementLHS);
		}

		queryResult.addColumn("a", statementNumbers);
		queryResult.addColumn(LHS, variables);

		break;
	default:
		break;
	}

	return queryResult;
}

QueryClauseTable PatternAEvaluator::getPatternByVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType, 
	const std::unordered_map<int, AssignStatement> assignStatements) {
	QueryClauseTable queryResult;
	std::vector<int> statementNumbers;

	switch (RHSType) {
	case EntityType::STRING: 
		if (RHS[0] == '_') { // a("x", _"x"_)
			std::string trimmedRHS = RHS.substr(1, RHS.length() - 2);

			for (auto const& pair : assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				if ((statementLHS == LHS) && (RPN::contains(statementRHS, trimmedRHS))) {
					statementNumbers.push_back(statementNum);
				}
			}

			queryResult.addColumn("a", statementNumbers);
		}
		else { // a("x", ”x + 1”)
			for (auto const& pair : assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				if ((statementLHS == LHS) && (statementRHS == RHS)) {
					statementNumbers.push_back(statementNum);
				}
			}

			queryResult.addColumn("a", statementNumbers);
		}
		break;
	break;
	case EntityType::WILD: // a(“x”, _)
		for (auto const& pair : assignStatements) {
			int statementNum = pair.first;
			AssignStatement statement = pair.second;
			std::string statementLHS = statement.getLeftHandSide();
			std::string statementRHS = statement.getRightHandSide();

			if (statementLHS == LHS) {
				statementNumbers.push_back(statementNum);
			}

			queryResult.addColumn("a", statementNumbers);
		}
		break;
	default:
		break;
	}

	return queryResult;
}
QueryClauseTable PatternAEvaluator::getPatternByUnderscore(const std::string& RHS, EntityType RHSType, 
	const std::unordered_map<int, AssignStatement> assignStatements) {
	QueryClauseTable queryResult;
	std::vector<int> statementNumbers;

	switch (RHSType) {
	case EntityType::STRING: 
		if (RHS[0] == '_') { // a("x", _"x"_)
			std::string trimmedRHS = RHS.substr(1, RHS.length() - 2);

			for (auto const& pair : assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				if (RPN::contains(statementRHS, trimmedRHS)) {
					statementNumbers.push_back(statementNum);
				}
			}

			queryResult.addColumn("a", statementNumbers);
		}
		else { // a("x", ”x + 1”)
			for (auto const& pair : assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				if (statementRHS == RHS) {
					statementNumbers.push_back(statementNum);
				}
			}

			queryResult.addColumn("a", statementNumbers);
		}
		break;
	case EntityType::WILD: // a(_,  _)
		for (auto const& pair : assignStatements) {
			int statementNum = pair.first;
			AssignStatement statement = pair.second;
			std::string statementLHS = statement.getLeftHandSide();
			std::string statementRHS = statement.getRightHandSide();

			statementNumbers.push_back(statementNum);
		}

		queryResult.addColumn("a", statementNumbers);

		break;
	default:
		break;
	}

	return queryResult;
}
