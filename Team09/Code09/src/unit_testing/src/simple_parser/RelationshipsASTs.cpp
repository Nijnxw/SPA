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

std::shared_ptr<PredicateNode> RelationshipASTs::predXLt1 = std::make_shared<PredicateNode>(
	std::make_shared<RelExprNode>(x, ComparatorOperator::LT, one)
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
	      }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
		std::make_shared<ReadNode>(4, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<PrintNode>(1, x),
		std::make_shared<ReadNode>(2, x),
		std::make_shared<WhileNode>(3, predXLt1, whileStmtList)
	};
	return generateAST(stmtList, "testProgram");
}