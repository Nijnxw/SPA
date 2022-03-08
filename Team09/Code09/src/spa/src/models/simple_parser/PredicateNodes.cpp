#include "PredicateNodes.h"

//overloaded functions to handle RelFactorNode variants for variable extraction
std::unordered_set<std::string> extractVariable(RelFactorNode relExpr);
std::unordered_set<std::string> extractVariable(std::shared_ptr<ConstantNode> constant) {
	return { constant->getValue() };
}

std::unordered_set<std::string> extractVariable(std::shared_ptr<VariableNode> variable) {
	return { variable->getName() };
}

std::unordered_set<std::string> extractVariable(std::shared_ptr<BinaryOperatorNode> binOp) {
	std::unordered_set<std::string> vars = extractVariable(binOp->getLhs());
	std::unordered_set<std::string> rightVar = extractVariable(binOp->getRhs());
	
	vars.insert(rightVar.begin(), rightVar.end());
	return vars;
}

std::unordered_set<std::string> extractVariable(RelFactorNode relExpr) {
	return std::visit(
		[](const auto& relFactor) { return extractVariable(relFactor); },
		relExpr
	);
}

RelExprNode::RelExprNode(RelFactorNode left, ComparatorOperator oper, RelFactorNode right) :
	Node(NodeType::RELEXPR) {
	lhs = left;
	op = oper;
	rhs = right;

	//populate variables bottom-up
	std::unordered_set<std::string> leftVars = extractVariable(left);
	variables.insert(leftVars.begin(), leftVars.end());
	std::unordered_set<std::string> rightVars = extractVariable(right);
	variables.insert(rightVars.begin(), rightVars.end());
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

std::unordered_set<std::string> RelExprNode::getVariables() const {
	return variables;
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

	//populate control variables bottom-up
	std::unordered_set<std::string> reControlVariables = re->getVariables();
	controlVariables.insert(reControlVariables.begin(), reControlVariables.end());
}

PredicateNode::PredicateNode(ConditionalOperator oper, std::shared_ptr<PredicateNode> right) :
	Node(NodeType::PREDICATE) {
	op = oper;
	rhs = right;

	//populate control variables bottom-up
	std::unordered_set<std::string> rightControlVariables = right->getControlVariables();
	controlVariables.insert(rightControlVariables.begin(), rightControlVariables.end());
}

PredicateNode::PredicateNode(std::shared_ptr<PredicateNode> left, ConditionalOperator oper, std::shared_ptr<PredicateNode> right) :
	Node(NodeType::PREDICATE) {
	lhs = left;
	op = oper;
	rhs = right;

	//populate control variables bottom-up
	std::unordered_set<std::string> leftControlVariables = left->getControlVariables();
	controlVariables.insert(leftControlVariables.begin(), leftControlVariables.end());
	std::unordered_set<std::string> rightControlVariables = right->getControlVariables();
	controlVariables.insert(rightControlVariables.begin(), rightControlVariables.end());
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

std::unordered_set<std::string> PredicateNode::getControlVariables() const {
	return controlVariables;
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
