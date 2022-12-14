#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/ComplexASTs.h"
#include "asts/EntityASTs.h"

//#include <memory>
#include <unordered_set>
#include <vector>

TEST_CASE("Entity 2.1 - Extract basic read") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_1(), EntityASTs::getStmtCount2_1());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{};
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 1 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {1, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.2 - Extract basic print") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_2(), EntityASTs::getStmtCount2_2());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 1 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ {1, "x"} };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.3 - Extract single assign - single constant") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_3(), EntityASTs::getStmtCount2_3());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "1"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.4 - Extract single assign - single variable") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_4(), EntityASTs::getStmtCount2_4());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x"};
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "x"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.5 - Extract single assign - two variables") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_5(), EntityASTs::getStmtCount2_5());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "x y +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.6 - Extract single assign - two constants") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_6(), EntityASTs::getStmtCount2_6());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "1 2 +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}


TEST_CASE("Entity 2.7 - Extract single assign - one constant one variable") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_7(), EntityASTs::getStmtCount2_7());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "x 1 +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.8 - Extract advanced assign 1") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_8(), EntityASTs::getStmtCount2_8());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x", "y", "z"};
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2", "3"};
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "1 x y 2 z / 3 % - * +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.9 - Extract advanced assign 2") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_9(), EntityASTs::getStmtCount2_9());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x", "y", "z" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2", "3" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "1 x y 2 - * z 3 % / +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.10 - While stmt - Constant to Constant comparison") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_10(), EntityASTs::getStmtCount2_10());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ 
		{1, {}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.11 - While stmt - Variable to variable comparison") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_11(), EntityASTs::getStmtCount2_11());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y"};
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.12 - While stmt - Variable to variable comparison") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_12(), EntityASTs::getStmtCount2_12());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.13 - While stmt - Term Expr comparison") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_13(), EntityASTs::getStmtCount2_13());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.14 - While stmt - Expr Term comparison") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_14(), EntityASTs::getStmtCount2_14());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.15 - While stmt - Expr Expr comparison") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_15(), EntityASTs::getStmtCount2_15());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.16 - While stmt - Advanced") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_16(), EntityASTs::getStmtCount2_16());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.17 - While stmt - Advanced") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_17(), EntityASTs::getStmtCount2_17());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.18 - While stmt - Advanced") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_18(), EntityASTs::getStmtCount2_18());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.19 - While stmt - Advanced") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_19(), EntityASTs::getStmtCount2_19());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.20 - While stmt - NOT in predicate") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_20(), EntityASTs::getStmtCount2_20());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.21 - While stmt - AND in predicate") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_21(), EntityASTs::getStmtCount2_21());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "3" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.22 - While stmt - OR in predicate") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_22(), EntityASTs::getStmtCount2_22());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "3" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ {2, "x"} };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.23 - While stmt - all statements nested within while stmt") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_23(), EntityASTs::getStmtCount2_23());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 3, 7 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2, 6, 9 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1, 8 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 5 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ 
		{3, "x"}, {7, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{2, "x"}, {6, "y"}, {9, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x"}}, {8, {"y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{5, {"y"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{4, "a", "x 1 +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.24 - If stmt - If-Read") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_24(), EntityASTs::getStmtCount2_24());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2, 3 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{2, "x"}, {3, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.25 - If stmt - If-Print") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_25(), EntityASTs::getStmtCount2_25());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 2, 3 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{2, "x"}, {3, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.26 - If stmt - If-Assign") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_26(), EntityASTs::getStmtCount2_26());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{2, "a", "x 1 +"},
		{3, "a", "y 1 +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.27 - If stmt - If-If(then)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_27(), EntityASTs::getStmtCount2_27());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 4, 5 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 3 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{4, "y"}, {5, "x"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{3, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}, {2, {"y"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.28 - If stmt - If-If(else)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_28(), EntityASTs::getStmtCount2_28());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 5 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2, 4 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1, 3 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{5, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{2, "x"}, {4, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}, {3, {"y"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.29 - If stmt - If-While(then)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_29(), EntityASTs::getStmtCount2_29());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 4 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 3 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 2 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{4, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{3, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{2, {"y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.30 - If stmt - If-While(else)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_30(), EntityASTs::getStmtCount2_30());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2, 4 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 3 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{2, "x"}, {4, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{3, {"y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.31 - If stmt - Every stmt in then") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_31(), EntityASTs::getStmtCount2_31());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x", "y", "z" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 3, 7, 10 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2, 6, 9 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 8 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1, 5 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{3, "x"}, {7, "y"}, {10, "x"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{2, "x"}, {6, "y"}, {9, "z"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{8, {"z"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}, {5, {"y"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{4, "a", "x 1 +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.32 - If stmt - Every stmt in else") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_32(), EntityASTs::getStmtCount2_32());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "x", "y", "z" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 4, 8 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2, 3, 7, 10 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 9 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1, 6 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{4, "x"}, {8, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{2, "x"}, {3, "x"}, {7, "y"}, {10, "z"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{9, {"z"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}, {6, {"y"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{5, "a", "x 1 +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.33 - 2 procedures; First: Read Second : If") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_33(), EntityASTs::getStmtCount2_33());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2"};
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y", "z" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5, 6 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 6 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 1, 3, 5 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 2, 4 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{6, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{1, "z"}, {3, "x"}, {5, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{2, {"x"}}, {4, {"y"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.34 - 2 procedures; First: Print Second : While") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_34(), EntityASTs::getStmtCount2_34());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y", "z" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2"};
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 1 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 3 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 2 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{1, "z"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{3, "x"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{2, {"x", "y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.35 - 2 procedures; First: Assignment Second : Print") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_35(), EntityASTs::getStmtCount2_35());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "a", "b", "x", "y", "z" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "2", "3" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 2 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{2, "b"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{1, "a", "1 x y 2 - * z 3 % / +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.36 - 2 procedures; First: While Second : Read") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_36(), EntityASTs::getStmtCount2_36());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 3, 4 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{ };
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{3, "y"}, {4, "x"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x"}}, {2, {"y"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.37 - 2 procedures; First: If Second : Assignment") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_37(), EntityASTs::getStmtCount2_37());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y", "a"};
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1", "3" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5, 6 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 5 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 2, 4 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1, 3 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{5, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{
		{2, "x"}, {4, "y"}
	};
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}, {3, {"y"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{6, "a", "1 x 3 * + y %"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.38 - Test call statement") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_38(), EntityASTs::getStmtCount2_38());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 2 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_set<int> expectedCallsTable{ 1 };
	REQUIRE(EntityStager::getStagedCallStatements() == expectedCallsTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{2, "x"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::unordered_map<int, std::string> expectedCallContents{
		{1, "testProgram2"}
	};
	REQUIRE(EntityStager::getStagedCallContent() == expectedCallContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.39 - Test call statement (opposite order)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_39(), EntityASTs::getStmtCount2_39());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 1 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_set<int> expectedCallsTable{ 2 };
	REQUIRE(EntityStager::getStagedCallStatements() == expectedCallsTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{1, "x"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::unordered_map<int, std::string> expectedCallContents{
		{2, "testProgram"}
	};
	REQUIRE(EntityStager::getStagedCallContent() == expectedCallContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.40 - Call nested in If - second program") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_40(), EntityASTs::getStmtCount2_40());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 2, 4 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 1 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_set<int> expectedCallsTable{ 3 };
	REQUIRE(EntityStager::getStagedCallStatements() == expectedCallsTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{2, "x"}, {4, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::unordered_map<int, std::string> expectedCallContents{
		{3, "testProgram2"}
	};
	REQUIRE(EntityStager::getStagedCallContent() == expectedCallContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.41 - Call nested in If - second program") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_41(), EntityASTs::getStmtCount2_41());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 1, 3 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 2 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_set<int> expectedCallsTable{ 4 };
	REQUIRE(EntityStager::getStagedCallStatements() == expectedCallsTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{1, "x"}, {3, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{ };
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{
		{2, {"x"}}
	};
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::unordered_map<int, std::string> expectedCallContents{
		{4, "testProgram"}
	};
	REQUIRE(EntityStager::getStagedCallContent() == expectedCallContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 2.42 - Call nested in While") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(EntityASTs::getAST2_42(), EntityASTs::getStmtCount2_42());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram", "testProgram2" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "1" };
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 3 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 1 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::unordered_set<int> expectedCallsTable{ 2 };
	REQUIRE(EntityStager::getStagedCallStatements() == expectedCallsTable);

	std::unordered_map<int, std::string> expectedPrintContents{
		{3, "y"}
	};
	REQUIRE(EntityStager::getStagedPrintContents() == expectedPrintContents);

	std::unordered_map<int, std::string> expectedReadContents{ };
	REQUIRE(EntityStager::getStagedReadContents() == expectedReadContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedWhileContents{
		{1, {"x"}}
	};
	REQUIRE(EntityStager::getStagedWhileContents() == expectedWhileContents);

	std::unordered_map<int, std::unordered_set<std::string>> expectedIfContents{ };
	REQUIRE(EntityStager::getStagedIfContents() == expectedIfContents);

	std::unordered_map<int, std::string> expectedCallContents{
		{2, "testProgram2"}
	};
	REQUIRE(EntityStager::getStagedCallContent() == expectedCallContents);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

TEST_CASE("Entity 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(ComplexASTs::getAST4_1(), ComplexASTs::getStmtCount4_1());
	de.extractDesignElements();

	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);

	std::unordered_set<std::string> expectedVarTable{ "x", "y", "length", "t", "tan", "sin", "cos"};
	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);

	std::unordered_set<std::string> expectedConstTable{ "30", "0", "1", "2", "10"};
	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);

	std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);

	std::unordered_set<int> expectedPrintTable{ 18 };
	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);

	std::unordered_set<int> expectedReadTable{ 1, 2 };
	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);

	std::unordered_set<int> expectedWhileTable{ 6 };
	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);

	std::unordered_set<int> expectedIfTable{ 5, 10 };
	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
		{3, "length", "x x * y y * +"},
		{4, "t", "30"},
		{7, "tan", "y x /"},
		{8, "sin", "y length / cos *"},
		{9, "cos", "x length / sin *"},
		{11, "x", "y 2 /"},
		{12, "y", "x 2 /"},
		{13, "x", "0"},
		{14, "length", "x x * y y * +"},
		{15, "x", "10"},
		{16, "y", "10"},
		{17, "length", "x x * y y * +"}
	};
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}