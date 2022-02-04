#include "DesignExtractor.h"

DesignExtractor::DesignExtractor() {}

//PKB interface functions - TO DO: might xfer to another facade class
void addProcedureToPkb(std::shared_ptr<ProcedureNode> proc) {
	PKB::addProcedure(proc->getProcName());
}

void addVariableToPkb(std::shared_ptr<VariableNode> var) {
	PKB::addVariable(var->getName());
}

void addConstantToPkb(std::shared_ptr<ConstantNode> con) {
	PKB::addConstant(con->getValue());
}

void addStmtNoToPkb(std::shared_ptr<StmtNode> stmt) {
	PKB::addStatementNumber(stmt->getStmtNumber());
}

void addPrintToPkb(std::shared_ptr<PrintNode> print) {
	PKB::addStatementWithType(EntityType::PRINT, print->getStmtNumber());
}

void addReadToPkb(std::shared_ptr<ReadNode> read) {
	PKB::addStatementWithType(EntityType::READ, read->getStmtNumber());
}

//individual node processing functions
void processPrintNode(std::shared_ptr<PrintNode> print) {
	addVariableToPkb(print->getVariable());
	addPrintToPkb(print);
}

void processReadNode(std::shared_ptr<ReadNode> read) {
	addVariableToPkb(read->getVariable());
	addReadToPkb(read);
}

//statement (list) processing functions
void processStmt(std::shared_ptr<StmtNode> stmt) {
	addStmtNoToPkb(stmt);
	if (stmt->isReadNode()) {
		processReadNode(std::dynamic_pointer_cast<ReadNode>(stmt));
	} else if (stmt->isPrintNode()) {
		processPrintNode(std::dynamic_pointer_cast<PrintNode>(stmt));
	}
}

void processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList) {
	for (int i = 0; i < stmtList.size(); i++) {
		processStmt(stmtList[i]);
	}
}

//procedure (list) processing functions
void processProcedure(std::shared_ptr<ProcedureNode> proc) {
	addProcedureToPkb(proc);
	processStmtList(proc->getStmtList());
}

void processProcedureList(std::vector<std::shared_ptr<ProcedureNode>> procList) {
	for (int i = 0; i < procList.size(); i++) {
		processProcedure(procList[i]);
	}
}

void DesignExtractor::extractDesignElements(AST ast) {
	processProcedureList(ast->getProcedureList());
}