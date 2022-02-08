#include "WhileNode.h"

WhileNode::WhileNode(int sn, std::shared_ptr<PredicateNode> pred, std::vector<std::shared_ptr<StmtNode>> stmts) :
	StmtNode(NodeType::WHILE, sn) {
	predicate = pred;
	stmtList = stmts;
}

std::shared_ptr<PredicateNode> WhileNode::getPredicate() const {
	return predicate;
}

std::vector<std::shared_ptr<StmtNode>> WhileNode::getStmtList() const {
	return stmtList;
}

bool WhileNode::operator==(const Node& other) const {
	const WhileNode* cast = dynamic_cast<const WhileNode*>(&other);
	std::vector<std::shared_ptr<StmtNode>> otherStmtList = cast->getStmtList();
	return cast != nullptr &&
		*predicate == *(cast->getPredicate()) &&
		std::equal(begin(stmtList), end(stmtList),
			begin(otherStmtList), end(otherStmtList),
			[](const std::shared_ptr<StmtNode> lhs, const std::shared_ptr<StmtNode> rhs) { return *lhs == *rhs; });
}