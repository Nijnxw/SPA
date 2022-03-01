#include "catch.hpp"
#include "pkb/stores/EntityStore.h"

TEST_CASE("EntityStore API") {
	EntityStore entityStore;
	// The same store is reused through tests, so clearing is a must.
	entityStore.clear();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		entityStore.addProcedure("testProg");
		
		entityStore.addVariable("p");
		entityStore.addVariable("a");
		entityStore.addVariable("c");
		entityStore.addVariable("k");
		entityStore.addVariable("pattern");
		entityStore.addVariable("ifs");
		entityStore.addVariable("w");

		entityStore.addConstant("2");
		entityStore.addConstant("0");
		entityStore.addConstant("1");

		entityStore.addStatementNumber(1);
		entityStore.addStatementNumber(2);
		entityStore.addStatementNumber(3);
		entityStore.addStatementNumber(4);
		entityStore.addStatementNumber(5);
		entityStore.addStatementNumber(6);

		entityStore.addAssignStatement(2, "a", "p 2 *");
		entityStore.addAssignStatement(4, "pattern", "p a * a * p ifs * + p w * +");
		entityStore.addAssignStatement(6, "w", "w 1 -");

		entityStore.addStatementWithType(EntityType::READ, 1);
		entityStore.addStatementWithType(EntityType::IF, 3);
		entityStore.addStatementWithType(EntityType::WHILE, 5);

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------
		// getProcedures()
		SECTION("getProcedures() positive query") {
			std::unordered_set<std::string> res = entityStore.getProcedures();
			std::unordered_set<std::string> expectedSet = {"testProg"};
			REQUIRE(res == expectedSet);
		}

		// getVariables()
		SECTION("getVariables() positive query") {
			std::unordered_set<std::string> res = entityStore.getVariables();
			std::unordered_set<std::string> expectedSet = { "p", "a", "c", "k", "pattern", "ifs", "w" };
			REQUIRE(res == expectedSet);
		}

		// getConstants()
		SECTION("getConstants() positive query") {
			std::unordered_set<std::string> res = entityStore.getConstants();
			std::unordered_set<std::string> expectedSet = { "2", "0", "1" };
			REQUIRE(res == expectedSet);
		}

		// getStatementNumbers()
		SECTION("getStatementNumbers() positive query") {
			std::unordered_set<int> res = entityStore.getStatementNumbers();
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 5, 6 };
			REQUIRE(res == expectedSet);
		}

		// getAssignStatements()
		SECTION("getAssignStatements() positive query") {
			std::unordered_map<int, AssignStatement> res = entityStore.getAssignStatements();
			
			AssignStatement assignStatementOne(2, "a", "p 2 *");
			AssignStatement assignStatementTwo(4, "pattern", "p a * a * p ifs * + p w * +");
			AssignStatement assignStatementThree(6, "w", "w 1 -");

			std::unordered_map<int, AssignStatement> expectedMap;
			expectedMap.insert({ 2, assignStatementOne });
			expectedMap.insert({ 4, assignStatementTwo });
			expectedMap.insert({ 6, assignStatementThree });

			REQUIRE(res == expectedMap);
		}

		// getStatementsWithType() IF
		SECTION("getStatementsWithType() IF positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::IF);
			std::unordered_set<int> expectedSet = { 3 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() WHILE
		SECTION("getStatementsWithType() WHILE positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::WHILE);
			std::unordered_set<int> expectedSet = { 5 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() PRINT
		SECTION("getStatementsWithType() PRINT positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::PRINT);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() READ
		SECTION("getStatementsWithType() READ positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::READ);
			std::unordered_set<int> expectedSet = { 1 };
			REQUIRE(res == expectedSet);
		}

		// getStatementsWithType() CALL
		SECTION("getStatementsWithType() CALL positive query") {
			std::unordered_set<int> res = entityStore.getStatementsWithType(EntityType::CALL);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}
	}
	entityStore.clear();
}
