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
	if (!isTerminalPredicate()) throw std::runtime_error("Predicate is not a terminal predicate");
	return relExpr;
}

std::shared_ptr<PredicateNode> PredicateNode::getLhs() const {
	if (!isFullPredicate()) throw std::runtime_error("Predicate does not contain a left predicate (Not terminal or a NOT predicate)");
	return lhs;
}

std::shared_ptr<PredicateNode> PredicateNode::getRhs() const {
	if (isTerminalPredicate()) throw std::runtime_error("Predicate is a terminal predicate");
	return rhs;
}

RelFactorNode PredicateNode::getRelLhs() const {
	if (!isTerminalPredicate()) throw std::runtime_error("Predicate is not a terminal predicate");
	return relExpr->getLhs();
}

RelFactorNode PredicateNode::getRelRhs() const {
	if (!isTerminalPredicate()) throw std::runtime_error("Predicate is not a terminal predicate");
	return relExpr->getRhs();
}

ConditionalOperator PredicateNode::getOperator() const {
	return op;
}

bool PredicateNode::isTerminalPredicate() const {
	return relExpr != nullptr;
}

bool PredicateNode::isNotPredicate() const {
	return !isTerminalPredicate() && lhs == nullptr;
}

bool PredicateNode::isFullPredicate() const {
	return lhs != nullptr && rhs != nullptr;
}

bool PredicateNode::operator==(const Node& other) const {
	const PredicateNode* cast = dynamic_cast<const PredicateNode*>(&other);
	if (cast == nullptr) return false;
	// case where both are terminal pred
	if (this->isTerminalPredicate() && cast->isTerminalPredicate() == this->isTerminalPredicate()) {
		return *relExpr == *(cast->getRelExprNode()) && op == cast->getOperator();
	// case where both are NOT pred
	} else if (this->isNotPredicate() && cast->isNotPredicate() == this->isNotPredicate()) {
		return *rhs == *(cast->getRhs()) && op == cast->getOperator();
	// case where both are pred with 2 children
	} else if (this->isFullPredicate() && cast->isFullPredicate() == this->isFullPredicate()) {
		return *lhs == *(cast->getLhs()) && *rhs == *(cast->getRhs()) && op == cast->getOperator();
	} 
	return false;
}
