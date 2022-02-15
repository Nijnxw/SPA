#include "NonContainerStmtASTs.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/AssignNode.h"

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

AST NonContainerStmtASTs::getAST1_1() {
	/*
	 * procedure testProgram {
	 * 1	read x;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<ReadNode>(1, x),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_2() {
	/*
	 * procedure testProgram {
	 * 1	print x;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<PrintNode>(1, x),
	};
	return generateAST(stmtList);
}

// ASSIGNMENT ASTs

AST NonContainerStmtASTs::getAST1_3() {
	/*
	 * procedure testProgram {
	 * 1	a = 1;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a, c1, "1"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_4() {
	/*
	 * procedure testProgram {
	 * 1	a = x;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a, x, "x"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_5() {
	/*
	 * procedure testProgram {
	 * 1	a = x + y;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, y),
										 "x y +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_6() {
	/*
	 * procedure testProgram {
	 * 1	a = 1 + 2;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, c2),
										 "1 2 +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_7() {
	/*
	 * procedure testProgram {
	 * 1	a = x + 1;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1),
										 "x 1 +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_8() {
	/*
	 * procedure testProgram {
	 * 1	a = 1 + x + y + 2 + z;
	 * }
	 */
	auto c1PlusX = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, x);
	auto c1PlusXPlusY = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1PlusX, y);
	auto c1PlusXPlusYPlusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1PlusXPlusY, c2);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1PlusXPlusYPlusC2, z),
										 "1 x + y + 2 + z +"),
	};
	return generateAST(stmtList);
}

// Single operator parsing

AST NonContainerStmtASTs::getAST1_10() {
	/*
	 * procedure testProgram {
	 * 1	a = x - 1;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, x, c1),
										 "x 1 -"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_11() {
	/*
	 * procedure testProgram {
	 * 1	a = x * 1;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, c1),
										 "x 1 *"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_12() {
	/*
	 * procedure testProgram {
	 * 1	a = x / 1;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, x, c1),
										 "x 1 /"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_13() {
	/*
	 * procedure testProgram {
	 * 1	a = x % 1;
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, x, c1),
										 "x 1 %"),
	};
	return generateAST(stmtList);
}

// Operator precedence

AST NonContainerStmtASTs::getAST1_14() {
	/*
	 * procedure testProgram {
	 * 1	a = x + 1 - y + 3;
	 * }
	 */
	auto xPlusC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1);
	auto xPlusC1MinusY = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, xPlusC1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, xPlusC1MinusY, c3),
										 " x 1 + y - 3+"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_15() {
	/*
	 * procedure testProgram {
	 * 1	a = x * 1 / y % 3;
	 * }
	 */
	auto xTimesC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, c1);
	auto xTimesC1DivideY = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, xTimesC1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, xTimesC1DivideY, c3),
										 "x 1 * y / 3 %"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_16() {
	/*
	 * procedure testProgram {
	 * 1	a = x + 1 * y;
	 * }
	 */
	auto c1TimesY = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1TimesY, x),
										 "x 1 y * +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_17() {
	/*
	 * procedure testProgram {
	 * 1	a = x + 1 / y;
	 * }
	 */
	auto c1DivY = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1DivY, x),
										 "x 1 y / +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_18() {
	/*
	 * procedure testProgram {
	 * 1	a = x + 1 % y;
	 * }
	 */
	auto c1ModY = std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1ModY, x),
										 "x 1 y % +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_19() {
	/*
	 * procedure testProgram {
	 * 1	a = x - 1 * y;
	 * }
	 */
	auto c1TimesY = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, c1TimesY, x),
										 "x 1 y / -"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_20() {
	/*
	 * procedure testProgram {
	 * 1	a = x - 1 / y;
	 * }
	 */
	auto c1DivY = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, c1DivY, x),
										 "x 1 y / -"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_21() {
	/*
	 * procedure testProgram {
	 * 1	a = x - 1 % y;
	 * }
	 */
	auto c1ModY = std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, c1ModY, x),
										 "x 1 y % -"),
	};
	return generateAST(stmtList);
}

// Parentheses interactions

