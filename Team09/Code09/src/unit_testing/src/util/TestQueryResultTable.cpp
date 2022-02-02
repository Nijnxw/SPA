#include "catch.hpp"
#include "models/QueryResultTable.h"

TEST_CASE("storing and retriving correctly", "[QueryResultTable]") {
    SECTION("no result stored") {
        Table emptyTable({});
        QueryResultTable testTable = QueryResultTable();
        REQUIRE(testTable.getTable() == emptyTable);
        REQUIRE(testTable.getBooleanResult() == false);
    }
    SECTION("adding different type of columns with addColumn() and retrieving") {
        Table testColWithHeader = { {"s", {"1","2","3"}} };
        SECTION("instantiate with data and retrieving") {
            QueryResultTable testTable = QueryResultTable(testColWithHeader);
            REQUIRE(testTable.getTable() == testColWithHeader);
            REQUIRE(testTable.getBooleanResult() == true);
        }

        SECTION("instantiate without data, addColumn(std::vector<std::string>>) and getTable()") {
            QueryResultTable testTable = QueryResultTable();
            std::vector<std::string> testCol({ "1", "2", "3" });
            testTable.addColumn("s", testCol);
            REQUIRE(testTable.getTable() == testColWithHeader);
            REQUIRE(testTable.getBooleanResult() == true);
        }

        SECTION("instantiate without data, addColumn(std::vector<int>>) and getTable()") {
            QueryResultTable testTable = QueryResultTable();
            std::vector<int> testCol({ 1, 2, 3 });
            testTable.addColumn("s", testCol);
            REQUIRE(testTable.getTable() == testColWithHeader);
            REQUIRE(testTable.getBooleanResult() == true);
        }

        SECTION("instantiate without data, addColumn(std::unoredered_set<std::string>>) and getTable()") {
            QueryResultTable testTable = QueryResultTable();
            std::unordered_set<std::string> testCol({ "1", "2", "3" });
            testTable.addColumn("s", testCol);
            REQUIRE(testTable.getTable() == testColWithHeader);
            REQUIRE(testTable.getBooleanResult() == true);
        }

        SECTION("instantiate without data, addColumn(std::unoredered_set<int>>) and getTable()") {
            QueryResultTable testTable = QueryResultTable();
            std::unordered_set<int> testCol({ 1, 2, 3 });
            testTable.addColumn("s", testCol);
            REQUIRE(testTable.getTable() == testColWithHeader);
            REQUIRE(testTable.getBooleanResult() == true);
        }
    }
    SECTION("adding and retrieving 2 column") {
        Table table = { {"s", {"1","2","3"}}, {"v", {"x","y","z"}} };
        SECTION("instantiate without data, addColumn() twice and getTable()") {
            QueryResultTable testTable = QueryResultTable();
            std::unordered_set<int> testCol1({ 1, 2, 3 });
            testTable.addColumn("s", testCol1);
            std::vector<std::string> testCol2({ "x", "y", "z" });
            testTable.addColumn("v", testCol2);
            REQUIRE(testTable.getTable() == table);
            REQUIRE(testTable.getBooleanResult() == true);
        }
    }
}
