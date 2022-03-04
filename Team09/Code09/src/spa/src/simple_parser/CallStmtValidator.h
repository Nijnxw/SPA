#pragma once

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class CallStmtValidator {
private:
	std::unordered_set<std::string> procNames;
	std::unordered_map<std::string, std::unordered_set<std::string>> callerCalleeMap;
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> recStack;

	bool isVisited(const std::string& procName);
	bool isCyclicCall(std::string caller);

public:
	CallStmtValidator();

	bool programHasProcName(const std::string& procName);
	void addProcName(std::string procName);
	void addProcCall(const std::string& caller, const std::string& callee);
	void checkCallStmtsValidity();
};

