#include "RelationshipASTs.h"

// construction helpers
std::shared_ptr<VariableNode> generateVariable(std::string varName) {
	return std::make_shared<VariableNode>(varName);
}

std::shared_ptr<ConstantNode> generateConstant(int conValue) {
	return std::make_shared<ConstantNode>(std::to_string(conValue));
}
//
//ExprNode generateExpr(std::string varName, BinaryOperator op, int constant) {
//	return std::make_shared<BinaryOperatorNode>(
//		op, generateVariable(varName), generateConstant(constant));
//}
//
//ExprNode generateExpr(std::string var1, BinaryOperator op, std::string var2) {
//	return std::make_shared<BinaryOperatorNode>(
//		op, generateVariable(var1), generateVariable(var2));
//}
//
//ExprNode generateExpr(ExprNode expr1, BinaryOperator op, ExprNode expr2) {
//	return std::make_shared<BinaryOperatorNode>(op, expr1, expr2);
//}

AST generateAST(std::vector<std::shared_ptr<StmtNode>> stmts, std::string progName) {
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, progName);
	std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
	return std::make_shared<ProgramNode>(procList);
}

std::shared_ptr<ConstantNode> RelationshipASTs::one = generateConstant(1);
std::shared_ptr<ConstantNode> RelationshipASTs::two = generateConstant(2);
std::shared_ptr<ConstantNode> RelationshipASTs::three = generateConstant(3);

std::shared_ptr<VariableNode> RelationshipASTs::w = generateVariable("w");
std::shared_ptr<VariableNode> RelationshipASTs::x = generateVariable("x");
std::shared_ptr<VariableNode> RelationshipASTs::y = generateVariable("y");
std::shared_ptr<VariableNode> RelationshipASTs::z = generateVariable("z");

ExprNode RelationshipASTs::xPLus1 = std::make_shared<BinaryOperatorNode>(
	BinaryOperator::PLUS, RelationshipASTs::x, RelationshipASTs::one
);
ExprNode RelationshipASTs::yPLus1 = std::make_shared<BinaryOperatorNode>(
	BinaryOperator::PLUS, RelationshipASTs::y, RelationshipASTs::one
);

std::shared_ptr<PredicateNode> RelationshipASTs::predXLt1 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(x, ComparatorOperator::LT, one)
);
std::shared_ptr<PredicateNode> RelationshipASTs::predYLt1 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(y, ComparatorOperator::LT, one)
);

