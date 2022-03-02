#include "catch.hpp"
#include "pkb/stores/ParentStore.h"

TEST_CASE("ParentStore API") {
	ParentStore parentStore;
	// The same store is reused through tests, so clearing is a must.
	parentStore.clear();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		parentStore.addRelationship(4, 5);
		parentStore.addRelationship(4, 6);
		parentStore.addRelationship(7, 8);

		parentStore.addRelationshipT(4, 5);
		parentStore.addRelationshipT(4, 6);
		parentStore.addRelationshipT(7, 8);

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------
		// hasRelationship()
		SECTION("hasRelationship() positive query") {
			bool res = parentStore.hasRelationship();
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		// hasTRelationship()
		SECTION("hasTRelationship() positive query") {
			bool res = parentStore.hasTRelationship();
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		// isRelationship()
		SECTION("isRelationship() positive query") {
			bool res = parentStore.isRelationship(4, 5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid ordering") {
			bool res = parentStore.isRelationship(5, 4);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid statement numbers") {
			bool res = parentStore.isRelationship(-10, 999);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isRelationshipT()
		SECTION("isRelationshipT() positive query - non-transitive") {
			bool res = parentStore.isTRelationship(4, 5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() positive query - transitive") {
			bool res = parentStore.isTRelationship(4, 5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() negative query - invalid ordering") {
			bool res = parentStore.isTRelationship(5, 4);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() negative query - invalid statements") {
			bool res = parentStore.isTRelationship(-10, 999);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstStatement()
		SECTION("isFirstStatement() positive query") {
			bool res = parentStore.isFirstStatement(4);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatement() negative query - second statement") {
			bool res = parentStore.isFirstStatement(5);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatement() negative query - invalid statement") {
			bool res = parentStore.isFirstStatement(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondStatement()
		SECTION("isSecondStatement() positive query") {
			bool res = parentStore.isSecondStatement(5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatement() negative query - first statement") {
			bool res = parentStore.isSecondStatement(4);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatement() negative query - invalid statement") {
			bool res = parentStore.isSecondStatement(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstStatementT()
		SECTION("isFirstStatementT() positive query") {
			bool res = parentStore.isFirstStatementT(4);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatementT() negative query - second statement") {
			bool res = parentStore.isFirstStatementT(5);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatementT() negative query - invalid statement") {
			bool res = parentStore.isFirstStatementT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondStatementT()
		SECTION("isSecondStatementT() positive query") {
			bool res = parentStore.isSecondStatementT(5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatementT() negative query - first statement") {
			bool res = parentStore.isSecondStatementT(4);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatementT() negative query - invalid statement") {
			bool res = parentStore.isSecondStatementT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// getFirstStatements
		SECTION("getFirstStatements(int secondStatement) positive query") {
			std::unordered_set<int> res = parentStore.getFirstStatements(5);
			std::unordered_set<int> expectedSet = { 4 };
			REQUIRE(res == expectedSet);
		}

		// getSecondStatements
		SECTION("getSecondStatements(int firstStatement) positive query") {
			std::unordered_set<int> res = parentStore.getSecondStatements(4);
			std::unordered_set<int> expectedSet = { 5, 6 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondStatements(int firstStatement) negative query - last statement as first statement") {
			std::unordered_set<int> res = parentStore.getSecondStatements(5);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getFirstStatementsT
		SECTION("getFirstStatementsT(int secondStatement) positive query - non-transitive") {
			std::unordered_set<int> res = parentStore.getFirstStatementsT(5);
			std::unordered_set<int> expectedSet = { 4 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstStatementsT(int secondStatement) positive query - transitive") {
			std::unordered_set<int> res = parentStore.getFirstStatementsT(5);
			std::unordered_set<int> expectedSet = { 4 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstStatementsT(int secondStatement) negative query - first statement as second statement") {
			std::unordered_set<int> res = parentStore.getFirstStatementsT(4);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondStatementsT
		SECTION("getSecondStatementsT(int firstStatement) positive query - transitive") {
			std::unordered_set<int> res = parentStore.getSecondStatementsT(4);
			std::unordered_set<int> expectedSet = { 5, 6 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondStatementsT(int firstStatement) negative query - last statement as first statement") {
			std::unordered_set<int> res = parentStore.getSecondStatementsT(5);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getAllFirstStatements
		SECTION("getAllFirstStatements() positive query") {
			std::unordered_set<int> res = parentStore.getAllFirstStatements();
			std::unordered_set<int> expectedSet = { 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondStatements
		SECTION("getAllSecondStatements() positive query") {
			std::unordered_set<int> res = parentStore.getAllSecondStatements();
			std::unordered_set<int> expectedSet = { 5, 6, 8 };
			REQUIRE(res == expectedSet);
		}

		// getAllFirstStatementsT
		SECTION("getAllFirstStatementsT() positive query") {
			std::unordered_set<int> res = parentStore.getAllFirstStatementsT();
			std::unordered_set<int> expectedSet = { 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondStatementsT
		SECTION("getAllSecondStatements() positive query") {
			std::unordered_set<int> res = parentStore.getAllSecondStatementsT();
			std::unordered_set<int> expectedSet = { 5, 6, 8 };
			REQUIRE(res == expectedSet);
		}

		// getAllRelationshipPairs
		SECTION("getAllRelationshipPairs() positive query") {
			std::tuple<std::vector<int>, std::vector<int>> res = parentStore.getAllRelationshipPairs();

			std::vector<int> firstColumn;
			std::vector<int> secondColumn;

			firstColumn.push_back(4);
			secondColumn.push_back(5);

			firstColumn.push_back(4);
			secondColumn.push_back(6);

			firstColumn.push_back(7);
			secondColumn.push_back(8);

			std::tuple<std::vector<int>, std::vector<int>> expectedRes = { firstColumn, secondColumn };
			
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> set = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> expectedSet = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		// getAllRelationshipPairsT
		SECTION("getAllRelationshipPairsT() positive query") {
			std::tuple<std::vector<int>, std::vector<int>> res = parentStore.getAllRelationshipTPairs();

			std::vector<int> firstColumn;
			std::vector<int> secondColumn;

			firstColumn.push_back(4);
			secondColumn.push_back(5);

			firstColumn.push_back(4);
			secondColumn.push_back(6);

			firstColumn.push_back(7);
			secondColumn.push_back(8);

			std::tuple<std::vector<int>, std::vector<int>> expectedRes = { firstColumn, secondColumn };
			
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> set = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> expectedSet = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}
	}
	parentStore.clear();
}
