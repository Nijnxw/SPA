#pragma once

#include "NodeType.h"
#include "StmtNode.h"
#include "ExprNodes.h"

#include <memory>
#include <string>

class AssignNode : public StmtNode {
private:
	std::shared_ptr<VariableNode> assignedVar;
	ExprNode expression;
	std::string postfix;

public:
	AssignNode(int sn, std::shared_ptr<VariableNode> var, ExprNode exp, std::string pf);
	std::shared_ptr<VariableNode> getAssignedVar() const;
	std::string getAssignedVarName() const;
	ExprNode getExpression() const;
	std::string getPostfix() const;
	bool operator==(const Node& other) const override;
};