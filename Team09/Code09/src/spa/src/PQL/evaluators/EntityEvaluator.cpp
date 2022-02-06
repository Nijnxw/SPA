#include "EntityEvaluator.h"
#include "pkb/PKB.h"

QueryClauseTable EntityEvaluator::evaluate(QueryArgument& entity) {
	Table result;
	std::vector<std::string> rows;
	switch (entity.getType()) {
		case EntityType::ASSIGN:
			rows = keySetIntToStringVector(PKB::getAssignStatements());
			break;
		case EntityType::STMT:
			rows = setIntToStringVector(PKB::getStatementNumbers());
			break;
		case EntityType::VAR: {
			std::unordered_set<std::string> vars = PKB::getVariables();
			rows = {vars.begin(), vars.end()};
			break;
		}
		case EntityType::PROC: {
			std::unordered_set<std::string> procedures = PKB::getProcedures();
			rows = {procedures.begin(), procedures.end()};
			break;
		}
		case EntityType::CONST: {
			std::unordered_set<std::string> constants = PKB::getConstants();
			rows = {constants.begin(), constants.end()};
			break;
		}
		case EntityType::CALL:
		case EntityType::READ:
		case EntityType::PRINT:
		case EntityType::WHILE:
		case EntityType::IF:
			rows = setIntToStringVector(PKB::getStatementsWithType(entity.getType()));
			break;
		default:
			return {};
	}
	result.emplace(entity.getValue(), rows);

	return {result};
}

template<typename T>
std::vector<std::string> EntityEvaluator::keySetIntToStringVector(const std::unordered_map<int, T>& map) {
	std::vector<std::string> rows;
	for (const auto& keyVal: map) {
		rows.push_back(std::to_string(keyVal.first));
	}
	return rows;
}

std::vector<std::string> EntityEvaluator::setIntToStringVector(const std::unordered_set<int>& set) {
	std::vector<std::string> rows;
	for (const auto& val: set) {
		rows.push_back(std::to_string(val));
	}
	return rows;
}
