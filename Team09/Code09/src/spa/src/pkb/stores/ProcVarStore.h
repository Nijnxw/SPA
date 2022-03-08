#pragma once

#include "pkb/stores/Store.h"

class ProcVarStore : public Store {
protected:
	std::unordered_set<std::string> procInRelationship;
	std::unordered_map<std::string, std::unordered_set<std::string>> procToVarRelationship;
	std::unordered_map<std::string, std::unordered_set<std::string>> varToProcRelationship;

public:
	/* Getters called by QE */
	std::unordered_set<std::string> getProcInRelationship();
	std::unordered_map<std::string, std::unordered_set<std::string>> getProcToVarRelationship();
	std::unordered_map<std::string, std::unordered_set<std::string>> getVarToProcRelationship();

	std::unordered_set<std::string> getVarByProc(const std::string& procName);
	std::unordered_set<std::string> getProcByVar(const std::string& variable);
	std::tuple<std::vector<std::string>, std::vector<std::string>> getProcToVarByProcs(const std::unordered_set<std::string>& procs);

	/* Setters called by DE */
	bool addProcVarRelationship(const std::string& procedure, const std::unordered_set<std::string>& variables);
};
