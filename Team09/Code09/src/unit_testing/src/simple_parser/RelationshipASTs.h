#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/WhileNode.h"

#include <memory>
#include <string>
#include <vector>

class RelationshipASTs {
private:
	static std::shared_ptr<ConstantNode> one;
	static std::shared_ptr<ConstantNode> two;
	static std::shared_ptr<ConstantNode> three;

	static std::shared_ptr<VariableNode> w;
	static std::shared_ptr<VariableNode> x;
	static std::shared_ptr<VariableNode> y;
	static std::shared_ptr<VariableNode> z;

	static ExprNode xPLus1;
	static ExprNode yPLus1;

	static std::shared_ptr<PredicateNode> predXLt1;
	static std::shared_ptr<PredicateNode> predYLt1;
public:
	//AST getAST3_1();
	//AST getAST3_2();
	//AST getAST3_3();
	//AST getAST3_4();
	static AST getAST3_5();
	static AST getAST3_6();
	static AST getAST3_7();
	static AST getAST3_8();
	static AST getAST3_9();
	static AST getAST3_10();
	static AST getAST3_11();
	static AST getAST3_12();
	static AST getAST3_13();
	static AST getAST3_14();
	static AST getAST3_15();
	static AST getAST3_16();
	static AST getAST3_17();
	static AST getAST3_18();
	static AST getAST3_19();
	static AST getAST3_20();
	static AST getAST3_21();
	static AST getAST3_22();
	static AST getAST3_23();
};