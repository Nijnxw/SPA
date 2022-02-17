#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE("Test parsing of valid if statements") {
	std::shared_ptr<VariableNode> xNode = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> yNode = std::make_shared<VariableNode>("y");
	std::shared_ptr<VariableNode> zNode = std::make_shared<VariableNode>("z");
	std::shared_ptr<ConstantNode> c1Node = std::make_shared<ConstantNode>("1");
	std::shared_ptr<ConstantNode> c2Node = std::make_shared<ConstantNode>("2");
	std::shared_ptr<ConstantNode> c3Node = std::make_shared<ConstantNode>("3");
	ExprNode yPlusOneExprNode = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, yNode, c1Node);
	std::shared_ptr<PredicateNode> eqNode = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(yNode,
										  ComparatorOperator::EQ,
										  c2Node));
	std::shared_ptr<PredicateNode> ltNode = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(xNode,
										  ComparatorOperator::LT,
										  c1Node));
	std::shared_ptr<PredicateNode> gteNode = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(yPlusOneExprNode,
										  ComparatorOperator::GTE,
										  c3Node));
	std::shared_ptr<PredicateNode> notNode = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
																			 gteNode);
	std::shared_ptr<PredicateNode> neqNode = std::make_shared<PredicateNode>(
			std::make_shared<RelExprNode>(yNode,
										  ComparatorOperator::NEQ,
										  c1Node));

	std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(2, xNode);
	std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(3, yNode);
	std::vector<std::shared_ptr<StmtNode>> simpleThenStmtLst{readNode};
	std::vector<std::shared_ptr<StmtNode>> simpleElseStmtLst{printNode};

	SECTION ("Simple predicate and statement") {
		/*
		 * procedure testProgram {
		 * 1	if (x < 1) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("if"),			new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("<"),		new IntegerToken("1"),
				new PunctuatorToken(")"),	new NameToken("then"),		new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new NameToken("else"),		new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("y"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),	new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(1, ltNode, simpleThenStmtLst, simpleElseStmtLst);
		std::vector<std::shared_ptr<StmtNode>> stmtLst{ifNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION ("Semi complex predicate and simple statement") {
		/*
		 * procedure testProgram {
		 * 1	if (!(y + 1 >= 3)) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("if"),			new PunctuatorToken("("), 		new OperatorToken("!"),
				new PunctuatorToken("("), 	new NameToken("y"),				new OperatorToken("+"),
				new IntegerToken("1"),		new OperatorToken(">="),			new IntegerToken("3"),
				new PunctuatorToken(")"),	new PunctuatorToken(")"),		new NameToken("then"),
				new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(1, notNode, simpleThenStmtLst, simpleElseStmtLst);
		std::vector<std::shared_ptr<StmtNode>> stmtLst1{ifNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst1, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);

	}
	SECTION ("Complex predicate and simple statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if ((x < 1) && ((!(y + 1 >= 3)) || (y == 2))) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("if"),			new PunctuatorToken("("), 		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
				new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
				new PunctuatorToken("("),	new OperatorToken("!"), 			new PunctuatorToken("("),
				new NameToken("y"),			new OperatorToken("+"),			new IntegerToken("1"),
				new OperatorToken(">="),		new IntegerToken("3"), 			new PunctuatorToken(")"),
				new PunctuatorToken(")"),	new OperatorToken("||"),			new PunctuatorToken("("),
				new NameToken("y"),			new OperatorToken("=="),			new IntegerToken("2"),
				new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
				new NameToken("then"),			new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<PredicateNode> orNode = std::make_shared<PredicateNode>(notNode,
																				ConditionalOperator::OR,
																				eqNode);
		std::shared_ptr<PredicateNode> andNode = std::make_shared<PredicateNode>(ltNode,
																				 ConditionalOperator::AND,
																				 orNode);

		std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(1, andNode, simpleThenStmtLst, simpleElseStmtLst);
		std::vector<std::shared_ptr<StmtNode>> stmtLst1{ifNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst1, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION ("Nested ifs in then block") {
		/*
		 * procedure testProgram {
		 * 1	if (x < 1) then {
		 * 2		read x;
		 * 3		if (y == 2) then {
		 * 4			read y;
		 * 			} else {
		 * 5			print y;
		 * 			}
		 * 		} else {
		 * 6		print x;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("if"),			new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
				new PunctuatorToken(")"),	new NameToken("then"),			new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),

				new NameToken("if"),			new PunctuatorToken("("),
				new NameToken("y"),			new OperatorToken("=="),			new IntegerToken("2"),
				new PunctuatorToken(")"),	new NameToken("then"),			new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("y"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),

				new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("x"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),			new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<StmtNode> readYNode = std::make_shared<ReadNode>(4, yNode);
		std::shared_ptr<StmtNode> printYNode = std::make_shared<PrintNode>(5, yNode);
		std::vector<std::shared_ptr<StmtNode>> innerIfThenStmtLst{readYNode};
		std::vector<std::shared_ptr<StmtNode>> innerIfElseStmtLst{printYNode};
		std::shared_ptr<StmtNode> innerIfNode = std::make_shared<IfNode>(3, eqNode, innerIfThenStmtLst, innerIfElseStmtLst);

		std::shared_ptr<StmtNode> printXNode = std::make_shared<PrintNode>(6, xNode);
		std::vector<std::shared_ptr<StmtNode>> outerIfThenStmtLst{readNode, innerIfNode};
		std::vector<std::shared_ptr<StmtNode>> outerIfElseStmtLst{printXNode};
		std::shared_ptr<StmtNode> outerIfNode = std::make_shared<IfNode>(1, ltNode, outerIfThenStmtLst, outerIfElseStmtLst);

		std::vector<std::shared_ptr<StmtNode>> procStmtLst{outerIfNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procStmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

// --------------------------------------------------
//                 UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Invalid if stmt - no stmt in then stmtLst") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 *
	 * 		} else {
	 * 2		print y;
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("if"),			new PunctuatorToken("("), 		new NameToken("x"),
			new OperatorToken("<"),		new IntegerToken("1"),			new PunctuatorToken(")"),
			new NameToken("then"), 		new PunctuatorToken("{"),		new PunctuatorToken("}"),
			new NameToken("else"),		new PunctuatorToken("{"),		new NameToken("print"),
			new NameToken("y"),			new PunctuatorToken("}"),		new PunctuatorToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
}

TEST_CASE("Invalid if stmt - no stmt in else stmtLst") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2 		read x;
	 * 		} else {
	 *
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("if"),			new PunctuatorToken("("), 		new NameToken("x"),
			new OperatorToken("<"),		new IntegerToken("1"),			new PunctuatorToken(")"),
			new NameToken("then"), 		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
}

TEST_CASE("Invalid if stmt - no predicate") {
	/*
	 * procedure testProgram {
	 * 1	if () then {
	 * 2		read x;
	 * 		} else {
	 * 3		print y;
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("if"),			new PunctuatorToken("("), 		new PunctuatorToken(")"),
			new NameToken("then"),		new PunctuatorToken("{"),	new NameToken("read"),
			new NameToken("x"),			new PunctuatorToken(";"),	new PunctuatorToken("}"),
			new NameToken("else"),		new PunctuatorToken("{"), 	new NameToken("print"),
			new NameToken("y"),			new PunctuatorToken(";"),	new PunctuatorToken("}"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE("Invalid if stmt - invalid predicate") {
	SECTION ("Integer as predicate") {
		/*
		 * procedure testProgram {
		 * 1	if (1) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("if"),			new PunctuatorToken("("), 		new IntegerToken("1"),
				new PunctuatorToken(")"),	new NameToken("then"),		new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new NameToken("else"),		new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("y"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),	new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected comparator operator but got ')' instead.\n");
	}
	SECTION ("Missing parentheses") {
		/*
		 * procedure testProgram {
		 * 1	if x < 1) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("if"),
				new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
				new PunctuatorToken(")"),	new NameToken("then"),		new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new NameToken("else"),		new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("y"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),	new EndOfFileToken(),
		};


		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '(' but got 'x' instead.\n");
	}
	SECTION ("Invalid rel_expr") {
		/*
		 * procedure testProgram {
		 * 1	if ((x < 1)) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("if"),			new PunctuatorToken("("),		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
				new PunctuatorToken(")"),	new PunctuatorToken(")"),	new NameToken("then"),
				new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new NameToken("else"),		new PunctuatorToken("{"),
				new NameToken("print"),		new NameToken("y"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),	new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ')' but got '<' instead.\n");
	}
}

TEST_CASE("Invalid if stmt - no 'then' keyword") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1)  {
	 * 2 		read x;
	 * 		} else {
	 * 3		print y;
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("if"),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),		 	new IntegerToken("1"),
			new PunctuatorToken(")"),								 		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'then' but got '{' instead.\n");
}

TEST_CASE("Invalid if stmt - no 'else' keyword") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2 		read x;
	 * 		}  {
	 * 3		print y;
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("if"),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),		 	new IntegerToken("1"),
			new PunctuatorToken(")"),	new NameToken("then"),	 		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),										new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'else' but got '{' instead.\n");
}

TEST_CASE("Invalid if stmt - no 'else' block") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2 		read x;
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("if"),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),		 	new IntegerToken("1"),
			new PunctuatorToken(")"),	new NameToken("then"),			new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'else' but got '}' instead.\n");
}