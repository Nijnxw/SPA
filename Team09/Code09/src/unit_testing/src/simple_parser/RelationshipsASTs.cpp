#include "RelationshipASTs.h"

// construction helpers
std::shared_ptr<VariableNode> generateVariable(std::string varName) {
	return std::make_shared<VariableNode>(varName);
}

std::shared_ptr<ConstantNode> generateConstant(int conValue) {
	return std::make_shared<ConstantNode>(std::to_string(conValue));
}

std::shared_ptr<ReadNode> generateRead(int stmtNo, std::string varName) {
	return std::make_shared<ReadNode>(stmtNo, generateVariable(varName));
}

std::shared_ptr<PrintNode> generatePrint(int stmtNo, std::string varName) {
	return std::make_shared<PrintNode>(stmtNo, generateVariable(varName));
}

ExprNode generateExpr(std::string varName, BinaryOperator op, int constant) {
	return std::make_shared<BinaryOperatorNode>(
		op, generateVariable(varName), generateConstant(constant));
}

ExprNode generateExpr(std::string var1, BinaryOperator op, std::string var2) {
	return std::make_shared<BinaryOperatorNode>(
		op, generateVariable(var1), generateVariable(var2));
}

ExprNode generateExpr(ExprNode expr1, BinaryOperator op, ExprNode expr2) {
	return std::make_shared<BinaryOperatorNode>(op, expr1, expr2);
}

AST generateAST(std::vector<std::shared_ptr<StmtNode>> stmts, std::string progName) {
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, progName);
	std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
	return std::make_shared<ProgramNode>(procList);
}

AST RelationshipASTs::getAST3_5() {
	/*
	 * procedure testProgram {
	 * 1	read x;
	 * 2	print x;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		generateRead(1, "x"),
		generatePrint(2, "x")
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
		generateRead(1, "x"),
		std::make_shared<AssignNode>(
			2, generateVariable("x"), generateExpr("x", BinaryOperator::PLUS, 1), "x 1 +")
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
		generatePrint(1, "x"),
		std::make_shared<AssignNode>(
			2, generateVariable("x"), generateExpr("x", BinaryOperator::PLUS, 1), "x 1 +")
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
		generateRead(1, "x"),
		generatePrint(2, "x"),
		std::make_shared<AssignNode>(
			3, generateVariable("x"), generateExpr("x", BinaryOperator::PLUS, 1), "x 1 +")
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
		generateRead(1, "x"),
		generateRead(2, "y"),
		generateRead(3, "z"),
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
		std::make_shared<AssignNode>(
			2, generateVariable("x"), generateExpr("x", BinaryOperator::PLUS, "y"), "x 1 +"),
		generatePrint(2, "x"),
		generateRead(3, "x"),
	};
	return generateAST(stmtList, "testProgram");
}