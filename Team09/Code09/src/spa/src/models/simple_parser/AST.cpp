#include "AST.h"

ProgramNode::ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procList) 
: Node(NodeType::PROGRAM) {
	procedureList = procList;
}

std::vector<std::shared_ptr<ProcedureNode>> ProgramNode::getProcedureList() const {
	return procedureList;
}

bool ProgramNode::operator==(const Node& other) const {
	const ProgramNode* cast = dynamic_cast<const ProgramNode*>(&other);
	if (cast == nullptr) return false;
	std::vector<std::shared_ptr<ProcedureNode>> otherProcedureList = cast->getProcedureList();
	return cast != nullptr &&
		std::equal(begin(procedureList), end(procedureList),
			begin(otherProcedureList), end(otherProcedureList),
			[](const std::shared_ptr<ProcedureNode> lhs, const std::shared_ptr<ProcedureNode> rhs) { return *lhs == *rhs; });
}