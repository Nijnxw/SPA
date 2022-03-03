#include "catch.hpp"
#include "pkb/stores/CallsStore.h"

TEST_CASE("CallsStore API") {
	CallsStore callsStore;
	// The same store is reused through tests, so clearing is a must.
	callsStore.clear();

	/*
	procedure First{
	01	read x;
	02	read z;
	03	call Second; }

	procedure Second{
	04        x = 0;
	05        i = 5;
	06        while (i != 0) {
	07            x = x + 2 * y;
	08            call Third;
	09            i = i - 1;
	 }
	10        if (x == 1) then {
	11            x = x + 1; }
			  else {
	12            z = 1;
	 }
	13        z = z + x + i;
	14        y = z + 2;
	15        x = x * y + z; }

	procedure Third{
	16	z = 5;
	17	v = z;
	18	prstd::string v; } 
	*/

	// Populating PKB information based on wiki example
	SECTION("Initialization of program variables") {
		callsStore.addRelationship("First", "Second");
		callsStore.addRelationship("Second", "Third");

		callsStore.addRelationshipT("First", "Second");
		callsStore.addRelationshipT("Second", "Third");
		callsStore.addRelationshipT("First", "Third");

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------
		// hasRelationship()
		SECTION("hasRelationship() positive query") {
			bool res = callsStore.hasRelationship();
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		// hasTRelationship()
		SECTION("hasTRelationship() positive query") {
			bool res = callsStore.hasTRelationship();
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}
		
		// isRelationship()
		SECTION("isRelationship() positive query") {
			bool res = callsStore.isRelationship("First", "Second");
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid ordering") {
			bool res = callsStore.isRelationship("Second", "First");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationship() negative query - invalid statement numbers") {
			bool res = callsStore.isRelationship("Fourth", "Fifth");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isRelationshipT()
		SECTION("isRelationshipT() positive query - non-transitive") {
			bool res = callsStore.isTRelationship("First", "Second");
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() positive query - transitive") {
			bool res = callsStore.isTRelationship("First", "Third");
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() negative query - invalid ordering") {
			bool res = callsStore.isTRelationship("Third", "First");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isRelationshipT() negative query - invalid statements") {
			bool res = callsStore.isTRelationship("Fourth", "Fifth");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstSynonym()
		SECTION("isFirstSynonym() positive query") {
			bool res = callsStore.isFirstSynonym("First");
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonym() negative query - second statement") {
			bool res = callsStore.isFirstSynonym("Third");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonym() negative query - invalid statement") {
			bool res = callsStore.isFirstSynonym("Fourth");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondSynonym()
		SECTION("isSecondSynonym() positive query") {
			bool res = callsStore.isSecondSynonym("Second");
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - first statement") {
			bool res = callsStore.isSecondSynonym("First");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonym() negative query - invalid statement") {
			bool res = callsStore.isSecondSynonym("Fourth");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isFirstSynonymT()
		SECTION("isFirstSynonymT() positive query") {
			bool res = callsStore.isFirstSynonymT("First");
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonymT() negative query - second statement") {
			bool res = callsStore.isFirstSynonymT("Third");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isFirstSynonymT() negative query - invalid statement") {
			bool res = callsStore.isFirstSynonymT("Fourth");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// isSecondSynonymT()
		SECTION("isSecondSynonymT() positive query") {
			bool res = callsStore.isSecondSynonymT("Second");
			bool expectedRes = true;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonymT() negative query - first statement") {
			bool res = callsStore.isSecondSynonymT("First");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		SECTION("isSecondSynonymT() negative query - invalid statement") {
			bool res = callsStore.isSecondSynonymT("Fourth");
			bool expectedRes = false;
			REQUIRE(res == expectedRes);
		}

		// getFirstSynonyms
		SECTION("getFirstSynonyms(std::string secondSynonym) positive query") {
			std::unordered_set<std::string> res = callsStore.getFirstSynonyms("Second");
			std::unordered_set<std::string> expectedSet = {"First"};
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonyms(std::string secondSynonym) negative query - first statement as second statement") {
			std::unordered_set<std::string> res = callsStore.getFirstSynonyms("First");
			std::unordered_set<std::string> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondSynonyms
		SECTION("getSecondSynonyms(std::string firstSynonym) positive query") {
			std::unordered_set<std::string> res = callsStore.getSecondSynonyms("First");
			std::unordered_set<std::string> expectedSet = { "Second" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondSynonyms(std::string firstSynonym) negative query - last statement as first statement") {
			std::unordered_set<std::string> res = callsStore.getSecondSynonyms("Third");
			std::unordered_set<std::string> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getFirstSynonymsT
		SECTION("getFirstSynonymsT(std::string secondSynonym) positive query - non-transitive") {
			std::unordered_set<std::string> res = callsStore.getFirstSynonymsT("Second");
			std::unordered_set<std::string> expectedSet = { "First"};
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonymsT(std::string secondSynonym) positive query - transitive") {
			std::unordered_set<std::string> res = callsStore.getFirstSynonymsT("Third");
			std::unordered_set<std::string> expectedSet = { "First", "Second"};
			REQUIRE(res == expectedSet);
		}

		SECTION("getFirstSynonymsT(std::string secondSynonym) negative query - first statement as second statement") {
			std::unordered_set<std::string> res = callsStore.getFirstSynonymsT("First");
			std::unordered_set<std::string> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getSecondSynonymsT
		SECTION("getSecondSynonymsT(std::string firstSynonym) positive query - transitive") {
			std::unordered_set<std::string> res = callsStore.getSecondSynonymsT("First");
			std::unordered_set<std::string> expectedSet = { "Second", "Third"};
			REQUIRE(res == expectedSet);
		}

		SECTION("getSecondSynonymsT(std::string firstSynonym) negative query - last statement as first statement") {
			std::unordered_set<std::string> res = callsStore.getSecondSynonymsT("Third");
			std::unordered_set<std::string> expectedSet;
			REQUIRE(res == expectedSet);
		}

		// getAllFirstSynonyms
		SECTION("getAllFirstSynonyms() positive query") {
			std::unordered_set<std::string> res = callsStore.getAllFirstSynonyms();
			std::unordered_set<std::string> expectedSet = { "First", "Second"};
			REQUIRE(res == expectedSet);
		}

		// getAllSecondSynonyms
		SECTION("getAllSecondSynonyms() positive query") {
			std::unordered_set<std::string> res = callsStore.getAllSecondSynonyms();
			std::unordered_set<std::string> expectedSet = { "Second", "Third" };
			REQUIRE(res == expectedSet);
		}

		// getAllFirstSynonymsT
		SECTION("getAllFirstSynonymsT() positive query") {
			std::unordered_set<std::string> res = callsStore.getAllFirstSynonymsT();
			std::unordered_set<std::string> expectedSet = { "First", "Second"};
			REQUIRE(res == expectedSet);
		}

		// getAllSecondSynonymsT
		SECTION("getAllSecondSynonyms() positive query") {
			std::unordered_set<std::string> res = callsStore.getAllSecondSynonymsT();
			std::unordered_set<std::string> expectedSet = { "Second", "Third" };
			REQUIRE(res == expectedSet);
		}

		// getAllRelationshipPairs
		SECTION("getAllRelationshipPairs() positive query") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = callsStore.getAllRelationshipPairs();
			
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			firstColumn.push_back("First");
			secondColumn.push_back("Second");

			firstColumn.push_back("Second");
			secondColumn.push_back("Third");
		
			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };
			
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		// getAllRelationshipPairsT
		SECTION("getAllRelationshipPairsT() positive query") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = callsStore.getAllRelationshipTPairs();

			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;
			
			firstColumn.push_back("First");
			secondColumn.push_back("Second");

			firstColumn.push_back("Second");
			secondColumn.push_back("Third");

			firstColumn.push_back("First");
			secondColumn.push_back("Third");

			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };
			
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet = PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}
	}
	callsStore.clear();
}
