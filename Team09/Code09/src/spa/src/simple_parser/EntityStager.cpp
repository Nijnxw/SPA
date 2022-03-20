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
	stagedCalls.clear();
	stagedCallsT.clear();
	stagedUsesStatement.clear();
	stagedUsesProcedure.clear();
	stagedModifiesStatement.clear();
	stagedModifiesProcedure.clear();
	stagedCFG.clear();
	stagedProcToLastStmts.clear();
}

//helper function
template <typename T>
std::unordered_set<int> getStmtNoFromSet(std::unordered_map<int, T> store) {
	std::unordered_set<int> output;
	for (auto& s : store) {
		output.insert(s.first);
	}
	return output;
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
	return getStmtNoFromSet(stagedReadStatements);
}

std::unordered_map<int, std::string> EntityStager::getStagedReadContents() {
	return stagedReadStatements;
}

std::unordered_set<int> EntityStager::getStagedPrintStatements() {
	return getStmtNoFromSet(stagedPrintStatements);
}

std::unordered_map<int, std::string> EntityStager::getStagedPrintContents() {
	return stagedPrintStatements;
}

std::unordered_set<int> EntityStager::getStagedIfStatements() {
	return getStmtNoFromSet(stagedIfStatements);
}

std::unordered_map<int, std::unordered_set<std::string>> EntityStager::getStagedIfContents() {
	return stagedIfStatements;
}

std::unordered_set<int> EntityStager::getStagedWhileStatements() {
	return getStmtNoFromSet(stagedWhileStatements);
}

std::unordered_map<int, std::unordered_set<std::string>> EntityStager::getStagedWhileContents() {
	return stagedWhileStatements;
}

std::unordered_set<int> EntityStager::getStagedCallStatements() {
	return getStmtNoFromSet(stagedCallStatements);
}

std::unordered_map<int, std::string> EntityStager::getStagedCallContent() {
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

std::vector<std::pair<std::string, std::string>> EntityStager::getStagedCalls() {
	return stagedCalls;
}

std::vector<std::pair<std::string, std::string>> EntityStager::getStagedCallsT() {
	return stagedCallsT;
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

std::vector<std::unordered_set<int>> EntityStager::getCFG() {
	return stagedCFG;
}

std::unordered_map<std::string, std::unordered_set<int>> EntityStager::getStagedProcToLastStmts() {
	return stagedProcToLastStmts;
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

void EntityStager::stageIfStatement(int stmtNo, std::unordered_set<std::string> vars) {
	stagedIfStatements.insert({ stmtNo, vars });
}

void EntityStager::stageWhileStatement(int stmtNo, std::unordered_set<std::string> vars) {
	stagedWhileStatements.insert({ stmtNo, vars });
}

void EntityStager::stageReadStatement(int stmtNo, std::string varName) {
	stagedReadStatements.insert({stmtNo, varName});
}

void EntityStager::stagePrintStatement(int stmtNo, std::string varName) {
	stagedPrintStatements.insert({ stmtNo, varName });
}

void EntityStager::stageCallStatement(int stmtNo, std::string procName) {
	stagedCallStatements.insert({ stmtNo, procName });
}

void EntityStager::stageAssignStatement(int stmtNo, std::string lhs, std::string rhs) {
	stagedAssignStatements.emplace_back(stmtNo, lhs, rhs);
}

void EntityStager::stageFollows(int follower, int followee) {
	stagedFollows.emplace_back(follower, followee);
}

void EntityStager::stageFollowsT(int follower, int followee) {
	stagedFollowsT.emplace_back(follower, followee);
}

void EntityStager::stageParent(int parent, std::unordered_set<int> children) {
	for (int child: children) {
		stagedParent.emplace_back(parent, child);
	}
}

void EntityStager::stageParentT(int parent, std::unordered_set<int> children) {
	for (int child: children) {
		stagedParentT.emplace_back(parent, child);
	}
}

void EntityStager::stageCalls(std::string caller, std::string callee) {
	stagedCalls.emplace_back(caller, callee);
}

void EntityStager::stageCallsT(std::string caller, std::string callee) {
	stagedCallsT.emplace_back(caller, callee);
}

void EntityStager::stageUsesStatements(int stmt, std::unordered_set<std::string> variables) {
	stagedUsesStatement.emplace_back(stmt, variables);
}

void EntityStager::stageUsesProcedure(std::string proc, std::unordered_set<std::string> variables) {
	stagedUsesProcedure.emplace_back(proc, variables);
}

void EntityStager::stageModifiesStatements(int stmt, std::unordered_set<std::string> variables) {
	stagedModifiesStatement.emplace_back(stmt, variables);

}

void EntityStager::stageModifiesProcedure(std::string proc, std::unordered_set<std::string> variables) {
	stagedModifiesProcedure.emplace_back(proc, variables);
}

void EntityStager::stageCFG(std::vector<std::unordered_set<int>> cfg) {
	stagedCFG = cfg;
}

void EntityStager::stageLastStmtMapping(std::unordered_map<std::string, std::unordered_set<int>> mappings) {
	stagedProcToLastStmts = mappings;
}

void EntityStager::commit() {
	PKB::addCFG(stagedCFG);
	for (auto& proc: stagedProcedures) { PKB::addProcedure(proc); }
	for (auto& var: stagedConstants) { PKB::addConstant(var); }
	for (auto& con: stagedVariables) { PKB::addVariable(con); }

	for (auto& stmt: stagedStatements) { PKB::addStatementNumber(stmt); }
	for (auto& read: stagedReadStatements) {PKB::addReadStatement(read.first, read.second); }
	for (auto& print: stagedPrintStatements) { PKB::addPrintStatement(print.first, print.second); }
	for (auto& ifs: stagedIfStatements) { PKB::addIfStatement(ifs.first, ifs.second); }
	for (auto& whiles: stagedWhileStatements) { PKB::addWhileStatement(whiles.first, whiles.second); }
	for (auto& call: stagedCallStatements) { PKB::addCallStatement(call.first, call.second); }

	for (auto& assign: stagedAssignStatements) {
		PKB::addAssignStatement(std::get<0>(assign), std::get<1>(assign), std::get<2>(assign));
	}

	for (auto& follow: stagedFollows) {
		PKB::addFollows(follow.first, follow.second);
	}
	for (auto& followT: stagedFollowsT) {
		PKB::addFollowsT(followT.first, followT.second);
	}
	for (auto& parent: stagedParent) {
		PKB::addParent(parent.first, parent.second);
	}
	for (auto& parentT: stagedParentT) {
		PKB::addParentT(parentT.first, parentT.second);
	}
	for (auto& call : stagedCalls) {
		PKB::addCalls(call.first, call.second);
	}
	for (auto& callT : stagedCallsT) {
		PKB::addCallsT(callT.first, callT.second);
	}
	for (auto& modifiesS: stagedModifiesStatement) {
		PKB::addModifiesStatement(modifiesS.first, modifiesS.second);
	}
	for (auto& modifiesP: stagedModifiesProcedure) {
		PKB::addModifiesProcedure(modifiesP.first, modifiesP.second);
	}
	for (auto& usesS: stagedUsesStatement) {
		PKB::addUsesStatement(usesS.first, usesS.second);
	}
	for (auto& usesP: stagedUsesProcedure) {
		PKB::addUsesProcedure(usesP.first, usesP.second);
	}
	for (auto& lasts : stagedProcToLastStmts) {
		PKB::addProcedureNameToLastCFGNode(lasts.first, lasts.second);
	}
	EntityStager::clear();
}