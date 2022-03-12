#include "catch.hpp"
#include "pkb/stores/EntityStore.h"

TEST_CASE("EntityStore API") {
	EntityStore entityStore;
	// The same store is reused through tests, so clearing is a must.
	entityStore.clear();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		entityStore.addProcedure("simplestSIMPLE");
		
		entityStore.addVariable("a");
		entityStore.addVariable("b");
		entityStore.addVariable("c");
		entityStore.addVariable("d");
		entityStore.addVariable("r");
		entityStore.addVariable("pn");
		entityStore.addVariable("true");
		entityStore.addVariable("such");
		entityStore.addVariable("that");
		entityStore.addVariable("team9");
		entityStore.addVariable("pattern");
		entityStore.addVariable("nice");
		entityStore.addVariable("false");

		entityStore.addConstant("1");
		entityStore.addConstant("2");
		entityStore.addConstant("34");
		entityStore.addConstant("235");

		entityStore.addStatementNumber(1);
		entityStore.addStatementNumber(2);
		entityStore.addStatementNumber(3);
		entityStore.addStatementNumber(4);
		entityStore.addStatementNumber(5);
		entityStore.addStatementNumber(6);
		entityStore.addStatementNumber(7);
		entityStore.addStatementNumber(8);
		entityStore.addStatementNumber(9);
		entityStore.addStatementNumber(10);

		entityStore.addAssignStatement(1, "a", "a 1 b / 2 * c / + d -");
		entityStore.addAssignStatement(5, "such", "that team9 +");
		entityStore.addAssignStatement(6, "pattern", "nice");
		entityStore.addAssignStatement(8, "aPlus", "true");
		entityStore.addAssignStatement(9, "d", "34 235 * c +");

		entityStore.addReadStatement(2, "r");
		entityStore.addPrintStatement(3, "pn");
		std::unordered_set<std::string> ifConditionalVariables = { "true" };
		entityStore.addIfStatement(4, ifConditionalVariables);
		std::unordered_set<std::string> whileConditionalVariables = { "a", "false"};
		entityStore.addWhileStatement(7, whileConditionalVariables);
		entityStore.addCallStatement(10, "TEST");

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------
		// getProcedures()
		SECTION("getProcedures() positive query") {
			std::unordered_set<std::string> res = entityStore.getProcedures();
			std::unordered_set<std::string> expectedSet = {"simplestSIMPLE"};
			REQUIRE(res == expectedSet);
		}

		// getVariables()
		SECTION("getVariables() positive query") {
			std::unordered_set<std::string> res = entityStore.getVariables();
			std::unordered_set<std::string> expectedSet = { "a", "b", "c", "d", "r", "pn", "true", "such",
				"that", "team9", "pattern", "nice", "false"};
			REQUIRE(res == expectedSet);
		}

		// getConstants()
		SECTION("getConstants() positive query") {
			std::unordered_set<std::string> res = entityStore.getConstants();
			std::unordered_set<std::string> expectedSet = { "1", "2", "34", "235"};
			REQUIRE(res == expectedSet);
		}

		// getStatementNumbers()
		SECTION("getStatementNumbers() positive query") {
			std::unordered_set<int> res = entityStore.getStatementNumbers();
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			REQUIRE(res == expectedSet);
		}

		// getAssignStatementsToStructs()
		SECTION("getAssignStatementsToStructs() positive query") {
			std::unordered_map<int, AssignStatement> res = entityStore.getAssignStatementsToStructs();

			AssignStatement assignStatementOne(1, "a", "a 1 b / 2 * c / + d -");
			AssignStatement assignStatementTwo(5, "such", "that team9 +");
			AssignStatement assignStatementThree(6, "pattern", "nice");
			AssignStatement assignStatementFour(8, "aPlus", "true");
			AssignStatement assignStatementFive(9, "d", "34 235 * c +");

			std::unordered_map<int, AssignStatement> expectedMap;
			expectedMap.insert({ 1, assignStatementOne });
			expectedMap.insert({ 5, assignStatementTwo });
			expectedMap.insert({ 6, assignStatementThree });
			expectedMap.insert({ 8, assignStatementFour });
			expectedMap.insert({ 9, assignStatementFive });

			REQUIRE(res == expectedMap);
		}

		// getIfStatementsToConditionalVariables()
		SECTION("getIfStatementsToConditionalVariables() positive query") {
			std::unordered_map<int, std::unordered_set<std::string>> res = entityStore.getIfStatementsToConditionalVariables();

			std::unordered_map<int, std::unordered_set<std::string>> expectedMap;
			std::unordered_set<std::string> conditionalVariables = { "true" };
			expectedMap.insert({ 4, conditionalVariables });

			REQUIRE(res == expectedMap);
		}

		// getWhileStatementsToConditionalVariables()
		SECTION("getWhileStatementsToConditionalVariables() positive query") {
			std::unordered_map<int, std::unordered_set<std::string>> res = entityStore.getWhileStatementsToConditionalVariables();

			std::unordered_map<int, std::unordered_set<std::string>> expectedMap;
			std::unordered_set<std::string> conditionalVariables = { "a", "false" };
			expectedMap.insert({ 7, conditionalVariables });

			REQUIRE(res == expectedMap);
		}

		// getCallStatementsToProcedures()
		SECTION("getCallStatementsToProcedures() positive query") {
			std::unordered_map<int, std::string> res = entityStore.getCallStatementsToProcedures();

			std::unordered_map<int, std::string> expectedMap;
			expectedMap.insert({ 10, "TEST" });

			REQUIRE(res == expectedMap);
		}

		// getPrintStatementsToVariables()
		SECTION("getPrintStatementsToVariables() positive query") {
			std::unordered_map<int, std::string> res = entityStore.getPrintStatementsToVariables();

			std::unordered_map<int, std::string> expectedMap;
			expectedMap.insert({ 3, "pn" });

			REQUIRE(res == expectedMap);
		}

		// getReadStatementsToVariables()
		SECTION("getReadStatementsToVariables() positive query") {
			std::unordered_map<int, std::string> res = entityStore.getReadStatementsToVariables();

			std::unordered_map<int, std::string> expectedMap;
			expectedMap.insert({ 2, "r" });

			REQUIRE(res == expectedMap);
		}

		// getStatementsWithType() ASSIGN
		SECTION("getStatementsWithType() ASSIGN positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::ASSIGN);
			std::unordered_set<int> expectedSet = { 1, 5, 6, 8, 9 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() IF
		SECTION("getStatementsWithType() IF positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::IF);
			std::unordered_set<int> expectedSet = { 4 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() WHILE
		SECTION("getStatementsWithType() WHILE positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::WHILE);
			std::unordered_set<int> expectedSet = { 7 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() PRINT
		SECTION("getStatementsWithType() PRINT positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::PRINT);
			std::unordered_set<int> expectedSet = { 3 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() READ
		SECTION("getStatementsWithType() READ positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::READ);
			std::unordered_set<int> expectedSet = { 2 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() CALL
		SECTION("getStatementsWithType() CALL positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::CALL);
			std::unordered_set<int> expectedSet = { 10 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() CALL
		SECTION("getStatementsWithType() CALL positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::CALL);
			std::unordered_set<int> expectedSet = { 10 };
			REQUIRE(res == expectedSet);
		}
		// getPrintVariables();
		SECTION("getPrintVariables() positive query") {
			std::unordered_set<std::string> res = entityStore.getPrintVariables();
			std::unordered_set<std::string> expectedSet = { "pn" };
			REQUIRE(res == expectedSet);
		}
		// getReadVariables();
		SECTION("getReadVariables() positive query") {
			std::unordered_set<std::string> res = entityStore.getReadVariables();
			std::unordered_set<std::string> expectedSet = { "r" };
			REQUIRE(res == expectedSet);
		}
		// getProceduresToCallStatements();
		SECTION("getProceduresToCallStatements() positive query") {
			std::unordered_map<std::string, std::unordered_set<int>> res = entityStore.getProceduresToCallStatements();
			std::unordered_map<std::string, std::unordered_set<int>> expectedMap = {{"TEST", { 10 }}};
			REQUIRE(res == expectedMap);
		}
		// getVariablesToPrintStatements();
		SECTION("getVariablesToPrintStatements() positive query") {
			std::unordered_map<std::string, std::unordered_set<int>> res = entityStore.getVariablesToPrintStatements();
			std::unordered_map<std::string, std::unordered_set<int>> expectedMap = {{"pn", { 3 }}};
			REQUIRE(res == expectedMap);
		}
		// getVariablesToReadStatements();
		SECTION("getVariablesToReadStatements() positive query") {
			std::unordered_map<std::string, std::unordered_set<int>> res = entityStore.getVariablesToReadStatements();
			std::unordered_map<std::string, std::unordered_set<int>> expectedMap = {{"r", { 2 }}};
			REQUIRE(res == expectedMap);
		}
	}
	entityStore.clear();
}
