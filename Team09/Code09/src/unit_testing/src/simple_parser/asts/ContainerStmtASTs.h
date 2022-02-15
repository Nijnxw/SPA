#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/WhileNode.h"

class ContainerStmtASTs {
public:
	// while statements
	// basic predicate
	static AST getAST1_39();
	static AST getAST1_40();
	static AST getAST1_41();
	// basic predicate - single comparator operator
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
	static AST getAST1_52();
	static AST getAST1_53();
	static AST getAST1_54();
	// predicate : advanced
	static AST getAST1_55();
	static AST getAST1_56();
	static AST getAST1_57();
	static AST getAST1_58();

	// while statements - single statement
	static AST getAST1_60();
	static AST getAST1_61();
	static AST getAST1_62();
	static AST getAST1_63();

};


