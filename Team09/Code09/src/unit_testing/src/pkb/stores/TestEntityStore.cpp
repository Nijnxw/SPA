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

		entityStore.addStatementWithType(EntityType::READ, 2);
		entityStore.addStatementWithType(EntityType::PRINT, 3);
		entityStore.addStatementWithType(EntityType::IF, 4);
		entityStore.addStatementWithType(EntityType::WHILE, 7);
		entityStore.addStatementWithType(EntityType::CALL, 10);

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

		// getAssignStatements()
		SECTION("getAssignStatements() positive query") {
			std::unordered_map<int, AssignStatement> res = entityStore.getAssignStatements();

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
	}
	entityStore.clear();
}
