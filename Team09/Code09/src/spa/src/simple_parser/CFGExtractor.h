#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/WhileNode.h"

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iterator>

using CFG = std::vector<std::unordered_set<int>>;

class CFGExtractor {
private:
	static inline CFG cfg;
	CFGExtractor();
	static void initialiseCFG(int totalStmts);
	static void CFGExtractor::extractCFGFromWhileNode(std::shared_ptr<WhileNode> whiles);
	static void CFGExtractor::extractCFGFromIfNode(std::shared_ptr<IfNode> ifs);
	static void CFGExtractor::extractCFGFromStmtLst(std::shared_ptr<StmtNode> stmt);
	static void CFGExtractor::extractCFGFromProcedure(std::shared_ptr<ProcedureNode> proc);
	static void CFGExtractor::extractCFGFromProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap);

public:
	static CFG extractCFG(AST ast, int totalStmts);
};
