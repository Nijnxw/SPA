#pragma once

#include "pkb/PKB.h"

#include <pair>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

class EntityStager {
private:
	static std::vector<std::string> stagedProcedures;
	static std::vector<std::string> stagedVariables;
	static std::vector<std::string> stagedConstants;

	static std::vector<int> stagedStatements;
	static std::vector<int> stagedReadStatements;
	static std::vector<int> stagedPrintStatements;
	static std::vector<int> stagedIfStatements;
	static std::vector<int> stagedWhileStatements;
	static std::vector<int> stagedCallStatements;

	static std::vector<std::tuple<int, std::string, std::string>> stagedAssignStatements;

	static std::vector<std::pair<int, int>> stagedFollows;
	static std::vector<std::pair<int, int>> stagedFollowsT;
	static std::vector<std::pair<int, int>> stagedParent;
	static std::vector<std::pair<int, int>> stagedParentT;

	static std::vector<std::pair<int, std::unordered_set<string>>> stagedUsesStatement;
	static std::vector<std::pair<std::string, std::unordered_set<string>>> stagedUsesProcedure;
	static std::vector<std::pair<int, std::unordered_set<string>>> stagedModifiesStatement;
	static std::vector<std::pair<std::string, std::unordered_set<string>>> stagedModifiesProcedure;

public:
	EntityStager();

	static void clear();
	static void commit();

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
};