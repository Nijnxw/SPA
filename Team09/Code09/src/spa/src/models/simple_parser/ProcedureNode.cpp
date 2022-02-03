#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::vector<std::shared_ptr<StmtNode>> stList, std::string procName)
	: Node(NodeType::PROCEDURE) {
	stmtList = stList;
	name = procName;
}

std::vector<std::shared_ptr<StmtNode>> ProcedureNode::getStmtList() {
	return stmtList;
}

std::string ProcedureNode::getProcName() {
	return name;
}