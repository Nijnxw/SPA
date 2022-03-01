#include "PatternAssignEvaluator.h"

QueryClauseResult
PatternAssignEvaluator::getPattern(const std::string& LHS, const std::string& RHS, const std::string& clauseSyn,
							  EntityType LHSType, EntityType RHSType,
							  bool isBooleanResult) {

	std::unordered_map<int, AssignStatement> assignStatements = PKB::getAssignStatements();

	switch (LHSType) {
		case EntityType::VAR:
			return PatternAssignEvaluator::getPatternBySynonym(LHS, RHS, RHSType, clauseSyn, assignStatements);
		case EntityType::STRING:
			return PatternAssignEvaluator::getPatternByVariable(LHS, RHS, RHSType, clauseSyn, assignStatements);
		case EntityType::WILD:
			return PatternAssignEvaluator::getPatternByUnderscore(RHS, RHSType, clauseSyn, assignStatements);
		default:
			QueryClauseResult emptyQueryResult;
			return emptyQueryResult;
	}
}

QueryClauseResult
PatternAssignEvaluator::getPatternBySynonym(const std::string& LHS, const std::string& RHS, EntityType RHSType,
									   const std::string& clauseSyn,
									   const std::unordered_map<int, AssignStatement> assignStatements) {
	QueryClauseResult queryResult;
	std::vector<int> statementNumbers;
	std::vector<std::string> variables;

	switch (RHSType) {
		case EntityType::STRING:
			if (RHS[0] == '_') { // a(v, _"x"_)
				std::string trimmedRHS = RHS.substr(1, RHS.length() - 2);

				for (auto const& pair: assignStatements) {
					int statementNum = pair.first;
					AssignStatement statement = pair.second;
					std::string statementLHS = statement.getLeftHandSide();
					std::string statementRHS = statement.getRightHandSide();

					if (RPN::contains(statementRHS, trimmedRHS)) {
						statementNumbers.push_back(statementNum);
						variables.push_back(statementLHS);
					}
				}

				queryResult.addColumn(clauseSyn, statementNumbers);
				queryResult.addColumn(LHS, variables);
			} else { // a(v, "x + 1")
				for (auto const& pair: assignStatements) {
					int statementNum = pair.first;
					AssignStatement statement = pair.second;
					std::string statementLHS = statement.getLeftHandSide();
					std::string statementRHS = statement.getRightHandSide();

					if (statementRHS == RHS) {
						statementNumbers.push_back(statementNum);
						variables.push_back(statementLHS);
					}
				}

				queryResult.addColumn(clauseSyn, statementNumbers);
				queryResult.addColumn(LHS, variables);
			}
			break;
		case EntityType::WILD: // a(v, _)
			for (auto const& pair: assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				statementNumbers.push_back(statementNum);
				variables.push_back(statementLHS);
			}

			queryResult.addColumn(clauseSyn, statementNumbers);
			queryResult.addColumn(LHS, variables);

			break;
		default:
			break;
	}

	return queryResult;
}

QueryClauseResult
PatternAssignEvaluator::getPatternByVariable(const std::string& LHS, const std::string& RHS, EntityType RHSType,
										const std::string& clauseSyn,
										const std::unordered_map<int, AssignStatement> assignStatements) {
	QueryClauseResult queryResult;
	std::vector<int> statementNumbers;

	switch (RHSType) {
		case EntityType::STRING:
			if (RHS[0] == '_') { // a("x", _"x"_)
				std::string trimmedRHS = RHS.substr(1, RHS.length() - 2);

				for (auto const& pair: assignStatements) {
					int statementNum = pair.first;
					AssignStatement statement = pair.second;
					std::string statementLHS = statement.getLeftHandSide();
					std::string statementRHS = statement.getRightHandSide();

					if ((statementLHS == LHS) && (RPN::contains(statementRHS, trimmedRHS))) {
						statementNumbers.push_back(statementNum);
					}
				}

				queryResult.addColumn(clauseSyn, statementNumbers);
			} else { // a("x", "x + 1")
				for (auto const& pair: assignStatements) {
					int statementNum = pair.first;
					AssignStatement statement = pair.second;
					std::string statementLHS = statement.getLeftHandSide();
					std::string statementRHS = statement.getRightHandSide();

					if ((statementLHS == LHS) && (statementRHS == RHS)) {
						statementNumbers.push_back(statementNum);
					}
				}

				queryResult.addColumn(clauseSyn, statementNumbers);
			}
			break;
		case EntityType::WILD: // a("x", _)
			for (auto const& pair: assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				if (statementLHS == LHS) {
					statementNumbers.push_back(statementNum);
				}

				queryResult.addColumn(clauseSyn, statementNumbers);
			}
			break;
		default:
			break;
	}

	return queryResult;
}

QueryClauseResult
PatternAssignEvaluator::getPatternByUnderscore(const std::string& RHS, EntityType RHSType, const std::string& clauseSyn,
										  const std::unordered_map<int, AssignStatement> assignStatements) {
	QueryClauseResult queryResult;
	std::vector<int> statementNumbers;

	switch (RHSType) {
		case EntityType::STRING:
			if (RHS[0] == '_') { // a("x", _"x"_)
				std::string trimmedRHS = RHS.substr(1, RHS.length() - 2);

				for (auto const& pair: assignStatements) {
					int statementNum = pair.first;
					AssignStatement statement = pair.second;
					std::string statementLHS = statement.getLeftHandSide();
					std::string statementRHS = statement.getRightHandSide();

					if (RPN::contains(statementRHS, trimmedRHS)) {
						statementNumbers.push_back(statementNum);
					}
				}

				queryResult.addColumn(clauseSyn, statementNumbers);
			} else { // a("x", "x + 1")
				for (auto const& pair: assignStatements) {
					int statementNum = pair.first;
					AssignStatement statement = pair.second;
					std::string statementLHS = statement.getLeftHandSide();
					std::string statementRHS = statement.getRightHandSide();

					if (statementRHS == RHS) {
						statementNumbers.push_back(statementNum);
					}
				}

				queryResult.addColumn(clauseSyn, statementNumbers);
			}
			break;
		case EntityType::WILD: // a(_,  _)
			for (auto const& pair: assignStatements) {
				int statementNum = pair.first;
				AssignStatement statement = pair.second;
				std::string statementLHS = statement.getLeftHandSide();
				std::string statementRHS = statement.getRightHandSide();

				statementNumbers.push_back(statementNum);
			}

			queryResult.addColumn(clauseSyn, statementNumbers);

			break;
		default:
			break;
	}

	return queryResult;
}
