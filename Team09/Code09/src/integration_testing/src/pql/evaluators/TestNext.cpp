#include "catch.hpp"
#include "PQL/evaluators/NextEvaluator.h"
#include "models/EntityType.h"

TEST_CASE("Next Relationship API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();
	NextEvaluator nextEvaluator = NextEvaluator();

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

	// Populating PKB information based on above source code
	SECTION("Initialization of program variables") {
		std::vector<std::unordered_set<int>> cfg;
		
		for (int index = 0; index <= 6; index++) {
			std::unordered_set<int> set;
			cfg.push_back(set);
		}

		cfg[1].insert(2);
		cfg[2].insert(3);
		cfg[3].insert(4);
		cfg[4].insert(5);
		cfg[4].insert(6);
		cfg[5].insert(2);
		cfg[6].insert(2);

		PKB::addCFG(cfg);

		std::unordered_set<int> endNodes = { 2 };
		PKB::addProcedureNameToLastCFGNode("Test", endNodes);

		SECTION("CFG same as one added - positive query") {
			std::vector<std::unordered_set<int>> pkbCFG = PKB::getCFG();
			REQUIRE(pkbCFG == cfg);
		}

		SECTION("Reversed CFG is correct - positive query") {
			std::vector<std::unordered_set<int>> pkbReversedCFG = PKB::getReversedCFG();

			std::vector<std::unordered_set<int>> reversedCfg;

			for (int index = 0; index <= 6; index++) {
				std::unordered_set<int> set;
				reversedCfg.push_back(set);
			}

			reversedCfg[2].insert(1);
			reversedCfg[2].insert(5);
			reversedCfg[2].insert(6);
			reversedCfg[3].insert(2);
			reversedCfg[4].insert(3);
			reversedCfg[5].insert(4);
			reversedCfg[6].insert(4);

			REQUIRE(pkbReversedCFG == reversedCfg);
		}
		
		// --------------------------------------------------
		//                  LHS int
		// --------------------------------------------------
		// getNext(LHS int, RHS int)
		SECTION("Next(1, 2) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Next(2, 1) negative query - invalid ordering") {
			QueryClauseResult res = nextEvaluator.getNext("2", "1", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(3, 3) negative query - same stmt") {
			QueryClauseResult res = nextEvaluator.getNext("3", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(7, 8) negative query - invalid numbers") {
			QueryClauseResult res = nextEvaluator.getNext("7", "8", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNextT(LHS int, RHS int) 
		SECTION("Next(1, 2) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("NextT(3, 3) positive query - same stmt while loop") {
			QueryClauseResult res = nextEvaluator.getNextT("3", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("NextT(2, 1) negative query - invalid ordering") {
			QueryClauseResult res = nextEvaluator.getNextT("2", "1", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("NextT(7, 8) negative query - invalid numbers") {
			QueryClauseResult res = nextEvaluator.getNextT("7", "8", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNext(LHS int, RHS stmt)
		SECTION("Next(4, s) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("4", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"5", "6"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Next(7, s) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNext("7", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNextT(LHS int, RHS stmt)
		SECTION("NextT(1, s) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("1", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"s", {"2", "3", "4", "5", "6"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("NextT(7, s) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNextT("7", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNext(LHS int, RHS wild)
		SECTION("Next(3, _) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("3", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Next(7, _) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNext("7", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNextT(LHS int, RHS wild)
		SECTION("NextT(1, _) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("NextT(7, _) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNextT("7", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//                  LHS stmt
		// --------------------------------------------------
		// getNext(LHS stmt, RHS int)
		SECTION("Next(s, 2) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("s", "2", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1", "5", "6"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Next(s, 1) negative query - no one's next node is 1") {
			QueryClauseResult res = nextEvaluator.getNext("s", "1", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(s, 7) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNext("s", "7", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNextT(LHS stmt, RHS int)
		SECTION("Next(s, 2) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("s", "2", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"s", {"1", "2", "3", "4", "5", "6"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("NextT(s, 7) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNextT("s", "7", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNext(LHS stmt, RHS stmt)
		SECTION("Next(s1, s2) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s1", {"1", "2", "3", "4", "4", "5", "6"}},
				{"s2", {"2", "3", "4", "5", "6", "2", "2"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Next(s, s) negative query - same synonym statement") {
			QueryClauseResult res = nextEvaluator.getNext("s", "s", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(a, a) negative query - same synonym assign") {
			QueryClauseResult res = nextEvaluator.getNext("a", "a", EntityType::ASSIGN, EntityType::ASSIGN, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(ifs, ifs) negative query - same synonym if") {
			QueryClauseResult res = nextEvaluator.getNext("ifs", "ifs", EntityType::IF, EntityType::IF, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(w, w) negative query - same synonym while") {
			QueryClauseResult res = nextEvaluator.getNext("w", "w", EntityType::WHILE, EntityType::WHILE, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(r, r) negative query - same synonym read") {
			QueryClauseResult res = nextEvaluator.getNext("r", "r", EntityType::READ, EntityType::READ, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(pn, pn) negative query - same synonym print") {
			QueryClauseResult res = nextEvaluator.getNext("pn", "pn", EntityType::PRINT, EntityType::PRINT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(c, c) negative query - same synonym call") {
			QueryClauseResult res = nextEvaluator.getNext("c", "c", EntityType::CALL, EntityType::CALL, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNextT(LHS stmt, RHS stmt)
		SECTION("Next(s1, s2) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s1", {"1", "1", "1", "1", "1", 
						"2", "2", "2", "2", "2",
						"3", "3", "3", "3", "3",
						"4", "4", "4", "4", "4", 
						"5", "5", "5", "5", "5",
						"6", "6", "6", "6", "6"}},
				{"s2", {"2", "3", "4", "5", "6", 
						"2", "3", "4", "5", "6",
						"2", "3", "4", "5", "6",
						"2", "3", "4", "5", "6",
						"2", "3", "4", "5", "6",
						"2", "3", "4", "5", "6"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("NextT(s, s) positive query - same synonym statement") {
			QueryClauseResult res = nextEvaluator.getNextT("s", "s", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"2", "3", "4", "5", "6"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getNext(LHS stmt, RHS wild)
		SECTION("Next(s, _) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1", "2", "3", "4", "5", "6"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getNextT(LHS stmt, RHS wild)
		SECTION("NextT(s, _) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"s", {"1", "2", "3", "4", "5", "6"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS wild
		// --------------------------------------------------
		// getNext(LHS wild, RHS int)
		SECTION("Next(_, 4) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("_", "4", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Next(_, 1) negative query - 1 is not anyone's next node") {
			QueryClauseResult res = nextEvaluator.getNext("_", "1", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Next(_, 7) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNext("_", "7", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNextT(LHS wild, RHS int)
		SECTION("NextT(_, 4) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("_", "2", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("NextT(_, 7) negative query - invalid number") {
			QueryClauseResult res = nextEvaluator.getNextT("_", "7", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getNext(LHS wild, RHS stmt)
		SECTION("Next(_, s) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"2", "3", "4", "5", "6"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getNextT(LHS wild, RHS stmt)
		SECTION("NextT(_, s) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"s", {"2", "3", "4", "5", "6"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getNext(LHS wild, RHS wild)
		SECTION("Next(_, _) positive query") {
			QueryClauseResult res = nextEvaluator.getNext("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		// getNextT(LHS wild, RHS wild)
		SECTION("NextT(_, _) positive query") {
			QueryClauseResult res = nextEvaluator.getNextT("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}
	}
	PKB::clearAllStores();
}
