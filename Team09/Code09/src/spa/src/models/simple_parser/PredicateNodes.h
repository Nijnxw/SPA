#pragma once

#include "Node.h"
#include "NodeType.h"
#include "ExprNodes.h"

#include <memory>;
#include <variant>

using RelFactorNode =
	std::variant<std::shared_ptr<VariableNode>, std::shared_ptr<ConstantNode>, std::shared_ptr<BinaryOperatorNode>>;

class RelExprNode : public Node {
private:
	RelFactorNode lhs;
	ComparatorOperator op;
	RelFactorNode rhs;

public:
	RelExprNode(RelFactorNode left, ComparatorOperator oper, RelFactorNode right);
	RelFactorNode getLhs();
	RelFactorNode getRhs();
	bool operator==(const Node& other) const override;
};

class PredicateNode : public Node {
private:
	std::shared_ptr<RelExprNode> relExpr;
	std::shared_ptr<PredicateNode> lhs;
	std::shared_ptr<ConditionalOperator> op;
	std::shared_ptr<PredicateNode> rhs;

public:
	PredicateNode(RelExprNode relExpr);
	PredicateNode(ConditionalOperator op, PredicateNode rhs);
	PredicateNode(PredicateNode lhs, ConditionalOperator op, PredicateNode rhs);

	std::shared_ptr<RelExprNode> getRelExprNode();
	std::shared_ptr<PredicateNode> getLhs();
	std::shared_ptr<PredicateNode> getRhs();

	bool isTerminalPredicate();

	bool operator==(const Node& other) const override;
};