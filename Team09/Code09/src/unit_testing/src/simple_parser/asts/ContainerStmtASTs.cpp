#include "ContainerStmtASTs.h"
#include "models/simple_parser/IfNode.h"

AST generateAST(std::vector<std::shared_ptr<StmtNode>> stmts) {
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
	return std::make_shared<ProgramNode>(procList);
}

std::shared_ptr<ConstantNode> c1 = std::make_shared<ConstantNode>("1");
std::shared_ptr<ConstantNode> c2 = std::make_shared<ConstantNode>("2");
std::shared_ptr<ConstantNode> c3 = std::make_shared<ConstantNode>("3");

std::shared_ptr<VariableNode> a = std::make_shared<VariableNode>("a");
std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");

ExprNode xPlusC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1);
ExprNode yPlusC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, c1);
ExprNode yMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, y, c2);

std::shared_ptr<PredicateNode> predC1NeqC1 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(c1, ComparatorOperator::NEQ, c1)
);

std::shared_ptr<PredicateNode> predXLtC1 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(x, ComparatorOperator::LT, c1)
);

std::shared_ptr<PredicateNode> predXEqC2 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(x, ComparatorOperator::EQ, c2)
);

std::shared_ptr<PredicateNode> predYLtC1 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(y, ComparatorOperator::LT, c1)
);

std::shared_ptr<PredicateNode> predYGteC3 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(y, ComparatorOperator::GTE, c3)
);

std::shared_ptr<PredicateNode> predYPlusC1LtX = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(yPlusC1, ComparatorOperator::LT, x)
);

std::vector<std::shared_ptr<StmtNode>> whileStmtListRead{
		std::make_shared<ReadNode>(2, x)
};

// basic predicate

