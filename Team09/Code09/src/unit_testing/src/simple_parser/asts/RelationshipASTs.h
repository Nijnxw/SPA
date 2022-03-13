#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/CallNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/WhileNode.h"
#include "NonContainerStmtASTs.h"

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

	static ExprNode xPlus1;
	static ExprNode xPlusY;
	static ExprNode yPlus1;
	static ExprNode zPlus1;

	static std::shared_ptr<PredicateNode> predXLt1;
	static std::shared_ptr<PredicateNode> predYLt1;
	static std::shared_ptr<PredicateNode> predYLt2;
	static std::shared_ptr<PredicateNode> predZLt1;
	static std::shared_ptr<PredicateNode> predZLt3;
	static std::shared_ptr<PredicateNode> predWLt3;
	static std::shared_ptr<PredicateNode> predWLt1;
public:
	static AST getAST3_1();
	static AST getAST3_2();
	static AST getAST3_3();
	static AST getAST3_4();
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
	static AST getAST3_24();
	static AST getAST3_25();
	static AST getAST3_26();
	static AST getAST3_27();
	static AST getAST3_28();
	static AST getAST3_29();
	static AST getAST3_30();
	static AST getAST3_31();
	static AST getAST3_32();
	static AST getAST3_33();
	static AST getAST3_34();
	static AST getAST3_35();
	static AST getAST3_36();
	static AST getAST3_37();
	static AST getAST3_38();
	static AST getAST3_39();
	static AST getAST3_40();
	static AST getAST3_41();
	static AST getAST3_42();
	static AST getAST3_43();
	static AST getAST3_44();
	static AST getAST3_45();
	static AST getAST3_46();
	static AST getAST3_47();
	static AST getAST3_48();
	static AST getAST3_49();
	static AST getAST3_50();
	static AST getAST3_51();
	static AST getAST3_52();
	static AST getAST3_53();
	static AST getAST3_54();
	static AST getAST3_55();
	static AST getAST3_56();
	static AST getAST3_57();

	// stmt count
	static int getStmtCount3_1();
	static int getStmtCount3_2();
	static int getStmtCount3_3();
	static int getStmtCount3_4();
	static int getStmtCount3_5();
	static int getStmtCount3_6();
	static int getStmtCount3_7();
	static int getStmtCount3_8();
	static int getStmtCount3_9();
	static int getStmtCount3_10();
	static int getStmtCount3_11();
	static int getStmtCount3_12();
	static int getStmtCount3_13();
	static int getStmtCount3_14();
	static int getStmtCount3_15();
	static int getStmtCount3_16();
	static int getStmtCount3_17();
	static int getStmtCount3_18();
	static int getStmtCount3_19();
	static int getStmtCount3_20();
	static int getStmtCount3_21();
	static int getStmtCount3_22();
	static int getStmtCount3_23();
	static int getStmtCount3_24();
	static int getStmtCount3_25();
	static int getStmtCount3_26();
	static int getStmtCount3_27();
	static int getStmtCount3_28();
	static int getStmtCount3_29();
	static int getStmtCount3_30();
	static int getStmtCount3_31();
	static int getStmtCount3_32();
	static int getStmtCount3_33();
	static int getStmtCount3_34();
	static int getStmtCount3_35();
	static int getStmtCount3_36();
	static int getStmtCount3_37();
	static int getStmtCount3_38();
	static int getStmtCount3_39();
	static int getStmtCount3_40();
	static int getStmtCount3_41();
	static int getStmtCount3_42();
	static int getStmtCount3_43();
	static int getStmtCount3_44();
	static int getStmtCount3_45();
	static int getStmtCount3_46();
	static int getStmtCount3_47();
	static int getStmtCount3_48();
	static int getStmtCount3_49();
	static int getStmtCount3_50();
	static int getStmtCount3_51();
	static int getStmtCount3_52();
	static int getStmtCount3_53();
	static int getStmtCount3_54();
	static int getStmtCount3_55();
	static int getStmtCount3_56();
	static int getStmtCount3_57();
};