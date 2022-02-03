#include "catch.hpp"
#include "../src/models/simple_parser/BinaryOperator.h"
#include "../src/models/simple_parser/ExprNodes.h"
#include "../src/models/simple_parser/IoNodes.h"
#include "../src/models/simple_parser/Node.h"
#include "../src/models/simple_parser/NodeType.h"
#include "../src/models/simple_parser/ProcedureNode.h"
#include "../src/models/simple_parser/RootNode.h"
#include "../src/models/simple_parser/StmtNode.h"

#include <memory>

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

	std::shared_ptr<ProcedureNode> p = std::make_shared<ProcedureNode>(stmtLst);
	REQUIRE(p->isProcedureNode() == true);
	REQUIRE(p->getStmtList()[0]->isPrintNode() == true);
	REQUIRE(p->getStmtList()[1]->isReadNode() == true);
}