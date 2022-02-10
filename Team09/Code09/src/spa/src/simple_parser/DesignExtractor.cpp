#include "DesignExtractor.h"

DesignExtractor::DesignExtractor() {}

//individual node processing functions
void processPrintNode(std::shared_ptr<PrintNode> print) {
	EntityStager::stageVariable(print->getVariable()->getName());
	EntityStager::stagePrintStatement(print->getStmtNumber());
}

void processReadNode(std::shared_ptr<ReadNode> read) {
	EntityStager::stageVariable(read->getVariable()->getName());
	EntityStager::stageReadStatement(read->getStmtNumber());
}

//statement (list) processing functions
void processStmt(std::shared_ptr<StmtNode> stmt) {
	EntityStager::stageStatement(stmt->getStmtNumber());
	if (stmt->isReadNode()) {
		processReadNode(std::dynamic_pointer_cast<ReadNode>(stmt));
	} else if (stmt->isPrintNode()) {
		processPrintNode(std::dynamic_pointer_cast<PrintNode>(stmt));
	}
}

void processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList) {
	for (int i = 0; i < stmtList.size(); i++) {
		if (i < stmtList.size() - 1) {
			EntityStager::stageFollows(stmtList[i]->getStmtNumber(), stmtList[i + 1]->getStmtNumber());
		}
		for (int j = i + 1; j < stmtList.size(); j++) {
			EntityStager::stageFollowsT(stmtList[i]->getStmtNumber(), stmtList[j]->getStmtNumber());
		}
		processStmt(stmtList[i]);
	}
}

//procedure (list) processing functions
void processProcedure(std::shared_ptr<ProcedureNode> proc) {
	EntityStager::stageProcedure(proc->getProcName());
	processStmtList(proc->getStmtList());
}

void processProcedureList(std::vector<std::shared_ptr<ProcedureNode>> procList) {
	for (int i = 0; i < procList.size(); i++) {
		processProcedure(procList[i]);
	}
}

void DesignExtractor::extractDesignElements(AST ast) {
	EntityStager::clear();
	processProcedureList(ast->getProcedureList());
}

void DesignExtractor::commit() {
	EntityStager::commit();
}