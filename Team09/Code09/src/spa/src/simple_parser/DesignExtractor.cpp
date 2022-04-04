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
void DesignExtractor::processPrintNode(std::shared_ptr<PrintNode> print) {
	processVariableNode(print->getVariable());
	EntityStager::stagePrintStatement(print->getStmtNumber(), print->getVariableName());

	//stage relationships
	EntityStager::stageUsesStatements(print->getStmtNumber(), { print->getVariableName() });

	//add recursive abstraction information
	std::stack<NestableRelationships> temp;
	while (!nestableRelationshipsStack.empty()) {
		NestableRelationships curr = nestableRelationshipsStack.top();
		nestableRelationshipsStack.pop();
		curr.addUses(print->getVariableName());
		temp.push(curr);
	}
	while (!temp.empty()) {
		nestableRelationshipsStack.push(temp.top());
		temp.pop();
	}
}

void DesignExtractor::processReadNode(std::shared_ptr<ReadNode> read) {
	processVariableNode(read->getVariable());
	EntityStager::stageReadStatement(read->getStmtNumber(), read->getVariableName());

	//stage relationships
	EntityStager::stageModifiesStatements(read->getStmtNumber(), { read->getVariableName() });

	//add recursive abstraction information
	std::stack<NestableRelationships> temp;
	while (!nestableRelationshipsStack.empty()) {
		NestableRelationships curr = nestableRelationshipsStack.top();
		nestableRelationshipsStack.pop();
		curr.addModifies(read->getVariableName());
		temp.push(curr);
	}
	while (!temp.empty()) {
		nestableRelationshipsStack.push(temp.top());
		temp.pop();
	}
}

void DesignExtractor::processAssignNode(std::shared_ptr<AssignNode> assign) {
	std::string varName = assign->getAssignedVarName();
	EntityStager::stageAssignStatement(
		assign->getStmtNumber(),
		varName,
		assign->getPostfix());

	//process lhs
	processVariableNode(assign->getAssignedVar());

	//process rhs
	NestableRelationships rs = processExprNode(assign->getExpression());
	rs.addModifies(varName);
	//stage relationships
	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(assign->getStmtNumber(), { assign->getAssignedVarName() });
	if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(assign->getStmtNumber(), rs.getUses());

	//add recursive abstraction information
	std::stack<NestableRelationships> temp;
	while (!nestableRelationshipsStack.empty()) {
		NestableRelationships curr = nestableRelationshipsStack.top();
		nestableRelationshipsStack.pop();
		curr.combine(rs);
		curr.addModifies(assign->getAssignedVarName());
		temp.push(curr);
	}
	while (!temp.empty()) {
		nestableRelationshipsStack.push(temp.top());
		temp.pop();
	}
}

void DesignExtractor::processWhileNode(std::shared_ptr<WhileNode> whiles) {
	if (containerStack.empty() || whiles != containerStack.top()) {
		// first visit with this node
		nodeStack.push(whiles); //push it back in for second visit
		nestableRelationshipsStack.push(NestableRelationships::createEmpty());
		containerStack.push(whiles);
		processStmtList(whiles->getStmtList());

	} else {
		//second visit
		containerStack.pop();
		//extract predicate control variables
		std::unordered_set<std::string> vars = extractControlVariables(whiles->getPredicate());
		EntityStager::stageWhileStatement(whiles->getStmtNumber(), vars);

		//process predicate
		NestableRelationships rs = processPredicateNode(whiles->getPredicate());

		rs.combine(nestableRelationshipsStack.top());
		nestableRelationshipsStack.pop();

		//extract direct children stmt number
		std::unordered_set<int> childrenList;
		std::vector<std::shared_ptr<StmtNode>> stmtList = whiles->getStmtList();
		std::transform(stmtList.begin(), stmtList.end(), std::inserter(childrenList, childrenList.begin()),
			[](std::shared_ptr<StmtNode> node) { return node->getStmtNumber(); });

		//stage relationships
		if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(whiles->getStmtNumber(), rs.getModifies());
		if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(whiles->getStmtNumber(), rs.getUses());
		if (rs.getChildrenSize() > 0) EntityStager::stageParentT(whiles->getStmtNumber(), rs.getChildren());
		if (childrenList.size() > 0) EntityStager::stageParent(whiles->getStmtNumber(), childrenList);

		//add recursive abstraction information
		std::stack<NestableRelationships> temp;
		while (!nestableRelationshipsStack.empty()) {
			NestableRelationships curr = nestableRelationshipsStack.top();
			nestableRelationshipsStack.pop();
			curr.combine(rs);
			temp.push(curr);
		}
		while (!temp.empty()) {
			nestableRelationshipsStack.push(temp.top());
			temp.pop();
		}
	}
}

