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
std::unordered_set<std::string> EntityStager::getStagedProcedures() {
	return stagedProcedures;
}

std::unordered_set<std::string> EntityStager::getStagedVariables() {
	return stagedVariables;
}

std::unordered_set<std::string> EntityStager::getStagedConstants() {
	return stagedConstants;
}

std::unordered_set<int> EntityStager::getStagedStatements() {
	return stagedStatements;
}

std::unordered_set<int> EntityStager::getStagedReadStatements() {
	return stagedReadStatements;
}
std::unordered_set<int> EntityStager::getStagedPrintStatements() {
	return stagedPrintStatements;
}

std::unordered_set<int> EntityStager::getStagedIfStatements() {
	return stagedIfStatements;
}

std::unordered_set<int> EntityStager::getStagedWhileStatements() {
	return stagedWhileStatements;
}

std::unordered_set<int> EntityStager::getStagedCallStatements() {
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
	stagedProcedures.insert(procedure);
}
void EntityStager::stageVariable(const std::string& variable) {
	stagedVariables.insert(variable);
}
void EntityStager::stageConstant(const std::string& constant) {
	stagedConstants.insert(constant);
}

void EntityStager::stageStatement(int stmtNo) {
	stagedStatements.insert(stmtNo);
}

void EntityStager::stageIfStatement(int stmtNo) {
	stagedIfStatements.insert(stmtNo);
}

void EntityStager::stageWhileStatement(int stmtNo) {
	stagedWhileStatements.insert(stmtNo);
}

void EntityStager::stageReadStatement(int stmtNo) {
	stagedReadStatements.insert(stmtNo);
}

void EntityStager::stagePrintStatement(int stmtNo) {
	stagedPrintStatements.insert(stmtNo);
}

void EntityStager::stageCallStatement(int stmtNo) {
	stagedCallStatements.insert(stmtNo);
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
	for (auto& read : stagedReadStatements) { PKB::addStatementWithType(EntityType::READ, read); }
	for (auto& print : stagedPrintStatements) { PKB::addStatementWithType(EntityType::PRINT, print); }
	for (auto& ifs : stagedIfStatements) { PKB::addStatementWithType(EntityType::IF, ifs); }
	for (auto& whiles : stagedWhileStatements) { PKB::addStatementWithType(EntityType::WHILE, whiles); }
	for (auto& call : stagedCallStatements) { PKB::addStatementWithType(EntityType::CALL, call); }

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