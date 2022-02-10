#include "DesignExtractor.h"

DesignExtractor::DesignExtractor() {}

//primitive node processing functions
void processConstantNode(std::shared_ptr<ConstantNode> constant) {
	EntityStager::stageConstant(constant->getValue());
}

void processVariableNode(std::shared_ptr<VariableNode> variable) {
	EntityStager::stageVariable(variable->getName());
}

//helper expression node processing functions

//process ExprNodes; only assignNode call this
void processExprNode(int stmtNo, ExprNode expr);

//overloaded functions to handle ExprNode variants
void processExprEntity(int stmtNo, std::shared_ptr<ConstantNode> constant) {
	processConstantNode(constant);
}

void processExprEntity(int stmtNo, std::shared_ptr<VariableNode> variable) {
	processVariableNode(variable);
	std::unordered_set<std::string> vars{ variable->getName() };
	EntityStager::stageUsesStatements(stmtNo, vars);
}

void processExprEntity(int stmtNo, std::shared_ptr<BinaryOperatorNode> binOp) {
	processExprNode(stmtNo, binOp->getLhs());
	processExprNode(stmtNo, binOp->getRhs());
}

void processExprNode(int stmtNo, ExprNode expr) {
	std::visit(
		[stmtNo](const auto& entity) { processExprEntity(stmtNo, entity); },
		expr);
}

//individual stmt node processing functions
void processPrintNode(std::shared_ptr<PrintNode> print) {
	processVariableNode(print->getVariable());
	//todo: implement getVariableName() -> current implementatiaon violates law of dementer
	std::unordered_set<std::string> vars;
	vars.insert(print->getVariable()->getName());

	EntityStager::stageUsesStatements(print->getStmtNumber(), vars);
	EntityStager::stagePrintStatement(print->getStmtNumber());
}

void processReadNode(std::shared_ptr<ReadNode> read) {
	processVariableNode(read->getVariable());
	//todo: implement getVariableName() -> current implementatiaon violates law of dementer
	std::unordered_set<std::string> vars;
	vars.insert(read->getVariable()->getName());

	EntityStager::stageModifiesStatements(read->getStmtNumber(), vars);
	EntityStager::stageReadStatement(read->getStmtNumber());
}

void processAssignNode(std::shared_ptr<AssignNode> assign) {
	EntityStager::stageAssignStatement(
		assign->getStmtNumber(),
		assign->getAssignedVar()->getName(),
		assign->getPostfix());
	//process lhs
	processVariableNode(assign->getAssignedVar());
	//todo: implement getAssignedVarName() -> current implementatiaon violates law of dementer
	std::unordered_set<std::string> vars;
	vars.insert(assign->getAssignedVar()->getName());
	EntityStager::stageModifiesStatements(assign->getStmtNumber(), vars);

	//process rhs
	processExprNode(assign->getStmtNumber(), assign->getExpression());
}

//statement (list) processing functions
void processStmt(std::shared_ptr<StmtNode> stmt) {
	EntityStager::stageStatement(stmt->getStmtNumber());
	if (stmt->isReadNode()) {
		processReadNode(std::dynamic_pointer_cast<ReadNode>(stmt));
	} else if (stmt->isPrintNode()) {
		processPrintNode(std::dynamic_pointer_cast<PrintNode>(stmt));
	} else if (stmt->isAssignNode()) {
		processAssignNode(std::dynamic_pointer_cast<AssignNode>(stmt));
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