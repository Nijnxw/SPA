#include "catch.hpp"
#include "models/QueryClauseTable.h"

TEST_CASE("storing and retriving correctly", "[QueryClauseTable]") {
	SECTION("no result stored") {
		Table emptyTable({});
		QueryClauseTable testTable = QueryClauseTable();
		REQUIRE(testTable == QueryClauseTable(emptyTable));
		REQUIRE(testTable.getBooleanResult() == false);
	} SECTION("adding different type of columns with addColumn() and retrieving") {
		Table testColWithHeader = {{"s", {"1", "2", "3"}}};
		SECTION("instantiate with data and retrieving") {
			QueryClauseTable testTable = QueryClauseTable(testColWithHeader);
			REQUIRE(testTable == QueryClauseTable(testColWithHeader));
			REQUIRE(testTable.getBooleanResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::vector<std::string>>) and getTable()") {
			QueryClauseTable testTable = QueryClauseTable();
			std::vector<std::string> testCol({"1", "2", "3"});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseTable(testColWithHeader));
			REQUIRE(testTable.getBooleanResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::vector<int>>) and getTable()") {
			QueryClauseTable testTable = QueryClauseTable();
			std::vector<int> testCol({1, 2, 3});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseTable(testColWithHeader));
			REQUIRE(testTable.getBooleanResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::unoredered_set<std::string>>) and getTable()") {
			QueryClauseTable testTable = QueryClauseTable();
			std::unordered_set<std::string> testCol({"1", "2", "3"});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseTable(testColWithHeader));
			REQUIRE(testTable.getBooleanResult() == true);
		}

		SECTION("instantiate without data, addColumn(std::unoredered_set<int>>) and getTable()") {
			QueryClauseTable testTable = QueryClauseTable();
			std::unordered_set<int> testCol({1, 2, 3});
			testTable.addColumn("s", testCol);
			REQUIRE(testTable == QueryClauseTable(testColWithHeader));
			REQUIRE(testTable.getBooleanResult() == true);
		}
	} SECTION("adding and retrieving 2 column") {
		Table table = {{"s", {"1", "2", "3"}},
					   {"v", {"x", "y", "z"}}};
		SECTION("instantiate without data, addColumn() twice and getTable()") {
			QueryClauseTable testTable = QueryClauseTable();
			std::vector<int> testCol1({1, 2, 3});
			testTable.addColumn("s", testCol1);
			std::vector<std::string> testCol2({"x", "y", "z"});
			testTable.addColumn("v", testCol2);
			REQUIRE(testTable == QueryClauseTable(table));
			REQUIRE(testTable.getBooleanResult() == true);
		}
	}
}
