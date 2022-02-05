#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::vector<std::shared_ptr<StmtNode>> stList, std::string procName)
	: Node(NodeType::PROCEDURE) {
	stmtList = stList;
	name = procName;
}

std::vector<std::shared_ptr<StmtNode>> ProcedureNode::getStmtList() const {
	return stmtList;
}

std::string ProcedureNode::getProcName() const {
	return name;
}

bool ProcedureNode::operator==(const Node& other) const {
	const ProcedureNode* cast = dynamic_cast<const ProcedureNode*>(&other);
	std::vector<std::shared_ptr<StmtNode>> otherStmtList = cast->getStmtList();
	return cast != nullptr &&
		name == cast->getProcName() &&
		std::equal(begin(stmtList), end(stmtList),
			begin(otherStmtList), end(otherStmtList),
			[](const std::shared_ptr<StmtNode> lhs, const std::shared_ptr<StmtNode> rhs) { return *lhs == *rhs; });
}