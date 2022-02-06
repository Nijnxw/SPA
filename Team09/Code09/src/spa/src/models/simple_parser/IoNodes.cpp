#include "IoNodes.h"

// IoNode Implementation
IoNode::IoNode(NodeType t, int sn, std::shared_ptr<VariableNode> var)
	: StmtNode(t, sn), variable(var) {
}

std::shared_ptr<VariableNode> IoNode::getVariable() const{
	return variable;
}

// ReadNode Implementation
ReadNode::ReadNode(int sn, std::shared_ptr<VariableNode> var)
	: IoNode(NodeType::READ, sn, var) { }

bool ReadNode::operator==(const Node& other) const {
	const ReadNode* cast = dynamic_cast<const ReadNode*>(&other);
	return cast != nullptr &&
		StmtNode::operator==(other) &&
		*(this->getVariable()) == *(cast->getVariable());
}

// PrintNode Implementation
PrintNode::PrintNode(int sn, std::shared_ptr<VariableNode> var)
	: IoNode(NodeType::PRINT, sn, var) { }

bool PrintNode::operator==(const Node& other) const {
	const PrintNode* cast = dynamic_cast<const PrintNode*>(&other);
	return cast != nullptr &&
		StmtNode::operator==(other) &&
		*(this->getVariable()) == *(cast->getVariable());
}