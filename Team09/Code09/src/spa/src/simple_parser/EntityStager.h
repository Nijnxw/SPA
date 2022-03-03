#pragma once

#include "pkb/PKB.h"
#include "models/EntityType.h"

#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

class EntityStager {
private:
	static inline std::unordered_set<std::string> stagedProcedures;
	static inline std::unordered_set<std::string> stagedVariables;
	static inline std::unordered_set<std::string> stagedConstants;

	static inline std::unordered_set<int> stagedStatements;
	static inline std::unordered_set<int> stagedReadStatements;
	static inline std::unordered_set<int> stagedPrintStatements;
	static inline std::unordered_set<int> stagedIfStatements;
	static inline std::unordered_set<int> stagedWhileStatements;
	static inline std::unordered_set<int> stagedCallStatements;

	static inline std::vector<std::tuple<int, std::string, std::string>> stagedAssignStatements;

	static inline std::vector<std::pair<int, int>> stagedFollows;
	static inline std::vector<std::pair<int, int>> stagedFollowsT;
	static inline std::vector<std::pair<int, int>> stagedParent;
	static inline std::vector<std::pair<int, int>> stagedParentT;
	static inline std::vector<std::pair<std::string, std::string>> stagedCalls;
	static inline std::vector<std::pair<std::string, std::string>> stagedCallsT;

	static inline std::vector<std::pair<int, std::unordered_set<std::string>>> stagedUsesStatement;
	static inline std::vector<std::pair<std::string, std::unordered_set<std::string>>> stagedUsesProcedure;
	static inline std::vector<std::pair<int, std::unordered_set<std::string>>> stagedModifiesStatement;
	static inline std::vector<std::pair<std::string, std::unordered_set<std::string>>> stagedModifiesProcedure;

public:
	EntityStager();

	static void clear();

	// getters
	static std::unordered_set<std::string> getStagedProcedures();
	static std::unordered_set<std::string> getStagedVariables();
	static std::unordered_set<std::string> getStagedConstants();

	static std::unordered_set<int> getStagedStatements();
	static std::unordered_set<int> getStagedReadStatements();
	static std::unordered_set<int> getStagedPrintStatements();
	static std::unordered_set<int> getStagedIfStatements();
	static std::unordered_set<int> getStagedWhileStatements();
	static std::unordered_set<int> getStagedCallStatements();

	static std::vector<std::tuple<int, std::string, std::string>> getStagedAssignStatements();

	static std::vector<std::pair<int, int>> getStagedFollows();
	static std::vector<std::pair<int, int>> getStagedFollowsT();
	static std::vector<std::pair<int, int>> getStagedParent();
	static std::vector<std::pair<int, int>> getStagedParentT();
	static std::vector<std::pair<std::string, std::string>> getStagedCalls();
	static std::vector<std::pair<std::string, std::string>> getStagedCallsT();

	static std::vector<std::pair<int, std::unordered_set<std::string>>> getStagedUsesStatement();
	static std::vector<std::pair<std::string, std::unordered_set<std::string>>> getStagedUsesProcedure();
	static std::vector<std::pair<int, std::unordered_set<std::string>>> getStagedModifiesStatement();
	static std::vector<std::pair<std::string, std::unordered_set<std::string>>> getStagedModifiesProcedure();

	// stagers
	static void stageProcedure(const std::string& procedure);
	static void stageVariable(const std::string& variable);
	static void stageConstant(const std::string& constant);

	static void stageStatement(int stmtNo);
	static void stageIfStatement(int stmtNo);
	static void stageWhileStatement(int stmtNo);
	static void stageReadStatement(int stmtNo);
	static void stagePrintStatement(int stmtNo);
	static void stageCallStatement(int stmtNo);

	static void stageAssignStatement(int stmtNo, std::string lhs, std::string rhs);

	static void stageFollows(int follower, int followee);
	static void stageFollowsT(int follower, int followee);
	static void stageParent(int parent, std::unordered_set<int> children);
	static void stageParentT(int parent, std::unordered_set<int> children);
	static void stageCalls(std::string caller, std::string callee);
	static void stageCallsT(std::string caller, std::string callee);

	static void stageUsesStatements(int stmt, std::unordered_set<std::string> variables);
	static void stageUsesProcedure(std::string proc, std::unordered_set<std::string> variables);

	static void stageModifiesStatements(int stmt, std::unordered_set<std::string> variables);
	static void stageModifiesProcedure(std::string proc, std::unordered_set<std::string> variables);

	static void commit();
};