#include "catch.hpp"
#include "PQL/evaluators/FollowsEvaluator.h"

TEST_CASE("Follows Relationship API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();
	FollowsEvaluator followsEvaluator = FollowsEvaluator();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		PKB::addFollows(1, 2);
		PKB::addFollows(2, 3);
		PKB::addFollows(4, 5);

		PKB::addFollowsT(1, 2);
		PKB::addFollowsT(2, 3);
		PKB::addFollowsT(1, 3);
		PKB::addFollowsT(4, 5);

		PKB::addStatementWithType(EntityType::CALL, 1);

		// --------------------------------------------------
		//                  LHS int
		// --------------------------------------------------
		// getFollows(LHS int, RHS int)
		SECTION("Follows(1, 2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(2, 3) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("2", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(4, 5) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("4", "5", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(1, 1) negative query") {
			QueryClauseResult res = followsEvaluator.getFollows("1", "1", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Follows(1, 3) negative query") {
			QueryClauseResult res = followsEvaluator.getFollows("1", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollowsT(LHS int, RHS int)
		SECTION("FollowsT(1, 2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(2, 3) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("2", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(4, 5) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("4", "5", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(1, 3) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("1", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(1, 1) negative query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("1", "1", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("FollowsT(1, 4) negative query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("1", "4", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollows(LHS int, RHS stmt)
		SECTION("Follows(1, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("1", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"2"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(2, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("2", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"3"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(4, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("4", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"5"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(3, s) negative query") {
			QueryClauseResult res = followsEvaluator.getFollows("3", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollowsT(LHS int, RHS stmt)
		SECTION("FollowsT(1, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("1", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"2", "3"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("FollowsT(2, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("2", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"3"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("FollowsT(4, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("4", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"5"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("FollowsT(3, s) negative query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("3", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollows(LHS int, RHS wild)
		SECTION("Follows(1, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(2, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("2", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(4, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("4", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(3, _) negative query") {
			QueryClauseResult res = followsEvaluator.getFollows("3", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollowsT(LHS int, RHS wild)
		SECTION("FollowsT(1, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(2, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("2", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(4, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("4", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(3, _) negative query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("3", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// --------------------------------------------------
			//                  LHS stmt
			// --------------------------------------------------
			// getFollows(LHS stmt, RHS int)
		SECTION("Follows(s, 2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("s", "2", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(c, 2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("c", "2", EntityType::CALL, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"c", {"1"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(s, 3) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("s", "3", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"2"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(s, 5) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("s", "5", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"4"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(s, 1) negative query") {
			QueryClauseResult res = followsEvaluator.getFollows("s", "1", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollowsT(LHS stmt, RHS int)
		SECTION("FollowsT(s, 2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("s", "2", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("FollowsT(s, 3) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("s", "3", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1", "2"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("FollowsT(s, 5) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("s", "5", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"4"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("FollowsT(s, 1) negative query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("s", "1", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollows(LHS stmt, RHS stmt)
		SECTION("Follows(s1, s2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s1", {"1", "2", "4"}},
				{"s2", {"2", "3", "5"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Follows(s, s) negative query - same stmt synonym") {
			QueryClauseResult res = followsEvaluator.getFollows("s", "s", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollowsT(LHS stmt, RHS stmt)
		SECTION("FollowsT(s1, s2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s1", {"1", "1", "2", "4"}},
				{"s2", {"2", "3", "3", "5"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("FollowsT(s, s) negative query - same stmt synonym") {
			QueryClauseResult res = followsEvaluator.getFollowsT("s", "s", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollows(LHS stmt, RHS wild)
		SECTION("Follows(s, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1", "2", "4"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

			// getFollowsT(LHS stmt, RHS wild)
		SECTION("FollowsT(s, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1", "2", "4"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

			// --------------------------------------------------
			//                  LHS wild
			// --------------------------------------------------
			// getFollows(LHS wild, RHS int)
		SECTION("Follows(_, 2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("_", "2", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(_, 3) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("_", "3", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(_, 5) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("_", "5", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Follows(_, 1) negative query") {
			QueryClauseResult res = followsEvaluator.getFollows("_", "1", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollowsT(LHS wild, RHS int)
		SECTION("FollowsT(_, 2) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("_", "2", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(_, 3) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("_", "3", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(_, 5) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("_", "5", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("FollowsT(_, 1) negative query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("_", "1", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.containsValidResult() == false);
		}

			// getFollows(LHS wild, RHS stmt)
		SECTION("Follows(_, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"2", "3", "5"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

			// getFollowsT(LHS wild, RHS stmt)
		SECTION("FollowsT(_, s) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"2", "3", "5"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

			// getFollows(LHS wild, RHS wild)
		SECTION("Follows(_, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollows("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		// getFollowsT(LHS wild, RHS wild)
		SECTION("FollowsT(_, _) positive query") {
			QueryClauseResult res = followsEvaluator.getFollowsT("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}
	}
	PKB::clearAllStores();
}
