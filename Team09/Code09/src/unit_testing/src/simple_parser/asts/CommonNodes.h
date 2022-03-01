#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"

class CommonNodes {
protected:
	static std::shared_ptr<ConstantNode> c1;
	static std::shared_ptr<ConstantNode> c2;
	static std::shared_ptr<ConstantNode> c3;

	static std::shared_ptr<VariableNode> a;
	static std::shared_ptr<VariableNode> x;
	static std::shared_ptr<VariableNode> y;
	static std::shared_ptr<VariableNode> z;
public:
	static AST generateBasicAST(std::vector<std::shared_ptr<StmtNode>> stmts);
};
