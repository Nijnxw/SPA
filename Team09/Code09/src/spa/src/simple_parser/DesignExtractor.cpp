#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(AST ast, int stmtCount) 
	:  ast(std::move(ast)), totalStmt(stmtCount) {}

bool DesignExtractor::isCached(std::string procName) {
	return DesignExtractor::procCache.find(procName) != DesignExtractor::procCache.end();
}

NestableRelationships DesignExtractor::retrieve(std::string procName) {
	if (!isCached(procName)) return NestableRelationships::createEmpty();
	return DesignExtractor::procCache.at(procName);
}

void DesignExtractor::cache(std::string procName, NestableRelationships rs) {
	DesignExtractor::procCache.insert({ procName, rs });
}

std::unordered_set<std::string> extractControlVariables(std::shared_ptr<PredicateNode> pred) {
	return pred->getControlVariables();
}

//primitive node processing functions
void processConstantNode(std::shared_ptr<ConstantNode> constant) {
	EntityStager::stageConstant(constant->getValue());
}

void processVariableNode(std::shared_ptr<VariableNode> variable) {
	EntityStager::stageVariable(variable->getName());
}

//helper expression node processing functions

//process ExprNodes
NestableRelationships processExprNode(ExprNode expr);

//overloaded functions to handle ExprNode variants
NestableRelationships processExprEntity(std::shared_ptr<ConstantNode> constant) {
	processConstantNode(constant);
	return NestableRelationships::createEmpty();
}

NestableRelationships processExprEntity(std::shared_ptr<VariableNode> variable) {
	processVariableNode(variable);
	std::unordered_set<std::string> vars{variable->getName()};

	NestableRelationships output = NestableRelationships::createEmpty();
	output.addUses(variable->getName());
	return output;
}

NestableRelationships processExprEntity(std::shared_ptr<BinaryOperatorNode> binOp) {
	NestableRelationships rs = processExprNode(binOp->getLhs());
	rs.combine(processExprNode(binOp->getRhs()));
	return rs;
}

NestableRelationships processExprNode(ExprNode expr) {
	return std::visit(
		[](const auto& entity) { return processExprEntity(entity); },
		expr);
}

//process PredicateNodes; only ifNode, whileNode call this
//returns the relationships only, no follows no parents relationships involved
NestableRelationships processPredicateNode(std::shared_ptr<PredicateNode> expr) {
	NestableRelationships rs = NestableRelationships::createEmpty();
	if (expr->isTerminalPredicate()) {
		rs.combine(processExprNode(expr->getRelLhs()));
		rs.combine(processExprNode(expr->getRelRhs()));
	} else {
		if (!(expr->isNotPredicate())) rs.combine(processPredicateNode(expr->getLhs()));
		rs.combine(processPredicateNode(expr->getRhs()));
	}
	return rs;
}

//individual stmt node processing functions
NestableRelationships DesignExtractor::processPrintNode(std::shared_ptr<PrintNode> print) {
	processVariableNode(print->getVariable());
	EntityStager::stagePrintStatement(print->getStmtNumber(), print->getVariableName());

	//stage relationships
	NestableRelationships rs = NestableRelationships::createEmpty();
	rs.addUses(print->getVariableName());
	EntityStager::stageUsesStatements(print->getStmtNumber(), rs.getUses());
	return rs;
}

NestableRelationships DesignExtractor::processReadNode(std::shared_ptr<ReadNode> read) {
	processVariableNode(read->getVariable());
	EntityStager::stageReadStatement(read->getStmtNumber(), read->getVariableName());

	//stage relationships
	NestableRelationships rs = NestableRelationships::createEmpty();
	rs.addModifies(read->getVariableName());
	EntityStager::stageModifiesStatements(read->getStmtNumber(), rs.getModifies());
	return rs;
}

