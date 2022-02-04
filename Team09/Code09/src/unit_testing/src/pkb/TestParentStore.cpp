#include "catch.hpp"
#include "pkb/stores/ParentStore.h"

TEST_CASE("ParentStore API") {
	// The same store is reused through tests, so clearing is a must.
	ParentStore::clear();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		ParentStore::addParent(3, 4);
		ParentStore::addParent(3, 5);
		ParentStore::addParent(5, 6);

		ParentStore::addParentT(3, 4);
		ParentStore::addParentT(3, 5);
		ParentStore::addParentT(5, 6);
		ParentStore::addParentT(3, 6);

		// --------------------------------------------------
		//                  LHS int
		// --------------------------------------------------
		// getParent(LHS int, RHS int)
		SECTION("Parent(3, 4) positive query") {
			QueryClauseTable res = ParentStore::getParent("3", "4", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(3, 5) positive query") {
			QueryClauseTable res = ParentStore::getParent("3", "5", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(5, 6) positive query") {
			QueryClauseTable res = ParentStore::getParent("5", "6", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(1, 2) negative query") {
			QueryClauseTable res = ParentStore::getParent("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParentT(LHS int, RHS int)
		SECTION("ParentT(3, 4) positive query") {
			QueryClauseTable res = ParentStore::getParentT("3", "4", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(3, 5) positive query") {
			QueryClauseTable res = ParentStore::getParentT("3", "5", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(5, 6) positive query") {
			QueryClauseTable res = ParentStore::getParentT("5", "6", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(3, 6) positive query") {
			QueryClauseTable res = ParentStore::getParentT("5", "6", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(1, 2) negative query") {
			QueryClauseTable res = ParentStore::getParentT("1", "2", EntityType::INT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParent(LHS int, RHS stmt)
		SECTION("Parent(3, s) positive query") {
			QueryClauseTable res = ParentStore::getParent("3", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"4", "5"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Parent(5, s) positive query") {
			QueryClauseTable res = ParentStore::getParent("5", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"6"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Parent(1, s) negative query") {
			QueryClauseTable res = ParentStore::getParent("1", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParentT(LHS int, RHS stmt)
		SECTION("ParentT(3, s) positive query") {
			QueryClauseTable res = ParentStore::getParentT("3", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"4", "5", "6"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("ParentT(5, s) positive query") {
			QueryClauseTable res = ParentStore::getParentT("5", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"6"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("ParentT(1, s) negative query") {
			QueryClauseTable res = ParentStore::getParentT("1", "s", EntityType::INT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParent(LHS int, RHS wild)
		SECTION("Parent(3, _) positive query") {
			QueryClauseTable res = ParentStore::getParent("3", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(5, _) positive query") {
			QueryClauseTable res = ParentStore::getParent("5", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(1, _) negative query") {
			QueryClauseTable res = ParentStore::getParent("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParentT(LHS int, RHS wild)
		SECTION("ParentT(3, _) positive query") {
			QueryClauseTable res = ParentStore::getParentT("3", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(5, _) positive query") {
			QueryClauseTable res = ParentStore::getParentT("5", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(1, _) negative query") {
			QueryClauseTable res = ParentStore::getParentT("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// --------------------------------------------------
		//                  LHS stmt
		// --------------------------------------------------
		// getParent(LHS stmt, RHS int)
		SECTION("Parent(s, 4) positive query") {
			QueryClauseTable res = ParentStore::getParent("s", "4", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Parent(s, 5) positive query") {
			QueryClauseTable res = ParentStore::getParent("s", "5", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Parent(s, 6) positive query") {
			QueryClauseTable res = ParentStore::getParent("s", "6", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Parent(s, 3) negative query") {
			QueryClauseTable res = ParentStore::getParent("s", "3", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParentT(LHS stmt, RHS int)
		SECTION("ParentT(s, 4) positive query") {
			QueryClauseTable res = ParentStore::getParentT("s", "4", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("ParentT(s, 5) positive query") {
			QueryClauseTable res = ParentStore::getParentT("s", "5", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("ParentT(s, 6) positive query") {
			QueryClauseTable res = ParentStore::getParentT("s", "6", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3", "5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("ParentT(s, 3) negative query") {
			QueryClauseTable res = ParentStore::getParentT("s", "3", EntityType::STMT, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParent(LHS stmt, RHS stmt)
		SECTION("Parent(s1, s2) positive query") {
			QueryClauseTable res = ParentStore::getParent("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s1", {"3", "3", "5"}},
				{"s2", {"4", "5", "6"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getParentT(LHS stmt, RHS stmt)
		SECTION("ParentT(s1, s2) positive query") {
			QueryClauseTable res = ParentStore::getParentT("s1", "s2", EntityType::STMT, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s1", {"3", "3", "3", "5"}},
				{"s2", {"4", "5", "6", "6"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getParent(LHS stmt, RHS wild)
		SECTION("Parent(s, _) positive query") {
			QueryClauseTable res = ParentStore::getParent("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3", "5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getParentT(LHS stmt, RHS wild)
		SECTION("ParentT(s, _) positive query") {
			QueryClauseTable res = ParentStore::getParentT("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"3", "5"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS stmt
		// --------------------------------------------------
		// getParent(LHS wild, RHS int)
		SECTION("Parent(_, 4) positive query") {
			QueryClauseTable res = ParentStore::getParent("_", "4", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(_, 5) positive query") {
			QueryClauseTable res = ParentStore::getParent("_", "5", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(_, 6) positive query") {
			QueryClauseTable res = ParentStore::getParent("_", "6", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Parent(_, 1) negative query") {
			QueryClauseTable res = ParentStore::getParent("_", "1", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParentT(LHS wild, RHS int)
		SECTION("ParentT(_, 4) positive query") {
			QueryClauseTable res = ParentStore::getParentT("_", "4", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(_, 5) positive query") {
			QueryClauseTable res = ParentStore::getParentT("_", "5", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(_, 6) positive query") {
			QueryClauseTable res = ParentStore::getParentT("_", "6", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("ParentT(_, 1) negative query") {
			QueryClauseTable res = ParentStore::getParentT("_", "1", EntityType::WILD, EntityType::INT, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		// getParent(LHS wild, RHS stmt)
		SECTION("Parent(_, s) positive query") {
			QueryClauseTable res = ParentStore::getParent("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"4", "5", "6"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getParentT(LHS wild, RHS stmt)
		SECTION("ParentT(_, s) positive query") {
			QueryClauseTable res = ParentStore::getParentT("_", "s", EntityType::WILD, EntityType::STMT, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = { {"s", {"4", "5", "6"}} };
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		// getParent(LHS wild, RHS wild)
		SECTION("Parent(_, _) positive query") {
			QueryClauseTable res = ParentStore::getParent("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}
	}
	ParentStore::clear();
}