#pragma once

#include "CommonNodes.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/CallNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/WhileNode.h"

class ContainerStmtASTs : public CommonNodes {
private:
	static ExprNode xPlusC1;
	static ExprNode yPlusC1;
	static ExprNode yMinusC2;

	static std::shared_ptr<PredicateNode> predC1NeqC1;
	static std::shared_ptr<PredicateNode> predXLtC1;
	static std::shared_ptr<PredicateNode> predXEqC2;

	static std::shared_ptr<PredicateNode> predYLtC1;
	static std::shared_ptr<PredicateNode> predYGteC3;
	static std::shared_ptr<PredicateNode> predYPlusC1LtX;
	static std::shared_ptr<PredicateNode> predZLtC1;

	static std::vector<std::shared_ptr<StmtNode>> whileStmtListRead;

public:
	// while statements
	// basic predicate
	static AST getAST1_39();
	static AST getAST1_40();
	static AST getAST1_41();
	// basic predicate - single comparator operator
	static AST getAST1_42();
	static AST getAST1_43();
	static AST getAST1_44();
	static AST getAST1_45();
	static AST getAST1_46();
	static AST getAST1_47();
	// basic predicate - single conditional operator
	static AST getAST1_48();
	static AST getAST1_49();
	static AST getAST1_50();
	// predicate : term-expr interactions
	static AST getAST1_51();
	static AST getAST1_52();
	static AST getAST1_53();
	static AST getAST1_54();
	// predicate : advanced
	static AST getAST1_55();
	static AST getAST1_56();
	static AST getAST1_57();
	static AST getAST1_58();

	// while statements - single statement in container
	static AST getAST1_59();
	static AST getAST1_60();
	static AST getAST1_61();
	static AST getAST1_62();
	static AST getAST1_63();

	// while statement - all statement types in container
	static AST getAST1_64();

	// If statement - single statement in container
	static AST getAST1_65();
	static AST getAST1_66();
	static AST getAST1_67();
	static AST getAST1_68();
	static AST getAST1_69();
	static AST getAST1_70();
	static AST getAST1_71();

	// if statement - all statement types in container
	static AST getAST1_72();
	static AST getAST1_73();

	// multiple procedures
	static AST getAST1_74();
	static AST getAST1_75();
	static AST getAST1_76();
	static AST getAST1_77();
	static AST getAST1_78();

	// call statement
	static AST getAST1_79();
	static AST getAST1_80();
	static AST getAST1_81();
	static AST getAST1_82();
	static AST getAST1_83();

	// stmt counts
	static int getStmtCount1_39();
	static int getStmtCount1_40();
	static int getStmtCount1_41();
	static int getStmtCount1_42();
	static int getStmtCount1_43();
	static int getStmtCount1_44();
	static int getStmtCount1_45();
	static int getStmtCount1_46();
	static int getStmtCount1_47();
	static int getStmtCount1_48();
	static int getStmtCount1_49();
	static int getStmtCount1_50();
	static int getStmtCount1_51();
	static int getStmtCount1_52();
	static int getStmtCount1_53();
	static int getStmtCount1_54();
	static int getStmtCount1_55();
	static int getStmtCount1_56();
	static int getStmtCount1_57();
	static int getStmtCount1_58();
	static int getStmtCount1_59();
	static int getStmtCount1_60();
	static int getStmtCount1_61();
	static int getStmtCount1_62();
	static int getStmtCount1_63();
	static int getStmtCount1_64();
	static int getStmtCount1_65();
	static int getStmtCount1_66();
	static int getStmtCount1_67();
	static int getStmtCount1_68();
	static int getStmtCount1_69();
	static int getStmtCount1_70();
	static int getStmtCount1_71();
	static int getStmtCount1_72();
	static int getStmtCount1_73();
	static int getStmtCount1_74();
	static int getStmtCount1_75();
	static int getStmtCount1_76();
	static int getStmtCount1_77();
	static int getStmtCount1_78();
	static int getStmtCount1_79();
	static int getStmtCount1_80();
	static int getStmtCount1_81();
	static int getStmtCount1_82();
	static int getStmtCount1_83();
};


