#include "catch.hpp"
#include "../src/models/simple_parser/BinaryOperator.h"
#include "../src/models/simple_parser/ExprNodes.h"
#include "../src/models/simple_parser/IoNodes.h"
#include "../src/models/simple_parser/Node.h"
#include "../src/models/simple_parser/NodeType.h"
#include "../src/models/simple_parser/ProcedureNode.h"
#include "../src/models/simple_parser/AST.h"
#include "../src/models/simple_parser/StmtNode.h"

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

	REQUIRE(var1 != con1);

	std::shared_ptr<VariableNode> var4 = std::make_shared<VariableNode>("x");
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
	REQUIRE(con.isRootNode() == false);
	REQUIRE(con.isPrintNode() == false);
	REQUIRE(con.getValue() == "12345");
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