#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <string>
#include <unordered_set>
#include <vector>

TEST_CASE("Uses 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{ };
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.2 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{ 
		{2, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{2, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x"}}, {2, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{ };
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {2, {"x"}},
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{2, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{2, {"x"}}, {3, {"x", "y"}}, {5, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {3, {"y"}}, {5, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{2, {"x", "y"}}, {4, {"y"}}, {5, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x"}}, {3, {"x", "y"}}, {5, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x"}}, {3, {"x"}}, {4, {"x"}},
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {3, {"x"}}, {4, {"x"}}, {6, {"y"}}, {7, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {3, {"y"}}, {6, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}, {3, {"y"}}, {7, {"y", "z"}},
		{5, {"y"}}, {9, {"z"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {2, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {2, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {3, {"x", "y"}}, {5, {"x"}}, {6, {"x"}}, {7, {"x"}},
		{8, {"x", "y"}}, {10, {"x"}}, {11, {"x"}}, {13, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {2, {"x", "y"}}, {4, {"x"}}, {5, {"x"}}, {7, {"x"}},
		{9, {"y"}}, {10, {"x", "y"}}, {12, {"x"}}, {13, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y"}}, {3, {"x"}}, {4, {"x", "y"}}, {6, {"x"}}, {7, {"x"}},
		{9, {"x", "y"}}, {11, {"x"}}, {12, {"x"}}, {13, {"y"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}, {2, {"x", "y", "z"}}, {4, {"x"}}, {5, {"x"}},
		{7, {"z"}}, {8, {"z"}}, {10, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}, {3, {"x", "y", "z"}}, {5, {"x"}}, {6, {"x"}},
		{8, {"z"}}, {9, {"z"}}, {10, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}, {3, {"x"}}, {4, {"x", "y", "z"}}, {6, {"x"}},
		{7, {"x"}}, {9, {"z"}}, {10, {"z"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {4, {"z"}}, {6, {"z"}},
		{7, {"y"}}, {9, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"z"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"w", "x", "y", "z"}}, {2, {"w", "y", "z"}}, {3, {"z"}}, {6, {"w"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"z"}}, {5, {"z"}}, {6, {"y"}},
		{8, {"x"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}

TEST_CASE("Uses 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(ComplexASTs::getAST4_1());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses{
		{3, {"x", "y"}},
		{5, {"tan", "sin", "cos", "x", "y", "length"}},
		{6, {"tan", "sin", "cos", "x", "y", "length"}},
		{7, {"x", "y"}}, {8, {"y", "length", "cos"}}, {9, {"x", "length", "sin"}},
		{10, {"sin", "cos", "tan", "x", "y"}},
		{11, {"y"}}, {12, {"x"}}, {14, {"x", "y"}}, {17, {"x", "y"}}, {18, {"length"}}
	};
	std::sort(expectedUses.begin(), expectedUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualUses = EntityStager::getStagedUsesStatement();
	std::sort(actualUses.begin(), actualUses.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualUses == expectedUses);
	EntityStager::clear();
}
