#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::vector<std::shared_ptr<StmtNode>> stList)
	: Node(NodeType::PROCEDURE) {
	stmtList = stList;
}

std::vector<std::shared_ptr<StmtNode>> ProcedureNode::getStmtList() {
	return stmtList;
}