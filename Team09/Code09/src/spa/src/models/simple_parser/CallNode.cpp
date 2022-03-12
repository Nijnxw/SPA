#include "CallNode.h"

CallNode::CallNode(int sn, std::string s)
	: StmtNode(NodeType::CALL, sn) {
	procedure = s;
}

std::string CallNode::getProcedureName() const {
	return procedure;
}

bool CallNode::operator==(const Node& other) const {
	const CallNode* cast = dynamic_cast<const CallNode*>(&other);
	return cast != nullptr &&
		procedure == cast->getProcedureName();
}