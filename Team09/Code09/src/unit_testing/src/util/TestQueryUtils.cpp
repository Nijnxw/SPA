#include "catch.hpp"
#include "../src/util/QueryUtils.h"
#include "models/QueryClauseResult.h"

TEST_CASE("join without common headers returns empty") {
	Table firstTable = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};
	Table secondTable = {
		{"c", {"1", "2",  "3",  "4"}},
		{"d", {"9", "10", "11", "12"}}
	};
	Table expectedTable = {};
	Table actualTable = QueryUtils::hashJoin(firstTable, secondTable);
	QueryClauseResult expected = QueryClauseResult(expectedTable);
	QueryClauseResult actual = QueryClauseResult(actualTable);

	REQUIRE(actual == expected);
}

TEST_CASE("join with single common header returns natural-joined tables") {
	Table firstTable = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};
	Table secondTable = {
		{"a", {"1", "2",  "3",  "4"}},
		{"c", {"9", "10", "11", "12"}}
	};
	Table expectedTable = {
		{"a", {"1", "2",  "3",  "4"}},
		{"b", {"5", "6",  "7",  "8"}},
		{"c", {"9", "10", "11", "12"}}
	};
	Table actualTable = QueryUtils::hashJoin(firstTable, secondTable);
	QueryClauseResult expected = QueryClauseResult(expectedTable);
	QueryClauseResult actual = QueryClauseResult(actualTable);

	REQUIRE(actual == expected);
}

TEST_CASE("join with single common header returns natural-joined tables with values after cross product") {
	Table firstTable = {
		{"a", {"1", "1", "2", "2"}},
		{"b", {"5", "6", "7", "8"}}
	};
	Table secondTable = {
		{"a", {"1", "1",  "2",  "3"}},
		{"c", {"9", "10", "11", "12"}}
	};
	Table expectedTable = {
		{"a", {"1", "1",  "1", "1",  "2",  "2"}},
		{"b", {"5", "5",  "6", "6",  "7",  "8"}},
		{"c", {"9", "10", "9", "10", "11", "11"}}
	};
	Table actualTable = QueryUtils::hashJoin(firstTable, secondTable);
	QueryClauseResult expected = QueryClauseResult(expectedTable);
	QueryClauseResult actual = QueryClauseResult(actualTable);

	REQUIRE(actual == expected);
}

TEST_CASE("join with multiple common headers returns natural-joined tables") {
	Table firstTable = {
		{"a", {"1", "2",  "3",  "4"}},
		{"b", {"5", "6",  "7",  "8"}},
		{"c", {"9", "10", "13", "14"}}
	};
	Table secondTable = {
		{"a", {"1", "2",  "3",  "4"}},
		{"c", {"9", "10", "11", "12"}}
	};
	Table expectedTable = {
		{"a", {"1", "2"}},
		{"b", {"5", "6"}},
		{"c", {"9", "10"}}
	};
	Table actualTable = QueryUtils::hashJoin(firstTable, secondTable);
	QueryClauseResult expected = QueryClauseResult(expectedTable);
	QueryClauseResult actual = QueryClauseResult(actualTable);

	REQUIRE(actual == expected);
}

TEST_CASE("join with duplicate common values returns natural-joined tables with values after cross product") {
	Table firstTable = {
		{"a", {"1", "1", "3",  "4"}},
		{"b", {"5", "6", "7",  "8"}},
		{"c", {"9", "9", "11", "12"}}
	};
	Table secondTable = {
		{"a", {"1",  "1",  "3",  "4"}},
		{"c", {"9",  "9",  "11", "12"}},
		{"d", {"13", "14", "15", "16"}}
	};
	Table expectedTable = {
		{"a", {"1",  "1",  "1",  "1",  "3",  "4"}},
		{"b", {"5",  "5",  "6",  "6",  "7",  "8"}},
		{"c", {"9",  "9",  "9",  "9",  "11", "12"}},
		{"d", {"13", "14", "13", "14", "15", "16"}}
	};
	Table actualTable = QueryUtils::hashJoin(firstTable, secondTable);
	QueryClauseResult expected = QueryClauseResult(expectedTable);
	QueryClauseResult actual = QueryClauseResult(actualTable);

	REQUIRE(actual == expected);
}

TEST_CASE("join with exactly same columns returns intersection of table") {
	Table firstTable = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"2", "3", "4", "5"}},
	};

	Table secondTable = {
		{"a", {"2", "3", "5", "6"}},
		{"b", {"3", "4", "6", "7"}},
	};

	Table expectedTable = {
		{"a", {"2", "3"}},
		{"b", {"3", "4"}},
	};
	Table actualTable = QueryUtils::hashJoin(firstTable, secondTable);
	QueryClauseResult expected = QueryClauseResult(expectedTable);
	QueryClauseResult actual = QueryClauseResult(actualTable);

	REQUIRE(actual == expected);
}

TEST_CASE("stringify rows of table with single column with valid column order returns space separated values") {
	Table table = {
		{"a", {"1", "2", "3", "4"}}
	};
	std::vector<std::string> colOrder = {"a"};
	std::unordered_set<std::string> expected = {"1", "2", "3", "4"};
	std::unordered_set<std::string> actual = QueryUtils::stringifyRows(table, colOrder);

	REQUIRE(actual == expected);
}

TEST_CASE("stringify rows of table with single column with invalid column order returns empty set") {
	Table table = {
		{"a", {"1", "2", "3", "4"}}
	};
	std::vector<std::string> colOrder = {"b"};
	std::unordered_set<std::string> actual = QueryUtils::stringifyRows(table, colOrder);

	REQUIRE(actual.empty());
}

TEST_CASE("stringify rows of table with multiple columns with valid column order returns space separated values") {
	Table table = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};
	std::vector<std::string> colOrder = {"a",
										 "b"};
	std::unordered_set<std::string> expected = {"1 5", "2 6", "3 7", "4 8"};
	std::unordered_set<std::string> actual = QueryUtils::stringifyRows(table, colOrder);

	REQUIRE(actual == expected);
}

TEST_CASE(
	"stringify rows of table with multiple columns with valid subset column order returns space separated values") {
	Table table = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};
	std::vector<std::string> colOrder = {"a"};
	std::unordered_set<std::string> expected = {"1", "2", "3", "4"};
	std::unordered_set<std::string> actual = QueryUtils::stringifyRows(table, colOrder);

	REQUIRE(actual == expected);
}

TEST_CASE("stringify rows of table with multiple columns with invalid column order returns empty set") {
	Table table = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};
	std::vector<std::string> colOrder = {"c"};
	std::unordered_set<std::string> actual = QueryUtils::stringifyRows(table, colOrder);

	REQUIRE(actual.empty());
}

TEST_CASE("stringify rows of table with single column without column order returns space separated values") {
	Table table = {
		{"a", {"1", "2", "3", "4"}}
	};
	std::unordered_set<std::string> expected = {"1", "2", "3", "4"};
	std::unordered_set<std::string> actual = QueryUtils::stringifyRows(table);

	REQUIRE(actual == expected);
}

TEST_CASE("stringify rows of table with multiple columns without column order returns space separated values") {
	Table table = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};
	std::unordered_set<std::string> expected = {"1 5", "2 6", "3 7", "4 8"};
	std::unordered_set<std::string> actual = QueryUtils::stringifyRows(table);

	REQUIRE(actual == expected);
}
