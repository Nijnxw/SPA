#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <unordered_set>
#include <vector>

TEST_CASE("Uses 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1(), RelationshipASTs::getStmtCount3_1());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{ };
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{ };
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.2 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2(), RelationshipASTs::getStmtCount3_2());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3(), RelationshipASTs::getStmtCount3_3());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4(), RelationshipASTs::getStmtCount3_4());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5(), RelationshipASTs::getStmtCount3_5());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{ 
		{2, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6(), RelationshipASTs::getStmtCount3_6());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7(), RelationshipASTs::getStmtCount3_7());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x"}}, {2, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8(), RelationshipASTs::getStmtCount3_8());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9(), RelationshipASTs::getStmtCount3_9());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{ };
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{ };
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10(), RelationshipASTs::getStmtCount3_10());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {2, {"x"}},
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11(), RelationshipASTs::getStmtCount3_11());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12(), RelationshipASTs::getStmtCount3_12());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13(), RelationshipASTs::getStmtCount3_13());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14(), RelationshipASTs::getStmtCount3_14());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x"}}, {3, {"x", "y"}}, {5, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15(), RelationshipASTs::getStmtCount3_15());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {3, {"y"}}, {5, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16(), RelationshipASTs::getStmtCount3_16());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x", "y"}}, {4, {"y"}}, {5, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17(), RelationshipASTs::getStmtCount3_17());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x"}}, {3, {"x", "y"}}, {5, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18(), RelationshipASTs::getStmtCount3_18());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x"}}, {3, {"x"}}, {4, {"x"}},
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19(), RelationshipASTs::getStmtCount3_19());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {3, {"x"}}, {4, {"x"}}, {6, {"y"}}, {7, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20(), RelationshipASTs::getStmtCount3_20());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {3, {"y"}}, {6, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21(), RelationshipASTs::getStmtCount3_21());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {3, {"y"}}, {7, {"y", "z"}},
		{5, {"y"}}, {9, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22(), RelationshipASTs::getStmtCount3_22());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {2, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23(), RelationshipASTs::getStmtCount3_23());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {2, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24(), RelationshipASTs::getStmtCount3_24());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {3, {"x", "y"}}, {5, {"x"}}, {6, {"x"}}, {7, {"x"}},
		{8, {"x", "y"}}, {10, {"x"}}, {11, {"x"}}, {13, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25(), RelationshipASTs::getStmtCount3_25());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {2, {"x", "y"}}, {4, {"x"}}, {5, {"x"}}, {7, {"x"}},
		{9, {"y"}}, {10, {"x", "y"}}, {12, {"x"}}, {13, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26(), RelationshipASTs::getStmtCount3_26());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {3, {"x"}}, {4, {"x", "y"}}, {6, {"x"}}, {7, {"x"}},
		{9, {"x", "y"}}, {11, {"x"}}, {12, {"x"}}, {13, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27(), RelationshipASTs::getStmtCount3_26());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {2, {"x", "y", "z"}}, {4, {"x"}}, {5, {"x"}},
		{7, {"z"}}, {8, {"z"}}, {10, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28(), RelationshipASTs::getStmtCount3_28());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {3, {"x", "y", "z"}}, {5, {"x"}}, {6, {"x"}},
		{8, {"z"}}, {9, {"z"}}, {10, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29(), RelationshipASTs::getStmtCount3_29());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {3, {"x"}}, {4, {"x", "y", "z"}}, {6, {"x"}},
		{7, {"x"}}, {9, {"z"}}, {10, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30(), RelationshipASTs::getStmtCount3_30());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {4, {"z"}}, {6, {"z"}},
		{7, {"y"}}, {9, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31(), RelationshipASTs::getStmtCount3_31());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32(), RelationshipASTs::getStmtCount3_32());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"w", "x", "y", "z"}}, {2, {"w", "y", "z"}}, {3, {"z"}}, {6, {"w"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"w", "x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33(), RelationshipASTs::getStmtCount3_33());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"z"}}, {5, {"z"}}, {6, {"y"}},
		{8, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

//ITERATION 2

TEST_CASE("Uses 3.34 - Complex two procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_34(), RelationshipASTs::getStmtCount3_34());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {2, {"x", "y"}}, {4, {"x"}}, {5, {"x"}}, {7, {"x"}},
		{9, {"y"}}, {10, {"x", "y"}}, {12, {"x"}}, {13, {"x"}},
		{14, {"w", "x", "y", "z"}}, {15, {"w", "y", "z"}}, {16, {"z"}}, {19, {"w"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"x", "y"}}, {"testProgram2", {"w", "x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.35 - Normal Post Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_35(), RelationshipASTs::getStmtCount3_35());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x", "y"}}, {4, {"x"}}, {5, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y"}},
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.36 - Normal Pre Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_36(), RelationshipASTs::getStmtCount3_36());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x"}}, {4, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram2", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.37 - Normal Pre declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_37(), RelationshipASTs::getStmtCount3_37());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x"}}, {3, {"x", "y"}}, {4, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x"}}, {"testProgram2", {"x", "y"}},
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.38 - Normal Pre declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_38(), RelationshipASTs::getStmtCount3_38());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x"}}, {3, {"x", "y"}}, {5, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x"}}, {"testProgram2", {"x", "y"}},
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.39 - Normal Post declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_39(), RelationshipASTs::getStmtCount3_39());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {2, {"x"}}, {6, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x"}},
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.40 - Normal Post declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_40(), RelationshipASTs::getStmtCount3_40());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y"}}, {3, {"x"}}, {6, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x"}},
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.41 - Normal Pre declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_41(), RelationshipASTs::getStmtCount3_41());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x"}}, {3, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x"}}, {"testProgram2", {"x"}},
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.42 - Normal Post declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_42(), RelationshipASTs::getStmtCount3_42());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x"}}, {3, {"x"}}, {5, {"x"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x"}}, {"testProgram2", {"x"}},
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.43 - 3 calls sequential predeclared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_43(), RelationshipASTs::getStmtCount3_43());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x"}}, {4, {"y"}}, {6, {"y"}}, {7, {"x", "y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram2", {"x", "y"}}, {"testProgram3", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.44 - 3 calls sequential post declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_44(), RelationshipASTs::getStmtCount3_44());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x", "y"}}, {4, {"x"}}, {5, {"y"}}, {6, {"y"}}, {7, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y"}}, {"testProgram3", {"y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.45 - 3 calls forking from top") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_45(), RelationshipASTs::getStmtCount3_45());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"x", "y"}}, {4, {"y"}}, {5, {"x"}}, {6, {"y"}}, {7, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y"}}, {"testProgram3", {"y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.46 - 3 calls forking from bottom") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_46(), RelationshipASTs::getStmtCount3_46());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x"}}, {4, {"y"}}, {6, {"y"}}, {7, {"x", "y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram2", {"x", "y"}}, {"testProgram3", {"x", "y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.47 - 3 calls forking from middle") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_47(), RelationshipASTs::getStmtCount3_47());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x"}}, {5, {"y"}}, {6, {"y"}}, {7, {"y"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram2", {"x", "y"}}, {"testProgram3", {"y"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.48 - 4 calls sequential call (mix of post and pre declared)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_48(), RelationshipASTs::getStmtCount3_48());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"y"}}, {4, {"x"}}, {5, {"y"}}, {6, {"y"}}, {7, {"y"}},
		{8, {"x", "y", "z"}}, {10, {"x", "y"}}, {11, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"y"}}, {"testProgram2", {"x", "y"}},
		{"testProgram3", {"y"}}, {"testProgram4", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.49 - 4 calls - 1 - (2, 3, 4)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_49(), RelationshipASTs::getStmtCount3_49());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"z"}}, {3, {"y"}}, {5, {"x", "y"}}, {6, {"x"}}, {7, {"y"}},
		{8, {"y"}}, {9, {"z"}}, {11, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x", "y", "z"}}, {"testProgram2", {"x", "y"}},
		{"testProgram3", {"y"}}, {"testProgram4", {"z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.50 - 4 calls - (1, 2, 4) - 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_50(), RelationshipASTs::getStmtCount3_50());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"y"}}, {4, {"x"}}, {5, {"y"}}, {6, {"y"}}, {7, {"y"}},
		{8, {"y", "z"}}, {9, {"y"}}, {11, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"y"}}, {"testProgram2", {"x", "y"}},
		{"testProgram3", {"y"}}, {"testProgram4", {"y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.51 - 4 calls - 1 - (3, 4) - 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_51(), RelationshipASTs::getStmtCount3_51());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{1, {"x", "y", "z"}}, {3, {"x", "y"}}, {5, {"x"}}, {6, {"y"}}, {7, {"y"}},
		{8, {"x", "y"}}, {9, {"x", "y", "z"}}, {11, {"x", "y"}}, {12, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"x", "y", "z"}}, {"testProgram2", {"x", "y"}},
		{"testProgram3", {"x", "y"}}, {"testProgram4", {"x", "y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.52 - 4 calls - 2 - 4 - (3, 1)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_52(), RelationshipASTs::getStmtCount3_52());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x"}}, {4, {"y", "z"}}, {5, {"y"}}, {6, {"y"}}, {7, {"y", "z"}},
		{8, {"y"}}, {10, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram2", {"x", "y", "z"}}, {"testProgram3", {"y"}}, {"testProgram4", {"y", "z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.53 - 4 calls - (1, 2) - 3 - 4") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_53(), RelationshipASTs::getStmtCount3_53());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"y", "z"}}, {4, {"x"}}, {5, {"y", "z"}}, {6, {"y"}}, {7, {"y"}},
		{8, {"z"}}, {9, {"z"}}, {11, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"y", "z"}}, {"testProgram2", {"x", "y", "z"}},
		{"testProgram3", {"y", "z"}}, {"testProgram4", {"z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.54 - 4 calls - (3, (2 - 4)) - 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_54(), RelationshipASTs::getStmtCount3_54());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x"}}, {4, {"z"}}, {5, {"y"}}, {6, {"y"}},
		{8, {"z"}}, {10, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram2", {"x", "y", "z"}}, {"testProgram3", {"y"}}, {"testProgram4", {"z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 3.55 - 4 calls - 2 - ((1 - 4), 3)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_55(), RelationshipASTs::getStmtCount3_55());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{2, {"z"}}, {4, {"y"}}, {5, {"x"}}, {6, {"z"}}, {7, {"y"}},
		{8, {"y"}}, {9, {"z"}}, {11, {"z"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram1", {"z"}},{"testProgram2", {"x", "y", "z"}},
		{"testProgram3", {"y"}}, {"testProgram4", {"z"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}

TEST_CASE("Uses 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(ComplexASTs::getAST4_1(), ComplexASTs::getStmtCount4_1());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUsesStatement{
		{3, {"x", "y"}},
		{5, {"tan", "sin", "cos", "x", "y", "length"}},
		{6, {"tan", "sin", "cos", "x", "y", "length"}},
		{7, {"x", "y"}}, {8, {"y", "length", "cos"}}, {9, {"x", "length", "sin"}},
		{10, {"sin", "cos", "tan", "x", "y"}},
		{11, {"y"}}, {12, {"x"}}, {14, {"x", "y"}}, {17, {"x", "y"}}, {18, {"length"}}
	};
	std::sort(expectedUsesStatement.begin(), expectedUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUsesStatement = EntityStager::getStagedUsesStatement();
	std::sort(actualUsesStatement.begin(), actualUsesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedUsesProcedure{
		{"testProgram", {"tan", "sin", "cos", "x", "y", "length"}}
	};
	std::sort(expectedUsesProcedure.begin(), expectedUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualUsesProcedure = EntityStager::getStagedUsesProcedure();
	std::sort(actualUsesProcedure.begin(), actualUsesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUsesStatement == expectedUsesStatement);
	REQUIRE(actualUsesProcedure == expectedUsesProcedure);
	EntityStager::clear();
}
