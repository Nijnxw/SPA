#include "catch.hpp"
#include "models/QueryClauseResult.h"

TEST_CASE("storing and retriving correctly", "[QueryClauseResult]") {
	SECTION("no result stored") {
		Table emptyTable({});
		QueryClauseResult testTable = QueryClauseResult();
		REQUIRE(testTable == QueryClauseResult(emptyTable));
		REQUIRE(testTable.containsValidResult() == false);
	} SECTION("adding different type of columns with addColumn() and retrieving") {
		Table testColWithHeader = {{"s", {"1", "2", "3"}}};
		SECTION("instantiate with data and retrieving") {
			QueryClauseResult testTable = QueryClauseResult(testColWithHeader);
			REQUIRE(testTable == QueryClauseResult(testColWithHeader));
			REQUIRE(testTable.containsValidResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::vector<std::string>>) and getTable()") {
			QueryClauseResult testTable = QueryClauseResult();
			std::vector<std::string> testCol({"1", "2", "3"});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseResult(testColWithHeader));
			REQUIRE(testTable.containsValidResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::vector<int>>) and getTable()") {
			QueryClauseResult testTable = QueryClauseResult();
			std::vector<int> testCol({1, 2, 3});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseResult(testColWithHeader));
			REQUIRE(testTable.containsValidResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::unoredered_set<std::string>>) and getTable()") {
			QueryClauseResult testTable = QueryClauseResult();
			std::unordered_set<std::string> testCol({"1", "2", "3"});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseResult(testColWithHeader));
			REQUIRE(testTable.containsValidResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::unoredered_set<int>>) and getTable()") {
			QueryClauseResult testTable = QueryClauseResult();
			std::unordered_set<int> testCol({1, 2, 3});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseResult(testColWithHeader));
			REQUIRE(testTable.containsValidResult() == true);
		}
	} SECTION("adding and retrieving 2 column") {
		Table table = {{"s", {"1", "2", "3"}},
					   {"v", {"x", "y", "z"}}};
		SECTION("instantiate without data, addColumn() twice and getTable()") {
			QueryClauseResult testTable = QueryClauseResult();
			std::vector<int> testCol1({1, 2, 3});
			testTable.addColumn("s", testCol1);
			std::vector<std::string> testCol2({"x", "y", "z"});
			testTable.addColumn("v", testCol2);
			REQUIRE(testTable == QueryClauseResult(table));
			REQUIRE(testTable.containsValidResult() == true);
		}
	}
}
