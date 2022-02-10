#include "DesignExtractor.h"

// {{"USES", set of used vars}, {"MODIFIES", set of modifed vars}}
using Relationships = std::unordered_map<std::string, std::unordered_set<std::string>>;

Relationships buildEmptyMap() {
	return {
		{"USES", std::unordered_set<std::string>{}},
		{"MODIFIES", std::unordered_set<std::string>{}}
	};
}

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
Relationships processExprNode(int stmtNo, ExprNode expr);

//overloaded functions to handle ExprNode variants
Relationships processExprEntity(int stmtNo, std::shared_ptr<ConstantNode> constant) {
	processConstantNode(constant);
	return buildEmptyMap();
}

Relationships processExprEntity(int stmtNo, std::shared_ptr<VariableNode> variable) {
	processVariableNode(variable);
	std::unordered_set<std::string> vars{ variable->getName() };
	EntityStager::stageUsesStatements(stmtNo, vars);

	Relationships output = buildEmptyMap();
	output["Uses"].insert(variable->getName());
	return output;
}

Relationships processExprEntity(int stmtNo, std::shared_ptr<BinaryOperatorNode> binOp) {
	Relationships rs1 = processExprNode(stmtNo, binOp->getLhs());
	Relationships rs2 = processExprNode(stmtNo, binOp->getRhs());
	Relationships output = buildEmptyMap();
	rs1["Uses"].merge(rs2["Uses"]);
	rs1["Modifies"].merge(rs2["Modifies"]);
	return rs1;
}

Relationships processExprNode(int stmtNo, ExprNode expr) {
	return std::visit(
		[stmtNo](const auto& entity) { return processExprEntity(stmtNo, entity); },
		expr);
}

//individual stmt node processing functions
Relationships processPrintNode(std::shared_ptr<PrintNode> print) {
	Relationships output = buildEmptyMap();
	processVariableNode(print->getVariable());
	//todo: implement getVariableName() -> current implementatiaon violates law of dementer
	std::unordered_set<std::string> vars;
	vars.insert(print->getVariable()->getName());

	EntityStager::stageUsesStatements(print->getStmtNumber(), vars);
	EntityStager::stagePrintStatement(print->getStmtNumber());
	output["Uses"].insert(print->getVariable()->getName());
	return output;
}

Relationships processReadNode(std::shared_ptr<ReadNode> read) {
	Relationships output = buildEmptyMap();
	processVariableNode(read->getVariable());
	//todo: implement getVariableName() -> current implementatiaon violates law of dementer
	std::unordered_set<std::string> vars;
	vars.insert(read->getVariable()->getName());

	EntityStager::stageModifiesStatements(read->getStmtNumber(), vars);
	EntityStager::stageReadStatement(read->getStmtNumber());
	output["Modifies"].insert(read->getVariable()->getName());
	return output;
}

Relationships processAssignNode(std::shared_ptr<AssignNode> assign) {
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
	Relationships output = processExprNode(assign->getStmtNumber(), assign->getExpression());
	output["Modifies"].insert(assign->getAssignedVar()->getName());
	return output;
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
		output["Uses"].merge(rs["Uses"]);
		output["Modifies"].merge(rs["Modifies"]);
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