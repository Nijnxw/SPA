#include "IfNode.h"

IfNode::IfNode(int sn, std::shared_ptr<PredicateNode> pred, std::vector<std::shared_ptr<StmtNode>> then, std::vector<std::shared_ptr<StmtNode>> els) :
	StmtNode(NodeType::IF, sn) {
	predicate = pred;
	thenStmtList = then;
	elseStmtList = els;
}

std::shared_ptr<PredicateNode> IfNode::getPredicate() const {
	return predicate;
}

std::vector<std::shared_ptr<StmtNode>> IfNode::getThenStmtList() const {
	return thenStmtList;
}

std::vector<std::shared_ptr<StmtNode>> IfNode::getElseStmtList() const {
	return elseStmtList;
}

bool IfNode::operator==(const Node& other) const {
	const IfNode* cast = dynamic_cast<const IfNode*>(&other);
	if (cast == nullptr) return false;
	std::vector<std::shared_ptr<StmtNode>> otherThenStmtList = cast->getThenStmtList();
	std::vector<std::shared_ptr<StmtNode>> otherElseStmtList = cast->getElseStmtList();
	return cast != nullptr &&
		*predicate == *(cast->getPredicate()) &&
		StmtNode::operator==(other) &&
		std::equal(begin(thenStmtList), end(thenStmtList),
			begin(otherThenStmtList), end(otherThenStmtList),
			[](const std::shared_ptr<StmtNode> lhs, const std::shared_ptr<StmtNode> rhs) { return *lhs == *rhs; }) &&
		std::equal(begin(elseStmtList), end(elseStmtList),
			begin(otherElseStmtList), end(otherElseStmtList),
			[](const std::shared_ptr<StmtNode> lhs, const std::shared_ptr<StmtNode> rhs) { return *lhs == *rhs; });
}