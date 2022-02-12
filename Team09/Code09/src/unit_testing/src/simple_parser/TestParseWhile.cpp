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
	std::shared_ptr<ConstantNode> c1Node = std::make_shared<ConstantNode>("1");
	std::shared_ptr<ConstantNode> c2Node = std::make_shared<ConstantNode>("2");
	std::shared_ptr<ConstantNode> c3Node = std::make_shared<ConstantNode>("3");
	std::shared_ptr<RelExprNode> xLTOneRelExprNode = std::make_shared<RelExprNode>(xNode,
																			 ComparatorOperator::LT,
																			 c1Node);
	std::shared_ptr<RelExprNode> yEqTwoRelExprNode = std::make_shared<RelExprNode>(yNode,
																			  ComparatorOperator::EQ,
																			  c2Node);
	ExprNode yPlusOneExprNode = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, yNode, c1Node);
	std::shared_ptr<RelExprNode> gteNode = std::make_shared<RelExprNode>(yPlusOneExprNode,
																		 ComparatorOperator::GTE,
																		 c3Node);

	std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(2, xNode);
	std::vector<std::shared_ptr<StmtNode>> simpleStmtLst{readNode};

	SECTION("Simple predicate and stmt") {
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

		std::shared_ptr<PredicateNode> predicateNode = std::make_shared<PredicateNode>(xLTOneRelExprNode);
		std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(1, predicateNode, simpleStmtLst);
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

		std::shared_ptr<PredicateNode> neqNode = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
																				 std::make_shared<PredicateNode>(gteNode));

		std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(1, neqNode, simpleStmtLst);
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

		std::shared_ptr<PredicateNode> neqNode = std::make_shared<PredicateNode>(ConditionalOperator::NOT,
																				 std::make_shared<PredicateNode>(gteNode));
		std::shared_ptr<PredicateNode> orNode = std::make_shared<PredicateNode>(neqNode,
																				ConditionalOperator::OR,
																				std::make_shared<PredicateNode>(yEqTwoRelExprNode));
		std::shared_ptr<PredicateNode> andNode = std::make_shared<PredicateNode>(std::make_shared<PredicateNode>(xLTOneRelExprNode),
		        																 ConditionalOperator::AND,
																				 orNode);

		std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(1, andNode, simpleStmtLst);
		std::vector<std::shared_ptr<StmtNode>> stmtLst1{whileNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst1, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}

}