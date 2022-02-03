#include "StmtNode.h"

StmtNode::StmtNode(NodeType t, int sn)
	: Node(t) {
	stmtNo = sn;
}

int StmtNode::getStmtNumber() {
	return stmtNo;
}