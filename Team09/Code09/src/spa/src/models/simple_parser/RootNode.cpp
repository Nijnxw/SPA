#include "RootNode.h"

RootNode::RootNode(std::vector<std::shared_ptr<ProcedureNode>> procList) 
: Node(NodeType::ROOT) {
	procedureList = procList;
}

std::vector<std::shared_ptr<ProcedureNode>> RootNode::getProcedureList() const {
	return procedureList;
}

bool RootNode::operator==(const Node& other) const {
	const RootNode* cast = dynamic_cast<const RootNode*>(&other);
	std::vector<std::shared_ptr<ProcedureNode>> otherProcedureList = cast->getProcedureList();
	return cast != nullptr &&
		std::equal(begin(procedureList), end(procedureList),
			begin(otherProcedureList), end(otherProcedureList),
			[](const std::shared_ptr<ProcedureNode> lhs, const std::shared_ptr<ProcedureNode> rhs) { return *lhs == *rhs; });
}