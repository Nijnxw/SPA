#include "DesignExtractor.h"

DesignExtractor::DesignExtractor() {}
DesignRelationships processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList);

//primitive node processing functions
void processConstantNode(std::shared_ptr<ConstantNode> constant) {
	EntityStager::stageConstant(constant->getValue());
}

void processVariableNode(std::shared_ptr<VariableNode> variable) {
	EntityStager::stageVariable(variable->getName());
}

//helper expression node processing functions

//process ExprNodes
DesignRelationships processExprNode(ExprNode expr);

//overloaded functions to handle ExprNode variants
DesignRelationships processExprEntity(std::shared_ptr<ConstantNode> constant) {
	processConstantNode(constant);
	return DesignRelationships::createEmpty();
}

DesignRelationships processExprEntity(std::shared_ptr<VariableNode> variable) {
	processVariableNode(variable);
	std::unordered_set<std::string> vars{ variable->getName() };

	DesignRelationships output = DesignRelationships::createEmpty();
	output.addUses(variable->getName());
	return output;
}

DesignRelationships processExprEntity(std::shared_ptr<BinaryOperatorNode> binOp) {
	DesignRelationships rs = processExprNode(binOp->getLhs());
	rs.combine(processExprNode(binOp->getRhs()));
	return rs;
}

DesignRelationships processExprNode(ExprNode expr) {
	return std::visit(
		[](const auto& entity) { return processExprEntity(entity); },
		expr);
}

//process PredicateNodes; only ifNode, whileNode call this
//returns the relationships only, no follows no parents relationships involved
DesignRelationships processPredicateNode(std::shared_ptr<PredicateNode> expr) {
	DesignRelationships rs = DesignRelationships::createEmpty();
	if (expr->isTerminalPredicate()) {
		//todo: violates law of dememter
		std::shared_ptr<RelExprNode> relExpr = expr->getRelExprNode();
		rs.combine(processExprNode(relExpr->getLhs()));
		rs.combine(processExprNode(relExpr->getRhs()));
	} else {
		rs.combine(processPredicateNode(expr->getLhs()));
		rs.combine(processPredicateNode(expr->getRhs()));
	}
	return rs;
}

//individual stmt node processing functions
DesignRelationships processPrintNode(std::shared_ptr<PrintNode> print) {
	processVariableNode(print->getVariable());
	EntityStager::stagePrintStatement(print->getStmtNumber());

	//stage relationships
	DesignRelationships rs = DesignRelationships::createEmpty();
	rs.addUses(print->getVariableName());
	EntityStager::stageUsesStatements(print->getStmtNumber(), rs.getUses());
	return rs;
}

DesignRelationships processReadNode(std::shared_ptr<ReadNode> read) {
	processVariableNode(read->getVariable());
	EntityStager::stageReadStatement(read->getStmtNumber());

	//stage relationships
	DesignRelationships rs = DesignRelationships::createEmpty();
	rs.addModifies(read->getVariableName());
	EntityStager::stageModifiesStatements(read->getStmtNumber(), rs.getModifies());
	return rs;
}

DesignRelationships processAssignNode(std::shared_ptr<AssignNode> assign) {
	EntityStager::stageAssignStatement(
		assign->getStmtNumber(),
		assign->getAssignedVar()->getName(),
		assign->getPostfix());
	
	//process lhs
	processVariableNode(assign->getAssignedVar());

	//process rhs
	DesignRelationships rs = processExprNode(assign->getExpression());
	
	//stage relationships
	rs.addModifies(assign->getAssignedVarName());
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(assign->getStmtNumber(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(assign->getStmtNumber(), rs.getUses());
	return rs;
}

DesignRelationships processWhileNode(std::shared_ptr<WhileNode> whiles) {
	EntityStager::stageWhileStatement(whiles->getStmtNumber());

	//process predicate
	DesignRelationships rs = processPredicateNode(whiles->getPredicate());

	//combine with stmtlist
	rs.combine(processStmtList(whiles->getStmtList()));

	//stage relationships
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(whiles->getStmtNumber(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(whiles->getStmtNumber(), rs.getUses());
	return rs;
}

DesignRelationships processIfNode(std::shared_ptr<IfNode> ifs) {
	EntityStager::stageIfStatement(ifs->getStmtNumber());

	//process predicate
	DesignRelationships rs = processPredicateNode(ifs->getPredicate());

	//combine with thenStmtList
	rs.combine(processStmtList(ifs->getThenStmtList()));
	//combine with elseStmtList
	rs.combine(processStmtList(ifs->getElseStmtList()));

	//stage relationships
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(ifs->getStmtNumber(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(ifs->getStmtNumber(), rs.getUses());
	return rs;
}

//statement (list) processing functions
DesignRelationships processStmt(std::shared_ptr<StmtNode> stmt) {
	EntityStager::stageStatement(stmt->getStmtNumber());
	if (stmt->isReadNode()) {
		return processReadNode(std::dynamic_pointer_cast<ReadNode>(stmt));
	} else if (stmt->isPrintNode()) {
		return processPrintNode(std::dynamic_pointer_cast<PrintNode>(stmt));
	} else if (stmt->isAssignNode()) {
		return processAssignNode(std::dynamic_pointer_cast<AssignNode>(stmt));
	} else if (stmt->isWhileNode()) {
		return processWhileNode(std::dynamic_pointer_cast<WhileNode>(stmt));
	} else if (stmt->isIfNode()) {
		return processIfNode(std::dynamic_pointer_cast<IfNode>(stmt));
	}
	return DesignRelationships::createEmpty();
}

DesignRelationships processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList) {
	DesignRelationships output = DesignRelationships::createEmpty();
	for (int i = 0; i < stmtList.size(); i++) {
		if (i < stmtList.size() - 1) {
			EntityStager::stageFollows(stmtList[i]->getStmtNumber(), stmtList[i + 1]->getStmtNumber());
		}
		for (int j = i + 1; j < stmtList.size(); j++) {
			EntityStager::stageFollowsT(stmtList[i]->getStmtNumber(), stmtList[j]->getStmtNumber());
		}
		DesignRelationships rs = processStmt(stmtList[i]);
		output.combine(rs);
	}
	return output;
}

//procedure (list) processing functions
DesignRelationships processProcedure(std::shared_ptr<ProcedureNode> proc) {
	EntityStager::stageProcedure(proc->getProcName());
	return processStmtList(proc->getStmtList());
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