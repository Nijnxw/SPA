#include "RootNode.h"

RootNode::RootNode(std::vector<std::shared_ptr<ProcedureNode>> procList) 
: Node(NodeType::Root) {
	procedureList = procList;
}

std::vector<std::shared_ptr<ProcedureNode>> RootNode::getProcedureList() {
	return procedureList;
}