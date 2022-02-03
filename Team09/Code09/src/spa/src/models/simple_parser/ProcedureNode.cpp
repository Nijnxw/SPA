#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::vector<StmtNode> stList)
	: Node(NodeType::Procedure) {
	stmtList = stList;
}

std::vector<StmtNode> ProcedureNode::getStmtList() {
	return stmtList;
}