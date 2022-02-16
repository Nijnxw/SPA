#include "catch.hpp"
//#include "models/EntityType.h"
//#include "models/simple_parser/AST.h"
//#include "models/simple_parser/ExprNodes.h"
//#include "models/simple_parser/IoNodes.h"
//#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/EntityASTs.h"

//#include <memory>
#include <unordered_set>
#include <vector>

TEST_CASE("Entity 2.1 - Extract basic read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_1());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_2());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_3());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_4());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_5());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_6());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_7());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_8());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_9());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_10());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_11());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_12());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_13());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_14());

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
	DesignExtractor::extractDesignElements(EntityASTs::getAST2_15());

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

	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });

	REQUIRE(actualAssignTable == expectedAssignTable);

	EntityStager::clear();
}

//TEST_CASE("Entity 2.16 - While stmt - Advanced") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(EntityASTs::getAST2_16());
//
//	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
//	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
//	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//	std::unordered_set<int> expectedStmtTable{ 1, 2 };
//	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//	std::unordered_set<int> expectedPrintTable{ };
//	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);
//
//	std::unordered_set<int> expectedReadTable{ 2 };
//	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);
//
//	std::unordered_set<int> expectedWhileTable{ 1 };
//	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);
//
//	std::unordered_set<int> expectedIfTable{ };
//	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);
//
//	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
//	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
//	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	REQUIRE(actualAssignTable == expectedAssignTable);
//
//	EntityStager::clear();
//}

//TEST_CASE("Entity 2.17 - While stmt - Advanced") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(EntityASTs::getAST2_17());
//
//	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
//	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
//	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//	std::unordered_set<int> expectedStmtTable{ 1, 2 };
//	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//	std::unordered_set<int> expectedPrintTable{ };
//	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);
//
//	std::unordered_set<int> expectedReadTable{ 2 };
//	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);
//
//	std::unordered_set<int> expectedWhileTable{ 1 };
//	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);
//
//	std::unordered_set<int> expectedIfTable{ };
//	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);
//
//	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
//	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
//	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	REQUIRE(actualAssignTable == expectedAssignTable);
//
//	EntityStager::clear();
//}

//TEST_CASE("Entity 2.18 - While stmt - Advanced") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(EntityASTs::getAST2_18());
//
//	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
//	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
//	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//	std::unordered_set<int> expectedStmtTable{ 1, 2 };
//	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//	std::unordered_set<int> expectedPrintTable{ };
//	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);
//
//	std::unordered_set<int> expectedReadTable{ 2 };
//	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);
//
//	std::unordered_set<int> expectedWhileTable{ 1 };
//	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);
//
//	std::unordered_set<int> expectedIfTable{ };
//	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);
//
//	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
//	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
//	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	REQUIRE(actualAssignTable == expectedAssignTable);
//
//	EntityStager::clear();
//}

//TEST_CASE("Entity 2.19 - While stmt - Advanced") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(EntityASTs::getAST2_19());
//
//	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//	std::unordered_set<std::string> expectedVarTable{ "x", "y" };
//	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//	std::unordered_set<std::string> expectedConstTable{ "1", "2" };
//	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//	std::unordered_set<int> expectedStmtTable{ 1, 2 };
//	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//	std::unordered_set<int> expectedPrintTable{ };
//	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);
//
//	std::unordered_set<int> expectedReadTable{ 2 };
//	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);
//
//	std::unordered_set<int> expectedWhileTable{ 1 };
//	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);
//
//	std::unordered_set<int> expectedIfTable{ };
//	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);
//
//	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
//	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
//	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	REQUIRE(actualAssignTable == expectedAssignTable);
//
//	EntityStager::clear();
//}

//TEST_CASE("Entity 2.20 - While stmt - NOT in predicate") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(EntityASTs::getAST2_20());
//
//	std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//	std::unordered_set<std::string> expectedVarTable{ "x" };
//	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//	std::unordered_set<std::string> expectedConstTable{ "1" };
//	REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//	std::unordered_set<int> expectedStmtTable{ 1, 2 };
//	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//	std::unordered_set<int> expectedPrintTable{ };
//	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);
//
//	std::unordered_set<int> expectedReadTable{ 2 };
//	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);
//
//	std::unordered_set<int> expectedWhileTable{ 1 };
//	REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);
//
//	std::unordered_set<int> expectedIfTable{ };
//	REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);
//
//	std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{ };
//	std::sort(expectedAssignTable.begin(), expectedAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	std::vector<std::tuple<int, std::string, std::string>> actualAssignTable = EntityStager::getStagedAssignStatements();
//	std::sort(actualAssignTable.begin(), actualAssignTable.end(),
//		[](auto& left, auto& right) { return std::get<0>(left) < std::get<0>(right); });
//
//	REQUIRE(actualAssignTable == expectedAssignTable);
//
//	EntityStager::clear();
//}



