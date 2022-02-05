#include "catch.hpp"
#include "pkb/stores/EntityStore.h"

TEST_CASE("EntityStore API") {
	// The same store is reused through tests, so clearing is a must.
	EntityStore::clear();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		EntityStore::addProcedure("testProg");
		
		EntityStore::addVariable("p");
		EntityStore::addVariable("a");
		EntityStore::addVariable("c");
		EntityStore::addVariable("k");
		EntityStore::addVariable("pattern");
		EntityStore::addVariable("ifs");
		EntityStore::addVariable("w");

		EntityStore::addConstant("2");
		EntityStore::addConstant("0");
		EntityStore::addConstant("1");

		EntityStore::addStatementNumber(1);
		EntityStore::addStatementNumber(2);
		EntityStore::addStatementNumber(3);
		EntityStore::addStatementNumber(4);
		EntityStore::addStatementNumber(5);
		EntityStore::addStatementNumber(6);

		EntityStore::addAssignStatement(2, "a", "p 2 *");
		EntityStore::addAssignStatement(4, "pattern", "p a * a * p ifs * + p w * +");
		EntityStore::addAssignStatement(6, "w", "w 1 -");

		EntityStore::addStatementWithType(EntityType::READ, 1);
		EntityStore::addStatementWithType(EntityType::IF, 3);
		EntityStore::addStatementWithType(EntityType::WHILE, 5);

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------
		// getProcedures()
		SECTION("getProcedures() positive query") {
			std::unordered_set<std::string> res = EntityStore::getProcedures();
			std::unordered_set<std::string> expectedTable = {"testProg"};
			REQUIRE(res == expectedTable);
		}

		// getVariables()
		SECTION("getVariables() positive query") {
			std::unordered_set<std::string> res = EntityStore::getVariables();
			std::unordered_set<std::string> expectedTable = { "p", "a", "c", "k", "pattern", "ifs", "w" };
			REQUIRE(res == expectedTable);
		}

		// getConstants()
		SECTION("getConstants() positive query") {
			std::unordered_set<std::string> res = EntityStore::getConstants();
			std::unordered_set<std::string> expectedTable = { "2", "0", "1" };
			REQUIRE(res == expectedTable);
		}

		// getStatementNumbers()
		SECTION("getStatementNumbers() positive query") {
			std::unordered_set<int> res = EntityStore::getStatementNumbers();
			std::unordered_set<int> expectedTable = { 1, 2, 3, 4, 5, 6 };
			REQUIRE(res == expectedTable);
		}

		// getAssignStatements()
		SECTION("getAssignStatements() positive query") {
			std::unordered_map<int, AssignStatement> res = EntityStore::getAssignStatements();
			
			AssignStatement assignStatementOne(2, "a", "p 2 *");
			AssignStatement assignStatementTwo(4, "pattern", "p a * a * p ifs * + p w * +");
			AssignStatement assignStatementThree(6, "w", "w 1 -");

			std::unordered_map<int, AssignStatement> expectedTable;
			expectedTable.insert({ 2, assignStatementOne });
			expectedTable.insert({ 4, assignStatementTwo });
			expectedTable.insert({ 6, assignStatementThree });

			REQUIRE(res == expectedTable);
		}

		// getStatementsWithType() IF
		SECTION("getStatementsWithType() IF positive query") {
			std::unordered_set<int> res = EntityStore::getStatementsWithType(EntityType::IF);
			std::unordered_set<int> expectedTable = { 3 };
			REQUIRE(res == expectedTable);
		}

		// getStatementsWithType() WHILE
		SECTION("getStatementsWithType() WHILE positive query") {
			std::unordered_set<int> res = EntityStore::getStatementsWithType(EntityType::WHILE);
			std::unordered_set<int> expectedTable = { 5 };
			REQUIRE(res == expectedTable);
		}

		// getStatementsWithType() PRINT
		SECTION("getStatementsWithType() PRINT positive query") {
			std::unordered_set<int> res = EntityStore::getStatementsWithType(EntityType::PRINT);
			std::unordered_set<int> expectedTable;
			REQUIRE(res == expectedTable);
		}

		// getStatementsWithType() READ
		SECTION("getStatementsWithType() READ positive query") {
			std::unordered_set<int> res = EntityStore::getStatementsWithType(EntityType::READ);
			std::unordered_set<int> expectedTable = { 1 };
			REQUIRE(res == expectedTable);
		}

		// getStatementsWithType() CALL
		SECTION("getStatementsWithType() CALL positive query") {
			std::unordered_set<int> res = EntityStore::getStatementsWithType(EntityType::CALL);
			std::unordered_set<int> expectedTable;
			REQUIRE(res == expectedTable);
		}
	}
	EntityStore::clear();
}
