#include "RelationshipASTs.h"

// construction helpers
std::shared_ptr<VariableNode> generateVariable(std::string varName) {
	return std::make_shared<VariableNode>(varName);
}

std::shared_ptr<ConstantNode> generateConstant(int conValue) {
	return std::make_shared<ConstantNode>(std::to_string(conValue));
}

AST generateBasicAST(std::vector<std::shared_ptr<StmtNode>> stmts, std::string progName) {
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, progName);
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {progName, proc} };
	return std::make_shared<ProgramNode>(procMap);
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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

	return generateBasicAST(stmtList, "testProgram");
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

	return generateBasicAST(stmtList, "testProgram");
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

	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
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
	return generateBasicAST(stmtList, "testProgram");
}

AST RelationshipASTs::getAST3_34() {
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
	 *       }
	 *     }
	 *   }
	 * 
	 *   procedure testProgram2 {
	 * 14  while (x < 1) {
	 * 15    if (y < 2) then {
	 * 16      while (z < 3) {
	 * 17        read z;
	 *         }
	 * 18      read y;
	 *       } else {
	 * 19      while (w < 3) {
	 * 20         read w;
	 *         }
	 * 21      read w;
	 *       }
	 * 22    read x;
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
	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<IfNode>(1, predXLt1, thenStmtList, elseStmtList)
	};

	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> whileThenWhileStmtList{
	std::make_shared<ReadNode>(17, z)
	};
	std::vector<std::shared_ptr<StmtNode>> whileThenStmtList{
		std::make_shared<WhileNode>(16, predZLt3, whileThenWhileStmtList),
		std::make_shared<ReadNode>(18, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileElseWhileStmtList{
		std::make_shared<ReadNode>(20, w)
	};
	std::vector<std::shared_ptr<StmtNode>> whileElseStmtList{
		std::make_shared<WhileNode>(19, predWLt3, whileElseWhileStmtList),
		std::make_shared<ReadNode>(21, w)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<IfNode>(15, predYLt2, whileThenStmtList, whileElseStmtList),
		std::make_shared<ReadNode>(22, x)
	};

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<WhileNode>(14, predXLt1, whileStmtList)
	};

	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_35() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  read x;
	 * 3  call testProgram2;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 4  print x;
	 * 5  print y;
	 *  }
     */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x),
		std::make_shared<CallNode>(3, "testProgram2")
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(4, x),
		std::make_shared<PrintNode>(5, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_36() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  read x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 3  print x;
	 * 4  print y;
	 * 5  call testProgram1;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(3, x),
		std::make_shared<PrintNode>(4, y),
		std::make_shared<CallNode>(5, "testProgram1")
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_37() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  print x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 3  if (y < 2) then {
	 * 4    call testProgram1;
	 * 5    read y;
	 *    } else {
	 * 6    read w;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<PrintNode>(2, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<CallNode>(4, "testProgram1"),
		std::make_shared<ReadNode>(5, y)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(6, w)
	};

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<IfNode>(3, predYLt2, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_38() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  print x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 3  if (y < 2) then {
	 * 4    read y;
	 *    } else {
	 * 5    call testProgram1;
	 * 6    read w;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<PrintNode>(2, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(4, y)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<CallNode>(5, "testProgram1"),
		std::make_shared<ReadNode>(6, w)
	};

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<IfNode>(3, predYLt2, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_39() {
	/*
	 *  procedure testProgram1 {
	 * 1  if (y < 2) then {
	 * 2    call testProgram2;
	 * 3    read y;
	 *    } else {
	 * 4    read w;
	 *    }
	 *  }
	 * 
	 *  procedure testProgram2 {
	 * 5  read y;
	 * 6  print x;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<CallNode>(2, "testProgram2"),
		std::make_shared<ReadNode>(3, y)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<ReadNode>(4, w)
	};

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<IfNode>(1, predYLt2, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<ReadNode>(5, y),
		std::make_shared<PrintNode>(6, x)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_40() {
	/*
	 *  procedure testProgram1 {
	 * 1  if (y < 2) then {
	 * 2    read y;
	 *    } else {
	 * 3    call testProgram2;
	 * 4    read w;
	 *    }
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 5  read y;
	 * 6  print x;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(2, y)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<CallNode>(3, "testProgram2"),
		std::make_shared<ReadNode>(4, w)
	};

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<IfNode>(1, predYLt2, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<ReadNode>(5, y),
		std::make_shared<PrintNode>(6, x)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_41() {
	/*
	 *  procedure testProgram1 {
	 * 1  print x;
	 *  }
	 *  procedure testProgram2 {
	 * 2  read z;
	 * 3  while (x < 1) {
	 * 4    call testProgram1;
	 * 5    read x;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<PrintNode>(1, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<CallNode>(4, "testProgram1"),
		std::make_shared<ReadNode>(5, x)
	};
	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<ReadNode>(2, z),
		std::make_shared<WhileNode>(3, predXLt1, whileStmtList)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");


	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_42() {
	/*
	 *  procedure testProgram1 {
	 * 1  while (x < 1) {
	 * 2    read x;
	 * 3    call testProgram2;
	 *    }
	 * 4  read z;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 5  print x;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(2, x),
		std::make_shared<CallNode>(3, "testProgram2")
	};
	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<WhileNode>(1, predXLt1, whileStmtList),
		std::make_shared<ReadNode>(4, z)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(5, x)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_43() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  read x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 3  print x;
	 * 4  print y;
	 * 5  call testProgram1;
	 *  }
	 *
	 *  procedure testProgram3 {
	 * 6  x = y + 1;
	 * 7  call testProgram2;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(3, x),
		std::make_shared<PrintNode>(4, y),
		std::make_shared<CallNode>(5, "testProgram1")
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(6, x, yPlus1, "y 1 +"),
		std::make_shared<CallNode>(7, "testProgram2")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_44() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  call testProgram2;
	 * 3  read x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 4  print x;
	 * 5  print y;
	 * 6  call testProgram3;
	 *  }
	 *
	 *  procedure testProgram3 {
	 * 7  x = y + 1;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<CallNode>(2, "testProgram2"),
		std::make_shared<ReadNode>(3, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(4, x),
		std::make_shared<PrintNode>(5, y),
		std::make_shared<CallNode>(6, "testProgram3")
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(7, x, yPlus1, "y 1 +")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_45() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  call testProgram2;
	 * 3  read x;
	 * 4  call testProgram3;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 5  print x;
	 * 6  print y;
	 *  }
	 *
	 *  procedure testProgram3 {
	 * 7  x = y + 1;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<CallNode>(2, "testProgram2"),
		std::make_shared<ReadNode>(3, x),
		std::make_shared<CallNode>(4, "testProgram3")
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(5, x),
		std::make_shared<PrintNode>(6, y),
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(7, x, yPlus1, "y 1 +")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_46() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  read x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 3  print x;
	 * 4  print y;
	 *  }
	 *
	 *  procedure testProgram3 {
	 * 5  call testProgram1;
	 * 6  x = y + 1;
	 * 7  call testProgram2;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x),
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(3, x),
		std::make_shared<PrintNode>(4, y),
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<CallNode>(5, "testProgram1"),
		std::make_shared<AssignNode>(6, x, yPlus1, "y 1 +"),
		std::make_shared<CallNode>(7, "testProgram2")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_47() {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  read x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 3  print x;
	 * 4  call testProgram1;
	 * 5  call testProgram3;
	 * 6  print y;
	 *  }
	 *
	 *  procedure testProgram3 {
	 * 7  x = y + 1;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x),
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(3, x),
		std::make_shared<CallNode>(4, "testProgram1"),
		std::make_shared<CallNode>(5, "testProgram3"),
		std::make_shared<PrintNode>(6, y),
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(7, x, yPlus1, "y 1 +")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_48() {
	/*
	 *   procedure testProgram1 {
	 * 1   read y;
	 * 2   call testProgram3;
	 * 3   read x;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 4   print x;
	 * 5   call testProgram1;
	 * 6   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 7   x = y + 1;
	 *   }
	 * 
	 *   procedure testProgram4 {
	 * 8   if (z < 3) then {
	 * 9     read z;
	 *     } else {
	 * 10    call testProgram2;
	 * 11    print z;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<CallNode>(2, "testProgram3"),
		std::make_shared<ReadNode>(3, x),
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(4, x),
		std::make_shared<CallNode>(5, "testProgram1"),
		std::make_shared<PrintNode>(6, y),
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(7, x, yPlus1, "y 1 +")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(9, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<CallNode>(10, "testProgram2"),
		std::make_shared<PrintNode>(11, z)
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(8, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_49() {
	/*
	 *   procedure testProgram1 {
	 * 1   read y;
	 * 2   call testProgram4;
	 * 3   call testProgram3;
	 * 4   read x;
	 * 5   call testProgram2;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 6   print x;
	 * 7   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 8   x = y + 1;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 9   if (z < 3) then {
	 * 10     read z;
	 *     } else {
	 * 11    print z;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<CallNode>(2, "testProgram4"),
		std::make_shared<CallNode>(3, "testProgram3"),
		std::make_shared<ReadNode>(4, x),
		std::make_shared<CallNode>(5, "testProgram2")
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(6, x),
		std::make_shared<PrintNode>(7, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(8, x, yPlus1, "y 1 +")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(10, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(11, z)
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(9, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_50() {
	/*
	 *   procedure testProgram1 {
	 * 1   read y;
	 * 2   call testProgram3;
	 * 3   read x;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 4   print x;
	 * 5   call testProgram3;
	 * 6   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 7   x = y + 1;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 8   if (z < 3) then {
	 * 9      call testProgram3;
	 * 10     read z;
	 *     } else {
	 * 11    print z;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<CallNode>(2, "testProgram3"),
		std::make_shared<ReadNode>(3, x),
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(4, x),
		std::make_shared<CallNode>(5, "testProgram3"),
		std::make_shared<PrintNode>(6, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(7, x, yPlus1, "y 1 +")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<CallNode>(9, "testProgram3"),
		std::make_shared<ReadNode>(10, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(11, z)
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(8, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_51() {
	/*
	 *   procedure testProgram1 {
	 * 1   call testProgram4;
	 * 2   read y;
	 * 3   call testProgram3;
	 * 4   read x;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 5   print x;
	 * 6   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 7   x = y + 1;
	 * 8   call testProgram2;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 9   if (z < 3) then {
	 * 10     read z;
	 * 11     call testProgram2;
	 *     } else {
	 * 12    print z;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<CallNode>(1, "testProgram4"),
		std::make_shared<ReadNode>(2, y),
		std::make_shared<CallNode>(3, "testProgram3"),
		std::make_shared<ReadNode>(4, x),
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(5, x),
		std::make_shared<PrintNode>(6, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(7, x, yPlus1, "y 1 +"),
		std::make_shared<CallNode>(8, "testProgram2")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(10, z),
		std::make_shared<CallNode>(11, "testProgram2")
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(12, z)
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(9, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_52() {
	/*
	 *   procedure testProgram1 {
	 * 1   read y;
	 * 2   read x;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 3   print x;
	 * 4   call testProgram4;
	 * 5   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 6   x = y + 1;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 7   if (z < 3) then {
	 * 8      call testProgram3;
	 * 9      read z;
	 *     } else {
	 * 10    print z;
	 * 11    call testProgram1;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x),
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(3, x),
		std::make_shared<CallNode>(4, "testProgram4"),
		std::make_shared<PrintNode>(5, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(6, x, yPlus1, "y 1 +"),
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<CallNode>(8, "testProgram3"),
		std::make_shared<ReadNode>(9, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(10, z),
		std::make_shared<CallNode>(11, "testProgram1")
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(7, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_53() {
	/*
	 *   procedure testProgram1 {
	 * 1   read y;
	 * 2   read x;
	 * 3   call testProgram3;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 4   print x;
	 * 5   call testProgram3;
	 * 6   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 7   x = y + 1;
	 * 8   call testProgram4;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 9   if (z < 3) then {
	 * 10     read z;
	 *     } else {
	 * 11    print z;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x),
		std::make_shared<CallNode>(3, "testProgram3")
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(4, x),
		std::make_shared<CallNode>(5, "testProgram3"),
		std::make_shared<PrintNode>(6, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(7, x, yPlus1, "y 1 +"),
		std::make_shared<CallNode>(8, "testProgram4")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(10, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(11, z)
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(9, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_54() {
	/*
	 *   procedure testProgram1 {
	 * 1   read y;
	 * 2   read x;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 3   print x;
	 * 4   call testProgram4;
	 * 5   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 6   x = y + 1;
	 * 7   call testProgram1;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 8   if (z < 3) then {
	 * 9      read z;
	 *     } else {
	 * 10    print z;
	 * 11    call testProgram1;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<ReadNode>(2, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(3, x),
		std::make_shared<CallNode>(4, "testProgram4"),
		std::make_shared<PrintNode>(5, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(6, x, yPlus1, "y 1 +"),
		std::make_shared<CallNode>(7, "testProgram1")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(9, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(10, z),
		std::make_shared<CallNode>(11, "testProgram1")
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(8, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST RelationshipASTs::getAST3_55() {
	/*
	 *   procedure testProgram1 {
	 * 1   read y;
	 * 2   call testProgram4;
	 * 3   read x;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 4   call testProgram3;
	 * 5   print x;
	 * 6   call testProgram1;
	 * 7   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 8   x = y + 1;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 9   if (z < 3) then {
	 * 10      read z;
	 *     } else {
	 * 11    print z;
	 *     }
	 *   }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, y),
		std::make_shared<CallNode>(2, "testProgram4"),
		std::make_shared<ReadNode>(3, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram1");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<CallNode>(4, "testProgram3"),
		std::make_shared<PrintNode>(5, x),
		std::make_shared<CallNode>(6, "testProgram1"),
		std::make_shared<PrintNode>(7, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::vector<std::shared_ptr<StmtNode>> proc3StmtLst{
		std::make_shared<AssignNode>(8, x, yPlus1, "y 1 +")
	};
	std::shared_ptr<ProcedureNode> proc3 = std::make_shared<ProcedureNode>(proc3StmtLst, "testProgram3");

	std::vector<std::shared_ptr<StmtNode>> thenStmtList{
		std::make_shared<ReadNode>(10, z)
	};
	std::vector<std::shared_ptr<StmtNode>> elseStmtList{
		std::make_shared<PrintNode>(11, z)
	};

	std::vector<std::shared_ptr<StmtNode>> proc4StmtLst{
		std::make_shared<IfNode>(9, predZLt3, thenStmtList, elseStmtList)
	};
	std::shared_ptr<ProcedureNode> proc4 = std::make_shared<ProcedureNode>(proc4StmtLst, "testProgram4");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram1", proc1},
		{"testProgram2", proc2},
		{"testProgram3", proc3},
		{"testProgram4", proc4}
	};
	return std::make_shared<ProgramNode>(procMap);
}