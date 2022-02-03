#include "RootNode.h"

RootNode::RootNode(std::vector<ProcedureNode> procList) 
: Node(NodeType::Root) {
	procedureList = procList;
}

std::vector<ProcedureNode> RootNode::getProcedureList() {
	return procedureList;
}