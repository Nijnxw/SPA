#include "EntityStager.h"

EntityStager::EntityStager() {}

void EntityStager::clear() {
	stagedProcedures.clear();
	stagedVariables.clear();
	stagedConstants.clear();

	stagedStatements.clear();
	stagedReadStatements.clear();
	stagedPrintStatements.clear();
	stagedIfStatements.clear();
	stagedWhileStatements.clear();
	stagedCallStatements.clear();

	stagedAssignStatements.clear();

	stagedFollows.clear();
	stagedFollowsT.clear();
	stagedParent.clear();
	stagedParentT.clear();
	stagedUsesStatement.clear();
	stagedUsesProcedure.clear();
	stagedModifiesStatement.clear();
	stagedModifiesProcedure.clear();
}

// getters
std::vector<std::string> EntityStager::getStagedProcedures() {
	return stagedProcedures;
}

std::vector<std::string> EntityStager::getStagedVariables() {
	return stagedVariables;
}

std::vector<std::string> EntityStager::getStagedConstants() {
	return stagedConstants;
}

std::vector<int> EntityStager::getStagedStatements() {
	return stagedStatements;
}

std::vector<int> EntityStager::getStagedReadStatements() {
	return stagedReadStatements;
}
std::vector<int> EntityStager::getStagedPrintStatements() {
	return stagedPrintStatements;
}

std::vector<int> EntityStager::getStagedIfStatements() {
	return stagedIfStatements;
}

std::vector<int> EntityStager::getStagedWhileStatements() {
	return stagedWhileStatements;
}

std::vector<int> EntityStager::getStagedCallStatements() {
	return stagedCallStatements;
}

std::vector<std::tuple<int, std::string, std::string>> EntityStager::getStagedAssignStatements() {
	return stagedAssignStatements;
}

std::vector<std::pair<int, int>> EntityStager::getStagedFollows() {
	return stagedFollows;
}

std::vector<std::pair<int, int>> EntityStager::getStagedFollowsT() {
	return stagedFollowsT;
}

std::vector<std::pair<int, int>> EntityStager::getStagedParent() {
	return stagedParent;
}

std::vector<std::pair<int, int>> EntityStager::getStagedParentT() {
	return stagedParentT;
}

std::vector<std::pair<int, std::unordered_set<std::string>>> EntityStager::getStagedUsesStatement() {
	return stagedUsesStatement;
}

std::vector<std::pair<std::string, std::unordered_set<std::string>>> EntityStager::getStagedUsesProcedure() {
	return stagedUsesProcedure;
}

std::vector<std::pair<int, std::unordered_set<std::string>>> EntityStager::getStagedModifiesStatement() {
	return stagedModifiesStatement;
}

std::vector<std::pair<std::string, std::unordered_set<std::string>>> EntityStager::getStagedModifiesProcedure() {
	return stagedModifiesProcedure;
}

// stagers
void EntityStager::stageProcedure(const std::string& procedure) {
	stagedProcedures.push_back(procedure);
}
void EntityStager::stageVariable(const std::string& variable) {
	stagedVariables.push_back(variable);
}
void EntityStager::stageConstant(const std::string& constant) {
	stagedConstants.push_back(constant);
}

void EntityStager::stageStatement(int stmtNo) {
	stagedStatements.push_back(stmtNo);
}

void EntityStager::stageIfStatement(int stmtNo) {
	stagedIfStatements.push_back(stmtNo);
}

void EntityStager::stageWhileStatement(int stmtNo) {
	stagedWhileStatements.push_back(stmtNo);
}

void EntityStager::stageReadStatement(int stmtNo) {
	stagedReadStatements.push_back(stmtNo);
}

void EntityStager::stagePrintStatement(int stmtNo) {
	stagedPrintStatements.push_back(stmtNo);
}

void EntityStager::stageCallStatement(int stmtNo) {
	stagedCallStatements.push_back(stmtNo);
}

void EntityStager::stageAssignStatement(int stmtNo, std::string lhs, std::string rhs) {
	stagedAssignStatements.push_back(std::make_tuple(stmtNo, lhs, rhs));
}

void EntityStager::stageFollows(int follower, int followee) {
	stagedFollows.push_back(std::make_pair(follower, followee));
}

void EntityStager::stageFollowsT(int follower, int followee) {
	stagedFollowsT.push_back(std::make_pair(follower, followee));
}

void EntityStager::stageParent(int parent, int child) {
	stagedParent.push_back(std::make_pair(parent, child));
}

void EntityStager::stageParentT(int parent, int child) {
	stagedParentT.push_back(std::make_pair(parent, child));
}

void EntityStager::stageUsesStatements(int stmt, std::unordered_set<std::string> variables) {
	stagedUsesStatement.push_back(std::make_pair(stmt, variables));
}

void EntityStager::stageUsesProcedure(std::string proc, std::unordered_set<std::string> variables) {
	stagedUsesProcedure.push_back(std::make_pair(proc, variables));
}

void EntityStager::stageModifiesStatements(int stmt, std::unordered_set<std::string> variables) {
	stagedModifiesStatement.push_back(std::make_pair(stmt, variables));

}

void EntityStager::stageModifiesProcedure(std::string proc, std::unordered_set<std::string> variables) {
	stagedModifiesProcedure.push_back(std::make_pair(proc, variables));
}

void EntityStager::commit() {
	for (auto& proc : stagedProcedures) { PKB::addProcedure(proc); }
	for (auto& var : stagedConstants) { PKB::addConstant(var); }
	for (auto& con : stagedVariables) { PKB::addVariable(con); }

	for (auto& stmt : stagedStatements) { PKB::addStatementNumber(stmt); }
	for (auto& read : stagedReadStatements) { PKB::addStatementNumber(read); }
	for (auto& print : stagedPrintStatements) { PKB::addStatementNumber(print); }
	for (auto& ifs : stagedIfStatements) { PKB::addStatementNumber(ifs); }
	for (auto& whiles : stagedWhileStatements) { PKB::addStatementNumber(whiles); }
	for (auto& call : stagedCallStatements) { PKB::addStatementNumber(call); }

	for (auto& assign : stagedAssignStatements) {
		PKB::addAssignStatement(std::get<0>(assign), std::get<1>(assign), std::get<2>(assign));
	}

	for (auto& follow : stagedFollows) {
		PKB::addFollows(follow.first, follow.second);
	}
	for (auto& followT : stagedFollowsT) {
		PKB::addFollowsT(followT.first, followT.second);
	}
	for (auto& parent : stagedParent) {
		PKB::addParent(parent.first, parent.second);
	}
	for (auto& parentT : stagedParentT) {
		PKB::addParentT(parentT.first, parentT.second);
	}
	for (auto& modifiesS : stagedModifiesStatement) {
		PKB::addModifiesStatement(modifiesS.first, modifiesS.second);
	}
	for (auto& modifiesP : stagedModifiesProcedure) {
		PKB::addModifiesProcedure(modifiesP.first, modifiesP.second);
	}
	for (auto& usesS : stagedUsesStatement) {
		PKB::addUsesStatement(usesS.first, usesS.second);
	}
	for (auto& usesP : stagedUsesProcedure) {
		PKB::addUsesProcedure(usesP.first, usesP.second);
	}
	EntityStager::clear();
}