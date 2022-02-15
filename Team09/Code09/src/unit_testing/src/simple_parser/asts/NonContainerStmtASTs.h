#pragma once

#include "models/simple_parser/AST.h"

class NonContainerStmtASTs {
public:
	// ast for read & print stmts
	static AST getAST1_1();
	static AST getAST1_2();

	// ast for assignment stmts
	static AST getAST1_3();
	static AST getAST1_4();
	static AST getAST1_5();
	static AST getAST1_6();
	static AST getAST1_7();
	static AST getAST1_8();
	// single operator parsing
	static AST getAST1_10();
	static AST getAST1_11();
	static AST getAST1_12();
	static AST getAST1_13();
	// operator precedences
	static AST getAST1_14();
	static AST getAST1_15();
	static AST getAST1_16();
	static AST getAST1_17();
	static AST getAST1_18();
	static AST getAST1_19();
	static AST getAST1_20();
	static AST getAST1_21();
	// parentheses interactions
	static AST getAST1_22();
	static AST getAST1_23();
	static AST getAST1_24();
	static AST getAST1_25();
	static AST getAST1_26();
	static AST getAST1_27();
	static AST getAST1_28();
	static AST getAST1_29();
	static AST getAST1_30();
	// operator precedences - Intermediate
	static AST getAST1_31();
	static AST getAST1_32();
	static AST getAST1_33();
	static AST getAST1_34();
	// operator precedence - Advanced
	static AST getAST1_35();
	static AST getAST1_36();
	static AST getAST1_37();
	static AST getAST1_38();
};
