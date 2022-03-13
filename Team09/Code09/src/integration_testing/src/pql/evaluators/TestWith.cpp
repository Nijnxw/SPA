#include "catch.hpp"
#include "PQL/evaluators/WithEvaluator.h"

TEST_CASE("WithRelationship API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();
	WithEvaluator withEvaluator = WithEvaluator();

	/*
	procedure First1{
	01	read x;
	02	read First1;
	03	call Second2; }

	procedure Second2{
	04        x = 0;
	05        i = 5;
	06        while (i != 14) {
	07            x = x + 2 * y;
	08            call Third3;
	09            i = i - 477;
	 }
	10        if (x == 1) then {
	11            x = Second2 + 12 + 6 + 10; }
			  else {
	12            z = 3;
	 }
	13        z = z + 5 + i;
	14        print Second2;
	15        x = x * y + 7; }

	procedure Third3{
	16	z = 5;
	17	v = z;
	18	print x; }
	*/


	SECTION("Initialization of program variables") {
		/*
			NAME
			procedure.procName
			call.procName
			variable.varName
			read.varName
			print.varName
			INTEGER
			constant.value
			stmt.stmt#
			read.stmt#
			print.stmt#
			call.stmt#
			while.stmt#
			if.stmt#
			assign.stmt#
		*/
		PKB::addProcedure("First1");
		PKB::addProcedure("Second2");
		PKB::addProcedure("Third3");

		PKB::addStatementNumber(1);
		PKB::addReadStatement(1, "x");
		PKB::addVariable("x");

		PKB::addStatementNumber(2);
		PKB::addReadStatement(2, "First1");
		PKB::addVariable("First1");

		PKB::addStatementNumber(3);
		PKB::addCallStatement(3, "Second2");
		PKB::addCalls("First1", "Second2");

		PKB::addStatementNumber(4);
		PKB::addAssignStatement(4, "<LHS>", "<RHS>");
		PKB::addVariable("x");
		PKB::addConstant("0");

		PKB::addStatementNumber(5);
		PKB::addAssignStatement(5, "<LHS>", "<RHS>");
		PKB::addVariable("i");
		PKB::addConstant("5");

		PKB::addStatementNumber(6);
		PKB::addWhileStatement(6, { "i" });
		PKB::addVariable("i");
		PKB::addConstant("14");

		PKB::addStatementNumber(7);
		PKB::addAssignStatement(7, "<LHS>", "<RHS>");
		PKB::addVariable("x");
		PKB::addVariable("y");
		PKB::addConstant("2");

		PKB::addStatementNumber(8);
		PKB::addCallStatement(8, "Third3");
		PKB::addCalls("Second2", "Third3");


		PKB::addStatementNumber(9);
		PKB::addAssignStatement(9, "<LHS>", "<RHS>");
		PKB::addVariable("i");
		PKB::addConstant("477");

		PKB::addStatementNumber(10);
		PKB::addIfStatement(10, { "x" });
		PKB::addVariable("x");
		PKB::addConstant("1");

		PKB::addStatementNumber(11);
		PKB::addAssignStatement(11, "<LHS>", "<RHS>");
		PKB::addVariable("x");
		PKB::addVariable("Second2");
		PKB::addConstant("12");
		PKB::addConstant("6");
		PKB::addConstant("10");


		PKB::addStatementNumber(12);
		PKB::addAssignStatement(12, "<LHS>", "<RHS>");
		PKB::addVariable("z");
		PKB::addConstant("3");

		PKB::addStatementNumber(13);
		PKB::addAssignStatement(13, "<LHS>", "<RHS>");
		PKB::addVariable("z");
		PKB::addVariable("i");
		PKB::addConstant("5");

		PKB::addStatementNumber(14);
		PKB::addPrintStatement(14, "Second2");

		PKB::addStatementNumber(15);
		PKB::addAssignStatement(15, "<LHS>", "<RHS>");
		PKB::addVariable("x");
		PKB::addVariable("y");
		PKB::addConstant("7");

		PKB::addStatementNumber(16);
		PKB::addAssignStatement(16, "<LHS>", "<RHS>");
		PKB::addVariable("z");
		PKB::addConstant("5");

		PKB::addStatementNumber(17);
		PKB::addAssignStatement(17, "<LHS>", "<RHS>");
		PKB::addVariable("v");
		PKB::addVariable("z");

		PKB::addStatementNumber(18);
		PKB::addPrintStatement(18, "x");
		PKB::addVariable("x");



		// --------------------------------------------------
		//                  String = String
		// --------------------------------------------------
		SECTION("with 'str1' = 'str1' positive query") {
			QueryClauseResult res = withEvaluator.getWith("str1", EntityType::STRING, AttributeRef::NONE, "str1", EntityType::STRING, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == true);
		}
		SECTION("with 'str1' = 'str2' negative query") {
			QueryClauseResult res = withEvaluator.getWith("str1", EntityType::STRING, AttributeRef::NONE, "str2", EntityType::STRING, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//                  Integer = Integer
		// --------------------------------------------------
		SECTION("with 4 = 4 positive query") {
			QueryClauseResult res = withEvaluator.getWith("4", EntityType::INT, AttributeRef::NONE, "4", EntityType::INT, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == true);
		}
		SECTION("with 444 = 445 negative query") {
			QueryClauseResult res = withEvaluator.getWith("444", EntityType::INT, AttributeRef::NONE, "445", EntityType::INT, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//                Invalid Primitive Types
		// --------------------------------------------------
		SECTION("with 'str1' = 2 negative query") {
			QueryClauseResult res = withEvaluator.getWith("str1", EntityType::STRING, AttributeRef::NONE, "2", EntityType::INT, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}
		SECTION("with 2 = 'str2' negative query") {
			QueryClauseResult res = withEvaluator.getWith("2", EntityType::INT, AttributeRef::NONE, "str2", EntityType::STRING, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}
		SECTION("with WILD = ASSIGN negative query") {
			QueryClauseResult res = withEvaluator.getWith("a", EntityType::WILD, AttributeRef::NONE, "b", EntityType::ASSIGN, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}
		SECTION("with CALL = READ negative query") {
			QueryClauseResult res = withEvaluator.getWith("a", EntityType::CALL, AttributeRef::NONE, "b", EntityType::READ, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}
		SECTION("with CONST = WHILE negative query") {
			QueryClauseResult res = withEvaluator.getWith("a", EntityType::CONST, AttributeRef::NONE, "b", EntityType::WHILE, AttributeRef::NONE, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//              Matching String Attr Ref
		// --------------------------------------------------
		SECTION("with procedure.procName = procedure.procName same syn") {
			QueryClauseResult res = withEvaluator.getWith("p", EntityType::PROC, AttributeRef::PROC_NAME, "p", EntityType::PROC, AttributeRef::PROC_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p", {"First1", "Second2", "Third3"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with procedure.procName = procedure.procName diff syn") {
			QueryClauseResult res = withEvaluator.getWith("p1", EntityType::PROC, AttributeRef::PROC_NAME, "p2", EntityType::PROC, AttributeRef::PROC_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p1", {"First1", "Second2", "Third3"}},
				{"p2", {"First1", "Second2", "Third3"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with procedure.procName = call.procName") {
			QueryClauseResult res = withEvaluator.getWith("p", EntityType::PROC, AttributeRef::PROC_NAME, "c", EntityType::CALL, AttributeRef::PROC_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p", {"Second2", "Third3"}},
				{"c", {"3", "8"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with procedure.procName = variable.varName") {
			QueryClauseResult res = withEvaluator.getWith("p", EntityType::PROC, AttributeRef::PROC_NAME, "v", EntityType::VAR, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p", {"First1", "Second2"}},
				{"v", {"First1", "Second2"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with procedure.procName = read.varName") {
			QueryClauseResult res = withEvaluator.getWith("p", EntityType::PROC, AttributeRef::PROC_NAME, "r", EntityType::READ, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p", {"First1"}},
				{"r", {"2"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with procedure.procName = print.varName") {
			QueryClauseResult res = withEvaluator.getWith("p", EntityType::PROC, AttributeRef::PROC_NAME, "pn", EntityType::PRINT, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p", {"Second2"}},
				{"pn", {"14"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with call.procName = call.procName same syn") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CALL, AttributeRef::PROC_NAME, "c", EntityType::CALL, AttributeRef::PROC_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", {"3", "8"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with call.procName = call.procName diff syn") {
			QueryClauseResult res = withEvaluator.getWith("c1", EntityType::CALL, AttributeRef::PROC_NAME, "c2", EntityType::CALL, AttributeRef::PROC_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c1", {"3", "8"}},
				{"c2", {"3", "8"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with call.procName = variable.varName") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CALL, AttributeRef::PROC_NAME, "v", EntityType::VAR, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", {"3"}},
				{"v", {"Second2"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with call.procName = read.varName") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CALL, AttributeRef::PROC_NAME, "r", EntityType::READ, AttributeRef::VAR_NAME, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}
		SECTION("with call.procName = print.varName") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CALL, AttributeRef::PROC_NAME, "pn", EntityType::PRINT, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", {"3"}},
				{"pn", {"14"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with variable.varName = variable.varName same syn") {
			QueryClauseResult res = withEvaluator.getWith("v", EntityType::VAR, AttributeRef::VAR_NAME, "v", EntityType::VAR, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"v", {"x", "First1", "i", "y", "Second2", "z", "v"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with variable.varName = variable.varName diff syn") {
			QueryClauseResult res = withEvaluator.getWith("v1", EntityType::VAR, AttributeRef::VAR_NAME, "v2", EntityType::VAR, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"v1", {"x", "First1", "i", "y", "Second2", "z", "v"}},
				{"v2", {"x", "First1", "i", "y", "Second2", "z", "v"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with variable.varName = read.varName") {
			QueryClauseResult res = withEvaluator.getWith("v", EntityType::VAR, AttributeRef::VAR_NAME, "r", EntityType::READ, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"v", {"x", "First1"}},
				{"r", {"1", "2"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with variable.varName = print.varName") {
			QueryClauseResult res = withEvaluator.getWith("v", EntityType::VAR, AttributeRef::VAR_NAME, "pn", EntityType::PRINT, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"v", {"Second2", "x"}},
				{"pn", {"14", "18"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with read.varName = read.varName same syn") {
			QueryClauseResult res = withEvaluator.getWith("r", EntityType::READ, AttributeRef::VAR_NAME, "r", EntityType::READ, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"r", {"1", "2"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with read.varName = read.varName diff syn") {
			QueryClauseResult res = withEvaluator.getWith("r1", EntityType::READ, AttributeRef::VAR_NAME, "r2", EntityType::READ, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"r1", {"1", "2"}},
				{"r2", {"1", "2"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with read.varName = print.varName") {
			QueryClauseResult res = withEvaluator.getWith("r", EntityType::READ, AttributeRef::VAR_NAME, "pn", EntityType::PRINT, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"r", {"1"}},
				{"pn", {"18"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with print.varName = print.varName same syn") {
			QueryClauseResult res = withEvaluator.getWith("pn", EntityType::PRINT, AttributeRef::VAR_NAME, "pn", EntityType::PRINT, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"pn", {"14", "18"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with print.varName = print.varName diff syn") {
			QueryClauseResult res = withEvaluator.getWith("pn1", EntityType::PRINT, AttributeRef::VAR_NAME, "pn2", EntityType::PRINT, AttributeRef::VAR_NAME, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"pn1", {"14", "18"}},
				{"pn2", {"14", "18"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		// --------------------------------------------------
		//              Matching Integer Attr Ref
		// --------------------------------------------------
		/*
			constant.value
			stmt.stmt#
			read.stmt# 
			print.stmt#
			call.stmt#
			while.stmt#
			if.stmt#
			assign.stmt#
		*/
		SECTION("with constant.value = constant.value same syn") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "c", EntityType::CONST, AttributeRef::VALUE, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "0", "5", "2", "3", "477", "1", "14", "12", "7", "6", "10"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = constant.value diff syn") {
			QueryClauseResult res = withEvaluator.getWith("c1", EntityType::CONST, AttributeRef::VALUE, "c2", EntityType::CONST, AttributeRef::VALUE, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c1", { "0", "5", "2", "477", "1", "14", "12", "3", "7", "6", "10" }},
				{"c2", { "0", "5", "2", "477", "1", "14", "12", "3", "7", "6", "10" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = stmt.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "s", EntityType::STMT, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "5", "2", "1", "14", "12", "3", "7", "6", "10" }},
				{"s", { "5", "2", "1", "14", "12", "3", "7", "6", "10" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = read.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "r", EntityType::READ, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "2", "1" }},
				{"r", { "2", "1" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = print.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "pn", EntityType::PRINT, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "14" }},
				{"pn", { "14" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = call.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "ca", EntityType::CALL, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "3" }},
				{"ca", { "3" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = while.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "w", EntityType::WHILE, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "6" }},
				{"w", { "6" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = if.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "if", EntityType::IF, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "10" }},
				{"if", { "10" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with constant.value = assign.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CONST, AttributeRef::VALUE, "a", EntityType::ASSIGN, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "5", "7", "12" }},
				{"a", { "5", "7", "12" }}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = stmt.stmt# same syn") {
			QueryClauseResult res = withEvaluator.getWith("s", EntityType::STMT, AttributeRef::STMT_NO, "s", EntityType::STMT, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = stmt.stmt# diff syn") {
			QueryClauseResult res = withEvaluator.getWith("s1", EntityType::STMT, AttributeRef::STMT_NO, "s2", EntityType::STMT, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s1", { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18" }},
				{"s2", { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = read.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("s", EntityType::STMT, AttributeRef::STMT_NO, "r", EntityType::READ, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", { "1", "2" }},
				{"r", { "1", "2" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = print.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("s", EntityType::STMT, AttributeRef::STMT_NO, "pn", EntityType::PRINT, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", { "14", "18" }},
				{"pn", { "14", "18" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = call.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("s", EntityType::STMT, AttributeRef::STMT_NO, "c", EntityType::CALL, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", { "3", "8" }},
				{"c", { "3", "8" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = while.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("s", EntityType::STMT, AttributeRef::STMT_NO, "w", EntityType::WHILE, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", { "6" }},
				{"w", { "6" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = if.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("s", EntityType::STMT, AttributeRef::STMT_NO, "if", EntityType::IF, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", { "10" }},
				{"if", { "10" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with stmt.stmt# = assign.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("s", EntityType::STMT, AttributeRef::STMT_NO, "a", EntityType::ASSIGN, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", { "4", "5", "7", "9", "11", "12", "13", "15", "16", "17" }},
				{"a", { "4", "5", "7", "9", "11", "12", "13", "15", "16", "17" }},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with read.stmt# = assign.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("r", EntityType::READ, AttributeRef::STMT_NO, "a", EntityType::ASSIGN, AttributeRef::STMT_NO, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}
		SECTION("with call.stmt# = while.stmt#") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CALL, AttributeRef::STMT_NO, "w", EntityType::WHILE, AttributeRef::STMT_NO, false);
			REQUIRE(res.getTable() == Table());
			REQUIRE(res.containsValidResult() == false);
		}
		SECTION("with call.stmt# = call.stmt# same syn") {
			QueryClauseResult res = withEvaluator.getWith("c", EntityType::CALL, AttributeRef::STMT_NO, "c", EntityType::CALL, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", { "3", "8"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		SECTION("with call.stmt# = call.stmt# diff syn") {
			QueryClauseResult res = withEvaluator.getWith("c1", EntityType::CALL, AttributeRef::STMT_NO, "c2", EntityType::CALL, AttributeRef::STMT_NO, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c1", { "3", "8"}},
				{"c2", { "3", "8"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
	}
	PKB::clearAllStores();
}
