#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <string>
#include <unordered_set>
#include <vector>

TEST_CASE("Modifies 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1());
	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.2 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2());
	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{ };
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{ };
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3());
	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"a"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"a"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4());
	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"a"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"a"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{2, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"y"}}, {3, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {3, {"x"}},
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {3, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {3, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}, {4, {"x"}},
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y"}}, {2, {"x"}}, {4, {"x"}}, {5, {"y"}}, {7, {"y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"y"}}, {4, {"y"}},
		{5, {"z"}}, {6, {"y"}},{7, {"y"}},
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"y"}}, {4, {"y"}},
		{6, {"z"}}, {7, {"z"}}, {8, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x", "z"}}, {3, {"x"}}, {4, {"z"}}, {5, {"y"}},
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y"}}, {2, {"x"}}, {3, {"x"}}, {4, {"y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x", "y"}}, {4, {"y"}}, {6, {"x"}}, {7, {"x"}},
		{8, {"x", "y"}}, {9, {"y"}}, {11, {"x"}}, {12, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x", "y"}}, {3, {"y"}}, {5, {"x"}}, {6, {"x"}}, {7, {"x"}},
		{8, {"z"}}, {10, {"x", "y"}}, {11, {"y"}}, {13, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x", "y"}}, {5, {"y"}}, {7, {"x"}},
		{8, {"z"}}, {9, {"x", "y"}}, {10, {"y"}}, {12, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x", "y", "z"}}, {3, {"y"}}, {5, {"x"}},
		{6, {"z"}}, {8, {"z"}}, {9, {"x"}}, {10, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x", "y", "z"}}, {4, {"y"}}, {6, {"x"}},
		{7, {"z"}}, {9, {"z"}}, {10, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x", "y", "z"}}, {5, {"y"}}, {7, {"x"}},
		{8, {"z"}}, {10, {"z"}},
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"y"}}, {4, {"z"}}, {5, {"z"}},
		{8, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"z"}},
		{4, {"z"}}, {5, {"y"}}, {6, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"w", "x", "y", "z"}}, {2, {"w", "y", "z"}}, {3, {"z"}}, {4, {"z"}},
		{5, {"y"}}, {6, {"w"}}, {7, {"w"}}, {8, {"w"}}, {9, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"w", "x", "y", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "z"}}, {2, {"z"}}, {3, {"z"}}, {4, {"z"}},
		{7, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "z"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}

TEST_CASE("Modifies 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(ComplexASTs::getAST4_1());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"y"}}, {3, {"length"}}, {4, {"t"}},
		{5, {"tan", "sin", "cos", "x", "y", "length"}},
		{6, {"tan", "sin", "cos", "x", "y", "length"}},
		{7, {"tan"}}, {8, {"sin"}}, {9, {"cos"}}, {10, {"x", "y"}},
		{11, {"x"}}, {12, {"y"}}, {13, {"x"}}, {14, {"length"}},
		{15, {"x"}}, {16, {"y"}}, {17, {"length"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"tan", "sin", "cos", "x", "y", "length", "t"}}
	};
	std::sort(expectedModifiesProcedure.begin(), expectedModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> actualModifiesProcedure = EntityStager::getStagedModifiesProcedure();
	std::sort(actualModifiesProcedure.begin(), actualModifiesProcedure.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifiesStatement == expectedModifiesStatement);
	REQUIRE(actualModifiesProcedure == expectedModifiesProcedure);
	EntityStager::clear();
}
