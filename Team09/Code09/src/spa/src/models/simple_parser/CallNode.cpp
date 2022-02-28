#include "CallNode.h"

CallNode::CallNode(std::string s)
	: Node(NodeType::CALL) {
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