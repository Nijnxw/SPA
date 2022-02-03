#include "catch.hpp"
#include "pkb/stores/FollowsStore.h"

TEST_CASE("FollowsStore API") {
	// The same store is reused through tests, so clearing is a must.
	FollowsStore::clear();  

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		FollowsStore::addFollows(1, 2);
		FollowsStore::addFollows(2, 3);
		FollowsStore::addFollows(4, 5);

		FollowsStore::addFollowsT(1, 2);
		FollowsStore::addFollowsT(2, 3);
		FollowsStore::addFollowsT(1, 3);
		FollowsStore::addFollowsT(4, 5);

		// --------------------------------------------------
		//                  LHS int
		// --------------------------------------------------
		// getFollows(LHS int, RHS int)
		SECTION("Follows(1, 2) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(2, 3) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("2", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(4, 5) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("4", "5", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(1, 3) negative query") {
			QueryClauseTable res = FollowsStore::getFollows("1", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollowsT(LHS int, RHS int)
		SECTION("FollowsT(1, 2) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(2, 3) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("2", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(4, 5) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("4", "5", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(1, 3) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("1", "3", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(1, 4) negative query") {
			QueryClauseTable res = FollowsStore::getFollowsT("1", "4", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		// getFollows(LHS int, RHS stmt)
		SECTION("Follows(1, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("1", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Follows(2, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("2", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Follows(4, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("4", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Follows(3, s) negative query") {
			QueryClauseTable res = FollowsStore::getFollows("3", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollowsT(LHS int, RHS stmt)
		SECTION("FollowsT(1, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("1", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"2", "3"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("FollowsT(2, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("2", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("FollowsT(4, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("4", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("FollowsT(3, s) negative query") {
			QueryClauseTable res = FollowsStore::getFollowsT("3", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollows(LHS int, RHS wild)
		SECTION("Follows(1, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(2, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("2", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(4, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("4", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(3, _) negative query") {
			QueryClauseTable res = FollowsStore::getFollows("3", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollowsT(LHS int, RHS wild)
		SECTION("FollowsT(1, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(2, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("2", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(4, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("4", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(3, _) negative query") {
			QueryClauseTable res = FollowsStore::getFollowsT("3", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		// --------------------------------------------------
		//                  LHS stmt
		// --------------------------------------------------
		// getFollows(LHS stmt, RHS int)
		SECTION("Follows(s, 2) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("s", "2", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"1"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Follows(s, 3) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("s", "3", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Follows(s, 5) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("s", "5", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"4"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Follows(s, 1) negative query") {
			QueryClauseTable res = FollowsStore::getFollows("s", "1", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollowsT(LHS stmt, RHS int)
		SECTION("FollowsT(s, 2) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("s", "2", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"1"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("FollowsT(s, 3) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("s", "3", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"1", "2"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("FollowsT(s, 5) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("s", "5", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"4"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("FollowsT(s, 1) negative query") {
			QueryClauseTable res = FollowsStore::getFollowsT("s", "1", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollows(LHS stmt, RHS stmt)
		SECTION("Follows(s1, s2) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s1", {"1", "2", "4"}},
				{"s2", {"2", "3", "5"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getFollowsT(LHS stmt, RHS stmt)
		SECTION("FollowsT(s1, s2) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s1", {"1", "1", "2", "4"}},
				{"s2", {"2", "3", "3", "5"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getFollows(LHS stmt, RHS wild)
		SECTION("Follows(s, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"2", "3", "5"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getFollowsT(LHS stmt, RHS wild)
		SECTION("FollowsT(s, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"2", "3", "5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS stmt
		// --------------------------------------------------
		// getFollows(LHS wild, RHS int)
		SECTION("Follows(_, 2) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("_", "2", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(_, 3) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("_", "3", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(_, 5) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("_", "5", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Follows(_, 1) negative query") {
			QueryClauseTable res = FollowsStore::getFollows("_", "1", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollowsT(LHS wild, RHS int)
		SECTION("FollowsT(_, 2) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("_", "2", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(_, 3) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("_", "3", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(_, 5) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("_", "5", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("FollowsT(_, 1) negative query") {
			QueryClauseTable res = FollowsStore::getFollowsT("_", "1", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getFollows(LHS wild, RHS stmt)
		SECTION("Follows(_, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"1", "2", "4"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getFollowsT(LHS wild, RHS stmt)
		SECTION("FollowsT(_, s) positive query") {
			QueryClauseTable res = FollowsStore::getFollowsT("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"2", "3", "5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getFollows(LHS wild, RHS wild)
		SECTION("Follows(_, _) positive query") {
			QueryClauseTable res = FollowsStore::getFollows("_", "s", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}
	}
	FollowsStore::clear();
}
