#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <unordered_set>
#include <vector>

TEST_CASE("Modifies 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_1(), RelationshipASTs::getStmtCount3_1());
	de.extractDesignElements();
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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_2(), RelationshipASTs::getStmtCount3_2());
	de.extractDesignElements();
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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_3(), RelationshipASTs::getStmtCount3_3());
	de.extractDesignElements();
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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_4(), RelationshipASTs::getStmtCount3_4());
	de.extractDesignElements();
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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_5(), RelationshipASTs::getStmtCount3_5());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_6(), RelationshipASTs::getStmtCount3_6());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_7(), RelationshipASTs::getStmtCount3_7());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_8(), RelationshipASTs::getStmtCount3_8());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_9(), RelationshipASTs::getStmtCount3_9());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_10(), RelationshipASTs::getStmtCount3_10());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_11(), RelationshipASTs::getStmtCount3_11());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_12(), RelationshipASTs::getStmtCount3_12());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_13(), RelationshipASTs::getStmtCount3_13());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_14(), RelationshipASTs::getStmtCount3_14());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_15(), RelationshipASTs::getStmtCount3_15());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_16(), RelationshipASTs::getStmtCount3_16());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_17(), RelationshipASTs::getStmtCount3_17());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_18(), RelationshipASTs::getStmtCount3_18());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_19(), RelationshipASTs::getStmtCount3_19());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_20(), RelationshipASTs::getStmtCount3_20());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_21(), RelationshipASTs::getStmtCount3_21());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_22(), RelationshipASTs::getStmtCount3_22());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_23(), RelationshipASTs::getStmtCount3_23());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_24(), RelationshipASTs::getStmtCount3_24());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_25(), RelationshipASTs::getStmtCount3_25());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_26(), RelationshipASTs::getStmtCount3_26());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_27(), RelationshipASTs::getStmtCount3_27());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_28(), RelationshipASTs::getStmtCount3_28());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_29(), RelationshipASTs::getStmtCount3_29());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_30(), RelationshipASTs::getStmtCount3_30());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_31(), RelationshipASTs::getStmtCount3_31());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_32(), RelationshipASTs::getStmtCount3_32());
	de.extractDesignElements();

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
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_33(), RelationshipASTs::getStmtCount3_33());
	de.extractDesignElements();

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

//ITERATION 2

TEST_CASE("Modifies 3.34 - Complex two procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_34(), RelationshipASTs::getStmtCount3_34());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x", "y", "z"}}, {2, {"x", "y"}}, {3, {"y"}}, {5, {"x"}}, {6, {"x"}}, {7, {"x"}},
		{8, {"z"}}, {10, {"x", "y"}}, {11, {"y"}}, {13, {"x"}},
		{14, {"w", "x", "y", "z"}}, {15, {"w", "y", "z"}}, {16, {"z"}}, {17, {"z"}},
		{18, {"y"}}, {19, {"w"}}, {20, {"w"}}, {21, {"w"}}, {22, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram", {"x", "y", "z"}}, {"testProgram2", {"w", "x", "y", "z"}}
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

TEST_CASE("Modifies 3.35 - Normal Post Declared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_35(), RelationshipASTs::getStmtCount3_35());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}
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

TEST_CASE("Modifies 3.36 - Normal Pre Declared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_36(), RelationshipASTs::getStmtCount3_36());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {5, {"x", "y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y"}}
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

TEST_CASE("Modifies 3.37 - Normal Pre declared Nested in If") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_37(), RelationshipASTs::getStmtCount3_37());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {3, {"w", "y"}}, {4, {"y"}}, {5, {"y"}}, {6, {"w"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"y"}}, {"testProgram2", {"w", "y"}},
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

TEST_CASE("Modifies 3.38 - Normal Pre declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_38(), RelationshipASTs::getStmtCount3_38());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {3, {"w", "y"}}, {4, {"y"}}, {5, {"y"}}, {6, {"w"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"y"}}, {"testProgram2", {"w", "y"}},
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

TEST_CASE("Modifies 3.39 - Normal Post declared Nested in If") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_39(), RelationshipASTs::getStmtCount3_39());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"w", "y"}}, {2, {"y"}}, {3, {"y"}}, {4, {"w"}}, {5, {"y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"w", "y"}}, {"testProgram2", {"y"}}
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

TEST_CASE("Modifies 3.40 - Normal Post declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_40(), RelationshipASTs::getStmtCount3_40());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"w", "y"}}, {2, {"y"}}, {3, {"y"}}, {4, {"w"}}, {5, {"y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"w", "y"}}, {"testProgram2", {"y"}}
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

TEST_CASE("Modifies 3.41 - Normal Pre declared Nested in While") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_41(), RelationshipASTs::getStmtCount3_41());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{2, {"z"}}, {3, {"x"}}, {5, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram2", {"x", "z"}}
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

TEST_CASE("Modifies 3.42 - Normal Post declared Nested in While") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_42(), RelationshipASTs::getStmtCount3_42());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"x"}}, {2, {"x"}}, {4, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "z"}}
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

