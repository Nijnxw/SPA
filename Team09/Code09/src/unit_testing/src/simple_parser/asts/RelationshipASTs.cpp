#include "RelationshipASTs.h"

// construction helpers
std::shared_ptr<VariableNode> generateVariable(std::string varName) {
	return std::make_shared<VariableNode>(varName);
}

std::shared_ptr<ConstantNode> generateConstant(int conValue) {
	return std::make_shared<ConstantNode>(std::to_string(conValue));
}

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

ExprNode RelationshipASTs::xPlus1 = std::make_shared<BinaryOperatorNode>(
	BinaryOperator::PLUS, RelationshipASTs::x, RelationshipASTs::one
);
ExprNode RelationshipASTs::yPlus1 = std::make_shared<BinaryOperatorNode>(
	BinaryOperator::PLUS, RelationshipASTs::y, RelationshipASTs::one
);
ExprNode RelationshipASTs::xPlusY = std::make_shared<BinaryOperatorNode>(
	BinaryOperator::PLUS, RelationshipASTs::x, RelationshipASTs::y
);
ExprNode RelationshipASTs::zPlus1 = std::make_shared<BinaryOperatorNode>(
	BinaryOperator::PLUS, RelationshipASTs::z, RelationshipASTs::one
);

std::shared_ptr<PredicateNode> RelationshipASTs::predXLt1 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(x, ComparatorOperator::LT, one)
);
std::shared_ptr<PredicateNode> RelationshipASTs::predYLt1 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(y, ComparatorOperator::LT, one)
);
std::shared_ptr<PredicateNode> RelationshipASTs::predYLt2 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(y, ComparatorOperator::LT, two)
);
std::shared_ptr<PredicateNode> RelationshipASTs::predZLt3 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(z, ComparatorOperator::LT, three)
);
std::shared_ptr<PredicateNode> RelationshipASTs::predWLt3 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(w, ComparatorOperator::LT, three)
	);


AST RelationshipASTs::getAST3_1() {
	return NonContainerStmtASTs::getAST1_1();
}

AST RelationshipASTs::getAST3_2() {
	return NonContainerStmtASTs::getAST1_2();
}

AST RelationshipASTs::getAST3_3() {
	return NonContainerStmtASTs::getAST1_37();
}

AST RelationshipASTs::getAST3_4() {
	return NonContainerStmtASTs::getAST1_37();
}

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
		std::make_shared<AssignNode>(2, x, xPlus1, "x 1 +")
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
		std::make_shared<AssignNode>(2, x, xPlus1, "x 1 +")
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
		std::make_shared<AssignNode>(3, x, xPlus1, "x 1 +")
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
		std::make_shared<AssignNode>(1, x, xPlusY, "x y +"),
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
		std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(4, x)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList),
		std::make_shared<IfNode>(3, predXLt1, thenStmtList, elseStmtList)
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
		std::make_shared<AssignNode>(4, x, xPlus1, "x 1 +")
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
		std::make_shared<AssignNode>(4, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(5, y),
		std::make_shared<PrintNode>(6, y),
		std::make_shared<AssignNode>(7, y, yPlus1, "y 1 +")
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
	 *      }
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
		std::make_shared<IfNode>(7, predYLt1, elseThenStmtList, elseElseStmtList)
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
		std::make_shared<ReadNode>(5, y)
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

