#include "ContainerStmtASTs.h"

ExprNode ContainerStmtASTs::xPlusC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1);
ExprNode ContainerStmtASTs::yPlusC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, c1);
ExprNode ContainerStmtASTs::yMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, y, c2);

std::shared_ptr<PredicateNode> ContainerStmtASTs::predC1NeqC1 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(c1, ComparatorOperator::NEQ, c1)
);

std::shared_ptr<PredicateNode> ContainerStmtASTs::predXLtC1 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(x, ComparatorOperator::LT, c1)
);

std::shared_ptr<PredicateNode> ContainerStmtASTs::predXEqC2 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(x, ComparatorOperator::EQ, c2)
);

std::shared_ptr<PredicateNode> ContainerStmtASTs::predYLtC1 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(y, ComparatorOperator::LT, c1)
);

std::shared_ptr<PredicateNode> ContainerStmtASTs::predYGteC3 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(y, ComparatorOperator::GTE, c3)
);

std::shared_ptr<PredicateNode> ContainerStmtASTs::predYPlusC1LtX = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(yPlusC1, ComparatorOperator::LT, x)
);

std::shared_ptr<PredicateNode> ContainerStmtASTs::predZLtC1 = std::make_shared<PredicateNode>(
		std::make_shared<RelExprNode>(z, ComparatorOperator::LT, c1)
);

std::vector<std::shared_ptr<StmtNode>> ContainerStmtASTs::whileStmtListRead {
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
			std::make_shared<WhileNode>(1, predC1EqC1, whileStmtListRead)
	};

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_41() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		read x; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtListRead),
	};

	return generateBasicAST(stmtLst);
}

// basic predicate - single comparator operator

AST ContainerStmtASTs::getAST1_42() {
	return getAST1_40();
}

AST ContainerStmtASTs::getAST1_43() {
	/*
	 * procedure testProgram {
	 * 1	while (x <= y) {
	 * 2		read x; } }
	 */
	std::shared_ptr<PredicateNode> predXLtY = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(x, ComparatorOperator::LTE, y)
	);

	std::vector<std::shared_ptr<StmtNode>> stmtLst{
			std::make_shared<WhileNode>(1, predXLtY, whileStmtListRead)
	};

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
}

// predicate : term-expr interactions

AST ContainerStmtASTs::getAST1_51() {
	return getAST1_39();
}

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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
}

// while statement - single statement in container

AST ContainerStmtASTs::getAST1_59() {
	return getAST1_41();
}

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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
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

	return generateBasicAST(stmtLst);
}

// while statement - all statement types in container

AST ContainerStmtASTs::getAST1_64() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		read x;
	 * 3		print x;
	 * 4		a = x + 1;
	 * 5		if (y < 1) then {
	 * 6			read y;
	 * 			} else {
	 * 7			print y; }
	 * 8		while (y < 1) {
	 * 9			read y; }
	 * 		}
	 * 	}
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<ReadNode>(6, y)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<PrintNode>(7, y)
	};

	std::vector<std::shared_ptr<StmtNode>> innerWhileStmtLst {
			std::make_shared<ReadNode>(9, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<ReadNode>(2, x),
			std::make_shared<PrintNode>(3, x),
			std::make_shared<AssignNode>(4, a, xPlusC1, "x 1 +"),
			std::make_shared<IfNode>(5, predYLtC1, thenStmtLst, elseStmtLst),
			std::make_shared<WhileNode>(8, predYLtC1, innerWhileStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtLst)
	};

	return generateBasicAST(stmtLst);
}

// If statement - single statement in container

