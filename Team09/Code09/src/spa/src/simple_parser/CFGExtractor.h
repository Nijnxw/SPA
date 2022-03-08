#pragma once

#include "models/simple_parser/AST.h"

#include <vector>
#include <unordered_set>

using CFG = std::vector<std::unordered_set<int>>;

class CFGExtractor {
private:
	CFGExtractor();

public:
	static CFG extractCFG(AST ast, int totalStmts);
};
