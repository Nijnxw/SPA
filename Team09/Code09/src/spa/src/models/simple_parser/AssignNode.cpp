#include "AssignNode.h"

AssignNode::AssignNode(int sn, std::shared_ptr<VariableNode> var, ExprNode exp, std::string pf)
	: StmtNode(NodeType::ASSIGN, sn), assignedVar(var), expression(exp) {
	postfix = pf;
}

std::shared_ptr<VariableNode> AssignNode::getAssignedVar() const {
	return assignedVar;
}

ExprNode AssignNode::getExpression() const {
	return expression;
}

std::string AssignNode::getPostfix() const {
	return postfix;
}

bool AssignNode::operator==(const Node & other) const {
	const AssignNode* cast = dynamic_cast<const AssignNode*>(&other);
	return cast != nullptr &&
		StmtNode::operator==(other) &&
		*(this->getAssignedVar()) == *(cast->getAssignedVar()) &&
		std::visit(
			[](const auto& thisExpr, const auto& otherExpr) { return *thisExpr == *otherExpr; },
			this->getExpression(),
			cast->getExpression());
}
