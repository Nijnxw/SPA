#include "catch.hpp"
#include "../src/models/simple_parser/Operator.h"
#include "../src/models/simple_parser/AssignNode.h"
#include "../src/models/simple_parser/IoNodes.h"
#include "../src/models/simple_parser/ProcedureNode.h"
#include "../src/models/simple_parser/PredicateNodes.h"
#include "../src/models/simple_parser/WhileNode.h"
#include "../src/models/simple_parser/IfNode.h"
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

//	std::shared_ptr<VariableNode> var4 = std::make_shared<VariableNode>("x");
//	std::shared_ptr<ConstantNode> con4 = std::make_shared<ConstantNode>("123");
//	BinaryOperatorNode op1(BinaryOperator::PLUS, var4, con4);
//	BinaryOperatorNode op2(BinaryOperator::MINUS, var4, con4);
//	BinaryOperatorNode op3(BinaryOperator::PLUS, var4, con4);
//	REQUIRE(op1 == op3);
//	REQUIRE(op1 != op2);
//
//	REQUIRE(var1 != con1);
//	REQUIRE(op1 != con1);
//	REQUIRE(var1 != op1);
//
//	std::shared_ptr<VariableNode> var5 = std::make_shared<VariableNode>("y");
//
//	std::shared_ptr<PrintNode> print1 = std::make_shared<PrintNode>(45, var4);
//	std::shared_ptr<PrintNode> print2 = std::make_shared<PrintNode>(45, var4);
//	std::shared_ptr<PrintNode> print3 = std::make_shared<PrintNode>(46, var4);
//	std::shared_ptr<PrintNode> print4 = std::make_shared<PrintNode>(45, var5);
//	REQUIRE(*print1 == *print2);
//	REQUIRE(*print1 != *print3);
//	REQUIRE(*print2 != *print4);
//
//	std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(45, var4);
//	std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(45, var4);
//	std::shared_ptr<ReadNode> read3 = std::make_shared<ReadNode>(46, var4);
//	std::shared_ptr<ReadNode> read4 = std::make_shared<ReadNode>(45, var5);
//	REQUIRE(*read1 == *read2);
//	REQUIRE(*read1 != *read3);
//	REQUIRE(*read2 != *read4);
//
//	std::vector<std::shared_ptr<StmtNode>> stmtLst1;
//	stmtLst1.push_back(print1);
//	stmtLst1.push_back(read1);
//
//	std::vector<std::shared_ptr<StmtNode>> stmtLst2;
//	stmtLst2.push_back(print2);
//	stmtLst2.push_back(read2);
//
//	std::vector<std::shared_ptr<StmtNode>> stmtLst3;
//	stmtLst3.push_back(print3);
//	stmtLst3.push_back(read4);
//
//	std::shared_ptr<ProcedureNode> p1 = std::make_shared<ProcedureNode>(stmtLst1, "test");
//	std::shared_ptr<ProcedureNode> p2 = std::make_shared<ProcedureNode>(stmtLst2, "test");
//	std::shared_ptr<ProcedureNode> p3 = std::make_shared<ProcedureNode>(stmtLst1, "test123");
//	std::shared_ptr<ProcedureNode> p4 = std::make_shared<ProcedureNode>(stmtLst3, "test");
//
//	REQUIRE(*p1 == *p2);
//	REQUIRE(*p1 != *p3);
//	REQUIRE(*p1 != *p4);
//
//	std::vector<std::shared_ptr<ProcedureNode>> procList1;
//	procList1.push_back(p1);
//
//	std::vector<std::shared_ptr<ProcedureNode>> procList2;
//	procList2.push_back(p2);
//
//	std::vector<std::shared_ptr<ProcedureNode>> procList3;
//	procList3.push_back(p3);
//
//	ProgramNode r1(procList1);
//	ProgramNode r2(procList2);
//	ProgramNode r3(procList3);
//
//	REQUIRE(r1 == r2);
//	REQUIRE(r1 != r3);
//}
//
//TEST_CASE("Test Expr nodes") {
//	VariableNode var("abcd");
//	REQUIRE(var.isVariableNode() == true);
//	REQUIRE(var.isConstantNode() == false);
//	REQUIRE(var.isProcedureNode() == false);
//	REQUIRE(var.getName() == "abcd");
//
//	ConstantNode con("12345");
//	REQUIRE(con.isConstantNode() == true);
//	REQUIRE(con.isProgramNode() == false);
//	REQUIRE(con.isPrintNode() == false);
//	REQUIRE(con.getValue() == "12345");
//
//	ExprNode var2 = std::make_shared<VariableNode>("x");
//	ExprNode con2 = std::make_shared<ConstantNode>("123");
//	BinaryOperatorNode op(BinaryOperator::PLUS, var2, con2);
//	REQUIRE(op.isBinOpNode() == true);
//	REQUIRE(op.isIfNode() == false);
//	REQUIRE(op.isWhileNode() == false);
//	REQUIRE(op.getOperator() == BinaryOperator::PLUS);
//	REQUIRE(op.getLhs() == var2);
//	REQUIRE(op.getRhs() == con2);
//}
//
//TEST_CASE("Test Assign statement nodes") {
//	SECTION("Constant Assignment") {
//		// testing = 123
//		std::shared_ptr<VariableNode> var = std::make_shared<VariableNode>("testing");
//		ExprNode con = std::make_shared<ConstantNode>("123");
//
//		REQUIRE_NOTHROW(AssignNode(1, var, con, "123"));
//		AssignNode ass = AssignNode(1, var, con, "123");
//
//		REQUIRE(ass.getAssignedVar() == var);
//		REQUIRE(ass.getExpression() == con);
//		REQUIRE(ass.getPostfix() == "123");
//
//		REQUIRE(ass.isAssignNode() == true);
//		REQUIRE(ass.getAssignedVar()->isVariableNode() == true);
//		REQUIRE(std::visit(
//			[](const auto& expr) { return expr->isConstantNode(); },
//			ass.getExpression()));
//	}
//
//	SECTION("Variable Assignment") {
//		// testing = test
//		std::shared_ptr<VariableNode> var1 = std::make_shared<VariableNode>("testing");
//		ExprNode var2 = std::make_shared<VariableNode>("test");
//
//		REQUIRE_NOTHROW(AssignNode(1, var1, var2, "test"));
//		AssignNode ass = AssignNode(1, var1, var2, "test");
//
//		REQUIRE(ass.getAssignedVar() == var1);
//		REQUIRE(ass.getExpression() == var2);
//		REQUIRE(ass.getPostfix() == "test");
//
//		REQUIRE(ass.isAssignNode() == true);
//		REQUIRE(ass.getAssignedVar()->isVariableNode() == true);
//		REQUIRE(std::visit(
//			[](const auto& expr) { return expr->isVariableNode(); },
//			ass.getExpression()) == true);
//	}
//
//	SECTION("Expression Assignment") {
//		// build somewhat complicated expression
//		// testing = a * b + 123 / 1
//		std::shared_ptr<VariableNode> var = std::make_shared<VariableNode>("testing");
//
//		std::string expr = "a * b + 123 / 1";
//		std::string postfix = RPN::convertToRpn(expr);
//
//		ExprNode a = std::make_shared<VariableNode>("a");
//		ExprNode b = std::make_shared<VariableNode>("b");
//		ExprNode left_side = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, a, b);
//
//		ExprNode con123 = std::make_shared<ConstantNode>("123");
//		ExprNode con1 = std::make_shared<ConstantNode>("1");
//		ExprNode right_side = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, con123, con1);
//
//		ExprNode overall = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, left_side, right_side);
//
//		REQUIRE_NOTHROW(AssignNode(1, var, overall, postfix));
//
//		AssignNode ass1 = AssignNode(1, var, overall, postfix);
//		AssignNode ass2 = AssignNode(1, var, overall, postfix);
//		AssignNode ass3 = AssignNode(2, var, overall, postfix);
//		AssignNode ass4 = AssignNode(1, var, left_side, postfix);
//
//		REQUIRE(ass1 == ass2);
//		REQUIRE(ass1 != ass3);
//		REQUIRE(ass1 != ass4);
//
//		REQUIRE(ass1.isAssignNode() == true);
//		REQUIRE(ass1.getAssignedVar()->isVariableNode() == true);
//		REQUIRE(std::visit(
//			[](const auto& expr) { return expr->isBinOpNode(); },
//			ass1.getExpression()) == true);
//	}
//}
//
//TEST_CASE("Test Predicate Nodes") {
//	SECTION("Simple Predicate without binary operators") {
//		// if (x > 0) ...
//		std::shared_ptr<VariableNode> var = std::make_shared<VariableNode>("x");
//		std::shared_ptr<ConstantNode> con = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<ConstantNode> con2 = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<RelExprNode> rel1 = std::make_shared<RelExprNode>(var, ComparatorOperator::GT, con);
//		std::shared_ptr<RelExprNode> rel2 = std::make_shared<RelExprNode>(var, ComparatorOperator::GT, con2);
//
//		PredicateNode pred1(rel1);
//		PredicateNode pred2(rel2);
//		
//		REQUIRE(pred1 == pred2);
//		REQUIRE(pred1.isTerminalPredicate() == true);
//		REQUIRE(pred1.isNotPredicate() == false);
//		REQUIRE(pred1.isFullPredicate() == false);
//
//		//legal accesses
//		REQUIRE_NOTHROW(pred1.getRelExprNode());
//		REQUIRE_NOTHROW(pred1.getRelLhs());
//		REQUIRE_NOTHROW(pred1.getRelRhs());
//
//		//illegal accesses
//		REQUIRE_THROWS_WITH(pred1.getLhs(), "Predicate does not contain a left predicate (Not terminal or a NOT predicate)");
//		REQUIRE_THROWS_WITH(pred1.getRhs(), "Predicate is a terminal predicate");
//	}
//
//	SECTION("Predicate with binary operators") {
//		// if (x + y == 8 * 9) ...
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		std::shared_ptr<BinaryOperatorNode> lhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, y);
//
//		std::shared_ptr<ConstantNode> eight = std::make_shared<ConstantNode>("8");
//		std::shared_ptr<ConstantNode> nine = std::make_shared<ConstantNode>("9");
//		std::shared_ptr<BinaryOperatorNode> rhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, eight, nine);
//
//		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(lhs, ComparatorOperator::EQ, rhs);
//		PredicateNode pred(rel);
//		PredicateNode pred2(std::make_shared<RelExprNode>(lhs, ComparatorOperator::EQ, rhs));
//		PredicateNode pred3(std::make_shared<RelExprNode>(rhs, ComparatorOperator::EQ, lhs));
//		PredicateNode pred4(std::make_shared<RelExprNode>(lhs, ComparatorOperator::LTE, rhs));
//
//		REQUIRE(pred == pred2);
//		REQUIRE(pred != pred3);
//		REQUIRE(pred != pred4);
//
//		REQUIRE(pred.isTerminalPredicate() == true);
//		REQUIRE(pred.isNotPredicate() == false);
//		REQUIRE(pred.isFullPredicate() == false);
//
//		//legal accesses
//		REQUIRE_NOTHROW(pred.getRelExprNode());
//		REQUIRE_NOTHROW(pred.getRelLhs());
//		REQUIRE_NOTHROW(pred.getRelRhs());
//
//		//illegal accesses
//		REQUIRE_THROWS_WITH(pred.getLhs(), "Predicate does not contain a left predicate (Not terminal or a NOT predicate)");
//		REQUIRE_THROWS_WITH(pred.getRhs(), "Predicate is a terminal predicate");
//	}
//
//	SECTION("Simple Predicate with NOT") {
//		// if (!(x > 0)) ...
//		std::shared_ptr<VariableNode> var = std::make_shared<VariableNode>("x");
//		std::shared_ptr<ConstantNode> con = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<ConstantNode> con2 = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(var, ComparatorOperator::GT, con);
//
//		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);
//		PredicateNode pred2(ConditionalOperator::NOT, pred);
//
//		REQUIRE(*pred != pred2);
//		REQUIRE(pred2.isTerminalPredicate() == false);
//		REQUIRE(pred2.isNotPredicate() == true);
//		REQUIRE(pred2.isFullPredicate() == false);
//		
//		//legal accesses
//		REQUIRE_NOTHROW(pred->getRelExprNode());
//		REQUIRE_NOTHROW(pred->getRelLhs());
//		REQUIRE_NOTHROW(pred->getRelRhs());
//		REQUIRE_NOTHROW(pred2.getRhs());
//
//		//illegal accesses
//		REQUIRE_THROWS_WITH(pred->getLhs(), "Predicate does not contain a left predicate (Not terminal or a NOT predicate)");
//		REQUIRE_THROWS_WITH(pred->getRhs(), "Predicate is a terminal predicate");
//		REQUIRE_THROWS_WITH(pred2.getRelExprNode(), "Predicate is not a terminal predicate");
//		REQUIRE_THROWS_WITH(pred2.getRelLhs(), "Predicate is not a terminal predicate");
//		REQUIRE_THROWS_WITH(pred2.getRelRhs(), "Predicate is not a terminal predicate");
//		REQUIRE_THROWS_WITH(pred2.getLhs(), "Predicate does not contain a left predicate (Not terminal or a NOT predicate)");
//	}
//
//	SECTION("Predicate with multiple comparisons") {
//		// if (x == 9 && 10 != y) ...
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<ConstantNode> nine = std::make_shared<ConstantNode>("9");
//		std::shared_ptr<RelExprNode> relLhs = std::make_shared<RelExprNode>(x, ComparatorOperator::EQ, nine);
//
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		std::shared_ptr<ConstantNode> ten = std::make_shared<ConstantNode>("10");
//		std::shared_ptr<RelExprNode> relRhs = std::make_shared<RelExprNode>(ten, ComparatorOperator::NEQ, y);
//
//		std::shared_ptr<PredicateNode> predLeft = std::make_shared<PredicateNode>(relLhs);
//		std::shared_ptr<PredicateNode> predRight = std::make_shared<PredicateNode>(relRhs);
//
//		PredicateNode pred1(predLeft, ConditionalOperator::AND, predRight);
//		PredicateNode pred2(predLeft, ConditionalOperator::AND, predRight);
//		PredicateNode pred3(predRight, ConditionalOperator::AND, predLeft);
//		PredicateNode pred4(predLeft, ConditionalOperator::OR, predRight);
//
//		REQUIRE(pred1 == pred2);
//		REQUIRE(pred1 != pred3);
//		REQUIRE(pred1 != pred4);
//
//		REQUIRE(pred1.isTerminalPredicate() == false);
//		REQUIRE(pred1.isNotPredicate() == false);
//		REQUIRE(pred1.isFullPredicate() == true);
//
//		//legal accesses
//		REQUIRE_NOTHROW(pred1.getLhs());
//		REQUIRE_NOTHROW(pred1.getRhs());
//
//		//illegal accesses
//		REQUIRE_THROWS_WITH(pred1.getRelExprNode(), "Predicate is not a terminal predicate");
//		REQUIRE_THROWS_WITH(pred1.getRelLhs(), "Predicate is not a terminal predicate");
//		REQUIRE_THROWS_WITH(pred1.getRelRhs(), "Predicate is not a terminal predicate");
//	}
//}
//
//TEST_CASE("Test IO statement nodes") {
//	std::shared_ptr<VariableNode> var1 = std::make_shared<VariableNode>("x");
//	std::shared_ptr<VariableNode> var2 = std::make_shared<VariableNode>("y");
//
//	PrintNode print(45, var1);
//	REQUIRE(print.isPrintNode() == true);
//	REQUIRE(print.getVariable()->isVariableNode() == true);
//
//	ReadNode read(10, var2);
//	REQUIRE(read.isReadNode() == true);
//	REQUIRE(read.getVariable()->isVariableNode() == true);
//}
//
//TEST_CASE("TestIfNode") {
//	SECTION("Single If") {
//		/*
//		if (x > 0) then {
//			read x;
//		} else {
//			print x;
//		}
//		*/
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<ConstantNode> zero = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<RelExprNode> rel1 = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, zero);
//		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel1);
//
//		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(1, x);
//		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(2, x);
//
//		std::vector<std::shared_ptr<StmtNode>> thenStmtLst;
//		thenStmtLst.push_back(read);
//
//		std::vector<std::shared_ptr<StmtNode>> elseStmtLst;
//		elseStmtLst.push_back(print);
//
//		IfNode ifs1(1, pred, thenStmtLst, elseStmtLst);
//		IfNode ifs2(2, pred, thenStmtLst, elseStmtLst);
//		IfNode ifs3(1, pred, elseStmtLst, thenStmtLst);
//
//		REQUIRE(ifs1 == ifs1);
//		REQUIRE(ifs1 != ifs2);
//		REQUIRE(ifs1 != ifs3);
//	}
//
//	SECTION("Nested If") {
//		/*
//		if (x > 0) then {
//			if (y == 1) then {
//				print y;
//			} else {}
//			read x;
//		} else {
//			print x;
//		}
//		*/
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<ConstantNode> zero = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<RelExprNode> outerRel = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, zero);
//		std::shared_ptr<PredicateNode> outerPred = std::make_shared<PredicateNode>(outerRel);
//
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("one");
//		std::shared_ptr<RelExprNode> innerRel = std::make_shared<RelExprNode>(y, ComparatorOperator::EQ, one);
//		std::shared_ptr<PredicateNode> innerPred = std::make_shared<PredicateNode>(innerRel);
//
//		std::shared_ptr<PrintNode> printx = std::make_shared<PrintNode>(1, x);
//		std::shared_ptr<PrintNode> printy = std::make_shared<PrintNode>(1, y);
//		std::shared_ptr<ReadNode> readx = std::make_shared<ReadNode>(2, x);
//
//		std::vector<std::shared_ptr<StmtNode>> innerThenStmtLst;
//		std::vector<std::shared_ptr<StmtNode>> innerElseStmtLst;
//		innerThenStmtLst.push_back(printy);
//
//		std::shared_ptr<IfNode> innerIf = std::make_shared<IfNode>(1, innerPred, innerThenStmtLst, innerElseStmtLst);
//		//random line to replace innerIf
//		std::shared_ptr<ReadNode> ready = std::make_shared<ReadNode>(1, y);
//
//		std::vector<std::shared_ptr<StmtNode>> outerThenStmtLst;
//		std::vector<std::shared_ptr<StmtNode>> outerElseStmtLst;
//		outerThenStmtLst.push_back(innerIf);
//		outerThenStmtLst.push_back(readx);
//		outerElseStmtLst.push_back(printx);
//
//		// completely wrong stmtList
//		std::vector<std::shared_ptr<StmtNode>> outerWrongThenStmtLst;
//		outerWrongThenStmtLst.push_back(ready);
//		outerWrongThenStmtLst.push_back(readx);
//
//		// stmtList wrong order
//		std::vector<std::shared_ptr<StmtNode>> outerWrongOrderThenStmtLst;
//		outerWrongOrderThenStmtLst.push_back(readx);
//		outerWrongOrderThenStmtLst.push_back(innerIf);
//
//		IfNode ifs1(1, outerPred, outerThenStmtLst, outerElseStmtLst);
//		IfNode ifs2(1, outerPred, outerElseStmtLst, outerThenStmtLst);
//		IfNode ifs3(1, outerPred, outerWrongThenStmtLst, outerElseStmtLst);
//		IfNode ifs4(1, outerPred, outerWrongOrderThenStmtLst, outerElseStmtLst);
//
//		REQUIRE(ifs1 == ifs1);
//		REQUIRE(ifs1 != ifs2);
//		REQUIRE(ifs1 != ifs3);
//		REQUIRE(ifs1 != ifs4);
//	}
//}
//
//TEST_CASE("TestWhileNode") {
//	SECTION("Single While") {
//		/*
//		while (x > 0) {
//			read x;
//		}
//		*/
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<ConstantNode> zero = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<RelExprNode> rel1 = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, zero);
//		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel1);
//
//		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(1, x);
//
//		std::vector<std::shared_ptr<StmtNode>> stmtLst;
//		stmtLst.push_back(read);
//
//		WhileNode while1(1, pred, stmtLst);
//		WhileNode while2(2, pred, stmtLst);
//		//empty stmtList
//		std::vector<std::shared_ptr<StmtNode>> emptyStmtLst;
//		WhileNode while3(1, pred, emptyStmtLst);
//
//		REQUIRE(while1 == while1);
//		REQUIRE(while1 != while2);
//		REQUIRE(while1 != while3);
//	}
//	
//	SECTION("Nested While") {
//		/*
//		while (x > 0)  {
//			while (y < 1) {
//				print y;
//			}
//			read y;
//		}
//		*/
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<ConstantNode> zero = std::make_shared<ConstantNode>("0");
//		std::shared_ptr<RelExprNode> outerRel = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, zero);
//		std::shared_ptr<PredicateNode> outerPred = std::make_shared<PredicateNode>(outerRel);
//
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("one");
//		std::shared_ptr<RelExprNode> innerRel = std::make_shared<RelExprNode>(y, ComparatorOperator::LT, one);
//		std::shared_ptr<PredicateNode> innerPred = std::make_shared<PredicateNode>(innerRel);
//
//		std::shared_ptr<PrintNode> printy = std::make_shared<PrintNode>(1, y);
//		std::shared_ptr<ReadNode> ready = std::make_shared<ReadNode>(2, y);
//
//		std::vector<std::shared_ptr<StmtNode>> innerStmtLst;
//		innerStmtLst.push_back(printy);
//
//		std::shared_ptr<WhileNode> innerWhile = std::make_shared<WhileNode>(1, innerPred, innerStmtLst);
//		//random line to replace innerWhile
//		std::shared_ptr<ReadNode> ready2 = std::make_shared<ReadNode>(1, y);
//
//		std::vector<std::shared_ptr<StmtNode>> outerStmtLst;
//		outerStmtLst.push_back(innerWhile);
//		outerStmtLst.push_back(ready);
//
//		// completely wrong stmtList
//		std::vector<std::shared_ptr<StmtNode>> outerWrongStmtLst;
//		outerWrongStmtLst.push_back(ready2);
//		outerWrongStmtLst.push_back(ready);
//
//		// stmtList wrong order
//		std::vector<std::shared_ptr<StmtNode>> outerWrongOrderStmtLst;
//		outerWrongOrderStmtLst.push_back(ready);
//		outerWrongOrderStmtLst.push_back(innerWhile);
//
//		WhileNode while1(1, outerPred, outerStmtLst);
//		WhileNode while2(1, outerPred, outerWrongStmtLst);
//		WhileNode while3(1, outerPred, outerWrongOrderStmtLst);
//
//		REQUIRE(while1 == while1);
//		REQUIRE(while1 != while2);
//		REQUIRE(while1 != while3);
//	}
//}
//
//TEST_CASE("Test Procedure nodes") {
//	std::shared_ptr<VariableNode> var1 = std::make_shared<VariableNode>("x");
//	std::shared_ptr<VariableNode> var2 = std::make_shared<VariableNode>("y");
//
//	std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(1, var1);
//	std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(2, var2);
//
//	std::vector<std::shared_ptr<StmtNode>> stmtLst;
//	stmtLst.push_back(print);
//	stmtLst.push_back(read);
//
//	REQUIRE(stmtLst[0]->isPrintNode() == true);
//	REQUIRE(stmtLst[1]->isReadNode() == true);
//
//	//test down casting
//	std::shared_ptr<StmtNode> s1 = stmtLst[0];
//	std::shared_ptr<PrintNode> p1 = std::dynamic_pointer_cast<PrintNode>(s1);
//	std::shared_ptr<StmtNode> s2 = stmtLst[1];
//	std::shared_ptr<ReadNode> p2 = std::dynamic_pointer_cast<ReadNode>(s2);
//
//	REQUIRE(p1->getVariable()->isVariableNode() == true);
//	REQUIRE(p2->getVariable()->isVariableNode() == true);
//
//	std::shared_ptr<ProcedureNode> p = std::make_shared<ProcedureNode>(stmtLst, "testing");
//	REQUIRE(p->isProcedureNode() == true);
//	REQUIRE(p->getStmtList()[0]->isPrintNode() == true);
//	REQUIRE(p->getStmtList()[1]->isReadNode() == true);
}