#include "DesignExtractor.h"

// {{"USES", set of used vars}, {"MODIFIES", set of modifed vars}}
using Relationships = std::unordered_map<std::string, std::unordered_set<std::string>>;

Relationships buildEmptyMap() {
	return {
		{"USES", std::unordered_set<std::string>{}},
		{"MODIFIES", std::unordered_set<std::string>{}}
	};
}

Relationships combine(Relationships rs1, Relationships rs2) {
	rs1["USES"].merge(rs2["USES"]);
	rs1["MODIFIES"].merge(rs2["MODIFIES"]);
	return rs1;
}

DesignExtractor::DesignExtractor() {}
Relationships processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList);

//primitive node processing functions
void processConstantNode(std::shared_ptr<ConstantNode> constant) {
	EntityStager::stageConstant(constant->getValue());
}

void processVariableNode(std::shared_ptr<VariableNode> variable) {
	EntityStager::stageVariable(variable->getName());
}

//helper expression node processing functions

//process ExprNodes
Relationships processExprNode(ExprNode expr);

//overloaded functions to handle ExprNode variants
Relationships processExprEntity(std::shared_ptr<ConstantNode> constant) {
	processConstantNode(constant);
	return buildEmptyMap();
}

Relationships processExprEntity(std::shared_ptr<VariableNode> variable) {
	processVariableNode(variable);
	std::unordered_set<std::string> vars{ variable->getName() };

	Relationships output = buildEmptyMap();
	output["USES"].insert(variable->getName());
	return output;
}

Relationships processExprEntity(std::shared_ptr<BinaryOperatorNode> binOp) {
	Relationships rs1 = processExprNode(binOp->getLhs());
	Relationships rs2 = processExprNode(binOp->getRhs());

	return combine(rs1, rs2);
}

Relationships processExprNode(ExprNode expr) {
	return std::visit(
		[](const auto& entity) { return processExprEntity(entity); },
		expr);
}

//process PredicateNodes; only ifNode, whileNode call this
//returns the relationships only, no follows no parents relationships involved
Relationships processPredicateNode(std::shared_ptr<PredicateNode> expr) {
	Relationships left;
	Relationships right;
	if (expr->isTerminalPredicate()) {
		//todo: violates law of dememter
		std::shared_ptr<RelExprNode> relExpr = expr->getRelExprNode();
		left = processExprNode(relExpr->getLhs());
		right = processExprNode(relExpr->getRhs());
	} else {
		left = processPredicateNode(expr->getLhs());
		right = processPredicateNode(expr->getRhs());
	}
	return combine(left, right);
}

//individual stmt node processing functions
Relationships processPrintNode(std::shared_ptr<PrintNode> print) {
	processVariableNode(print->getVariable());
	EntityStager::stagePrintStatement(print->getStmtNumber());

	//stage relationships
	Relationships rs = buildEmptyMap();
	rs["USES"].insert(print->getVariableName());
	EntityStager::stageUsesStatements(print->getStmtNumber(), rs["USES"]);
	return rs;
}

Relationships processReadNode(std::shared_ptr<ReadNode> read) {
	processVariableNode(read->getVariable());
	EntityStager::stageReadStatement(read->getStmtNumber());

	//stage relationships
	Relationships rs = buildEmptyMap();
	rs["MODIFIES"].insert(read->getVariableName());
	EntityStager::stageModifiesStatements(read->getStmtNumber(), rs["MODIFIES"]);
	return rs;
}

Relationships processAssignNode(std::shared_ptr<AssignNode> assign) {
	EntityStager::stageAssignStatement(
		assign->getStmtNumber(),
		assign->getAssignedVar()->getName(),
		assign->getPostfix());
	
	//process lhs
	processVariableNode(assign->getAssignedVar());

	//process rhs
	Relationships rs = processExprNode(assign->getExpression());
	
	//stage relationships
	rs["MODIFIES"].insert(assign->getAssignedVarName());
	if (rs["MODIFIES"].size() > 0) EntityStager::stageModifiesStatements(assign->getStmtNumber(), rs["MODIFIES"]);
	if (rs["USES"].size() > 0) EntityStager::stageUsesStatements(assign->getStmtNumber(), rs["USES"]);
	return rs;
}

Relationships processWhileNode(std::shared_ptr<WhileNode> whiles) {
	EntityStager::stageWhileStatement(whiles->getStmtNumber());

	//process predicate
	Relationships rs = processPredicateNode(whiles->getPredicate());

	//combine with stmtlist
	rs = combine(rs, processStmtList(whiles->getStmtList()));

	//stage relationships
	if (rs["MODIFIES"].size() > 0) EntityStager::stageModifiesStatements(whiles->getStmtNumber(), rs["MODIFIES"]);
	if (rs["USES"].size() > 0) EntityStager::stageUsesStatements(whiles->getStmtNumber(), rs["USES"]);
	return rs;
}

Relationships processIfNode(std::shared_ptr<IfNode> ifs) {
	EntityStager::stageWhileStatement(ifs->getStmtNumber());

	//process predicate
	Relationships rs = processPredicateNode(ifs->getPredicate());

	//combine with thenStmtList
	rs = combine(rs, processStmtList(ifs->getThenStmtList()));
	//combine with elseStmtList
	rs = combine(rs, processStmtList(ifs->getElseStmtList()));

	//stage relationships
	if (rs["MODIFIES"].size() > 0) EntityStager::stageModifiesStatements(ifs->getStmtNumber(), rs["MODIFIES"]);
	if (rs["USES"].size() > 0)  EntityStager::stageUsesStatements(ifs->getStmtNumber(), rs["USES"]);
	return rs;
}

//statement (list) processing functions
Relationships processStmt(std::shared_ptr<StmtNode> stmt) {
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
	return buildEmptyMap();
}

Relationships processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList) {
	Relationships output = buildEmptyMap();
	for (int i = 0; i < stmtList.size(); i++) {
		if (i < stmtList.size() - 1) {
			EntityStager::stageFollows(stmtList[i]->getStmtNumber(), stmtList[i + 1]->getStmtNumber());
		}
		for (int j = i + 1; j < stmtList.size(); j++) {
			EntityStager::stageFollowsT(stmtList[i]->getStmtNumber(), stmtList[j]->getStmtNumber());
		}
		Relationships rs = processStmt(stmtList[i]);
		output = combine(output, rs);
	}
	return output;
}

//procedure (list) processing functions
Relationships processProcedure(std::shared_ptr<ProcedureNode> proc) {
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