void DesignExtractor::processIfNode(std::shared_ptr<IfNode> ifs) {
	if (containerStack.empty() || ifs != containerStack.top()) {
		// first visit with this node
		nodeStack.push(ifs); //push it back in for second visit
		nestableRelationshipsStack.push(NestableRelationships::createEmpty());
		containerStack.push(ifs);
		processStmtList(ifs->getThenStmtList());
		processStmtList(ifs->getElseStmtList());
	} else {
		// second visit
		containerStack.pop();
		//extract predicate control variables
		std::unordered_set<std::string> vars = extractControlVariables(ifs->getPredicate());
		EntityStager::stageIfStatement(ifs->getStmtNumber(), vars);

		//process predicate
		NestableRelationships rs = processPredicateNode(ifs->getPredicate());

		rs.combine(nestableRelationshipsStack.top());
		nestableRelationshipsStack.pop();

		//extract direct children stmt number
		std::unordered_set<int> childrenList;
		std::vector<std::shared_ptr<StmtNode>> thenStmtList = ifs->getThenStmtList();
		std::vector<std::shared_ptr<StmtNode>> elseStmtList = ifs->getElseStmtList();
		std::transform(thenStmtList.begin(), thenStmtList.end(), std::inserter(childrenList, childrenList.begin()),
			[](std::shared_ptr<StmtNode> node) { return node->getStmtNumber(); });
		std::transform(elseStmtList.begin(), elseStmtList.end(), std::inserter(childrenList, childrenList.begin()),
			[](std::shared_ptr<StmtNode> node) { return node->getStmtNumber(); });

		//stage relationships
		if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(ifs->getStmtNumber(), rs.getModifies());
		if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(ifs->getStmtNumber(), rs.getUses());
		if (rs.getChildrenSize() > 0) EntityStager::stageParentT(ifs->getStmtNumber(), rs.getChildren());
		if (childrenList.size() > 0) EntityStager::stageParent(ifs->getStmtNumber(), childrenList);

		//add recursive abstraction information
		std::stack<NestableRelationships> temp;
		while (!nestableRelationshipsStack.empty()) {
			NestableRelationships curr = nestableRelationshipsStack.top();
			nestableRelationshipsStack.pop();
			curr.combine(rs);
			temp.push(curr);
		}
		while (!temp.empty()) {
			nestableRelationshipsStack.push(temp.top());
			temp.pop();
		}
	}
}

void DesignExtractor::processCallNode(std::shared_ptr<CallNode> call) {
	if (containerStack.empty() || call != containerStack.top()) {
		// first visit with this node
		nodeStack.push(call); //push it back in for second visit
		//nestableRelationshipsStack.push(NestableRelationships::createEmpty());
		containerStack.push(call);
		//callStack.push(call->getProcedureName());
		if (ast->contains(call->getProcedureName())) processProcedure(ast->retrieve(call->getProcedureName()));
	} else {
		containerStack.pop();
		EntityStager::stageCallStatement(call->getStmtNumber(), call->getProcedureName());

		NestableRelationships rs = nestableRelationshipsStack.top();
		nestableRelationshipsStack.pop();
		std::unordered_set<int> unwantedChildren = rs.getChildren();
		rs.clearChildren(); //remove parent-child information

		if (rs.getModifiesSize() > 0) EntityStager::stageModifiesStatements(call->getStmtNumber(), rs.getModifies());
		if (rs.getUsesSize() > 0) EntityStager::stageUsesStatements(call->getStmtNumber(), rs.getUses());

		rs.addCalls(call->getProcedureName());
		if (callStack.size() > 0) {
			EntityStager::stageCalls(callStack.top(), call->getProcedureName());
			for (std::string callee : rs.getCalls()) {
				EntityStager::stageCallsT(callStack.top(), callee);
			}
		}

		//add recursive abstraction information
		std::stack<NestableRelationships> temp;
		while (!nestableRelationshipsStack.empty()) {
			NestableRelationships curr = nestableRelationshipsStack.top();
			nestableRelationshipsStack.pop();
			curr.combine(rs);
			curr.removeChildren(unwantedChildren);
			temp.push(curr);
		}
		while (!temp.empty()) {
			nestableRelationshipsStack.push(temp.top());
			temp.pop();
		}
	}
}

