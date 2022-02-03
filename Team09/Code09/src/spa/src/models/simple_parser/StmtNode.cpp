#include "StmtNode.h"

StmtNode::StmtNode(NodeType t, int sn)
	: Node(t) {
	stmtNo = sn;
}

int StmtNode::getStmtNumber() const {
	return stmtNo;
}

bool StmtNode::operator==(const Node& other) const {
	const StmtNode* cast = dynamic_cast<const StmtNode*>(&other);
	return cast != nullptr &&
		stmtNo == cast->getStmtNumber();
}