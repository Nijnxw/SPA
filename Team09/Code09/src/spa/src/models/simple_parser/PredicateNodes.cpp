#include "PredicateNodes.h"

RelExprNode::RelExprNode(RelFactorNode left, ComparatorOperator oper, RelFactorNode right) :
	Node(NodeType::RELEXPR) {
	lhs = left;
	op = oper;
	rhs = right;
}

RelFactorNode RelExprNode::getLhs() const {
	return lhs;
}

RelFactorNode RelExprNode::getRhs() const {
	return rhs;
}

ComparatorOperator RelExprNode::getOperator() const {
	return op;
}


bool RelExprNode::operator==(const Node& other) const {
	const RelExprNode* cast = dynamic_cast<const RelExprNode*> (&other);
	return cast != nullptr &&
		op == cast->getOperator() &&
		std::visit(
			[](const auto& thisLhs, const auto& otherLhs) { return *thisLhs == *otherLhs; },
			lhs,
			cast->getLhs()) && 
		std::visit(
			[](const auto& thisRhs, const auto& otherRhs) { return *thisRhs == *otherRhs; },
			rhs,
			cast->getRhs());
}