NestableRelationships DesignExtractor::processAssignNode(std::shared_ptr<AssignNode> assign) {
	EntityStager::stageAssignStatement(
		assign->getStmtNumber(),
		assign->getAssignedVar()->getName(),
		assign->getPostfix());

	//process lhs
	processVariableNode(assign->getAssignedVar());

	//process rhs
	NestableRelationships rs = processExprNode(assign->getExpression());

	//stage relationships
	rs.addModifies(assign->getAssignedVarName());
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(assign->getStmtNumber(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(assign->getStmtNumber(), rs.getUses());
	return rs;
}

NestableRelationships DesignExtractor::processWhileNode(std::vector<std::string> callStack, std::shared_ptr<WhileNode> whiles) {
	//extract predicate control variables
	std::unordered_set<std::string> vars = extractControlVariables(whiles->getPredicate());
	EntityStager::stageWhileStatement(whiles->getStmtNumber(), vars);

	//process predicate
	NestableRelationships rs = processPredicateNode(whiles->getPredicate());

	std::vector<std::shared_ptr<StmtNode>> stmtList = whiles->getStmtList();

	//combine with stmtlist
	rs.combine(processStmtList(callStack, stmtList));

	//extract direct children stmt number
	std::unordered_set<int> childrenList;
	std::transform(stmtList.begin(), stmtList.end(), std::inserter(childrenList, childrenList.begin()),
				   [](std::shared_ptr<StmtNode> node) { return node->getStmtNumber(); });

	//stage relationships
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(whiles->getStmtNumber(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(whiles->getStmtNumber(), rs.getUses());
	if (rs.getChildrenSize() > 0) EntityStager::stageParentT(whiles->getStmtNumber(), rs.getChildren());
	if (childrenList.size() > 0) EntityStager::stageParent(whiles->getStmtNumber(), childrenList);
	return rs;
}

NestableRelationships DesignExtractor::processIfNode(std::vector<std::string> callStack, std::shared_ptr<IfNode> ifs) {
	//extract predicate control variables
	std::unordered_set<std::string> vars = extractControlVariables(ifs->getPredicate());
	EntityStager::stageIfStatement(ifs->getStmtNumber(), vars);

	//process predicate
	NestableRelationships rs = processPredicateNode(ifs->getPredicate());

	std::vector<std::shared_ptr<StmtNode>> thenStmtList = ifs->getThenStmtList();
	std::vector<std::shared_ptr<StmtNode>> elseStmtList = ifs->getElseStmtList();

	//combine with thenStmtList
	rs.combine(processStmtList(callStack, thenStmtList));
	//combine with elseStmtList
	rs.combine(processStmtList(callStack, elseStmtList));

	//extract direct children stmt number
	std::unordered_set<int> childrenList;
	std::transform(thenStmtList.begin(), thenStmtList.end(), std::inserter(childrenList, childrenList.begin()),
				   [](std::shared_ptr<StmtNode> node) { return node->getStmtNumber(); });
	std::transform(elseStmtList.begin(), elseStmtList.end(), std::inserter(childrenList, childrenList.begin()),
				   [](std::shared_ptr<StmtNode> node) { return node->getStmtNumber(); });

	//stage relationships
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(ifs->getStmtNumber(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(ifs->getStmtNumber(), rs.getUses());
	if (rs.getChildrenSize() > 0) EntityStager::stageParentT(ifs->getStmtNumber(), rs.getChildren());
	if (childrenList.size() > 0) EntityStager::stageParent(ifs->getStmtNumber(), childrenList);
	return rs;
}

NestableRelationships DesignExtractor::processCallNode(std::vector<std::string> callStack, std::shared_ptr<CallNode> call) {
	EntityStager::stageCallStatement(call->getStmtNumber(), call->getProcedureName());

	if (!ast->contains(call->getProcedureName())) return NestableRelationships::createEmpty();

	NestableRelationships rs = processProcedure(callStack, ast->retrieve(call->getProcedureName())); //under cache system: this wont populate callstore also
	rs.clearChildren(); //remove parent-child information

	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(call->getStmtNumber(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(call->getStmtNumber(), rs.getUses());

	rs.addCalls(call->getProcedureName());
	if (callStack.size() > 0) {
		EntityStager::stageCalls(callStack[0], call->getProcedureName());
		for (std::string callee : rs.getCalls()) {
			EntityStager::stageCallsT(callStack[0], callee);
		}
	}
	return rs;
}

//statement (list) processing functions
NestableRelationships DesignExtractor::processStmt(std::vector<std::string> callStack, std::shared_ptr<StmtNode> stmt) {
	EntityStager::stageStatement(stmt->getStmtNumber());
	if (stmt->isReadNode()) {
		return processReadNode(std::dynamic_pointer_cast<ReadNode>(stmt));
	} else if (stmt->isPrintNode()) {
		return processPrintNode(std::dynamic_pointer_cast<PrintNode>(stmt));
	} else if (stmt->isAssignNode()) {
		return processAssignNode(std::dynamic_pointer_cast<AssignNode>(stmt));
	} else if (stmt->isWhileNode()) {
		return processWhileNode(callStack, std::dynamic_pointer_cast<WhileNode>(stmt));
	} else if (stmt->isIfNode()) {
		return processIfNode(callStack, std::dynamic_pointer_cast<IfNode>(stmt));
	} else if (stmt->isCallNode()) {
		return processCallNode(callStack, std::dynamic_pointer_cast<CallNode>(stmt));
	}
	return NestableRelationships::createEmpty();
}

NestableRelationships DesignExtractor::processStmtList(std::vector<std::string> callStack, std::vector<std::shared_ptr<StmtNode>> stmtList) {
	NestableRelationships output = NestableRelationships::createEmpty();
	for (int i = 0; i < stmtList.size(); i++) {
		if (i < stmtList.size() - 1) {
			EntityStager::stageFollows(stmtList[i]->getStmtNumber(), stmtList[i + 1]->getStmtNumber());
		}
		for (int j = i + 1; j < stmtList.size(); j++) {
			EntityStager::stageFollowsT(stmtList[i]->getStmtNumber(), stmtList[j]->getStmtNumber());
		}
		NestableRelationships rs = processStmt(callStack, stmtList[i]);
		rs.addChildren(stmtList[i]->getStmtNumber());
		output.combine(rs);
	}
	return output;
}

//procedure (list) processing functions
NestableRelationships DesignExtractor::processProcedure(std::vector<std::string> callStack, std::shared_ptr<ProcedureNode> proc) {
	EntityStager::stageProcedure(proc->getProcName());

	if (DesignExtractor::isCached(proc->getProcName())) return DesignExtractor::retrieve(proc->getProcName());

	//only run when rs is not cached
	callStack.insert(callStack.begin(), proc->getProcName());
	NestableRelationships rs = processStmtList(callStack, proc->getStmtList());
	DesignExtractor::cache(proc->getProcName(), rs);
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesProcedure(proc->getProcName(), rs.getModifies());
	if (rs.getUsesSize() > 0) EntityStager::stageUsesProcedure(proc->getProcName(), rs.getUses());
	return rs;
}

void DesignExtractor::processProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap) {
	for (auto& procPair : procMap) {
		processProcedure({ }, procPair.second);
	}
}

void DesignExtractor::extractDesignElements() {
	EntityStager::clear();
	DesignExtractor::procCache.clear();
	processProcedureList(ast->getProcedureMap());
	std::pair<CFG, std::unordered_map<std::string, std::unordered_set<int>>> pair = CFGExtractor::extractCFG(ast, totalStmt);
	EntityStager::stageCFG(pair.first);
	EntityStager::stageLastStmtMapping(pair.second);
}

void DesignExtractor::commit() {
	EntityStager::commit();
	DesignExtractor::procCache.clear();
}