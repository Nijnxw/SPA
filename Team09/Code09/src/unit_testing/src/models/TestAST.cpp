#include "catch.hpp"
#include "../src/models/simple_parser/Operator.h"
#include "../src/models/simple_parser/AssignNode.h"
#include "../src/models/simple_parser/ExprNodes.h"
#include "../src/models/simple_parser/IoNodes.h"
#include "../src/models/simple_parser/ProcedureNode.h"
#include "../src/models/simple_parser/AST.h"
#include "../src/util/RPN.h"

#include <memory>

TEST_CASE("Test Equality Comparisons") {
	VariableNode var1("abcd");
	VariableNode var2("abcd");
	VariableNode var3("abcde");
	REQUIRE(var1 == var2);
	REQUIRE(var1 != var3);

	ConstantNode con1("12345");
	ConstantNode con2("12345");
	ConstantNode con3("123456");
	REQUIRE(con1 == con2);
	REQUIRE(con1 != con3);

	std::shared_ptr<VariableNode> var4 = std::make_shared<VariableNode>("x");
	std::shared_ptr<ConstantNode> con4 = std::make_shared<ConstantNode>("123");
	OperatorNode op1(BinaryOperator::PLUS, var4, con4);
	OperatorNode op2(BinaryOperator::MINUS, var4, con4);
	OperatorNode op3(BinaryOperator::PLUS, var4, con4);
	REQUIRE(op1 == op3);
	REQUIRE(op1 != op2);

	REQUIRE(var1 != con1);
	REQUIRE(op1 != con1);
	REQUIRE(var1 != op1);

	std::shared_ptr<VariableNode> var5 = std::make_shared<VariableNode>("y");

	std::shared_ptr<PrintNode> print1 = std::make_shared<PrintNode>(45, var4);
	std::shared_ptr<PrintNode> print2 = std::make_shared<PrintNode>(45, var4);
	std::shared_ptr<PrintNode> print3 = std::make_shared<PrintNode>(46, var4);
	std::shared_ptr<PrintNode> print4 = std::make_shared<PrintNode>(45, var5);
	REQUIRE(*print1 == *print2);
	REQUIRE(*print1 != *print3);
	REQUIRE(*print2 != *print4);

	std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(45, var4);
	std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(45, var4);
	std::shared_ptr<ReadNode> read3 = std::make_shared<ReadNode>(46, var4);
	std::shared_ptr<ReadNode> read4 = std::make_shared<ReadNode>(45, var5);
	REQUIRE(*read1 == *read2);
	REQUIRE(*read1 != *read3);
	REQUIRE(*read2 != *read4);

	std::vector<std::shared_ptr<StmtNode>> stmtLst1;
	stmtLst1.push_back(print1);
	stmtLst1.push_back(read1);

	std::vector<std::shared_ptr<StmtNode>> stmtLst2;
	stmtLst2.push_back(print2);
	stmtLst2.push_back(read2);

	std::vector<std::shared_ptr<StmtNode>> stmtLst3;
	stmtLst3.push_back(print3);
	stmtLst3.push_back(read4);

	std::shared_ptr<ProcedureNode> p1 = std::make_shared<ProcedureNode>(stmtLst1, "test");
	std::shared_ptr<ProcedureNode> p2 = std::make_shared<ProcedureNode>(stmtLst2, "test");
	std::shared_ptr<ProcedureNode> p3 = std::make_shared<ProcedureNode>(stmtLst1, "test123");
	std::shared_ptr<ProcedureNode> p4 = std::make_shared<ProcedureNode>(stmtLst3, "test");

	REQUIRE(*p1 == *p2);
	REQUIRE(*p1 != *p3);
	REQUIRE(*p1 != *p4);

	std::vector<std::shared_ptr<ProcedureNode>> procList1;
	procList1.push_back(p1);

	std::vector<std::shared_ptr<ProcedureNode>> procList2;
	procList2.push_back(p2);

	std::vector<std::shared_ptr<ProcedureNode>> procList3;
	procList3.push_back(p3);

	ProgramNode r1(procList1);
	ProgramNode r2(procList2);
	ProgramNode r3(procList3);

	REQUIRE(r1 == r2);
	REQUIRE(r1 != r3);
}

TEST_CASE("Test Expr nodes") {
	VariableNode var("abcd");
	REQUIRE(var.isVariableNode() == true);
	REQUIRE(var.isConstantNode() == false);
	REQUIRE(var.isProcedureNode() == false);
	REQUIRE(var.getName() == "abcd");

	ConstantNode con("12345");
	REQUIRE(con.isConstantNode() == true);
	REQUIRE(con.isProgramNode() == false);
	REQUIRE(con.isPrintNode() == false);
	REQUIRE(con.getValue() == "12345");

	ExprNode var2 = std::make_shared<VariableNode>("x");
	ExprNode con2 = std::make_shared<ConstantNode>("123");
	OperatorNode op(BinaryOperator::LT, var2, con2);
	REQUIRE(op.isBinOpNode() == true);
	REQUIRE(op.isIfNode() == false);
	REQUIRE(op.isWhileNode() == false);
	REQUIRE(op.getOperator() == BinaryOperator::LT);
	REQUIRE(op.getLhs() == var2);
	REQUIRE(op.getRhs() == con2);
}

