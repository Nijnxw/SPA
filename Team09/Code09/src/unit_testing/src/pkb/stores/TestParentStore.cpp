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

		// isFirstSynonym()
		SECTION("isFirstSynonym() positive query") {
			bool res = parentStore.isFirstSynonym(4);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonym() negative query - second statement") {
			bool res = parentStore.isFirstSynonym(5);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonym() negative query - invalid statement") {
			bool res = parentStore.isFirstSynonym(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondSynonym()
		SECTION("isSecondSynonym() positive query") {
			bool res = parentStore.isSecondSynonym(5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - first statement") {
			bool res = parentStore.isSecondSynonym(4);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - invalid statement") {
			bool res = parentStore.isSecondSynonym(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstSynonymT()
		SECTION("isFirstSynonymT() positive query") {
			bool res = parentStore.isFirstSynonymT(4);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonymT() negative query - second statement") {
			bool res = parentStore.isFirstSynonymT(5);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonymT() negative query - invalid statement") {
			bool res = parentStore.isFirstSynonymT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondSynonymT()
		SECTION("isSecondSynonymT() positive query") {
			bool res = parentStore.isSecondSynonymT(5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonymT() negative query - first statement") {
			bool res = parentStore.isSecondSynonymT(4);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonymT() negative query - invalid statement") {
			bool res = parentStore.isSecondSynonymT(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// getFirstSynonyms
		SECTION("getFirstSynonyms(int secondSynonym) positive query") {
			std::unordered_set<int> res = parentStore.getFirstSynonyms(5);
			std::unordered_set<int> expectedSet = { 4 };
			REQUIRE(res == expectedSet);
		}

		// getSecondSynonyms
		SECTION("getSecondSynonyms(int firstSynonym) positive query") {
			std::unordered_set<int> res = parentStore.getSecondSynonyms(4);
			std::unordered_set<int> expectedSet = { 5, 6 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondSynonyms(int firstSynonym) negative query - last statement as first statement") {
			std::unordered_set<int> res = parentStore.getSecondSynonyms(5);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getFirstSynonymsT
		SECTION("getFirstSynonymsT(int secondSynonym) positive query - non-transitive") {
			std::unordered_set<int> res = parentStore.getFirstSynonymsT(5);
			std::unordered_set<int> expectedSet = { 4 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonymsT(int secondSynonym) positive query - transitive") {
			std::unordered_set<int> res = parentStore.getFirstSynonymsT(5);
			std::unordered_set<int> expectedSet = { 4 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonymsT(int secondSynonym) negative query - first statement as second statement") {
			std::unordered_set<int> res = parentStore.getFirstSynonymsT(4);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondSynonymsT
		SECTION("getSecondSynonymsT(int firstSynonym) positive query - transitive") {
			std::unordered_set<int> res = parentStore.getSecondSynonymsT(4);
			std::unordered_set<int> expectedSet = { 5, 6 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondSynonymsT(int firstSynonym) negative query - last statement as first statement") {
			std::unordered_set<int> res = parentStore.getSecondSynonymsT(5);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getAllFirstSynonyms
		SECTION("getAllFirstSynonyms() positive query") {
			std::unordered_set<int> res = parentStore.getAllFirstSynonyms();
			std::unordered_set<int> expectedSet = { 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondSynonyms
		SECTION("getAllSecondSynonyms() positive query") {
			std::unordered_set<int> res = parentStore.getAllSecondSynonyms();
			std::unordered_set<int> expectedSet = { 5, 6, 8 };
			REQUIRE(res == expectedSet);
		}

		// getAllFirstSynonymsT
		SECTION("getAllFirstSynonymsT() positive query") {
			std::unordered_set<int> res = parentStore.getAllFirstSynonymsT();
			std::unordered_set<int> expectedSet = { 4, 7 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondSynonymsT
		SECTION("getAllSecondSynonyms() positive query") {
			std::unordered_set<int> res = parentStore.getAllSecondSynonymsT();
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
			
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> set = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> expectedSet = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

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
			
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> set = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> expectedSet = PKBUtils::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}
	}
	parentStore.clear();
}