AST ContainerStmtASTs::getAST1_39() {
	/*
	 * procedure testProgram {
	 * 1	while (1 == 1) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predC1EqC1 = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(c1, ComparatorOperator::EQ, c1)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(3, predC1EqC1, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_40() {
	/*
	 * procedure testProgram {
	 * 1	while (x < y) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predXLtY = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(x, ComparatorOperator::LT, y)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtY, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_41() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		read x; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> whileStmtList{
			std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtListRead),
	};

	return generateAST(stmtLst);
}

// basic predicate - single comparator operator

AST ContainerStmtASTs::getAST1_43() {
	/*
	 * procedure testProgram {
	 * 1	while (x <= 1) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predXLtY = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(x, ComparatorOperator::LTE, y)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtY, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_44() {
	/*
	 * procedure testProgram {
	 * 1	while (x > y) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predXLtY = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(x, ComparatorOperator::GT, y)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtY, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_45() {
	/*
	 * procedure testProgram {
	 * 1	while (x >= y) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predXLtY = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(x, ComparatorOperator::GTE, y)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtY, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_46() {
	/*
	 * procedure testProgram {
	 * 1	while (x == y) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predXLtY = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(x, ComparatorOperator::EQ, y)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtY, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_47() {
	/*
	 * procedure testProgram {
	 * 1	while (x != y) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predXLtY = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(x, ComparatorOperator::NEQ, y)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtY, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

// basic predicate - single conditional operator

AST ContainerStmtASTs::getAST1_48() {
	/*
	 * procedure testProgram {
	 * 1	while (!(x < 1)) {
	 * 2		read x; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1,
										std::make_shared<PredicateNode>(ConditionalOperator::NOT, predXLtC1),
										whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_49() {
	/*
	 * procedure testProgram {
	 * 1	while ((x < 1) && (y >= 3)) {
	 * 2		read x; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1,
										std::make_shared<PredicateNode>(predXLtC1, ConditionalOperator::AND, predYGteC3),
										whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_50() {
	/*
	 * procedure testProgram {
	 * 1	while ((x < 1) || (y >= 3)) {
	 * 2		read x; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1,
										std::make_shared<PredicateNode>(predXLtC1, ConditionalOperator::OR, predYGteC3),
										whileStmtListRead)
	};

	return generateAST(stmtLst);
}

// predicate : term-expr interactions

AST ContainerStmtASTs::getAST1_52() {
	/*
	 * procedure testProgram {
	 * 1	while (1 > x + 1) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(c1, ComparatorOperator::GT, xPlusC1)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<WhileNode>(1, pred, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_53() {
	/*
	 * procedure testProgram {
	 * 1	while (x + 1 >= 1) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(xPlusC1, ComparatorOperator::GTE, c1)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<WhileNode>(1, pred, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_54() {
	/*
	 * procedure testProgram {
	 * 1	while (x + 1 < y - 2) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(xPlusC1, ComparatorOperator::LT, yMinusC2)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, pred, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

// predicate : advanced

AST ContainerStmtASTs::getAST1_55() {
	/*
	 * procedure testProgram {
	 * 1	while ((y + 1 < x) && (!(x == 2) || (1 != 1))) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predNot = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
																			 predXEqC2);
	std::shared_ptr<PredicateNode> predOr = std::make_shared<PredicateNode>(predNot,
																			ConditionalOperator::OR,
																			predC1NeqC1);
	std::shared_ptr<PredicateNode> predAnd = std::make_shared<PredicateNode>(predYPlusC1LtX,
																			 ConditionalOperator::AND,
																			 predOr);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predAnd, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_56() {
	/*
	 * procedure testProgram {
	 * 1	while (!((y + 1 < x) && ((x == 2) || (1 != 1)))) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predOr = std::make_shared<PredicateNode>(predXEqC2,
																			ConditionalOperator::OR,
																			predC1NeqC1);
	std::shared_ptr<PredicateNode> predAnd = std::make_shared<PredicateNode>(predYPlusC1LtX,
																			 ConditionalOperator::AND,
																			 predOr);
	std::shared_ptr<PredicateNode> predNot = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
																			 predAnd);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predNot, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_57() {
	/*
	 * procedure testProgram {
	 * 1	while ((!(y + 1 < x)) && (((x == 2) || (1 != 1)))) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predNot = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
																			 predYPlusC1LtX);
	std::shared_ptr<PredicateNode> predOr = std::make_shared<PredicateNode>(predXEqC2,
																			ConditionalOperator::OR,
																			predC1NeqC1);
	std::shared_ptr<PredicateNode> predAnd = std::make_shared<PredicateNode>(predNot,
																			 ConditionalOperator::AND,
																			 predOr);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predAnd, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_58() {
	/*
	 * procedure testProgram {
	 * 1	while ((!((y + 1 < x) && (x == 2))) || (1 != 1)) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predAnd = std::make_shared<PredicateNode>(predYPlusC1LtX,
																			 ConditionalOperator::AND,
																			 predXEqC2);
	std::shared_ptr<PredicateNode> predNot = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
																			 predAnd);
	std::shared_ptr<PredicateNode> predOr = std::make_shared<PredicateNode>(predNot,
																			ConditionalOperator::OR,
																			predC1NeqC1);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predOr, whileStmtListRead)
	};

	return generateAST(stmtLst);
}

// while statement - single statement

AST ContainerStmtASTs::getAST1_60() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		print x; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<PrintNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtLst)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_61() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		a = x + 1;; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<AssignNode>(2, a, xPlusC1, "x 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtLst)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_62() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		if (y < 1) then {
	 * 3        	read y;
	 * 			} else {
	 * 4			print y; } } }
	 */
	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<ReadNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<PrintNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<IfNode>(2, predYLtC1, thenStmtLst, elseStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtLst)
	};

	return generateAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_63() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		while (y < 1) {
	 * 3        	read y; } } }
	 */

	std::vector<std::shared_ptr<StmtNode>> innerWhileStmtLst {
			std::make_shared<ReadNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<WhileNode>(2, predYLtC1, innerWhileStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtLst)
	};

	return generateAST(stmtLst);
}