TEST_CASE("Test Assign statement nodes") {
	SECTION("Constant Assignment") {
		// testing = 123
		std::shared_ptr<VariableNode> var = std::make_shared<VariableNode>("testing");
		ExprNode con = std::make_shared<ConstantNode>("123");

		REQUIRE_NOTHROW(AssignNode(1, var, con, "123"));
		AssignNode ass = AssignNode(1, var, con, "123");

		REQUIRE(ass.getAssignedVar() == var);
		REQUIRE(ass.getExpression() == con);
		REQUIRE(ass.getPostfix() == "123");

		REQUIRE(ass.isAssignNode() == true);
		REQUIRE(ass.getAssignedVar()->isVariableNode() == true);
		REQUIRE(std::visit(
			[](const auto& expr) { return expr->isConstantNode(); },
			ass.getExpression()));
	}

	SECTION("Variable Assignment") {
		// testing = test
		std::shared_ptr<VariableNode> var1 = std::make_shared<VariableNode>("testing");
		ExprNode var2 = std::make_shared<VariableNode>("test");

		REQUIRE_NOTHROW(AssignNode(1, var1, var2, "test"));
		AssignNode ass = AssignNode(1, var1, var2, "test");

		REQUIRE(ass.getAssignedVar() == var1);
		REQUIRE(ass.getExpression() == var2);
		REQUIRE(ass.getPostfix() == "test");

		REQUIRE(ass.isAssignNode() == true);
		REQUIRE(ass.getAssignedVar()->isVariableNode() == true);
		REQUIRE(std::visit(
			[](const auto& expr) { return expr->isVariableNode(); },
			ass.getExpression()) == true);
	}

	SECTION("Expression Assignment") {
		// build somewhat complicated expression
		// testing = a * b + 123 / 1
		std::shared_ptr<VariableNode> var = std::make_shared<VariableNode>("testing");

		std::string expr = "a * b + 123 / 1";
		std::string postfix = RPN::convertToRpn(expr);

		ExprNode a = std::make_shared<VariableNode>("a");
		ExprNode b = std::make_shared<VariableNode>("b");
		ExprNode left_side = std::make_shared<OperatorNode>(BinaryOperator::TIMES, a, b);

		ExprNode con123 = std::make_shared<ConstantNode>("123");
		ExprNode con1 = std::make_shared<ConstantNode>("1");
		ExprNode right_side = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, con123, con1);

		ExprNode overall = std::make_shared<OperatorNode>(BinaryOperator::PLUS, left_side, right_side);

		REQUIRE_NOTHROW(AssignNode(1, var, overall, postfix));

		AssignNode ass1 = AssignNode(1, var, overall, postfix);
		AssignNode ass2 = AssignNode(1, var, overall, postfix);
		AssignNode ass3 = AssignNode(2, var, overall, postfix);
		AssignNode ass4 = AssignNode(1, var, left_side, postfix);

		REQUIRE(ass1 == ass2);
		REQUIRE(ass1 != ass3);
		REQUIRE(ass1 != ass4);

		REQUIRE(ass1.isAssignNode() == true);
		REQUIRE(ass1.getAssignedVar()->isVariableNode() == true);
		REQUIRE(std::visit(
			[](const auto& expr) { return expr->isBinOpNode(); },
			ass1.getExpression()) == true);
	}
}

TEST_CASE("Test IO statement nodes") {
	std::shared_ptr<VariableNode> var1 = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> var2 = std::make_shared<VariableNode>("y");

	PrintNode print(45, var1);
	REQUIRE(print.isPrintNode() == true);
	REQUIRE(print.getVariable()->isVariableNode() == true);

	ReadNode read(10, var2);
	REQUIRE(read.isReadNode() == true);
	REQUIRE(read.getVariable()->isVariableNode() == true);
}

TEST_CASE("Test Procedure nodes") {
	std::shared_ptr<VariableNode> var1 = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> var2 = std::make_shared<VariableNode>("y");

	std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(1, var1);
	std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(2, var2);

	std::vector<std::shared_ptr<StmtNode>> stmtLst;
	stmtLst.push_back(print);
	stmtLst.push_back(read);

	REQUIRE(stmtLst[0]->isPrintNode() == true);
	REQUIRE(stmtLst[1]->isReadNode() == true);

	//test down casting
	std::shared_ptr<StmtNode> s1 = stmtLst[0];
	std::shared_ptr<PrintNode> p1 = std::dynamic_pointer_cast<PrintNode>(s1);
	std::shared_ptr<StmtNode> s2 = stmtLst[1];
	std::shared_ptr<ReadNode> p2 = std::dynamic_pointer_cast<ReadNode>(s2);

	REQUIRE(p1->getVariable()->isVariableNode() == true);
	REQUIRE(p2->getVariable()->isVariableNode() == true);

	std::shared_ptr<ProcedureNode> p = std::make_shared<ProcedureNode>(stmtLst, "testing");
	REQUIRE(p->isProcedureNode() == true);
	REQUIRE(p->getStmtList()[0]->isPrintNode() == true);
	REQUIRE(p->getStmtList()[1]->isReadNode() == true);
}