AST RelationshipASTs::getAST3_5() {
	/*
	 * procedure testProgram {
	 * 1	read x;
	 * 2	print x;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<PrintNode>(2, x)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_6() {
	/*
	 * procedure testProgram {
	 * 1	read x;
	 * 2	x = x + 1;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<AssignNode>(2, x, xPLus1, "x 1 +")
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_7() {
	/*
	 * procedure testProgram {
	 * 1	print x;
	 * 2	x = x + 1;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<PrintNode>(1, x),
		std::make_shared<AssignNode>(2, x, xPLus1, "x 1 +")
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_8() {
	/*
	 * procedure testProgram {
	 * 1	read x;
	 * 2    print x;
	 * 3	x = x + 1;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<PrintNode>(2, x),
		std::make_shared<AssignNode>(3, x, xPLus1, "x 1 +")
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_9() {
	/*
	 * procedure testProgram {
	 * 1	read x;
	 * 2	read y;
	 * 3	read z;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<ReadNode>(2, y),
		std::make_shared<ReadNode>(3, z)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_10() {
	/*
	 * procedure testProgram {
	 * 1	x = x + y;
	 * 2    print x;
	 * 3	read x;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<AssignNode>(1, x, y, "x y +"),
		std::make_shared<PrintNode>(2, x),
		std::make_shared<ReadNode>(3, x)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_11() {
	/*
	 * procedure testProgram {
	 * 1  read x;
	 * 2  print x;
	 * 3  while (x < 1) {
	 * 4    read x;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(4, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<PrintNode>(2, x),
		std::make_shared<WhileNode>(3, predXLt1, whileStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_12() {
	/*
	 * procedure testProgram {
	 * 1  while (x < 1) {
	 * 2    read x;
		  }
	 * 3  read x;
	 * 4  print x;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList),
		std::make_shared<ReadNode>(3, x),
		std::make_shared<PrintNode>(4, x)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_13() {
	/*
	 * procedure testProgram {
	 * 1  read x;
	 * 2  while (x < 1) {
	 * 3    read x;
		  }
	 * 4  print x;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(3, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<WhileNode>(2, predXLt1, whileStmtList),
		std::make_shared<PrintNode>(4, x)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_14() {
	/*
	 * procedure testProgram {
	 * 1  read x;
	 * 2  print x;
	 * 3  if (x < 1) then {
	 * 4    read x;
	 *    } else {
	 * 5    print y;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(4, x)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<PrintNode>(2, x),
		std::make_shared<IfNode>(3, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_15() {
	/*
	 * procedure testProgram {
	 * 1  if (x < 1) then {
	 * 2    read x;
	 *    } else {
	 * 3    print y;
	 *    }
	 * 4  read x;
	 * 5  print x;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(2, x)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList),
		std::make_shared<ReadNode>(4, x),
		std::make_shared<PrintNode>(5, x)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_16() {
	/*
	 * procedure testProgram {
	 * 1  read x;
	 * 2  if (x < 1) then {
	 * 3    read x;
	 *    } else {
	 * 4    print y;
	 *    }
	 * 5  print x;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(3, x)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, x),
		std::make_shared<IfNode>(2, predXLt1, thenStmtList, elseStmtList),
		std::make_shared<PrintNode>(5, x)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_17() {
	/*
	 * procedure testProgram {
	 * 1  while (x < 1) {
	 * 2    read x;
	 *    }
	 * 3  if (x < 1) then {
	 * 4    read x;
	 *    } else {
	 * 5    print y;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(1, x)
	};

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(4, x)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList),
		std::make_shared<IfNode>(2, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_18() {
	/*
	 * procedure testProgram {
	 * 1  while (x < 1) {
	 * 2    read x;
	 * 3    print x;
	 * 4    x = x + 1;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<PrintNode>(3, x),
		std::make_shared<AssignNode>(4, x, xPLus1, "x 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_19() {
	/*
	 * procedure testProgram {
	 * 1  if (x < 1) then {
	 * 2    read x;
	 * 3    print x;
	 * 4    x = x + 1;
	 *    } else {
	 * 5    read y;
	 * 6    print y;
	 * 7    y = y + 1;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<PrintNode>(3, x),
		std::make_shared<AssignNode>(4, x, xPLus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(5, y),
		std::make_shared<PrintNode>(6, y),
		std::make_shared<AssignNode>(7, y, yPLus1, "y 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_20() {
	/*
	 * procedure testProgram {
	 * 1  if (x < 1) then {
	 * 2    read x;
	 * 3    while (y < 1) {
	 * 4      read y;
	 *      }
	 *    } else {
	 * 5    read z;
	 * 6    while (y < 1) {
	 * 7      read y;
	 *      }
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenWhileStmtList{
		std::make_shared<ReadNode>(4, y)
	};
	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<WhileNode>(3, predYLt1, thenWhileStmtList)
	};


	std::vector<std::shared_ptr<StmtNode>> elseWhileStmtList{
		std::make_shared<ReadNode>(7, y)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(5, z),
		std::make_shared<WhileNode>(6, predYLt1, elseWhileStmtList)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_21() {
	/*
	 * procedure testProgram {
	 * 1  if (x < 1) then {
	 * 2    read x;
	 * 3    if (y < 1) then {
	 * 4      read y;
	 *      } else {
	 * 5      print y;
	 *      }
	 *    } else {
	 * 6    read z;
	 * 7    if (y < 1) then {
	 * 8      read z;
	 *      } else {
	 * 9      print z;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenThenStmtList{
		std::make_shared<ReadNode>(4, y)
	};	
	std::vector<std::shared_ptr<StmtNode>> thenElseStmtList{
		std::make_shared<PrintNode>(5, y)
	};
	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<IfNode>(3, predYLt1, thenThenStmtList, thenElseStmtList)
	};


	std::vector<std::shared_ptr<StmtNode>> elseThenStmtList{
		std::make_shared<ReadNode>(8, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseElseStmtList{
		std::make_shared<PrintNode>(9, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(6, z),
		std::make_shared<WhileNode>(7, predYLt1, elseThenStmtList, elseElseStmtList)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_22() {
	/*
	 * procedure testProgram {
	 * 1  while (x < 1)  {
	 * 2    if (y < 1) then {
	 * 3      read x;
	 *      } else {
	 * 4      read z;
	 *      }
	 * 5    read y;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileThenStmtList{
		std::make_shared<ReadNode>(3, x)
	};
	std::vector<std::shared_ptr<StmtNode>> whileElseStmtList{
		std::make_shared<ReadNode>(4, z)
	};
	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<IfNode>(2, predYLt1, whileThenStmtList, whileElseStmtList),
		std::make_shared<ReadNode>(5, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_23() {
	/*
	 * procedure testProgram {
	 * 1  while (x < 1)  {
	 * 2    while (y < 1) {
	 * 3      read x;
	 *      }
	 * 4    read y;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileWhileStmtList{
		std::make_shared<ReadNode>(3, x)
	};
	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<WhileNode>(2, predYLt1, whileWhileStmtList),
		std::make_shared<ReadNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};
	return generateAST(stmtList, "testProgram");
}