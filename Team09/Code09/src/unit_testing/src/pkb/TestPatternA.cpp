#include "catch.hpp"
#include "PQL/evaluators/PatternAEvaluator.h"

TEST_CASE("Assignment Pattern API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		PKB::addAssignStatement(2, "a", "p 2 *");
		PKB::addAssignStatement(4, "pattern", "p a * a * p ifs * + p w * +");
		PKB::addAssignStatement(6, "w", "w 1 -");

		// --------------------------------------------------
		//                  LHS synonym
		// --------------------------------------------------
		// getPattern(LHS synonym, RHS wild card match)
		SECTION("pattern a(v, _p_) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "_p_", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"2", "4"}},
				{"v", {"a", "pattern"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(v, _2_) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "_2_", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"2"}},
				{"v", {"a"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(v, _p 2 *_) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "_p 2 *_", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"2"}},
				{"v", {"a"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(v, _x_) negative query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "_x_", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getPattern(LHS synonym, RHS exact match)
		SECTION("pattern a(v, p 2 *) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "p 2 *", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"2"}},
				{"v", {"a"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(v, p a * a * p ifs * + p w * +) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "p a * a * p ifs * + p w * +", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"4"}},
				{"v", {"pattern"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(v, w 1 -) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "w 1 -", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"6"}},
				{"v", {"w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(v, p) negative query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "p", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getPattern(LHS synonym, RHS wild card)
		SECTION("pattern a(v, _) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("v", "_", EntityType::VAR, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"2", "4", "6"}},
				{"v", {"a", "pattern", "w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS variable
		// --------------------------------------------------
		// getPattern(LHS variable, RHS wild card match)
		SECTION("pattern a(a, _p_) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("a", "_p_", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(a, _p 2 *_) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("a", "_p 2 *_", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(x, _p_) negative query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("x", "_p_", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getPattern(LHS variable, RHS exact match)
		SECTION("pattern a(a, p 2 *) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("a", "p 2 *", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(pattern, p a * a * p ifs * + p w * +) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("pattern", "p a * a * p ifs * + p w * +", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"4"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(w, w 1 -) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("w", "w 1 -", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"6"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(x, w 1 -) negative query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("x", "w 1 -", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getPattern(LHS variable, RHS wildcard)
		SECTION("pattern a(a, _) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("a", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(pattern, _) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("pattern", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"4"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(w, _) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("w", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"6"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(x, _) negative query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("x", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// --------------------------------------------------
		//                  LHS wild card
		// --------------------------------------------------
		// getPattern(LHS wild card, RHS wild card match)
		SECTION("pattern a(_, _p_) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("_", "_p_", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2", "4"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(_, _p 2 *_) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("_", "_p 2 *_", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(_, _x_) negative query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("_", "_x_", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getPattern(LHS wild card, RHS exact match)
		SECTION("pattern a(_, p 2 *) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("_", "p 2 *", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(_, w 1 -) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("_", "w 1 -", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"6"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("pattern a(_, p) negative query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("_", "p", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getPattern(LHS wildcard, RHS wildcard)
		SECTION("pattern a(_, _) positive query") {
			QueryClauseTable res = PatternAEvaluator::getPattern("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"a", {"2", "4", "6"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}
	}
	PKB::clearAllStores();
}