////missing basic single line test cases
//
//TEST_CASE("Extract simple SIMPLE code no design entities") {
//	EntityStager::clear();
//
//	/*
//	 * Test Simple Program
//	 * procedure testProgram {
//	 * 1	read x;
//	 * 2	print x;
//	 * 3	print y;
//	 * }
//	 */
//
//	// building AST
//	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//
//	std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);
//	std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(2, x);
//	std::shared_ptr<PrintNode> stmt3 = std::make_shared<PrintNode>(3, y);
//
//	std::vector<std::shared_ptr<StmtNode>> stmtList{ stmt1, stmt2, stmt3 };
//
//	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//	std::vector<std::shared_ptr<ProcedureNode>> procList{ proc1 };
//
//	AST ast = std::make_shared<ProgramNode>(procList);
//
//	DesignExtractor::extractDesignElements(ast);
//
//	std::unordered_set<std::string> expectedProcedureTable;
//	expectedProcedureTable.insert("testProgram");
//	REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//	std::unordered_set<std::string> expectedVarTable{"x", "y"};
//	REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//	std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
//	REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//	std::unordered_set<int> expectedPrintTable{ 2, 3 };
//	REQUIRE(EntityStager::getStagedPrintStatements() == expectedPrintTable);
//
//	std::unordered_set<int> expectedReadTable{ 1 };
//	REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);
//
//	EntityStager::clear();
//}
//
//TEST_CASE("Extract SIMPLE assign statement") {
//	EntityStager::clear();
//
//	SECTION("RHS - constant") {
//		/*
//		 * Test Simple Program
//		 * procedure testProgram {
//		 * 1	x = 1;
//		 * }
//		 */
//
//		 // building AST
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		ExprNode one = std::make_shared<ConstantNode>("1");
//
//		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, one, "1");
//
//		std::vector<std::shared_ptr<StmtNode>> stmtList{ stmt };
//
//		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//		std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
//
//		AST ast = std::make_shared<ProgramNode>(procList);
//
//		DesignExtractor::extractDesignElements(ast);
//
//		std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//		REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//		std::unordered_set<std::string> expectedVarTable{ "x" };
//		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//		std::unordered_set<std::string> expectedConstTable{ "1" };
//		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//		std::unordered_set<int> expectedStmtTable{ 1 };
//		REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//		std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
//			std::make_tuple<int, std::string, std::string>(1, "x", "1")
//		};
//		REQUIRE(EntityStager::getStagedAssignStatements() == expectedAssignTable);
//
//		EntityStager::clear();
//	}
//
//	SECTION("RHS - Variable") {
//		/*
//		 * Test Simple Program
//		 * procedure testProgram {
//		 * 1	x = y;
//		 * }
//		 */
//
//		 // building AST
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		ExprNode y = std::make_shared<VariableNode>("y");
//
//		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, y, "y");
//
//		std::vector<std::shared_ptr<StmtNode>> stmtList{ stmt };
//
//		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//		std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
//
//		AST ast = std::make_shared<ProgramNode>(procList);
//
//		DesignExtractor::extractDesignElements(ast);
//
//		std::unordered_set<std::string> expectedVarTable{ "x", "y"};
//		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//		std::unordered_set<std::string> expectedConstTable;
//		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//		std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
//			std::make_tuple<int, std::string, std::string>(1, "x", "y")
//		};
//		REQUIRE(EntityStager::getStagedAssignStatements() == expectedAssignTable);
//
//		EntityStager::clear();
//	}
//
//	SECTION("RHS - Complex") {
//		/*
//		 * Test Simple Program
//		 * procedure testProgram {
//		 * 1	x = y + 1;
//		 * }
//		 */
//
//		 // building AST
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//
//		ExprNode y = std::make_shared<VariableNode>("y");
//		ExprNode one = std::make_shared<ConstantNode>("1");
//		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, one);
//
//		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, expression, "y 1 +");
//
//		std::vector<std::shared_ptr<StmtNode>> stmtList{ stmt };
//
//		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//		std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
//
//		AST ast = std::make_shared<ProgramNode>(procList);
//
//		DesignExtractor::extractDesignElements(ast);
//
//		std::unordered_set<std::string> expectedVarTable{ "x", "y" };
//		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//		std::unordered_set<std::string> expectedConstTable{ "1" };
//		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//		std::vector<std::tuple<int, std::string, std::string>> expectedAssignTable{
//			std::make_tuple<int, std::string, std::string>(1, "x", "y 1 +")
//		};
//		REQUIRE(EntityStager::getStagedAssignStatements() == expectedAssignTable);
//
//		EntityStager::clear();
//	}
//}
//
//TEST_CASE("Extract SIMPLE while statement") {
//	EntityStager::clear();
//
//	SECTION("Single While loop - simple predicate") {
//		/*
//		 * Test Simple Program
//		 * procedure testProgram {
//		 * 1	while (y > 1) {
//		 * 2        read x;
//		 *      }
//		 * }
//		 */
//
//		 // building AST
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		RelFactorNode one = std::make_shared<ConstantNode>("1");
//
//		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
//		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);
//
//		std::vector<std::shared_ptr<StmtNode>> whileStmtList;
//		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(2, x);
//		whileStmtList.push_back(read);
//
//		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);
//
//		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
//		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//		std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
//		AST ast = std::make_shared<ProgramNode>(procList);
//
//		DesignExtractor::extractDesignElements(ast);
//
//		std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//		REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//		std::unordered_set<std::string> expectedVarTable{ "y", "x" };
//		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//		std::unordered_set<std::string> expectedConstTable{ "1" };
//		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//		std::unordered_set<int> expectedStmtTable{ 1, 2 };
//		REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//		std::unordered_set<int> expectedWhileTable{ 1 };
//		REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);
//
//		EntityStager::clear();
//	}
//
//	//todo: everything in between
//	SECTION("Single While loop - complex predicate") {
//		/*
//		 * Test Simple Program
//		 * procedure testProgram {
//		 * 1	while (y + 2 > z - 1 && a == 123) {
//		 * 2        read x;
//		 * 3        read y;
//		 *      }
//		 * }
//		 */
//
//		 // building AST
//		std::shared_ptr<VariableNode> a = std::make_shared<VariableNode>("a");
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
//		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");
//		std::shared_ptr<ConstantNode> two = std::make_shared<ConstantNode>("2");
//		std::shared_ptr<ConstantNode> onetwothree = std::make_shared<ConstantNode>("123");
//
//		std::shared_ptr<BinaryOperatorNode> leftRelLhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, two);
//		std::shared_ptr<BinaryOperatorNode> leftRelRhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, z, one);
//		
//		std::shared_ptr<RelExprNode> leftRel = std::make_shared<RelExprNode>(leftRelLhs, ComparatorOperator::GT, leftRelRhs);
//		std::shared_ptr<RelExprNode> rightRel = std::make_shared<RelExprNode>(a, ComparatorOperator::EQ, onetwothree);
//
//		std::shared_ptr<PredicateNode> leftPred = std::make_shared<PredicateNode>(leftRel);
//		std::shared_ptr<PredicateNode> rightPred = std::make_shared<PredicateNode>(rightRel);
//
//		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(leftPred, ConditionalOperator::AND, rightPred);
//
//		std::vector<std::shared_ptr<StmtNode>> whileStmtList;
//		std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(2, x);
//		std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(3, y);
//		whileStmtList.push_back(read1);
//		whileStmtList.push_back(read2);
//
//		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);
//
//		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
//		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//		std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
//
//		AST ast = std::make_shared<ProgramNode>(procList);
//
//		DesignExtractor::extractDesignElements(ast);
//
//		std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//		REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//		std::unordered_set<std::string> expectedVarTable{ "a", "x", "y", "z"};
//		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//		std::unordered_set<std::string> expectedConstTable{ "1", "2", "123"};
//		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//		std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
//		REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//		std::unordered_set<int> expectedWhileTable{ 1 };
//		REQUIRE(EntityStager::getStagedWhileStatements() == expectedWhileTable);
//
//		std::unordered_set<int> expectedReadTable{ 2, 3 };
//		REQUIRE(EntityStager::getStagedReadStatements() == expectedReadTable);
//
//		EntityStager::clear();
//	}
//}
//
//TEST_CASE("Extract SIMPLE if statement") {
//	EntityStager::clear();
//
//	SECTION("Single if - simple predicate") {
//		/*
//		 * Test Simple Program
//		 * procedure testProgram {
//		 * 1	if (y > 1) then {
//		 * 2        read x;
//		 *      } else {
//		 * 3        print z;
//		 *      }
//		 * }
//		 */
//
//		 // building AST
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
//		RelFactorNode one = std::make_shared<ConstantNode>("1");
//
//		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
//		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);
//
//		std::vector<std::shared_ptr<StmtNode>> thenStmtList;
//		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(2, x);
//		thenStmtList.push_back(read);
//
//		std::vector<std::shared_ptr<StmtNode>> elseStmtList;
//		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(3, z);
//		elseStmtList.push_back(print);
//
//		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred, thenStmtList, elseStmtList);
//
//		std::vector<std::shared_ptr<StmtNode>> stmtList{ ifs };
//		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//		std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
//
//		AST ast = std::make_shared<ProgramNode>(procList);
//
//		DesignExtractor::extractDesignElements(ast);
//
//		std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//		REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//		std::unordered_set<std::string> expectedVarTable{ "y", "x", "z" };
//		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//		std::unordered_set<std::string> expectedConstTable{ "1" };
//		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//		std::unordered_set<int> expectedStmtTable{ 1, 2, 3 };
//		REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//		std::unordered_set<int> expectedIfTable{ 1 };
//		REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);
//
//		EntityStager::clear();
//	}
//
//	SECTION("Nested if - simple predicate") {
//		/*
//		 * Test Simple Program
//		 * procedure testProgram {
//		 * 1	if (y > 1) then {
//		 * 2        if (a > 123) then {
//		 * 3            read m;
//		 *          } else {}
//		 * 4        read x;
//		 *      } else {
//		 * 5        print z;
//		 *      }
//		 * }
//		 */
//
//		 // building AST
//		std::shared_ptr<VariableNode> a = std::make_shared<VariableNode>("a");
//		std::shared_ptr<VariableNode> m = std::make_shared<VariableNode>("m");
//		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
//		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
//		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
//		RelFactorNode one = std::make_shared<ConstantNode>("1");
//		RelFactorNode onetwothree = std::make_shared<ConstantNode>("123");
//
//		std::shared_ptr<RelExprNode> outerRel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
//		std::shared_ptr<PredicateNode> outerPred = std::make_shared<PredicateNode>(outerRel);
//
//		std::shared_ptr<RelExprNode> innerRel = std::make_shared<RelExprNode>(a, ComparatorOperator::GT, onetwothree);
//		std::shared_ptr<PredicateNode> innerPred = std::make_shared<PredicateNode>(innerRel);
//		std::vector<std::shared_ptr<StmtNode>> innerThenStmtList;
//		std::vector<std::shared_ptr<StmtNode>> innerElseStmtList;
//		std::shared_ptr<ReadNode> readm = std::make_shared<ReadNode>(3, m);
//		innerThenStmtList.push_back(readm);
//
//		std::vector<std::shared_ptr<StmtNode>> thenStmtList;
//		std::shared_ptr<IfNode> innerIf = std::make_shared<IfNode>(2, innerPred, innerThenStmtList, innerElseStmtList);
//		std::shared_ptr<ReadNode> readx = std::make_shared<ReadNode>(4, x);
//		thenStmtList.push_back(innerIf);
//		thenStmtList.push_back(readx);
//
//		std::vector<std::shared_ptr<StmtNode>> elseStmtList;
//		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(5, z);
//		elseStmtList.push_back(print);
//
//		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, outerPred, thenStmtList, elseStmtList);
//
//		std::vector<std::shared_ptr<StmtNode>> stmtList{ ifs };
//		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
//		std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
//
//		AST ast = std::make_shared<ProgramNode>(procList);
//
//		DesignExtractor::extractDesignElements(ast);
//
//		std::unordered_set<std::string> expectedProcedureTable{ "testProgram" };
//		REQUIRE(EntityStager::getStagedProcedures() == expectedProcedureTable);
//
//		std::unordered_set<std::string> expectedVarTable{ "y", "x", "z" ,"a", "m"};
//		REQUIRE(EntityStager::getStagedVariables() == expectedVarTable);
//
//		std::unordered_set<std::string> expectedConstTable{ "1", "123"};
//		REQUIRE(EntityStager::getStagedConstants() == expectedConstTable);
//
//		std::unordered_set<int> expectedStmtTable{ 1, 2, 3, 4, 5 };
//		REQUIRE(EntityStager::getStagedStatements() == expectedStmtTable);
//
//		std::unordered_set<int> expectedIfTable{ 1, 2 };
//		REQUIRE(EntityStager::getStagedIfStatements() == expectedIfTable);
//
//		EntityStager::clear();
//	}
//}
