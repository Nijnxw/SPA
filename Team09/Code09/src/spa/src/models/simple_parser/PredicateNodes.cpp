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

PredicateNode::PredicateNode(std::shared_ptr<RelExprNode> re) :
	Node(NodeType::PREDICATE) {
	relExpr = re;
}

PredicateNode::PredicateNode(ConditionalOperator oper, std::shared_ptr<PredicateNode> right) :
	Node(NodeType::PREDICATE) {
	op = oper;
	rhs = right;
}

PredicateNode::PredicateNode(std::shared_ptr<PredicateNode> left, ConditionalOperator oper, std::shared_ptr<PredicateNode> right) :
	Node(NodeType::PREDICATE) {
	lhs = left;
	op = oper;
	rhs = right;
}

std::shared_ptr<RelExprNode> PredicateNode::getRelExprNode() const {
	return relExpr;
}

std::shared_ptr<PredicateNode> PredicateNode::getLhs() const {
	return lhs;
}

std::shared_ptr<PredicateNode> PredicateNode::getRhs() const {
	return rhs;
}

ConditionalOperator PredicateNode::getOperator() const {
	return op;
}

bool PredicateNode::isTerminalPredicate() const {
	return relExpr != nullptr;
}

bool PredicateNode::operator==(const Node& other) const {
	const PredicateNode* cast = dynamic_cast<const PredicateNode*>(&other);
	return cast != nullptr && 
		cast->isTerminalPredicate() == this->isTerminalPredicate() &&
		(lhs == cast->getLhs() || *lhs == *(cast->getLhs())) &&
		(rhs == cast->getRhs() || *rhs == *(cast->getRhs())) &&
		(relExpr == cast->getRelExprNode() || *relExpr == *(cast->getRelExprNode())) &&
		op == cast->getOperator();	
}
