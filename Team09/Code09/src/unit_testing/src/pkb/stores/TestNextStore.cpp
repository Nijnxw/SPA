#include "catch.hpp"
#include "pkb/stores/NextStore.h"

TEST_CASE("NextStore API") {
	NextStore nextStore;
	// The same store is reused through tests, so clearing is a must.
	nextStore.clear();

	/*
	Source
	1 x = x + 1;
	2 while (y = true) {
	3	y = y + 1;
	4	if (z = false) then {
	5		z = z + 1;
		}
		else {
	6		z = z - 1;
		}}
	CFG, vector is 1-indexed
	1 -> {2}
	2 -> {3}
	3 -> {4}
	4 -> {5,6}
	5 -> {2}
	6 -> {2}
	*/

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		nextStore.addRelationship(1, 2);
		nextStore.addRelationship(2, 3);
		nextStore.addRelationship(3, 4);
		nextStore.addRelationship(4, 5);
		nextStore.addRelationship(4, 6);
		nextStore.addRelationship(5, 2);
		nextStore.addRelationship(6, 2);

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------
		// hasRelationship()
		SECTION("hasRelationship() positive query") {
			bool res = nextStore.hasRelationship();
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		// TODO: hasTRelationship()

		// isRelationship()
		SECTION("isRelationship() positive query") {
			bool res = nextStore.isRelationship(1, 2);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid ordering") {
			bool res = nextStore.isRelationship(2, 1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid statement numbers") {
			bool res = nextStore.isRelationship(-10, 999);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// TODO: isRelationshipT()

		// isFirstSynonym()
		SECTION("isFirstSynonym() positive query") {
			bool res = nextStore.isFirstSynonym(1);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonym() negative query - invalid statement") {
			bool res = nextStore.isFirstSynonym(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondSynonym()
		SECTION("isSecondSynonym() positive query") {
			bool res = nextStore.isSecondSynonym(5);
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - statement 1") {
			bool res = nextStore.isSecondSynonym(1);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - invalid statement") {
			bool res = nextStore.isSecondSynonym(-100);
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// TODO: isFirstSynonymT()

		// TODO: isSecondSynonymT()

		// getFirstSynonyms
		SECTION("getFirstSynonyms(int secondSynonym) positive query") {
			std::unordered_set<int> res = nextStore.getFirstSynonyms(2);
			std::unordered_set<int> expectedSet = { 1, 5, 6 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonyms(int secondSynonym) negative query - invalid number") {
			std::unordered_set<int> res = nextStore.getFirstSynonyms(-100);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondSynonyms
		SECTION("getSecondSynonyms(int firstSynonym) positive query") {
			std::unordered_set<int> res = nextStore.getSecondSynonyms(4);
			std::unordered_set<int> expectedSet = { 5, 6 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondSynonyms(int firstSynonym) negative query - invalid number") {
			std::unordered_set<int> res = nextStore.getSecondSynonyms(-100);
			std::unordered_set<int> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// TODO: getFirstSynonymsT

		// TODO: getSecondSynonymsT

		// getAllFirstSynonyms
		SECTION("getAllFirstSynonyms() positive query") {
			std::unordered_set<int> res = nextStore.getAllFirstSynonyms();
			std::unordered_set<int> expectedSet = { 1, 2, 3, 4, 5, 6 };
			REQUIRE(res == expectedSet);
		}

		// getAllSecondSynonyms
		SECTION("getAllSecondSynonyms() positive query") {
			std::unordered_set<int> res = nextStore.getAllSecondSynonyms();
			std::unordered_set<int> expectedSet = { 2, 3, 4, 5, 6 };
			REQUIRE(res == expectedSet);
		}

		// TODO: getAllFirstSynonymsT

		// TODO: getAllSecondSynonymsT

		// getAllRelationshipPairs
		SECTION("getAllRelationshipPairs() positive query") {
			std::tuple<std::vector<int>, std::vector<int>> res = nextStore.getAllRelationshipPairs();

			std::vector<int> firstColumn;
			std::vector<int> secondColumn;

			firstColumn.push_back(1);
			secondColumn.push_back(2);

			firstColumn.push_back(2);
			secondColumn.push_back(3);

			firstColumn.push_back(3);
			secondColumn.push_back(4);

			firstColumn.push_back(4);
			secondColumn.push_back(5);

			firstColumn.push_back(4);
			secondColumn.push_back(6);

			firstColumn.push_back(5);
			secondColumn.push_back(2);

			firstColumn.push_back(6);
			secondColumn.push_back(2);

			std::tuple<std::vector<int>, std::vector<int>> expectedRes = { firstColumn, secondColumn };
			
			std::unordered_set<std::pair<int, int>, PKBUtil::pairHashFunction> set = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<int, int>, PKBUtil::pairHashFunction> expectedSet = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		// TODO: getAllRelationshipPairsT
	}
	nextStore.clear();
}
