#include "IoNodes.h"

// IoNode Implementation
IoNode::IoNode(NodeType t, int sn, VariableNode var)
	: StmtNode(t, sn), variable(var) {
}

VariableNode IoNode::getVariable() {
	return variable;
}

// ReadNode Implementation
ReadNode::ReadNode(int sn, VariableNode var)
	: IoNode(NodeType::Read, sn, var) { }

// PrintNode Implementation
PrintNode::PrintNode(int sn, VariableNode var)
	: IoNode(NodeType::Print, sn, var) { }