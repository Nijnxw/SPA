#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <memory>
#include <vector>

TEST_CASE("Parents 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1());
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.2 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2());
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3());
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4());
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5());

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6());

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7());

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8());

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9());

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10());

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11());

	std::vector<std::pair<int, int>> expectedParents{ {3, 4} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12());

	std::vector<std::pair<int, int>> expectedParents{ {1, 2} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13());

	std::vector<std::pair<int, int>> expectedParents{ {2, 3} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14());

	std::vector<std::pair<int, int>> expectedParents{ {3, 4}, {3, 5} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15());

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {1, 3} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16());

	std::vector<std::pair<int, int>> expectedParents{ {2, 3}, {2, 4} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17());

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {3, 4}, {3, 5} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18());

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {1, 3}, {1, 4} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19());

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20());

	std::vector<std::pair<int, int>> expectedParents{ 
		{1, 2}, {1, 3}, {3, 4}, {1, 5}, {1, 6}, {6, 7}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}, {3, 4}, {3, 5}, {1, 6}, {1, 7}, {7, 8}, {7, 9}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22());

	std::vector<std::pair<int, int>> expectedParents{ 
		{1, 2}, {2, 3}, {2, 4}, {1, 5}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {2, 3}, {1, 4}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}, {1, 7}, {1, 8}, {1, 12}, {1, 13},
		{3, 4}, {3, 5}, {3, 6}, {8, 9}, {8, 10}, {8, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10},
		{2, 3}, {2, 4}, {2, 5}, {10, 11}, {10, 12}, {10, 13}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}, {1, 4}, {1, 8}, {1, 9}, {1, 13},
		{4, 5}, {4, 6}, {4, 7}, {9, 10}, {9, 11}, {9, 12}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 9}, {1, 10},
		{2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}, {1, 10},
		{3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}, {1, 4},
		{4, 5}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 10}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 8}, {1, 9},
		{2, 3}, {2, 4}, {2, 7},
		{4, 5}, {4, 6}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 6},
		{2, 3}, {2, 5},
		{3, 4}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 9},
		{2, 3}, {2, 5}, {2, 6}, {2, 8},
		{3, 4}, {6, 7}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33());

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 7}, {1, 8},
		{2, 3}, {2, 6},
		{3, 4}, {3, 5}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(ComplexASTs::getAST4_1());

	std::vector<std::pair<int, int>> expectedParents{
		{5, 6}, {5, 15}, {5, 16}, {5, 17},
		{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 14},
		{10, 11}, {10, 12}, {10, 13}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}
