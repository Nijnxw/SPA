#include "catch.hpp"
#include "models/EntityType.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"

#include <memory>
#include <unordered_set>
#include <vector>

//missing basic single line test cases

TEST_CASE("Extract simple SIMPLE code no design entities") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	read x;
	 * 2	print x;
	 * 3	print y;
	 * }
	 */

	// building AST
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");

	std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);
	std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(2, x);
	std::shared_ptr<PrintNode> stmt3 = std::make_shared<PrintNode>(3, y);

	std::vector<std::shared_ptr<StmtNode>> stmtList;
	stmtList.push_back(stmt1);
	stmtList.push_back(stmt2);
	stmtList.push_back(stmt3);

	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList;
	procList.push_back(proc1);

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::unordered_set<std::string> expected_procedure_table;
	expected_procedure_table.insert("testProgram");
	REQUIRE(EntityStager::getStagedProcedures() == expected_procedure_table);

	std::unordered_set<std::string> expected_var_table;
	expected_var_table.insert("x");
	expected_var_table.insert("y");
	REQUIRE(EntityStager::getStagedVariables() == expected_var_table);

	std::unordered_set<int> expected_stmt_table;
	expected_stmt_table.insert(1);
	expected_stmt_table.insert(2);
	expected_stmt_table.insert(3);
	REQUIRE(EntityStager::getStagedStatements() == expected_stmt_table);

	std::unordered_set<int> expected_print_table;
	expected_print_table.insert(2);
	expected_print_table.insert(3);
	REQUIRE(EntityStager::getStagedPrintStatements() == expected_print_table);

	std::unordered_set<int> expected_read_table;
	expected_read_table.insert(1);
	REQUIRE(EntityStager::getStagedReadStatements() == expected_read_table);

	EntityStager::clear();
}

TEST_CASE("Extract simple assign statement") {
	EntityStager::clear();

	SECTION("RHS - constant") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	x = 1;
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		ExprNode one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, one, "1");

		std::vector<std::shared_ptr<StmtNode>> stmtList;
		stmtList.push_back(stmt);

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
		REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

		std::unordered_set<std::string> expectedVarTable{ "x" };
		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

		std::unordered_set<std::string> expectedConstTable{ "1" };
		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

		std::unordered_set<int> expectedStmtTable{ 1 };
		REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

		std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
			std::make_tuple<int, std::string, std::string>(1, "x", "1")
		};
		REQUIRE(EntityStager::getStagedAssignStatements() == expectedAssignTable);

		EntityStager::clear();
	}

	SECTION("RHS - Variable") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	x = y;
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		ExprNode y = std::make_shared<VariableNode>("y");

		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, y, "y");

		std::vector<std::shared_ptr<StmtNode>> stmtList;
		stmtList.push_back(stmt);

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::unordered_set<std::string> expectedVarTable{ "x", "y"};
		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

		std::unordered_set<std::string> expectedConstTable;
		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

		std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
			std::make_tuple<int, std::string, std::string>(1, "x", "y")
		};
		REQUIRE(EntityStager::getStagedAssignStatements() == expectedAssignTable);

		EntityStager::clear();
	}

	SECTION("RHS - Complex") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	x = y + 1;
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");

		ExprNode y = std::make_shared<VariableNode>("y");
		ExprNode one = std::make_shared<ConstantNode>("1");
		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, one);

		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, expression, "y 1 +");

		std::vector<std::shared_ptr<StmtNode>> stmtList;
		stmtList.push_back(stmt);

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::unordered_set<std::string> expectedVarTable{ "x", "y" };
		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

		std::unordered_set<std::string> expectedConstTable{ "1" };
		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

		std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
			std::make_tuple<int, std::string, std::string>(1, "x", "y 1 +")
		};
		REQUIRE(EntityStager::getStagedAssignStatements() == expectedAssignTable);

		EntityStager::clear();
	}
}