//statement (list) processing functions
void DesignExtractor::processStmt(std::shared_ptr<StmtNode> stmt) {
	EntityStager::stageStatement(stmt->getStmtNumber());
	if (stmt->isReadNode()) {
		processReadNode(std::dynamic_pointer_cast<ReadNode>(stmt));
	} else if (stmt->isPrintNode()) {
		processPrintNode(std::dynamic_pointer_cast<PrintNode>(stmt));
	} else if (stmt->isAssignNode()) {
		processAssignNode(std::dynamic_pointer_cast<AssignNode>(stmt));
	} else if (stmt->isWhileNode()) {
		processWhileNode(std::dynamic_pointer_cast<WhileNode>(stmt));
	} else if (stmt->isIfNode()) {
		processIfNode(std::dynamic_pointer_cast<IfNode>(stmt));
	} else if (stmt->isCallNode()) {
		processCallNode(std::dynamic_pointer_cast<CallNode>(stmt));
	}
}

void DesignExtractor::processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList) {
	//NestableRelationships output = NestableRelationships::createEmpty();
	for (int i = 0; i < stmtList.size(); i++) {
		if (i < stmtList.size() - 1) {
			EntityStager::stageFollows(stmtList[i]->getStmtNumber(), stmtList[i + 1]->getStmtNumber());
		}
		for (int j = i + 1; j < stmtList.size(); j++) {
			EntityStager::stageFollowsT(stmtList[i]->getStmtNumber(), stmtList[j]->getStmtNumber());
		}
		nodeStack.push(stmtList[i]);

		std::stack<NestableRelationships> temp;
		while (!nestableRelationshipsStack.empty()) {
			NestableRelationships curr = nestableRelationshipsStack.top();
			nestableRelationshipsStack.pop();
			curr.addChildren(stmtList[i]->getStmtNumber());
			temp.push(curr);
		}
		while (!temp.empty()) {
			nestableRelationshipsStack.push(temp.top());
			temp.pop();
		}
		//NestableRelationships rs = processStmt(callStack, stmtList[i]);
		//rs.addChildren(stmtList[i]->getStmtNumber());
		//output.combine(rs);
	}
	//return output;
}

//procedure (list) processing functions
void DesignExtractor::processProcedure(std::shared_ptr<ProcedureNode> proc) {
	//processProcedure called by call statement probably broken
	NestableRelationships rs;
	if (containerStack.empty() || proc != containerStack.top()) {
		// first encounter with this node
		EntityStager::stageProcedure(proc->getProcName());

		nodeStack.push(proc); //push it back in for second visit
		containerStack.push(proc);
		callStack.push(proc->getProcName());
		if (DesignExtractor::isCached(proc->getProcName())) {
			NestableRelationships cachedRelatonships = DesignExtractor::retrieve(proc->getProcName());
			nestableRelationshipsStack.push(cachedRelatonships);
		} else {
			nestableRelationshipsStack.push(NestableRelationships::createEmpty());
			processStmtList(proc->getStmtList());
		}
	} else {
		containerStack.pop();
		callStack.pop();
		NestableRelationships rs = nestableRelationshipsStack.top();
		nestableRelationshipsStack.pop();

		if (!containerStack.empty()) {
			std::shared_ptr<Node> top = containerStack.top();
			if (top->isCallNode()) nestableRelationshipsStack.push(rs);
		}

		if (!DesignExtractor::isCached(proc->getProcName())) {
			DesignExtractor::cache(proc->getProcName(), rs);

			if (rs.getModifiesSize() > 0) EntityStager::stageModifiesProcedure(proc->getProcName(), rs.getModifies());
			if (rs.getUsesSize() > 0) EntityStager::stageUsesProcedure(proc->getProcName(), rs.getUses());
		}
	}

	//NestableRelationships rs;
	//if (DesignExtractor::isCached(proc->getProcName())) {
	//	rs = DesignExtractor::retrieve(proc->getProcName());
	//} else {
	//	//only run when rs is not cached
	//	callStack.insert(callStack.begin(), proc->getProcName());
	//	NestableRelationships rs = processStmtList(proc->getStmtList());
	//	DesignExtractor::cache(proc->getProcName(), rs);
	//	if (rs.getModifiesSize() > 0) EntityStager::stageModifiesProcedure(proc->getProcName(), rs.getModifies());
	//	if (rs.getUsesSize() > 0) EntityStager::stageUsesProcedure(proc->getProcName(), rs.getUses());
	//}
	//nestableRelationshipsStack.push(rs);
}

void DesignExtractor::processProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap) {
	for (auto& procPair : procMap) {
		nodeStack.push(procPair.second);
		//processProcedure(procPair.second);
	}
	// main driver loop
	while (!nodeStack.empty()) {
		std::shared_ptr<Node> curr = nodeStack.top();
		nodeStack.pop();
		if (curr->isProcedureNode()) {
			processProcedure(std::dynamic_pointer_cast<ProcedureNode>(curr));
		} else {
			processStmt(std::dynamic_pointer_cast<StmtNode>(curr));
		}
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