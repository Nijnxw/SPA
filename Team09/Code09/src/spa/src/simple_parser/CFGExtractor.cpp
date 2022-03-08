#include "CFGExtractor.h"

CFGExtractor::CFGExtractor() {}

void CFGExtractor::initialiseCFG(int totalStmts) {
	CFGExtractor::cfg.clear();
	for (int i = 0; i < totalStmts + 1; i++) {
		CFGExtractor::cfg.push_back({});
	}
}

void CFGExtractor::extractCFGFromWhileNode(std::shared_ptr<WhileNode> whiles) {

}

void CFGExtractor::extractCFGFromIfNode(std::shared_ptr<IfNode> ifs) {

}

void CFGExtractor::extractCFGFromStmtLst(std::shared_ptr<StmtNode> stmt) {

}

void CFGExtractor::extractCFGFromProcedure(std::shared_ptr<ProcedureNode> proc) {

}

void CFGExtractor::extractCFGFromProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap) {

}

CFG CFGExtractor::extractCFG(AST ast, int totalStmts) {
	CFGExtractor::initialiseCFG(totalStmts);

	return CFGExtractor::cfg;
}