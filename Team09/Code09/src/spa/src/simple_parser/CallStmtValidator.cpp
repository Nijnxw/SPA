#include "CallStmtValidator.h"

CallStmtValidator::CallStmtValidator() = default;

bool CallStmtValidator::programHasProcName(const std::string& procName) {
	return procNames.find(procName) != procNames.end();
}

void CallStmtValidator::addProcName(std::string procName) {
	procNames.emplace(procName);
}

void CallStmtValidator::addProcCall(const std::string& caller, const std::string& callee) {
	// SEMANTIC RULE: Recursive calls are not allowed.
	if (caller == callee) {
		throw std::runtime_error("Recursive calls are not allowed. Procedure '" + caller + "' tried to call itself.\n");
	}
	callerCalleeMap[caller].emplace(callee);
}

bool CallStmtValidator::isVisited(const std::string& procName) {
	return visited.find(procName) != visited.end();
}

bool CallStmtValidator::isCyclicCall(std::string caller) {
	// SEMANTIC RULE: A procedure cannot call a non-existing procedure.
	if (!programHasProcName(caller)) {
		throw std::runtime_error("A procedure cannot call a non-existing procedure.\n");
	}

	if (!isVisited(caller)) {
		visited.emplace(caller);
		recStack.emplace(caller);

		for (const auto& callee : callerCalleeMap[caller]) {
			assert(caller != callee); // assumption: semantic rule handled in addProcCall function
			if (!isVisited(callee) && isCyclicCall(callee)) return true;
			if (recStack.find(callee) != recStack.end()) return true;
		}
	}

	recStack.erase(caller);
	return false;
}

void CallStmtValidator::checkCallStmtsValidity() {
	// SEMANTIC RULE: Cyclic calls are not allowed.
	// DFS to check for cyclic calls
	visited.clear();
	recStack.clear();

	for (auto const& [caller, callees] : callerCalleeMap) {
		if (!isVisited(caller) && isCyclicCall(caller)) {
			throw std::runtime_error("Cyclic calls are not allowed.\n");
		}
	}
}