AST ContainerStmtASTs::getAST1_65() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		read x;
	 * 		} else {
	 * 3		read y; } }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<ReadNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_66() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		print x;
	 * 		} else {
	 * 3		print y; } }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<PrintNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<PrintNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_67() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		a = x + 1;
	 * 		} else {
	 * 3		a = y + 1; } }
	 */

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<AssignNode>(2, a, xPlusC1, "x 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<AssignNode>(3, a, yPlusC1, "y 1 +")
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_68() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		if (y < 1) then {
	 * 3			read y;
	 * 			} else {
	 * 4			print y; }
	 * 		} else {
	 * 5		print x; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> innerThenStmtLst {
			std::make_shared<ReadNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> innerElseStmtLst {
			std::make_shared<PrintNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<IfNode>(2, predYLtC1, innerThenStmtLst, innerElseStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<PrintNode>(5, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_69() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		read x;
	 * 		} else {
	 * 3		if (y < 1) then {
	 * 4			read y;
	 * 			} else {
	 * 5			print y; } } }
	 */
	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> innerThenStmtLst {
			std::make_shared<ReadNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> innerElseStmtLst {
			std::make_shared<PrintNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<IfNode>(3, predYLtC1, innerThenStmtLst, innerElseStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_70() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		while (y < 1) {
	 * 3			read y; }
	 * 		} else {
	 * 4		print y; } }
	 */
	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<ReadNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<WhileNode>(2, predYLtC1, whileStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<PrintNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_71() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		read x;
	 * 		} else {
	 * 3		while (y < 1) {
	 * 4			read y; } } }
	 */
	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<ReadNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<WhileNode>(3, predYLtC1, whileStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

// if statement - all statement types in container

AST ContainerStmtASTs::getAST1_72() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		read x;
	 * 3		print x;
	 * 4		a = x + 1;
	 * 5		if (y < 1) then {
	 * 6			read y;
	 * 			} else {
	 * 7			print y; }
	 * 8		while (z < 1) {
	 * 9			read z; }
	 * 		} else {
	 * 10		print x; } }
	 */

	std::vector<std::shared_ptr<StmtNode>> innerThenStmtLst {
			std::make_shared<ReadNode>(6, y)
	};

	std::vector<std::shared_ptr<StmtNode>> innerElseStmtLst {
			std::make_shared<PrintNode>(7, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<ReadNode>(9, z)
	};

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<ReadNode>(2, x),
			std::make_shared<PrintNode>(3, x),
			std::make_shared<AssignNode>(4, a, xPlusC1, "x 1 +"),
			std::make_shared<IfNode>(5, predYLtC1, innerThenStmtLst, innerElseStmtLst),
			std::make_shared<WhileNode>(8, predZLtC1, whileStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<PrintNode>(10, x)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_73() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		read x;
	 * 		} else {
	 * 3		read x;
	 * 4		print x;
	 * 5		a = x + 1;
	 * 6		if (y < 1) then {
	 * 7			read y;
	 * 			} else {
	 * 8			print y; }
	 * 9		while (z < 1) {
	 * 10			read z; } } }
	 */
	std::vector<std::shared_ptr<StmtNode>> thenStmtLst {
			std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> innerThenStmtLst {
			std::make_shared<ReadNode>(7, y)
	};

	std::vector<std::shared_ptr<StmtNode>> innerElseStmtLst {
			std::make_shared<PrintNode>(8, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst {
			std::make_shared<ReadNode>(10, z)
	};


	std::vector<std::shared_ptr<StmtNode>> elseStmtLst {
			std::make_shared<ReadNode>(3, x),
			std::make_shared<PrintNode>(4, x),
			std::make_shared<AssignNode>(5, a, xPlusC1, "x 1 +"),
			std::make_shared<IfNode>(6, predYLtC1, innerThenStmtLst, innerElseStmtLst),
			std::make_shared<WhileNode>(9, predZLtC1, whileStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> stmtLst {
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};

	return generateBasicAST(stmtLst);
}

AST ContainerStmtASTs::getAST1_74() {
	/*
	 * procedure testProgram {
	 * 1    read z;
	 * }
	 *
	 * procedure testProgram2 {
	 * 2	if (x < 1) then {
	 * 3		read x;
	 * 		} else {
	 * 4		if (y < 1) then {
	 * 5			read y;
	 * 			} else {
	 * 6			print y; } } }
	 */
	
	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<ReadNode>(1, z)
	};
	
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst{
			std::make_shared<ReadNode>(3, x)
	};

	std::vector<std::shared_ptr<StmtNode>> innerThenStmtLst{
			std::make_shared<ReadNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> innerElseStmtLst{
			std::make_shared<PrintNode>(6, y)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst{
			std::make_shared<IfNode>(4, predYLtC1, innerThenStmtLst, innerElseStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
			std::make_shared<IfNode>(2, predXLtC1, thenStmtLst, elseStmtLst)
	};

	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ 
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_75() {
	/*
	 * procedure testProgram {
	 * 1	print z;
	 *  }
	 * 
	 * procedure testProgram2 {
	 * 2	while (!((y + 1 < x) && ((x == 2) || (1 != 1)))) {
	 * 3		read x; } }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<PrintNode>(1, z)
	};

	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::shared_ptr<PredicateNode> predOr = std::make_shared<PredicateNode>(predXEqC2,
		ConditionalOperator::OR,
		predC1NeqC1);
	std::shared_ptr<PredicateNode> predAnd = std::make_shared<PredicateNode>(predYPlusC1LtX,
		ConditionalOperator::AND,
		predOr);
	std::shared_ptr<PredicateNode> predNot = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
		predAnd);

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst{
		std::make_shared<ReadNode>(3, x)
	};

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
			std::make_shared<WhileNode>(2, predNot, whileStmtLst)
	};

	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_76() {
	/*
	 * procedure testProgram {
	 * 1	a = 1 + (x * (y - 2) / (z % 3));
	 * }
	 * 
	 * procedure testProgram2 {
	 * 2	print b;
	 * }
	 */
	
	auto zModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, z, c3);
	auto yMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, y, c2);
	auto xTimesYMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, yMinusC2);
	auto xTimesYMinusC2DivZModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, xTimesYMinusC2, zModC3);

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xTimesYMinusC2DivZModC3),
										 "1 x y 2 - * z 3 % / +"),
	};

	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(2, b)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_77() {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		while (y < 1) {
	 * 3        	read y; } } }
	 * 
	 * procedure testProgram2 {
	 * 4	read x; }
	 */

	std::vector<std::shared_ptr<StmtNode>> innerWhileStmtLst{
			std::make_shared<ReadNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst{
			std::make_shared<WhileNode>(2, predYLtC1, innerWhileStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
			std::make_shared<WhileNode>(1, predXLtC1, whileStmtLst)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<ReadNode>(4, x)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_78() {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		read x;
	 * 		} else {
	 * 3		if (y < 1) then {
	 * 4			read y;
	 * 			} else {
	 * 5			print y; } } }
	 * 
	 * procedure testProgram2 {
	 * 6	a = (1 + x * 3) % (y);
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> thenStmtLst{
			std::make_shared<ReadNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> innerThenStmtLst{
			std::make_shared<ReadNode>(4, y)
	};

	std::vector<std::shared_ptr<StmtNode>> innerElseStmtLst{
			std::make_shared<PrintNode>(5, y)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst{
			std::make_shared<IfNode>(3, predYLtC1, innerThenStmtLst, innerElseStmtLst)
	};

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
			std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	auto xTimesC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, c3);
	auto c1PlusXTimesC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xTimesC3);

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
			std::make_shared<AssignNode>(6, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, c1PlusXTimesC3, y),
										 "1 x 3 * + y %")
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_79() {
	/*
	 * procedure testProgram {
	 * 1	call testProgram2;
	 * }
	 *
	 * procedure testProgram2 {
	 * 2	print x;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<CallNode>(1, "testProgram2")
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(2, x)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_80() {
	/*
	 * procedure testProgram {
	 * 1	print x;
	 * }
	 *
	 * procedure testProgram2 {
	 * 2	call testProgram;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<PrintNode>(1, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<CallNode>(2, "testProgram")
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};

	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_81() {
	/*
	 *  procedure testProgram {
	 * 1  if (x < 1) then {
	 * 2    print x;
	 *    } else {
	 * 3    call testProgram2;
	 *    }
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 4  print y;
	 *  }
	 */
	std::vector<std::shared_ptr<StmtNode>> thenStmtLst{
		std::make_shared<PrintNode>(2, x)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst{
		std::make_shared<CallNode>(3, "testProgram2")
	};
	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<IfNode>(1, predXLtC1, thenStmtLst, elseStmtLst)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(4, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_82() {
	/*
	 *  procedure testProgram {
	 * 1  print x;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 2  if (x < 1) then {
	 * 3    print y;
	 *    } else {
	 * 4    call testProgram;
	 *    }
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<PrintNode>(1, x)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> thenStmtLst{
		std::make_shared<PrintNode>(3, y)
	};

	std::vector<std::shared_ptr<StmtNode>> elseStmtLst{
		std::make_shared<CallNode>(4, "testProgram")
	};
	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<IfNode>(2, predXLtC1, thenStmtLst, elseStmtLst)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};
	return std::make_shared<ProgramNode>(procMap);
}

AST ContainerStmtASTs::getAST1_83() {
	/*
	 *  procedure testProgram {	
	 * 1  while (x < 1) {
	 * 2    call testProgram2;
	 *    }
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 3  print y;
	 *  }
	 */

	std::vector<std::shared_ptr<StmtNode>> whileStmtLst{
		std::make_shared<CallNode>(2, "testProgram2")
	};
	std::vector<std::shared_ptr<StmtNode>> proc1StmtLst{
		std::make_shared<WhileNode>(1, predXLtC1, whileStmtLst)
	};
	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(proc1StmtLst, "testProgram");

	std::vector<std::shared_ptr<StmtNode>> proc2StmtLst{
		std::make_shared<PrintNode>(3, y)
	};
	std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(proc2StmtLst, "testProgram2");

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{
		{"testProgram", proc1},
		{"testProgram2", proc2},
	};
	return std::make_shared<ProgramNode>(procMap);
}

int ContainerStmtASTs::getStmtCount1_39() { return 2; }

int ContainerStmtASTs::getStmtCount1_40() { return 2; }

int ContainerStmtASTs::getStmtCount1_41() { return 2; }

int ContainerStmtASTs::getStmtCount1_42() { return 2; }

int ContainerStmtASTs::getStmtCount1_43() { return 2; }

int ContainerStmtASTs::getStmtCount1_44() { return 2; }

int ContainerStmtASTs::getStmtCount1_45() { return 2; }

int ContainerStmtASTs::getStmtCount1_46() { return 2; }

int ContainerStmtASTs::getStmtCount1_47() { return 2; }

int ContainerStmtASTs::getStmtCount1_48() { return 2; }

int ContainerStmtASTs::getStmtCount1_49() { return 2; }

int ContainerStmtASTs::getStmtCount1_50() { return 2; }

int ContainerStmtASTs::getStmtCount1_51() { return 2; }

int ContainerStmtASTs::getStmtCount1_52() { return 2; }

int ContainerStmtASTs::getStmtCount1_53() { return 2; }

int ContainerStmtASTs::getStmtCount1_54() { return 2; }

int ContainerStmtASTs::getStmtCount1_55() { return 2; }

int ContainerStmtASTs::getStmtCount1_56() { return 2; }

int ContainerStmtASTs::getStmtCount1_57() { return 2; }

int ContainerStmtASTs::getStmtCount1_58() { return 2; }

int ContainerStmtASTs::getStmtCount1_59() { return 2; }

int ContainerStmtASTs::getStmtCount1_60() { return 2; }

int ContainerStmtASTs::getStmtCount1_61() { return 2; }

int ContainerStmtASTs::getStmtCount1_62() { return 4; }

int ContainerStmtASTs::getStmtCount1_63() { return 3; }

int ContainerStmtASTs::getStmtCount1_64() { return 8; }

int ContainerStmtASTs::getStmtCount1_65() { return 3; }

int ContainerStmtASTs::getStmtCount1_66() { return 3; }

int ContainerStmtASTs::getStmtCount1_67() { return 3; }

int ContainerStmtASTs::getStmtCount1_68() { return 5; }

int ContainerStmtASTs::getStmtCount1_69() { return 5; }

int ContainerStmtASTs::getStmtCount1_70() { return 4; }

int ContainerStmtASTs::getStmtCount1_71() { return 4; }

int ContainerStmtASTs::getStmtCount1_72() { return 10; }

int ContainerStmtASTs::getStmtCount1_73() { return 10; }

int ContainerStmtASTs::getStmtCount1_74() { return 6; }

int ContainerStmtASTs::getStmtCount1_75() { return 3; }

int ContainerStmtASTs::getStmtCount1_76() { return 2; }

int ContainerStmtASTs::getStmtCount1_77() { return 4; }

int ContainerStmtASTs::getStmtCount1_78() { return 6; }

int ContainerStmtASTs::getStmtCount1_79() { return 2; }

int ContainerStmtASTs::getStmtCount1_80() { return 2; }

int ContainerStmtASTs::getStmtCount1_81() { return 4; }

int ContainerStmtASTs::getStmtCount1_82() { return 4; }

int ContainerStmtASTs::getStmtCount1_83() { return 3; }