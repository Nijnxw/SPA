#include "ProcVarStore.h"

// ============ GETTER METHODS ==============

std::unordered_set<std::string> ProcVarStore::getProcInRelationship() {
	return procInRelationship;
}

std::unordered_map<std::string, std::unordered_set<std::string>> ProcVarStore::getProcToVarRelationship() {
	return procToVarRelationship;
}

std::unordered_map<std::string, std::unordered_set<std::string>> ProcVarStore::getVarToProcRelationship() {
	return varToProcRelationship;
}

// ============ HELPER METHODS ==============

std::unordered_set<std::string> ProcVarStore::getVarByProc(const std::string& procName) {
	if (!getProcToVarRelationship().count(procName)) {
		return {};
	}
	return getProcToVarRelationship().at(procName);
}

std::unordered_set<std::string> ProcVarStore::getProcByVar(const std::string& variable) {
	if (!getVarToProcRelationship().count(variable)) {
		return {};
	}
	return getVarToProcRelationship().at(variable);
}

std::tuple<std::vector<std::string>, std::vector<std::string>>
ProcVarStore::getProcToVarByProcs(const std::unordered_set<std::string>& procs) {
	std::vector<std::string> resultProcs;
	std::vector<std::string> resultVars;
	for (std::string proc : procs) {
		for (const std::string& var : getVarByProc(proc)) {
			resultProcs.push_back(proc);
			resultVars.push_back(var);
		}
	}
	return { resultProcs, resultVars };
}

// ============ STORE METHODS ==============

bool ProcVarStore::addProcVarRelationship(const std::string& procedure, const std::unordered_set<std::string>& variables) {
	procInRelationship.insert(procedure);

	if (!procToVarRelationship.emplace(procedure, variables).second) {
		procToVarRelationship.at(procedure).insert(variables.begin(), variables.end());
	}

	for (const std::string& v : variables) {
		if (!varToProcRelationship.emplace(v, std::unordered_set<std::string>{procedure}).second) {
			varToProcRelationship.at(v).emplace(procedure);
		}
	}

	return true;
}
