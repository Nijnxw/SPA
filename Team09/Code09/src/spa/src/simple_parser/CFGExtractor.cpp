#include "CFGExtractor.h"

CFGExtractor::CFGExtractor() {}

void CFGExtractor::initialiseCFG(int totalStmts) {
	CFGExtractor::cfg.clear();
	for (int i = 0; i <= totalStmts; i++) {
		CFGExtractor::cfg.push_back({});
	}
}

void CFGExtractor::insertIntoCFG(std::unordered_set<int> prev, int next) {
	for (int x : prev) {
		std::unordered_set<int>& setToInsert = CFGExtractor::cfg.at(x);
		setToInsert.insert(next);
	}
}

//return final stmtNo to link to next node
std::unordered_set<int> CFGExtractor::extractCFGFromWhileNode(std::shared_ptr<WhileNode> whiles) {
	int origin = whiles->getStmtNumber();
	std::unordered_set<int> end = CFGExtractor::extractCFGFromStmtLst(origin, whiles->getStmtList());
	for (int x : end) {
		CFGExtractor::insertIntoCFG(end, origin);
	}
	return {origin};
}

//return final stmtNo to link to next node
std::unordered_set<int> CFGExtractor::extractCFGFromIfNode(std::shared_ptr<IfNode> ifs) {
	int origin = ifs->getStmtNumber();
	std::unordered_set<int> endThen = CFGExtractor::extractCFGFromStmtLst(origin, ifs->getThenStmtList());
	std::unordered_set<int> endElse = CFGExtractor::extractCFGFromStmtLst(origin, ifs->getElseStmtList());
	endThen.insert(endElse.begin(), endElse.end());
	return endThen;
}

std::unordered_set<int> CFGExtractor::extractCFGFromStmtLst(int prev, std::vector<std::shared_ptr<StmtNode>> stmtLst) {
	std::unordered_set<int> prevStmts = { prev };
	for (std::shared_ptr<StmtNode>& stmt : stmtLst) {
		CFGExtractor::insertIntoCFG(prevStmts, stmt->getStmtNumber());
		if (stmt->isIfNode()) {
			prevStmts = CFGExtractor::extractCFGFromIfNode(std::dynamic_pointer_cast<IfNode>(stmt));
		} else if (stmt->isWhileNode()) {
			prevStmts = CFGExtractor::extractCFGFromWhileNode(std::dynamic_pointer_cast<WhileNode>(stmt));
		} else {
			//assign, read, print, call are all treated equally
			prevStmts = { stmt->getStmtNumber() };
		}
	}
	return prevStmts;
}

std::unordered_set<int> CFGExtractor::extractCFGFromProcedure(std::shared_ptr<ProcedureNode> proc) {
	std::unordered_set<int> lastStmts = CFGExtractor::extractCFGFromStmtLst(PROG_START, proc->getStmtList());
	return lastStmts;
}

std::unordered_map<std::string, std::unordered_set<int>>
CFGExtractor::extractCFGFromProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap) {
	std::unordered_map<std::string, std::unordered_set<int>> mappings;
	for (auto& procPair : procMap) {
		std::unordered_set<int> lastStmts = CFGExtractor::extractCFGFromProcedure(procPair.second);
		mappings.insert({ procPair.first, lastStmts });
	}
	return mappings;
}

std::pair<CFG, std::unordered_map<std::string, std::unordered_set<int>>>
CFGExtractor::extractCFG(AST ast, int totalStmts) {
	CFGExtractor::initialiseCFG(totalStmts);
	std::unordered_map<std::string, std::unordered_set<int>> mappings = CFGExtractor::extractCFGFromProcedureList(ast->getProcedureMap());
	return std::make_pair(CFGExtractor::cfg, mappings);
}