TEST_CASE("Modifies 3.43 - 3 calls sequential predeclared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_43(), RelationshipASTs::getStmtCount3_43());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {5, {"x", "y"}}, {6, {"x"}}, {7, {"x", "y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y"}}, {"testProgram3", {"x", "y"}}
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

TEST_CASE("Modifies 3.44 - 3 calls sequential post declared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_44(), RelationshipASTs::getStmtCount3_44());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {3, {"x"}}, {6, {"x"}}, {7, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x"}}, {"testProgram3", {"x"}}
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

TEST_CASE("Modifies 3.45 - 3 calls forking from top") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_45(), RelationshipASTs::getStmtCount3_45());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {3, {"x"}}, {4, {"x"}}, {7, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram3", {"x"}}
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

TEST_CASE("Modifies 3.46 - 3 calls forking from bottom") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_46(), RelationshipASTs::getStmtCount3_46());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {5, {"x", "y"}}, {6, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram3", {"x", "y"}}
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

TEST_CASE("Modifies 3.47 - 3 calls forking from middle") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_47(), RelationshipASTs::getStmtCount3_47());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {4, {"x", "y"}}, {5, {"x"}}, {7, {"x"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y"}}, {"testProgram3", {"x"}}
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

TEST_CASE("Modifies 3.48 - 4 calls sequential call (mix of post and pre declared)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_48(), RelationshipASTs::getStmtCount3_48());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {3, {"x"}}, {5, {"x", "y"}}, {7, {"x"}},
		{8, {"x", "y", "z"}}, {9, {"z"}}, {10, {"x", "y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y"}},
		{"testProgram3", {"x"}}, {"testProgram4", {"x", "y", "z"}}
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

TEST_CASE("Modifies 3.49 - 4 calls - 1 - (2, 3, 4)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_49(), RelationshipASTs::getStmtCount3_49());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"z"}}, {3, {"x"}}, {4, {"x"}}, {8, {"x"}},
		{9, {"z"}}, {10, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y", "z"}}, 
		{"testProgram3", {"x"}}, {"testProgram4", {"z"}}
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

TEST_CASE("Modifies 3.50 - 4 calls - (1, 2, 4) - 3") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_50(), RelationshipASTs::getStmtCount3_50());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {3, {"x"}}, {5, {"x"}}, {7, {"x"}},
		{8, {"x", "z"}}, {9, {"x"}}, {10, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x"}},
		{"testProgram3", {"x"}}, {"testProgram4", {"x", "z"}}
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

TEST_CASE("Modifies 3.51 - 4 calls - 1 - (3, 4) - 2") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_51(), RelationshipASTs::getStmtCount3_51());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"z"}}, {2, {"y"}}, {3, {"x"}}, {4, {"x"}}, {7, {"x"}},
		{9, {"z"}}, {10, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y", "z"}},
		{"testProgram3", {"x"}}, {"testProgram4", {"z"}}
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

TEST_CASE("Modifies 3.52 - 4 calls - 2 - 4 - (3, 1)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_52(), RelationshipASTs::getStmtCount3_52());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {4, {"x", "y", "z"}}, {6, {"x"}}, {7, {"x", "y", "z"}},
		{8, {"x"}}, {9, {"z"}}, {11, {"x", "y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y", "z"}},
		{"testProgram3", {"x"}}, {"testProgram4", {"x", "y", "z"}}
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

TEST_CASE("Modifies 3.53 - 4 calls - (1, 2) - 3 - 4") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_53(), RelationshipASTs::getStmtCount3_53());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {3, {"x", "z"}}, {5, {"x", "z"}}, {7, {"x"}},
		{8, {"z"}}, {9, {"z"}}, {10, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y", "z"}}, {"testProgram2", {"x", "z"}},
		{"testProgram3", {"x", "z"}}, {"testProgram4", {"z"}}
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

TEST_CASE("Modifies 3.54 - 4 calls - (3, (2 - 4)) - 1") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_54(), RelationshipASTs::getStmtCount3_54());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"x"}}, {4, {"x", "y", "z"}}, {6, {"x"}}, {7, {"x", "y"}},
		{8, {"x", "y", "z"}}, {9, {"z"}}, {11, {"x", "y"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y"}}, {"testProgram2", {"x", "y", "z"}},
		{"testProgram3", {"x", "y"}}, {"testProgram4", {"x", "y", "z"}}
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

TEST_CASE("Modifies 3.55 - 4 calls - 2 - ((1 - 4), 3)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_55(), RelationshipASTs::getStmtCount3_55());
	de.extractDesignElements();

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifiesStatement{
		{1, {"y"}}, {2, {"z"}}, {3, {"x"}}, {4, {"x"}}, {6, {"x", "y", "z"}},
		{8, {"x"}}, {9, {"z"}}, {10, {"z"}}
	};
	std::sort(expectedModifiesStatement.begin(), expectedModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifiesStatement = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifiesStatement.begin(), actualModifiesStatement.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<std::string, std::unordered_set<std::string>>> expectedModifiesProcedure{
		{"testProgram1", {"x", "y", "z"}},{"testProgram2", {"x", "y", "z"}},
		{"testProgram3", {"x"}}, {"testProgram4", {"z"}}
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
	DesignExtractor de = DesignExtractor(ComplexASTs::getAST4_1(), ComplexASTs::getStmtCount4_1());
	de.extractDesignElements();

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
