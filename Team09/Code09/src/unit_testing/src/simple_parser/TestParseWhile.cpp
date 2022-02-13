#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE("Test parsing of valid while statements") {
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
	std::vector<std::shared_ptr<StmtNode>> simpleStmtLst{readNode};

	SECTION ("Simple predicate and statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (x < 1) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("while"),
				new PunctuatorToken("("), 	new NameToken("x"),
				new OperatorToken("<"),		new IntegerToken("1"),
				new PunctuatorToken(")"),	new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(1, ltNode, simpleStmtLst);
		std::vector<std::shared_ptr<StmtNode>> stmtLst1{whileNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst1, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION ("Semi complex predicate and simple statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (!(y + 1 >= 3)) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("while"),		new PunctuatorToken("("), 		new OperatorToken("!"),
				new PunctuatorToken("("), 	new NameToken("y"),			new OperatorToken("+"),
				new IntegerToken("1"),		new OperatorToken(">="),		new IntegerToken("3"),
				new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(1, notNode, simpleStmtLst);
		std::vector<std::shared_ptr<StmtNode>> stmtLst1{whileNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst1, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);

	}
	SECTION ("Complex predicate and simple statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while ((x < 1) && ((!(y + 1 >= 3)) || (y == 2))) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("while"),		new PunctuatorToken("("), 		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
				new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
				new PunctuatorToken("("),	new OperatorToken("!"), 		new PunctuatorToken("("),
				new NameToken("y"),			new OperatorToken("+"),		new IntegerToken("1"),
				new OperatorToken(">="),		new IntegerToken("3"), 			new PunctuatorToken(")"),
				new PunctuatorToken(")"),
				new OperatorToken("||"),		new PunctuatorToken("("),		new NameToken("y"),
				new OperatorToken("=="),		new IntegerToken("2"),			new PunctuatorToken(")"),
				new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
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

		std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(1, andNode, simpleStmtLst);
		std::vector<std::shared_ptr<StmtNode>> stmtLst1{whileNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst1, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION ("Nested while loops") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (x < 1) {
		 * 2		read x;
		 * 3		while (y != 1) {
		 * 4			print y;
		 * 5			y = y + 1;
		 * 			}
		 * 6		read y;
		 * 		}
		 * 7	print x;
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("while"),		new PunctuatorToken("("), 		new NameToken("x"),
				new OperatorToken("<"),		new IntegerToken("1"),		new PunctuatorToken(")"),
				new PunctuatorToken("{"),
				new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
				new NameToken("while"),		new PunctuatorToken("("),		new NameToken("y"),
				new OperatorToken("!="),		new IntegerToken("1"),			new PunctuatorToken(")"),
				new PunctuatorToken("{"),	new NameToken("print"),			new NameToken("y"),
				new PunctuatorToken(";"),	new NameToken("y"),				new OperatorToken("="),
				new NameToken("y"),			new OperatorToken("+"),			new IntegerToken("1"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),		new NameToken("read"),
				new NameToken("y"),			new PunctuatorToken(";"),		new PunctuatorToken("}"),
				new NameToken("print"),		new NameToken("x"),				new PunctuatorToken(";"),
				new PunctuatorToken("}"),		new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<StmtNode> printYNode = std::make_shared<PrintNode>(4, yNode);
		std::shared_ptr<StmtNode> assignNode = std::make_shared<AssignNode>(5, yNode, yPlusOneExprNode, "y 1 +");
		std::vector<std::shared_ptr<StmtNode>> innerWhileStmtLst{printYNode, assignNode};
		std::shared_ptr<StmtNode> innerWhileNode = std::make_shared<WhileNode>(3, neqNode, innerWhileStmtLst);

		std::shared_ptr<StmtNode> readYNode = std::make_shared<ReadNode>(6, yNode);
		std::vector<std::shared_ptr<StmtNode>> outerWhileStmtLst{readNode, innerWhileNode, readYNode};
		std::shared_ptr<StmtNode> outerWhileNode = std::make_shared<WhileNode>(1, ltNode, outerWhileStmtLst);

		std::shared_ptr<StmtNode> printXNode = std::make_shared<PrintNode>(7, xNode);
		std::vector<std::shared_ptr<StmtNode>> procStmtLst{outerWhileNode, printXNode};

		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(procStmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

// --------------------------------------------------
//                 UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Invalid while stmt - no stmt in stmtLst") {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 *
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("), 		new NameToken("x"),
			new OperatorToken("<"),		new IntegerToken("1"),		new PunctuatorToken(")"),
			new PunctuatorToken("{"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
}

TEST_CASE("Invalid while stmt - no predicate") {
	/*
	 * procedure testProgram {
	 * 1	while () {
	 * 2		read x;
	 * 		}
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("), 		new PunctuatorToken(")"),
			new PunctuatorToken("{"),	new NameToken("read"),			new NameToken("x"),
			new PunctuatorToken(";"), 	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE("Invalid while stmt - invalid predicate") {
	SECTION ("Integer as predicate") {
		/*
		 * procedure testProgram {
		 * 1	while (1) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("while"),		new PunctuatorToken("("), 		new IntegerToken("1"),
				new PunctuatorToken(")"),
				new PunctuatorToken("{"),	new NameToken("read"),			new NameToken("x"),
				new PunctuatorToken(";"), 	new PunctuatorToken("}"),		new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected comparator operator but got ')' instead.\n");
	}
	SECTION ("Missing parentheses") {
		/*
		 * procedure testProgram {
		 * 1	while ((x < 1) || x == 3) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("while"),		new PunctuatorToken("("), 		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
				new PunctuatorToken(")"),	new OperatorToken("||"), 		new NameToken("x"),
				new OperatorToken("=="),		new IntegerToken("3"),			new PunctuatorToken(")"),
				new PunctuatorToken("{"),	new NameToken("read"),			new NameToken("x"),
				new PunctuatorToken(";"), 	new PunctuatorToken("}"),		new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '(' but got 'x' instead.\n");
	}
	SECTION ("Missing conditional") {
		/*
		 * procedure testProgram {
		 * 1	while ((x < 1)) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
				new NameToken("while"),		new PunctuatorToken("("), 		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
				new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
				new NameToken("read"),			new NameToken("x"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),		new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '&&' or '||' but got ')' instead.\n");
	}
}