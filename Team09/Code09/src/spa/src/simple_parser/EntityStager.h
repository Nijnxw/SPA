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
	static inline std::vector<std::string> stagedProcedures;
	static inline std::vector<std::string> stagedVariables;
	static inline std::vector<std::string> stagedConstants;

	static inline std::vector<int> stagedStatements;
	static inline std::vector<int> stagedReadStatements;
	static inline std::vector<int> stagedPrintStatements;
	static inline std::vector<int> stagedIfStatements;
	static inline std::vector<int> stagedWhileStatements;
	static inline std::vector<int> stagedCallStatements;

	static inline std::vector<std::tuple<int, std::string, std::string>> stagedAssignStatements;

	static inline std::vector<std::pair<int, int>> stagedFollows;
	static inline std::vector<std::pair<int, int>> stagedFollowsT;
	static inline std::vector<std::pair<int, int>> stagedParent;
	static inline std::vector<std::pair<int, int>> stagedParentT;

	static inline std::vector<std::pair<int, std::unordered_set<std::string>>> stagedUsesStatement;
	static inline std::vector<std::pair<std::string, std::unordered_set<std::string>>> stagedUsesProcedure;
	static inline std::vector<std::pair<int, std::unordered_set<std::string>>> stagedModifiesStatement;
	static inline std::vector<std::pair<std::string, std::unordered_set<std::string>>> stagedModifiesProcedure;

public:
	EntityStager();

	static void clear();

	// getters
	static std::vector<std::string> getStagedProcedures();
	static std::vector<std::string> getStagedVariables();
	static std::vector<std::string> getStagedConstants();

	static std::vector<int> getStagedStatements();
	static std::vector<int> getStagedReadStatements();
	static std::vector<int> getStagedPrintStatements();
	static std::vector<int> getStagedIfStatements();
	static std::vector<int> getStagedWhileStatements();
	static std::vector<int> getStagedCallStatements();

	static std::vector<std::tuple<int, std::string, std::string>> getStagedAssignStatements();

	static std::vector<std::pair<int, int>> getStagedFollows();
	static std::vector<std::pair<int, int>> getStagedFollowsT();
	static std::vector<std::pair<int, int>> getStagedParent();
	static std::vector<std::pair<int, int>> getStagedParentT();

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
	static void stageParent(int parent, int child);
	static void stageParentT(int parent, int child);

	static void stageUsesStatements(int stmt, std::unordered_set<std::string> variables);
	static void stageUsesProcedure(std::string proc, std::unordered_set<std::string> variables);

	static void stageModifiesStatements(int stmt, std::unordered_set<std::string> variables);
	static void stageModifiesProcedure(std::string proc, std::unordered_set<std::string> variables);

	static void commit();
};