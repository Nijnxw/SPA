#include "simple_parser/Parser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of valid assign - variable") {
	// a = x;
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),
			new PunctuatorToken("{"),   	new NameToken("a"),
			new OperatorToken("="),		new NameToken("x"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),
			new EndOfFileToken(),
	};

	Parser parser = Parser(input);
	AST output = parser.parseProgram();

	std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
	ExprNode exprNode = std::make_shared<VariableNode>("x");
	std::string postfix = "x";
	std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode, postfix);
	std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
	AST expected = std::make_shared<ProgramNode>(procLst);

	REQUIRE(*output == *expected);
};

TEST_CASE ("Test parsing of valid assign - constant") {
	// a = 123;
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),
			new PunctuatorToken("{"),   	new NameToken("a"),
			new OperatorToken("="),		new IntegerToken("123"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),
			new EndOfFileToken(),
	};

	Parser parser = Parser(input);
	AST output = parser.parseProgram();

	std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
	ExprNode exprNode = std::make_shared<ConstantNode>("123");
	std::string postfix = "123";
	std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode, postfix);
	std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
	AST expected = std::make_shared<ProgramNode>(procLst);

	REQUIRE(*output == *expected);
};

TEST_CASE ("Test parsing of valid assign - PLUS") {
	SECTION("Simple expression") {
		// a = 123 + x;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new NameToken("x"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode = std::make_shared<ConstantNode>("123");
		ExprNode varNode = std::make_shared<VariableNode>("x");
		ExprNode exprNode = std::make_shared<OperatorNode>(BinaryOperator::PLUS, constNode, varNode);
		std::string postfix = "123 x +";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Complex expression") {
		// a = 123 + x + Y3 + 345 + Sum;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new NameToken("x"),
				new OperatorToken("+"),		new NameToken("Y3"),
				new OperatorToken("+"),		new IntegerToken("345"),
				new OperatorToken("+"),		new NameToken("Sum"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode varNode3 = std::make_shared<VariableNode>("Sum");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, constNode1, varNode1);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, exprNode1, varNode2);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, exprNode2, constNode2);
		ExprNode exprNode4 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, exprNode3, varNode3);
		std::string postfix = "123 x + Y + 345 + Sum + tree3 +";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode4, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

TEST_CASE ("Test parsing of valid assign - MINUS") {
	SECTION("Simple expression") {
		// a = 123 - x;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("-"),		new NameToken("x"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode = std::make_shared<ConstantNode>("123");
		ExprNode varNode = std::make_shared<VariableNode>("x");
		ExprNode exprNode = std::make_shared<OperatorNode>(BinaryOperator::MINUS, constNode, varNode);
		std::string postfix = "123 x -";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Complex expression") {
		// a = 123 - x - Y3 - 345 - Sum;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("-"),		new NameToken("x"),
				new OperatorToken("-"),		new NameToken("Y3"),
				new OperatorToken("-"),		new IntegerToken("345"),
				new OperatorToken("-"),		new NameToken("Sum"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode varNode3 = std::make_shared<VariableNode>("Sum");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::MINUS, constNode1, varNode1);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::MINUS, exprNode1, varNode2);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::MINUS, exprNode2, constNode2);
		ExprNode exprNode4 = std::make_shared<OperatorNode>(BinaryOperator::MINUS, exprNode3, varNode3);
		std::string postfix = "123 x - Y - 345 - Sum - tree3 -";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode4, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

TEST_CASE ("Test parsing of valid assign - DIVIDE") {
	SECTION("Simple expression") {
		// a = 123 / x;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("/"),		new NameToken("x"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode = std::make_shared<ConstantNode>("123");
		ExprNode varNode = std::make_shared<VariableNode>("x");
		ExprNode exprNode = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, constNode, varNode);
		std::string postfix = "123 x /";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Complex expression") {
		// a = 123 / x / Y3 / 345 / Sum;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("/"),		new NameToken("x"),
				new OperatorToken("/"),		new NameToken("Y3"),
				new OperatorToken("/"),		new IntegerToken("345"),
				new OperatorToken("/"),		new NameToken("Sum"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode varNode3 = std::make_shared<VariableNode>("Sum");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, constNode1, varNode1);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, exprNode1, varNode2);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, exprNode2, constNode2);
		ExprNode exprNode4 = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, exprNode3, varNode3);
		std::string postfix = "123 x - Y - 345 - Sum - tree3 -";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode4, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

TEST_CASE ("Test parsing of valid assign - MODULO") {
	SECTION("Simple expression") {
		// a = 123 % x;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("%"),		new NameToken("x"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode = std::make_shared<ConstantNode>("123");
		ExprNode varNode = std::make_shared<VariableNode>("x");
		ExprNode exprNode = std::make_shared<OperatorNode>(BinaryOperator::MODULO, constNode, varNode);
		std::string postfix = "123 x %";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Complex expression") {
		// a = 123 % x % Y3 % 345 % Sum;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("%"),		new NameToken("x"),
				new OperatorToken("%"),		new NameToken("Y"),
				new OperatorToken("%"),		new IntegerToken("345"),
				new OperatorToken("%"),		new NameToken("Sum"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode varNode3 = std::make_shared<VariableNode>("Sum");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::MODULO, constNode1, varNode1);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::MODULO, exprNode1, varNode2);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::MODULO, exprNode2, constNode2);
		ExprNode exprNode4 = std::make_shared<OperatorNode>(BinaryOperator::MODULO, exprNode3, varNode3);
		std::string postfix = "123 x % Y % 345 % Sum % tree3 %";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode4, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

