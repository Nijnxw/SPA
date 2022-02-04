#include "DesignExtractor.h"

DesignExtractor::DesignExtractor() {}

//PKB interface functions - TO DO: might xfer to another facade class
bool addProcedureToPkb(std::shared_ptr<ProcedureNode> proc) {
	return PKB::addProcedure(proc->getProcName());
}

bool addVariableToPkb(std::shared_ptr<VariableNode> var) {
	return PKB::addVariable(var->getName());
}

bool addConstantToPkb(std::shared_ptr<ConstantNode> con) {
	return PKB::addConstant(con->getValue());
}

bool addStmtNoToPkb(std::shared_ptr<StmtNode> stmt) {
	return PKB::addStatementNumber(stmt->getStmtNumber());
}

bool addPrintToPkb(std::shared_ptr<PrintNode> print) {
	return PKB::addStatementWithType(EntityType::PRINT, print->getStmtNumber());
}

bool addReadToPkb(std::shared_ptr<ReadNode> read) {
	return PKB::addStatementWithType(EntityType::READ, read->getStmtNumber());
}

//individual node processing functions
bool processPrintNode(std::shared_ptr<PrintNode> print) {
	return
		addVariableToPkb(print->getVariable()) &&
		addPrintToPkb(print);
}

bool processReadNode(std::shared_ptr<ReadNode> read) {
	return 
		addVariableToPkb(read->getVariable()) &&
		addReadToPkb(read);
}

//statement (list) processing functions
bool processStmt(std::shared_ptr<StmtNode> stmt) {
	bool result = addStmtNoToPkb(stmt);
	if (stmt->isReadNode()) {
		result = result && processReadNode(std::dynamic_pointer_cast<ReadNode>(stmt));
	} else if (stmt->isPrintNode()) {
		result = result && processPrintNode(std::dynamic_pointer_cast<PrintNode>(stmt));
	}
	return result;
}

bool processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList) {
	bool result = true;
	for (int i = 0; i < stmtList.size(); i++) {
		bool temp = processStmt(stmtList[i]);
		result = result && temp;
	}
	return result;
}

//procedure (list) processing functions
bool processProcedure(std::shared_ptr<ProcedureNode> proc) {
	return 
		addProcedureToPkb(proc) &&
		processStmtList(proc->getStmtList());
}

bool processProcedureList(std::vector<std::shared_ptr<ProcedureNode>> procList) {
	bool result = true;
	for (int i = 0; i < procList.size(); i++) {
		result = result && processProcedure(procList[i]);
	}
	return result;
}

bool DesignExtractor::extractDesignElements(AST ast) {
	return processProcedureList(ast->getProcedureList());
}