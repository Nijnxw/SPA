#include "catch.hpp"
#include "pkb/stores/FollowsStore.h"

TEST_CASE("FollowsStore API") {
	FollowsStore followsStore;
	// The same store is reused through tests, so clearing is a must.
	followsStore.clear();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		followsStore.addRelationship(1, 2);
		followsStore.addRelationship(2, 3);
		followsStore.addRelationship(3, 4);
		followsStore.addRelationship(4, 7);
		followsStore.addRelationship(7, 9);

		followsStore.addRelationshipT(1, 2);
		followsStore.addRelationshipT(2, 3);
		followsStore.addRelationshipT(3, 4);
		followsStore.addRelationshipT(4, 7);
		followsStore.addRelationshipT(7, 9);

		followsStore.addRelationshipT(1, 3);
		followsStore.addRelationshipT(1, 4);
		followsStore.addRelationshipT(1, 7);
		followsStore.addRelationshipT(1, 9);

		followsStore.addRelationshipT(2, 4);
		followsStore.addRelationshipT(2, 7);
		followsStore.addRelationshipT(2, 9);

		followsStore.addRelationshipT(3, 7);
		followsStore.addRelationshipT(3, 9);

		followsStore.addRelationshipT(4, 9);

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------
		// hasRelationship()
		SECTION("hasRelationship() positive query") {
			bool res = followsStore.hasRelationship();
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		// hasTRelationship()
		SECTION("hasTRelationship() positive query") {
			bool res = followsStore.hasTRelationship();
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}
		
		// isRelationship()
		SECTION("isRelationship() positive query") {
			bool res = followsStore.isRelationship(1, 2);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid ordering") {
			bool res = followsStore.isRelationship(2, 1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid statement numbers") {
			bool res = followsStore.isRelationship(-10, 999);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isRelationshipT()
		SECTION("isRelationshipT() positive query - non-transitive") {
			bool res = followsStore.isTRelationship(1, 2);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() positive query - transitive") {
			bool res = followsStore.isTRelationship(1, 9);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() negative query - invalid ordering") {
			bool res = followsStore.isTRelationship(2, 1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() negative query - invalid statements") {
			bool res = followsStore.isTRelationship(-10, 999);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstStatement()
		SECTION("isFirstStatement() positive query") {
			bool res = followsStore.isFirstStatement(1);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatement() negative query - second statement") {
			bool res = followsStore.isFirstStatement(9);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatement() negative query - invalid statement") {
			bool res = followsStore.isFirstStatement(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondStatement()
		SECTION("isSecondStatement() positive query") {
			bool res = followsStore.isSecondStatement(2);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatement() negative query - first statement") {
			bool res = followsStore.isSecondStatement(1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatement() negative query - invalid statement") {
			bool res = followsStore.isSecondStatement(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstStatementT()
		SECTION("isFirstStatementT() positive query") {
			bool res = followsStore.isFirstStatementT(1);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatementT() negative query - second statement") {
			bool res = followsStore.isFirstStatementT(9);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstStatementT() negative query - invalid statement") {
			bool res = followsStore.isFirstStatementT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondStatementT()
		SECTION("isSecondStatementT() positive query") {
			bool res = followsStore.isSecondStatementT(2);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatementT() negative query - first statement") {
			bool res = followsStore.isSecondStatementT(1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondStatementT() negative query - invalid statement") {
			bool res = followsStore.isSecondStatementT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// getFirstStatements
		SECTION("getFirstStatements(int secondStatement) positive query") {
			std::unordered_set<int> res = followsStore.getFirstStatements(2);
			std::unordered_set<int> expectedSet = {1};
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstStatements(int secondStatement) negative query - first statement as second statement") {
			std::unordered_set<int> res = followsStore.getFirstStatements(1);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondStatements
		SECTION("getSecondStatements(int firstStatement) positive query") {
			std::unordered_set<int> res = followsStore.getSecondStatements(1);
			std::unordered_set<int> expectedSet = { 2 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondStatements(int firstStatement) negative query - last statement as first statement") {
			std::unordered_set<int> res = followsStore.getSecondStatements(9);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getFirstStatementsT
		SECTION("getFirstStatementsT(int secondStatement) positive query - non-transitive") {
			std::unordered_set<int> res = followsStore.getFirstStatementsT(2);
			std::unordered_set<int> expectedSet = { 1 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstStatementsT(int secondStatement) positive query - transitive") {
			std::unordered_set<int> res = followsStore.getFirstStatementsT(9);
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 7 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstStatementsT(int secondStatement) negative query - first statement as second statement") {
			std::unordered_set<int> res = followsStore.getFirstStatementsT(1);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondStatementsT
		SECTION("getSecondStatementsT(int firstStatement) positive query - transitive") {
			std::unordered_set<int> res = followsStore.getSecondStatementsT(1);
			std::unordered_set<int> expectedSet = { 2, 3, 4, 7, 9 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondStatementsT(int firstStatement) negative query - last statement as first statement") {
			std::unordered_set<int> res = followsStore.getSecondStatementsT(9);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getAllFirstStatements
		SECTION("getAllFirstStatements() positive query") {
			std::unordered_set<int> res = followsStore.getAllFirstStatements();
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondStatements
		SECTION("getAllSecondStatements() positive query") {
			std::unordered_set<int> res = followsStore.getAllSecondStatements();
			std::unordered_set<int> expectedSet = { 2, 3, 4, 7, 9 };
			REQUIRE(res == expectedSet);
		}

		// getAllFirstStatementsT
		SECTION("getAllFirstStatementsT() positive query") {
			std::unordered_set<int> res = followsStore.getAllFirstStatementsT();
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondStatementsT
		SECTION("getAllSecondStatements() positive query") {
			std::unordered_set<int> res = followsStore.getAllSecondStatementsT();
			std::unordered_set<int> expectedSet = { 2, 3, 4, 7, 9 };
			REQUIRE(res == expectedSet);
		}

		// getAllRelationshipPairs
		SECTION("getAllRelationshipPairs() positive query") {
			std::tuple<std::vector<int>, std::vector<int>> res = followsStore.getAllRelationshipPairs();
			
			std::vector<int> firstColumn;
			std::vector<int> secondColumn;

			firstColumn.push_back(1);
			secondColumn.push_back(2);

			firstColumn.push_back(2);
			secondColumn.push_back(3);

			firstColumn.push_back(3);
			secondColumn.push_back(4);

			firstColumn.push_back(4);
			secondColumn.push_back(7);

			firstColumn.push_back(7);
			secondColumn.push_back(9);
		
			std::tuple<std::vector<int>, std::vector<int>> expectedRes = { firstColumn, secondColumn };
			
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> set = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> expectedSet = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		// getAllRelationshipPairsT
		SECTION("getAllRelationshipPairsT() positive query") {
			std::tuple<std::vector<int>, std::vector<int>> res = followsStore.getAllRelationshipTPairs();

			std::vector<int> firstColumn;
			std::vector<int> secondColumn;
			
			firstColumn.push_back(1);
			secondColumn.push_back(2);

			firstColumn.push_back(2);
			secondColumn.push_back(3);

			firstColumn.push_back(3);
			secondColumn.push_back(4);

			firstColumn.push_back(4);
			secondColumn.push_back(7);

			firstColumn.push_back(7);
			secondColumn.push_back(9);

			firstColumn.push_back(1);
			secondColumn.push_back(3);

			firstColumn.push_back(1);
			secondColumn.push_back(4);

			firstColumn.push_back(1);
			secondColumn.push_back(7);

			firstColumn.push_back(1);
			secondColumn.push_back(9);

			firstColumn.push_back(2);
			secondColumn.push_back(4);

			firstColumn.push_back(2);
			secondColumn.push_back(7);

			firstColumn.push_back(2);
			secondColumn.push_back(9);

			firstColumn.push_back(3);
			secondColumn.push_back(7);

			firstColumn.push_back(3);
			secondColumn.push_back(9);

			firstColumn.push_back(4);
			secondColumn.push_back(9);

			std::tuple<std::vector<int>, std::vector<int>> expectedRes = { firstColumn, secondColumn };
			
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> set = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtil::hashFunction> expectedSet = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}
	}
	followsStore.clear();
}