AST RelationshipASTs::getAST3_24() {
	/*
	 * procedure testProgram {
	 * 1   if (x < 1) then {
	 * 2     read x;
	 * 3     while (y < 1) {
	 * 4       read y;
	 * 5       print x;
	 * 6       x = x + 1;
	 *       }
	 * 7     x = x + 1;
	 *     } else {
	 * 8     while (y < 1) {
	 * 9       read y;
	 * 10      print x;
	 * 11      x = x + 1;
	 *      }
	 * 12    read z;
	 * 13    print y;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenWhileStmtList{
		std::make_shared<ReadNode>(4, y),
		std::make_shared<PrintNode>(5, x),
		std::make_shared<AssignNode>(6, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<WhileNode>(3, predYLt1, thenWhileStmtList),
		std::make_shared<AssignNode>(7, x, xPlus1, "x 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> elseWhileStmtList{
		std::make_shared<ReadNode>(9, y),
		std::make_shared<PrintNode>(10, x),
		std::make_shared<AssignNode>(11, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<WhileNode>(8, predYLt1, elseWhileStmtList),
		std::make_shared<ReadNode>(12, z),
		std::make_shared<PrintNode>(13, y)
	};
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_25() {
	/*
	 * procedure testProgram {
	 * 1   if (x < 1) then {
	 * 2     while (y < 1) {
	 * 3       read y;
	 * 4       print x;
	 * 5       x = x + 1;
	 *       }
	 * 6     read x;
	 * 7     x = x + 1;
	 *     } else {
	 * 8     read z;
	 * 9     print y;
	 * 10    while (y < 1) {
	 * 11      read y;
	 * 12      print x;
	 * 13      x = x + 1;
	 *      }
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenWhileStmtList{
		std::make_shared<ReadNode>(3, y),
		std::make_shared<PrintNode>(4, x),
		std::make_shared<AssignNode>(5, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<WhileNode>(2, predYLt1, thenWhileStmtList),
		std::make_shared<ReadNode>(6, x),
		std::make_shared<AssignNode>(7, x, xPlus1, "x 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> elseWhileStmtList{
		std::make_shared<ReadNode>(11, y),
		std::make_shared<PrintNode>(12, x),
		std::make_shared<AssignNode>(13, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(8, z),
		std::make_shared<PrintNode>(9, y),
		std::make_shared<WhileNode>(10, predYLt1, elseWhileStmtList)
	};
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_26() {
	/*
	 * procedure testProgram {
	 * 1   if (x < 1) then {
	 * 2     read x;
	 * 3     x = x + 1;
	 * 4     while (y < 1) {
	 * 5       read y;
	 * 6       print x;
	 * 7       x = x + 1;
	 *       }
	 *     } else {
	 * 8     read z;
	 * 9     while (y < 1) {
	 * 10      read y;
	 * 11      print x;
	 * 12      x = x + 1;
	 *      }
	 * 13    print y;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenWhileStmtList{
		std::make_shared<ReadNode>(5, y),
		std::make_shared<PrintNode>(6, x),
		std::make_shared<AssignNode>(7, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<AssignNode>(3, x, xPlus1, "x 1 +"),
		std::make_shared<WhileNode>(4, predYLt1, thenWhileStmtList)
	};

	std::vector<std::shared_ptr<StmtNode>> elseWhileStmtList{
		std::make_shared<ReadNode>(10, y),
		std::make_shared<PrintNode>(11, x),
		std::make_shared<AssignNode>(12, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(8, z),
		std::make_shared<WhileNode>(9, predYLt1, elseWhileStmtList),
		std::make_shared<PrintNode>(13, y)
	};
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_27() {
	/*
	 * procedure testProgram {
	 * 1   while (x < 1)  {
	 * 2     if (y < 1) then {
	 * 3       read x;
	 * 4       print x;
	 * 5       x = x + 1;
	 *       } else {
	 * 6       read z;
	 * 7       print z;
	 * 8       z = z + 1;
	 *       }
	 * 9     read x;
	 * 10    x = x + 1;
	 *     }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileThenStmtList{
		std::make_shared<ReadNode>(3, y),
		std::make_shared<PrintNode>(4, x),
		std::make_shared<AssignNode>(5, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> whileElseStmtList{
		std::make_shared<ReadNode>(6, z),
		std::make_shared<PrintNode>(7, z),
		std::make_shared<AssignNode>(8, z, zPlus1, "z 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<IfNode>(2, predYLt1, whileThenStmtList, whileElseStmtList),
		std::make_shared<ReadNode>(9, x),
		std::make_shared<AssignNode>(10, x, xPlus1, "x 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};

	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_28() {
	/*
	 * procedure testProgram {
	 * 1   while (x < 1)  {
	 * 2     read x;
	 * 3     if (y < 1) then {
	 * 4       read x;
	 * 5       print x;
	 * 6       x = x + 1;
	 *       } else {
	 * 7       read z;
	 * 8       print z;
	 * 9       z = z + 1;
	 *       }
	 * 10    x = x + 1;
	 *     }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileThenStmtList{
		std::make_shared<ReadNode>(4, y),
		std::make_shared<PrintNode>(5, x),
		std::make_shared<AssignNode>(6, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> whileElseStmtList{
		std::make_shared<ReadNode>(7, z),
		std::make_shared<PrintNode>(8, z),
		std::make_shared<AssignNode>(9, z, zPlus1, "z 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<IfNode>(3, predYLt1, whileThenStmtList, whileElseStmtList),
		std::make_shared<AssignNode>(10, x, xPlus1, "x 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};

	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_29() {
	/*
	 * procedure testProgram {
	 * 1   while (x < 1)  {
	 * 2     read x;
	 * 3     x = x + 1;
	 * 4     if (y < 1) then {
	 * 5       read x;
	 * 6       print x;
	 * 7       x = x + 1;
	 *       } else {
	 * 8       read z;
	 * 9       print z;
	 * 10      z = z + 1;
	 *       }
	 *     }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileThenStmtList{
		std::make_shared<ReadNode>(5, y),
		std::make_shared<PrintNode>(6, x),
		std::make_shared<AssignNode>(7, x, xPlus1, "x 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> whileElseStmtList{
		std::make_shared<ReadNode>(8, z),
		std::make_shared<PrintNode>(9, z),
		std::make_shared<AssignNode>(10, z, zPlus1, "z 1 +")
	};
	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<AssignNode>(3, x, xPlus1, "x 1 +"),
		std::make_shared<IfNode>(4, predYLt1, whileThenStmtList, whileElseStmtList)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};

	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_30() {
	/*
	 * procedure testProgram {
	 * 1   if (x < 1) then {
	 * 2     if (y < 2) then {
	 * 3       read y;
	 *       } else {
	 * 4       if (z < 3) then {
	 * 5         read z;
	 *         } else {
	 * 6         print z;
	 *         }
	 * 7       print y;
	 *       }
	 * 8     read x;
	 *     } else {
	 * 9     print x;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenThenThenStmtList{
		std::make_shared<ReadNode>(5, z)
	};
	std::vector<std::shared_ptr<StmtNode>> thenThenElseStmtList{
		std::make_shared<PrintNode>(6, z)
	};

	std::vector<std::shared_ptr<StmtNode>> thenThenStmtList{
		std::make_shared<ReadNode>(3, y)
	};
	std::vector<std::shared_ptr<StmtNode>> thenElseStmtList{
		std::make_shared<IfNode>(4, predZLt3, thenThenThenStmtList, thenThenElseStmtList),
		std::make_shared<PrintNode>(7, y)
	};

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<IfNode>(2, predYLt2, thenThenStmtList, thenElseStmtList),
		std::make_shared<ReadNode>(8, x)
	};	
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(9, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_31() {
	/*
	 * procedure testProgram {
	 * 1   while (x < 1)  {
	 * 2     while (y < 2) {
	 * 3       while (z < 3) {
	 * 4         read z;
	 *         }
	 * 5       read y;
	 *       }
	 * 6     read x;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileWhileWhileStmtList{
		std::make_shared<ReadNode>(4, z)
	};

	std::vector<std::shared_ptr<StmtNode>> whileWhileStmtList{
		std::make_shared<WhileNode>(3, predZLt3, whileWhileWhileStmtList),
		std::make_shared<ReadNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<WhileNode>(2, predYLt2, whileWhileStmtList),
		std::make_shared<ReadNode>(6, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_32() {
	/*
	 * procedure testProgram {
	 * 1   while (x < 1)  {
	 * 2     if (y < 2) then {
	 * 3       while (z < 3) {
	 * 4         read z;
	 *         }
	 * 5       read y;
	 *       } else {
	 * 6       while (w < 3) {
	 * 7         read w;
	 *         }
	 * 8       read w;
	 *       }
	 * 9     read x;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileThenWhileStmtList{
		std::make_shared<ReadNode>(4, z)
	};
	std::vector<std::shared_ptr<StmtNode>> whileThenStmtList{
		std::make_shared<WhileNode>(3, predZLt3, whileThenWhileStmtList),
		std::make_shared<ReadNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileElseWhileStmtList{
		std::make_shared<ReadNode>(7, w)
	};
	std::vector<std::shared_ptr<StmtNode>> whileElseStmtList{
		std::make_shared<WhileNode>(6, predWLt3, whileElseWhileStmtList),
		std::make_shared<ReadNode>(8, w)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<IfNode>(2, predYLt2, whileThenStmtList, whileElseStmtList),
		std::make_shared<ReadNode>(9, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList)
	};
	return generateAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_33() {
	/*
	 * procedure testProgram {
	 * 1   if (x < 1) then {
	 * 2     while (y < 2) {
	 * 3       if (z < 3) then {
	 * 4         read z;
	 *         } else {
	 * 5         print z;
	 *         }
	 * 6       print y;
	 *       }
	 * 7     read x;
	 *     } else {
	 * 8     print x;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenWhileThenStmtList{
		std::make_shared<ReadNode>(4, z)
	};
	std::vector<std::shared_ptr<StmtNode>> thenWhileElseStmtList{
		std::make_shared<PrintNode>(5, z)
	};
	std::vector<std::shared_ptr<StmtNode>> thenWhileStmtList{
		std::make_shared<IfNode>(3, predZLt3, thenWhileThenStmtList, thenWhileElseStmtList),
		std::make_shared<PrintNode>(6, y)
	};

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<WhileNode>(2, predYLt2, thenWhileStmtList),
		std::make_shared<ReadNode>(7, x)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(8, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};
	return generateAST(stmtList, "testProgram");
}