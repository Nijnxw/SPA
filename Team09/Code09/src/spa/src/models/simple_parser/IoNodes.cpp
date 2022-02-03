#include "IoNodes.h"

// IoNode Implementation
IoNode::IoNode(NodeType t, int sn, std::shared_ptr<VariableNode> var)
	: StmtNode(t, sn), variable(var) {
}

std::shared_ptr<VariableNode> IoNode::getVariable() {
	return variable;
}

// ReadNode Implementation
ReadNode::ReadNode(int sn, std::shared_ptr<VariableNode> var)
	: IoNode(NodeType::READ, sn, var) { }

// PrintNode Implementation
PrintNode::PrintNode(int sn, std::shared_ptr<VariableNode> var)
	: IoNode(NodeType::PRINT, sn, var) { }