AST NonContainerStmtASTs::getAST1_22() {
	/*
	 * procedure testProgram {
	 * 1	a = (1);
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a, c1, "1"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_23() {
	/*
	 * procedure testProgram {
	 * 1	a = (x);
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a, x, "x"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_24() {
	/*
	 * procedure testProgram {
	 * 1	a = (x + 1);
	 * }
	 */
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1),
										 "x 1 +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_25() {
	/*
	 * procedure testProgram {
	 * 1	a = (x + 1) + y;
	 * }
	 */
	auto xPlusC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, xPlusC1, y),
										 "x 1 + y +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_26() {
	/*
	 * procedure testProgram {
	 * 1	a = x + (1 + y);
	 * }
	 */
	auto c1PlusY = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1PlusY),
										 "x 1 y + +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_27() {
	/*
	 * procedure testProgram {
	 * 1	a = x + (1 * y);
	 * }
	 */
	auto c1TimesY = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, c1TimesY),
										 "x 1 y * +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_28() {
	/*
	 * procedure testProgram {
	 * 1	a = x * (1 + y);
	 * }
	 */
	auto c1PlusY = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, c1PlusY),
										 "x 1 y + *"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_29() {
	/*
	 * procedure testProgram {
	 * 1	a = (x * 1) * y;
	 * }
	 */
	auto xTimesC1 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, c1);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, xTimesC1, y),
										 "x 1 * y *"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_30() {
	/*
	 * procedure testProgram {
	 * 1	a = x * (1 * y);
	 * }
	 */
	auto c1TimesY = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, c1, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, c1TimesY),
										 "x 1 y * *"),
	};
	return generateAST(stmtList);
}

// operator precedences - Intermediate

AST NonContainerStmtASTs::getAST1_31() {
	/*
	 * procedure testProgram {
	 * 1	a = (1 + (x - y)) / 3;
	 * }
	 */
	auto xMinusY = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, x, y);
	auto c1PlusXMinusY = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xMinusY);

	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, c1PlusXMinusY, c3),
										 "1 x y - + 3 /"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_32() {
	/*
	 * procedure testProgram {
	 * 1	a = (1 + x) - (y / 3);
	 * }
	 */
	auto c1PlusX = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, x);
	auto yDivC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, y, c3);

	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, c1PlusX, yDivC3),
										 "1 x + y 3 / -"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_33() {
	/*
	 * procedure testProgram {
	 * 1	a = (1 + (x) - 3 % y);
	 * }
	 */
	auto c1PlusX = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, x);
	auto c3ModY = std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, c3, y);

	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, c1PlusX, c3ModY),
										 "1 x + 3 y % -"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_34() {
	/*
	 * procedure testProgram {
	 * 1	a = (1 + x * 3) % (y);
	 * }
	 */
	auto xTimesC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, c3);
	auto c1PlusXTimesC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xTimesC3);

	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, c1PlusXTimesC3, y),
										 "1 x 3 * + y %"),
	};
	return generateAST(stmtList);
}

// Operator Precedence - Advanced

AST NonContainerStmtASTs::getAST1_35() {
	/*
	 * procedure testProgram {
	 * 1	a = 1 + (x * (y - 2)) / (z % 3);
	 * }
	 */
	auto yMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, y, c2);
	auto xTimesYMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, yMinusC2);
	auto zModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, z, c3);
	auto xTimesYMinusC2DivZModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, xTimesYMinusC2, zModC3);

	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xTimesYMinusC2DivZModC3),
										 "1 x y 2 - * z 3 % / +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_36() {
	/*
	 * procedure testProgram {
	 * 1	a = (1 + (x * y)) - (2 / z % 3);
	 * }
	 */
	auto xTimesY = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, y);
	auto c1PlusXTimesY = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xTimesY);
	auto c2DivZ = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, c2, z);
	auto c2DivZModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, c2DivZ, c3);

	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, c1PlusXTimesY, c2DivZModC3),
										 "1 x y * + 2 z / 3 % -"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_37() {
	/*
	 * procedure testProgram {
	 * 1	a = (1 + (x * (y - 2 / z % 3)));
	 * }
	 */
	auto c2DivZ = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, c2, z);
	auto c2DivZModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, c2DivZ, c3);

	auto yMinusC2DivZModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, y, c2DivZModC3);
	auto xTimesYMinusC2DivZModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, yMinusC2DivZModC3);

	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xTimesYMinusC2DivZModC3),
										 "1 x y 2 z / 3 % - * +"),
	};
	return generateAST(stmtList);
}

AST NonContainerStmtASTs::getAST1_38() {
	/*
	 * procedure testProgram {
	 * 1	a = 1 + (x * (y - 2) / (z % 3));
	 * }
	 */
	auto zModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MODULO, z, c3);
	auto yMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, y, c2);
	auto xTimesYMinusC2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, yMinusC2);
	auto xTimesYMinusC2DivZModC3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, xTimesYMinusC2, zModC3);


	std::vector<std::shared_ptr<StmtNode>> stmtList{
			std::make_shared<AssignNode>(1, a,
										 std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, c1, xTimesYMinusC2DivZModC3),
										 "1 x y 2 - * z 3 % / +"),
	};
	return generateAST(stmtList);
}
