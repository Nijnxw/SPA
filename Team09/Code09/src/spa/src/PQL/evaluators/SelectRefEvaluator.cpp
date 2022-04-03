#include "SelectRefEvaluator.h"

void
SelectRefEvaluator::evaluate(Table& results,
							 const std::unordered_set<QueryArgument, std::hash<QueryArgument>>& args) {
	for (const auto& arg: args) {
		supplementResults(results, arg);
	}
}

void SelectRefEvaluator::supplementResults(Table& table, const QueryArgument& arg) {
	if (table.find(arg.getValue()) == table.end()) {
		return;
	}
	AttributeRef ref = arg.getAttrRef();
	EntityType type = arg.getType();
	std::string val = arg.getValue();

	std::vector<std::string> outputCol;
	if (ref == AttributeRef::STMT_NO || (type == EntityType::PROC && ref == AttributeRef::PROC_NAME) ||
		(type == EntityType::CONST && ref == AttributeRef::VALUE) ||
		(type == EntityType::VAR && ref == AttributeRef::VAR_NAME)) {

		const std::vector<std::string>& stmtNum = table.at(val);
		outputCol = {stmtNum.begin(), stmtNum.end()};

	} else if (type == EntityType::CALL && ref == AttributeRef::PROC_NAME) {

		const std::vector<std::string>& stmtNums = table.at(val);
		const std::unordered_map<int, std::string>& stmtToProc = PKB::getCallStatementsToProcedures();
		for (const auto& num: stmtNums) {
			outputCol.push_back(stmtToProc.at(std::stoi(num)));
		}

	} else if ((type == EntityType::READ || type == EntityType::PRINT) && ref == AttributeRef::VAR_NAME) {

		std::unordered_map<int, std::string> stmtToVar;
		if (type == EntityType::READ) {
			stmtToVar = PKB::getReadStatementsToVariables();
		} else {
			stmtToVar = PKB::getPrintStatementsToVariables();
		}

		const std::vector<std::string>& stmtNums = table.at(val);
		for (const auto& num: stmtNums) {
			outputCol.push_back(stmtToVar.at(std::stoi(num)));
		}

	} else {
		return;
	}
	table.emplace(arg.toString(), outputCol);
}
