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

		// isFirstSynonym()
		SECTION("isFirstSynonym() positive query") {
			bool res = followsStore.isFirstSynonym(1);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonym() negative query - second statement") {
			bool res = followsStore.isFirstSynonym(9);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonym() negative query - invalid statement") {
			bool res = followsStore.isFirstSynonym(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondSynonym()
		SECTION("isSecondSynonym() positive query") {
			bool res = followsStore.isSecondSynonym(2);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - first statement") {
			bool res = followsStore.isSecondSynonym(1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - invalid statement") {
			bool res = followsStore.isSecondSynonym(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstSynonymT()
		SECTION("isFirstSynonymT() positive query") {
			bool res = followsStore.isFirstSynonymT(1);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonymT() negative query - second statement") {
			bool res = followsStore.isFirstSynonymT(9);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonymT() negative query - invalid statement") {
			bool res = followsStore.isFirstSynonymT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondSynonymT()
		SECTION("isSecondSynonymT() positive query") {
			bool res = followsStore.isSecondSynonymT(2);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonymT() negative query - first statement") {
			bool res = followsStore.isSecondSynonymT(1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonymT() negative query - invalid statement") {
			bool res = followsStore.isSecondSynonymT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// getFirstSynonyms
		SECTION("getFirstSynonyms(int secondSynonym) positive query") {
			std::unordered_set<int> res = followsStore.getFirstSynonyms(2);
			std::unordered_set<int> expectedSet = {1};
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonyms(int secondSynonym) negative query - first statement as second statement") {
			std::unordered_set<int> res = followsStore.getFirstSynonyms(1);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondSynonyms
		SECTION("getSecondSynonyms(int firstSynonym) positive query") {
			std::unordered_set<int> res = followsStore.getSecondSynonyms(1);
			std::unordered_set<int> expectedSet = { 2 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondSynonyms(int firstSynonym) negative query - last statement as first statement") {
			std::unordered_set<int> res = followsStore.getSecondSynonyms(9);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getFirstSynonymsT
		SECTION("getFirstSynonymsT(int secondSynonym) positive query - non-transitive") {
			std::unordered_set<int> res = followsStore.getFirstSynonymsT(2);
			std::unordered_set<int> expectedSet = { 1 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonymsT(int secondSynonym) positive query - transitive") {
			std::unordered_set<int> res = followsStore.getFirstSynonymsT(9);
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 7 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonymsT(int secondSynonym) negative query - first statement as second statement") {
			std::unordered_set<int> res = followsStore.getFirstSynonymsT(1);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondSynonymsT
		SECTION("getSecondSynonymsT(int firstSynonym) positive query - transitive") {
			std::unordered_set<int> res = followsStore.getSecondSynonymsT(1);
			std::unordered_set<int> expectedSet = { 2, 3, 4, 7, 9 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondSynonymsT(int firstSynonym) negative query - last statement as first statement") {
			std::unordered_set<int> res = followsStore.getSecondSynonymsT(9);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getAllFirstSynonyms
		SECTION("getAllFirstSynonyms() positive query") {
			std::unordered_set<int> res = followsStore.getAllFirstSynonyms();
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondSynonyms
		SECTION("getAllSecondSynonyms() positive query") {
			std::unordered_set<int> res = followsStore.getAllSecondSynonyms();
			std::unordered_set<int> expectedSet = { 2, 3, 4, 7, 9 };
			REQUIRE(res == expectedSet);
		}

		// getAllFirstSynonymsT
		SECTION("getAllFirstSynonymsT() positive query") {
			std::unordered_set<int> res = followsStore.getAllFirstSynonymsT();
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondSynonymsT
		SECTION("getAllSecondSynonyms() positive query") {
			std::unordered_set<int> res = followsStore.getAllSecondSynonymsT();
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
			
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> set = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> expectedSet = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

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
			
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> set = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> expectedSet = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}
	}
	followsStore.clear();
}
