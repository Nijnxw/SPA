#include "catch.hpp"
#include "../src/util/QueryUtils.h"

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
    QueryResultTable expected = QueryResultTable(expectedTable);
    QueryResultTable actual = QueryResultTable(actualTable);

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
    QueryResultTable expected = QueryResultTable(expectedTable);
    QueryResultTable actual = QueryResultTable(actualTable);

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
    QueryResultTable expected = QueryResultTable(expectedTable);
    QueryResultTable actual = QueryResultTable(actualTable);

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
    QueryResultTable expected = QueryResultTable(expectedTable);
    QueryResultTable actual = QueryResultTable(actualTable);

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
    QueryResultTable expected = QueryResultTable(expectedTable);
    QueryResultTable actual = QueryResultTable(actualTable);

    REQUIRE(actual == expected);
}
