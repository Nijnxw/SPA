#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <memory>
#include <vector>

TEST_CASE("Parents 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1(), 0);
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.2 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2(), 0);
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3(), 0);
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4(), 0);
	std::vector<std::pair<int, int>> expectedParents{};
	REQUIRE(EntityStager::getStagedParent() == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {3, 4} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {1, 2} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {2, 3} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {3, 4}, {3, 5} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {1, 3} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {2, 3}, {2, 4} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {3, 4}, {3, 5} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {1, 3}, {1, 4} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19(), 0);

	std::vector<std::pair<int, int>> expectedParents{ {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7} };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32(), 0);

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
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33(), 0);

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

//ITERATION 2

TEST_CASE("Parents 3.34 - Complex two procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_34(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10},
		{2, 3}, {2, 4}, {2, 5}, {10, 11}, {10, 12}, {10, 13},
		{14, 15}, {14, 22},
		{15, 16}, {15, 18}, {15, 19}, {15, 21},
		{16, 17}, {19, 20}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.35 - Normal Post Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_35(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.36 - Normal Pre Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_36(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.37 - Normal Pre declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_37(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{3, 4}, {3, 5}, {3, 6}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.38 - Normal Pre declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_38(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{3, 4}, {3, 5}, {3, 6}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.39 - Normal Post declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_39(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}, {1, 4}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.40 - Normal Post declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_40(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}, {1, 4}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.41 - Normal Pre declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_41(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{3, 4}, {3, 5}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.42 - Normal Post declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_42(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{1, 2}, {1, 3}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.43 - 3 calls sequential predeclared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_43(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.44 - 3 calls sequential post declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_44(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.45 - 3 calls forking from top") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_45(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.46 - 3 calls forking from bottom") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_46(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.47 - 3 calls forking from middle") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_47(), 0);

	std::vector<std::pair<int, int>> expectedParents{ };
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.48 - 4 calls sequential call (mix of post and pre declared)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_48(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{8, 9}, {8, 10}, {8, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.49 - 4 calls - 1 - (2, 3, 4)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_49(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{9, 10}, {9, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.50 - 4 calls - (1, 2, 4) - 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_50(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{8, 9}, {8, 10}, {8, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.51 - 4 calls - 1 - (3, 4) - 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_51(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{9, 10}, {9, 11}, {9, 12}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.52 - 4 calls - 2 - 4 - (3, 1)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_52(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{7, 8}, {7, 9}, {7, 10}, {7, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.53 - 4 calls - (1, 2) - 3 - 4") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_53(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{9, 10}, {9, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.54 - 4 calls - (3, (2 - 4)) - 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_54(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{8, 9}, {8, 10}, {8, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 3.55 - 4 calls - 2 - ((1 - 4), 3)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_55(), 0);

	std::vector<std::pair<int, int>> expectedParents{
		{9, 10}, {9, 11}
	};
	std::sort(expectedParents.begin(), expectedParents.end());

	std::vector<std::pair<int, int>> actualParents = EntityStager::getStagedParent();
	std::sort(actualParents.begin(), actualParents.end());

	REQUIRE(actualParents == expectedParents);
	EntityStager::clear();
}

TEST_CASE("Parents 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(ComplexASTs::getAST4_1(), 0);

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
