#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/WhileNode.h"

#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <vector>

using CFG = std::vector<std::unordered_set<int>>;

#define PROG_START 0

class CFGExtractor {
private:
	static inline CFG cfg;
	CFGExtractor();
	static void initialiseCFG(int totalStmts);
	static void insertIntoCFG(std::unordered_set<int> prev, int next);
	static std::unordered_set<int> extractCFGFromWhileNode(std::shared_ptr<WhileNode> whiles);
	static std::unordered_set<int> extractCFGFromIfNode(std::shared_ptr<IfNode> ifs);
	static std::unordered_set<int> extractCFGFromStmtLst(int prev, std::vector<std::shared_ptr<StmtNode>> stmtLst);
	static std::unordered_set<int> extractCFGFromProcedure(std::shared_ptr<ProcedureNode> proc);
	static std::unordered_map<std::string, std::unordered_set<int>> extractCFGFromProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap);

public:
	static std::pair<CFG, std::unordered_map<std::string, std::unordered_set<int>>> extractCFG(AST ast, int totalStmts);
};
