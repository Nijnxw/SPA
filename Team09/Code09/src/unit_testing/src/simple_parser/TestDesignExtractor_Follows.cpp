#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/ComplexASTs.h"
#include "asts/RelationshipASTs.h"

#include <memory>
#include <vector>

TEST_CASE("Follows 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1());
	std::vector<std::pair<int, int>> expectedFollows{ };
	REQUIRE(EntityStager::getStagedFollows() == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.2 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2());
	std::vector<std::pair<int, int>> expectedFollows{ };
	REQUIRE(EntityStager::getStagedFollows() == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3());
	std::vector<std::pair<int, int>> expectedFollows{ };
	REQUIRE(EntityStager::getStagedFollows() == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4());
	std::vector<std::pair<int, int>> expectedFollows{ };
	REQUIRE(EntityStager::getStagedFollows() == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2}, {2, 3} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2}, {2, 3} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2}, {2, 3} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2}, {2, 3} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 3}, {3, 4} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2}, {2, 4} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2}, {2, 3} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 4}, {4, 5} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 2}, {2, 5} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17());

	std::vector<std::pair<int, int>> expectedFollows{ {1, 3} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18());

	std::vector<std::pair<int, int>> expectedFollows{ {2, 3}, {3, 4} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19());

	std::vector<std::pair<int, int>> expectedFollows{ {2, 3}, {3, 4}, {5, 6}, {6, 7} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20());

	std::vector<std::pair<int, int>> expectedFollows{ {2, 3}, {5, 6} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21());

	std::vector<std::pair<int, int>> expectedFollows{ {2, 3}, {6, 7} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22());

	std::vector<std::pair<int, int>> expectedFollows{ {2, 5} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23());

	std::vector<std::pair<int, int>> expectedFollows{ {2, 4} };
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24());

	std::vector<std::pair<int, int>> expectedFollows{ 
		{2, 3}, {4, 5}, {5, 6}, {3, 7}, {8, 12}, {9, 10}, {10, 11}, {12, 13}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 6}, {3, 4}, {4, 5}, {6, 7}, {8, 9}, {9, 10}, {11, 12}, {12, 13}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 3}, {3, 4}, {5, 6}, {6, 7}, {8, 9}, {10, 11}, {11, 12}, {9, 13}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 9}, {9, 10}, {3, 4}, {4, 5}, {6, 7}, {7, 8}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 3}, {3, 10}, {4, 5}, {5, 6}, {7, 8}, {8, 9}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 3}, {3, 4}, {5, 6}, {6, 7}, {8, 9}, {9, 10}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30());

	std::vector<std::pair<int, int>> expectedFollows{
		{4, 7}, {2, 8}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31());

	std::vector<std::pair<int, int>> expectedFollows{
		{3, 5}, {2, 6}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32());

	std::vector<std::pair<int, int>> expectedFollows{
		{3, 5}, {2, 9}, {6, 8}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33());

	std::vector<std::pair<int, int>> expectedFollows{
		{3, 6}, {2, 7}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

//ITERATION 2

TEST_CASE("Follows 3.34 - Complex two procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_34());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 6}, {3, 4}, {4, 5}, {6, 7}, {8, 9}, {9, 10}, {11, 12}, {12, 13},
		{16, 18}, {19, 21}, {15, 22}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.35 - Normal Post Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_35());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {4, 5}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.36 - Normal Pre Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_36());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {3, 4}, {4, 5}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.37 - Normal Pre declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_37());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {4, 5}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.38 - Normal Pre declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_38());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {5, 6}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.39 - Normal Post declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_39());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 3}, {5, 6}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.40 - Normal Post declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_40());

	std::vector<std::pair<int, int>> expectedFollows{
		{3, 4}, {5, 6}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.41 - Normal Pre declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_41());

	std::vector<std::pair<int, int>> expectedFollows{
		{2, 3}, {4, 5}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.42 - Normal Post declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_42());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 4}, {2, 3}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.43 - 3 calls sequential predeclared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_43());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {3, 4}, {4, 5}, {6, 7}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.44 - 3 calls sequential post declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_44());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {4, 5}, {5, 6}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.45 - 3 calls forking from top") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_45());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {3, 4}, {5, 6}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.46 - 3 calls forking from bottom") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_46());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {3, 4}, {5, 6}, {6, 7}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.47 - 3 calls forking from middle") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_47());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {3, 4}, {4, 5}, {5, 6}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.48 - 4 calls sequential call (mix of post and pre declared)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_48());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {10, 11}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.49 - 4 calls - 1 - (2, 3, 4)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_49());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {3, 4}, {4, 5}, {6, 7}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.50 - 4 calls - (1, 2, 4) - 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_50());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {9, 10}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.51 - 4 calls - 1 - (3, 4) - 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_51());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {3, 4}, {5, 6}, {7, 8}, {10, 11}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.52 - 4 calls - 2 - 4 - (3, 1)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_52());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {3, 4}, {4, 5}, {8, 9}, {10, 11}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.53 - 4 calls - (1, 2) - 3 - 4") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_53());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.54 - 4 calls - (3, (2 - 4)) - 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_54());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {3, 4}, {4, 5}, {6, 7}, {10, 11}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 3.55 - 4 calls - 2 - ((1 - 4), 3)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_55());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 7}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}

TEST_CASE("Follows 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(ComplexASTs::getAST4_1());

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 18},
		{7, 8}, {8, 9}, {9, 10}, {10, 14}, {11, 12}, {15, 16}, {16, 17}
	};
	std::sort(expectedFollows.begin(), expectedFollows.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollows();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollows);
	EntityStager::clear();
}