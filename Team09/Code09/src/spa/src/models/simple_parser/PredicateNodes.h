#pragma once

#include "Node.h"
#include "NodeType.h"
#include "ExprNodes.h"

#include <memory>
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
	RelFactorNode getLhs() const;
	RelFactorNode getRhs() const;
	ComparatorOperator getOperator() const;
	bool operator==(const Node& other) const override;
};

class PredicateNode : public Node {
private:
	std::shared_ptr<RelExprNode> relExpr = nullptr;
	std::shared_ptr<PredicateNode> lhs = nullptr;
	ConditionalOperator op = ConditionalOperator::NONE;
	std::shared_ptr<PredicateNode> rhs = nullptr;

public:
	PredicateNode(std::shared_ptr<RelExprNode> re);
	PredicateNode(ConditionalOperator oper, std::shared_ptr<PredicateNode> right);
	PredicateNode(std::shared_ptr<PredicateNode> left, ConditionalOperator oper, std::shared_ptr<PredicateNode> right);

	std::shared_ptr<RelExprNode> getRelExprNode() const;
	std::shared_ptr<PredicateNode> getLhs() const;
	std::shared_ptr<PredicateNode> getRhs() const;
	ConditionalOperator getOperator() const;

	bool isTerminalPredicate() const;

	bool operator==(const Node& other) const override;
};