TEST_CASE ("Test parsing of valid assign - mixed operators") {
	SECTION("Simple expression") {
		// a = 123 + x * Y3;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new NameToken("x"),
				new OperatorToken("*"),		new NameToken("Y3"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::TIMES, varNode1, varNode2);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, constNode, exprNode1);
		std::string postfix = "123 x Y3 * +";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode2, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Semi-complex expression") {
		// a = 123 + x * Y3 - 345;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new NameToken("x"),
				new OperatorToken("*"),		new NameToken("Y3"),
				new OperatorToken("-"),		new IntegerToken("345"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::TIMES, varNode1, varNode2);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, constNode1, exprNode1);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::MINUS,  exprNode2, constNode2);
		std::string postfix = "123 x Y3 * + 345 -";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode3, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Complex expression") {
		// a = 123 + x * Y3 - 345 / Sum % 4;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new NameToken("x"),
				new OperatorToken("*"),		new NameToken("Y3"),
				new OperatorToken("-"),		new IntegerToken("345"),
				new OperatorToken("/"),		new NameToken("Sum"),
				new OperatorToken("%"),		new IntegerToken("4"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode varNode3 = std::make_shared<VariableNode>("Sum");
		ExprNode c4Node = std::make_shared<ConstantNode>("4");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::TIMES, varNode1, varNode2);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, constNode1, exprNode1);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, constNode2, varNode3);
		ExprNode exprNode4 = std::make_shared<OperatorNode>(BinaryOperator::MODULO, exprNode3, c4Node);
		ExprNode exprNode5 = std::make_shared<OperatorNode>(BinaryOperator::MINUS, exprNode2, exprNode4);
		std::string postfix = "123 x Y3 * + 345 Sum / 4 % -";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode5, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

TEST_CASE ("Test parsing of valid assign - parentheses") {
	SECTION("Simple expression") {
		// a = 123 + (x + Y3);
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("+"),
				new NameToken("Y3"),			new PunctuatorToken(")"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, varNode1, varNode2);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, constNode, exprNode1);
		std::string postfix = "123 x Y3 + +";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode2, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Semi-complex expression") {
		// a = 123 + (x - Y3) / 345;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("-"),
				new NameToken("Y3"),			new PunctuatorToken(")"),
				new OperatorToken("/"),		new IntegerToken("345"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::MINUS, varNode1, varNode2);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, exprNode1, constNode2);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::PLUS,  constNode1, exprNode2);
		std::string postfix = "123 x Y3 - 345 / +";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode3, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("Complex expression") {
		// a = 123 + (x * (Y3 - 345)) / (Sum % 4);
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new IntegerToken("123"),
				new OperatorToken("+"),		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("*"),
				new PunctuatorToken("("), 	new NameToken("Y3"),
				new OperatorToken("-"),		new IntegerToken("345"),
				new PunctuatorToken(")"),	new PunctuatorToken(")"),
				new OperatorToken("/"),		new PunctuatorToken("("),
				new NameToken("Sum"),		new OperatorToken("%"),
				new IntegerToken("4"), 		new PunctuatorToken(")"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<VariableNode> variableNode = std::make_shared<VariableNode>("a");
		ExprNode constNode1 = std::make_shared<ConstantNode>("123");
		ExprNode varNode1 = std::make_shared<VariableNode>("x");
		ExprNode varNode2 = std::make_shared<VariableNode>("Y3");
		ExprNode constNode2 = std::make_shared<ConstantNode>("345");
		ExprNode varNode3 = std::make_shared<VariableNode>("Sum");
		ExprNode constNode3 = std::make_shared<ConstantNode>("4");
		ExprNode exprNode1 = std::make_shared<OperatorNode>(BinaryOperator::MINUS, varNode2, constNode2);
		ExprNode exprNode2 = std::make_shared<OperatorNode>(BinaryOperator::TIMES, varNode1, exprNode1);
		ExprNode exprNode3 = std::make_shared<OperatorNode>(BinaryOperator::MODULO, varNode3, constNode3);
		ExprNode exprNode4 = std::make_shared<OperatorNode>(BinaryOperator::DIVIDE, exprNode2, exprNode3);
		ExprNode exprNode5 = std::make_shared<OperatorNode>(BinaryOperator::PLUS, constNode1, exprNode4);
		std::string postfix = "123 x Y3 345 - * Sum 4 % / +";
		std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1, variableNode, exprNode5, postfix);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(assignNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of invalid assign statements") {

}

