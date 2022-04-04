#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <memory>
#include <vector>

TEST_CASE("ParentsT 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_1(), RelationshipASTs::getStmtCount3_1());
	de.extractDesignElements();
	std::vector<std::pair<int, int>> expectedParentsT{};
	REQUIRE(EntityStager::getStagedParentT() == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.2 - Single Read") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_2(), RelationshipASTs::getStmtCount3_2());
	de.extractDesignElements();
	std::vector<std::pair<int, int>> expectedParentsT{};
	REQUIRE(EntityStager::getStagedParentT() == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_3(), RelationshipASTs::getStmtCount3_3());
	de.extractDesignElements();
	std::vector<std::pair<int, int>> expectedParentsT{};
	REQUIRE(EntityStager::getStagedParentT() == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_4(), RelationshipASTs::getStmtCount3_4());
	de.extractDesignElements();
	std::vector<std::pair<int, int>> expectedParentsT{};
	REQUIRE(EntityStager::getStagedParentT() == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_5(), RelationshipASTs::getStmtCount3_5());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_6(), RelationshipASTs::getStmtCount3_6());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_7(), RelationshipASTs::getStmtCount3_7());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_8(), RelationshipASTs::getStmtCount3_8());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_9(), RelationshipASTs::getStmtCount3_9());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_10(), RelationshipASTs::getStmtCount3_10());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_11(), RelationshipASTs::getStmtCount3_11());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {3, 4} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_12(), RelationshipASTs::getStmtCount3_12());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {1, 2} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_13(), RelationshipASTs::getStmtCount3_13());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {2, 3} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_14(), RelationshipASTs::getStmtCount3_14());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {3, 4}, {3, 5} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_15(), RelationshipASTs::getStmtCount3_15());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {1, 2}, {1, 3} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_16(), RelationshipASTs::getStmtCount3_16());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {2, 3}, {2, 4} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_17(), RelationshipASTs::getStmtCount3_17());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {1, 2}, {3, 4}, {3, 5} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_18(), RelationshipASTs::getStmtCount3_18());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {1, 2}, {1, 3}, {1, 4} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_19(), RelationshipASTs::getStmtCount3_19());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7} };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_20(), RelationshipASTs::getStmtCount3_20());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {3, 4}, {1, 4}, {1, 5}, {1, 6}, {6, 7}, {1, 7}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_21(), RelationshipASTs::getStmtCount3_21());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {3, 4}, {1, 4}, {3, 5}, {1, 5}, {1, 6}, {1, 7}, {7, 8}, {1, 8}, {7, 9}, {1, 9}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_22(), RelationshipASTs::getStmtCount3_22());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {2, 3}, {1, 3}, {2, 4}, {1, 4}, {1, 5}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_23(), RelationshipASTs::getStmtCount3_23());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {2, 3}, {1, 3}, {1, 4}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_24(), RelationshipASTs::getStmtCount3_24());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {1, 7}, {1, 8}, {1, 12}, {1, 13},
		{3, 4}, {3, 5}, {3, 6}, {8, 9}, {8, 10}, {8, 11},
		{1, 4}, {1, 5}, {1, 6}, {1, 9}, {1, 10}, {1, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_25(), RelationshipASTs::getStmtCount3_25());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10},
		{2, 3}, {2, 4}, {2, 5}, {10, 11}, {10, 12}, {10, 13},
		{1, 3}, {1, 4}, {1, 5}, {1, 11}, {1, 12}, {1, 13}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_26(), RelationshipASTs::getStmtCount3_26());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {1, 4}, {1, 8}, {1, 9}, {1, 13},
		{4, 5}, {4, 6}, {4, 7}, {9, 10}, {9, 11}, {9, 12},
		{1, 5}, {1, 6}, {1, 7}, {1, 10}, {1, 11}, {1, 12}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_27(), RelationshipASTs::getStmtCount3_27());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 9}, {1, 10},
		{2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8},
		{1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8},
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_28(), RelationshipASTs::getStmtCount3_28());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {1, 10},
		{3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9},
		{1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_29(), RelationshipASTs::getStmtCount3_29());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {1, 4},
		{4, 5}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 10},
		{1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_30(), RelationshipASTs::getStmtCount3_30());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 8}, {1, 9},
		{2, 3}, {2, 4}, {2, 7}, {1, 3}, {1, 4}, {1, 7},
		{4, 5}, {4, 6}, {1, 5}, {1, 6}, {2, 5}, {2, 6}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_31(), RelationshipASTs::getStmtCount3_31());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 6},
		{2, 3}, {2, 5}, {1, 3}, {1, 5},
		{3, 4}, {1, 4}, {2, 4}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_32(), RelationshipASTs::getStmtCount3_32());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 9},
		{2, 3}, {2, 5}, {2, 6}, {2, 8}, {1, 3}, {1, 5}, {1, 6}, {1, 8},
		{3, 4}, {6, 7}, {1, 4}, {1, 7}, {2, 4}, {2, 7}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_33(), RelationshipASTs::getStmtCount3_33());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 7}, {1, 8},
		{2, 3}, {2, 6}, {1, 3}, {1, 6},
		{3, 4}, {3, 5}, {1, 4}, {1, 5}, {2, 4}, {2, 5}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

//ITERATION 2

TEST_CASE("ParentsT 3.34 - Complex two procedure") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_34(), RelationshipASTs::getStmtCount3_34());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10},
		{2, 3}, {2, 4}, {2, 5}, {10, 11}, {10, 12}, {10, 13},
		{1, 3}, {1, 4}, {1, 5}, {1, 11}, {1, 12}, {1, 13},
		{14, 15}, {14, 22},
		{15, 16}, {15, 18}, {15, 19}, {15, 21}, {14, 16}, {14, 18}, {14, 19}, {14, 21},
		{16, 17}, {19, 20}, {15, 17}, {15, 20}, {14, 17}, {14, 20}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.35 - Normal Post Declared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_35(), RelationshipASTs::getStmtCount3_35());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.36 - Normal Pre Declared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_36(), RelationshipASTs::getStmtCount3_36());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.37 - Normal Pre declared Nested in If") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_37(), RelationshipASTs::getStmtCount3_37());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{3, 4}, {3, 5}, {3, 6}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.38 - Normal Pre declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_38(), RelationshipASTs::getStmtCount3_38());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{3, 4}, {3, 5}, {3, 6}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.39 - Normal Post declared Nested in If") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_39(), RelationshipASTs::getStmtCount3_39());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {1, 4}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.40 - Normal Post declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_40(), RelationshipASTs::getStmtCount3_40());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}, {1, 4}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.41 - Normal Pre declared Nested in While") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_41(), RelationshipASTs::getStmtCount3_41());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{3, 4}, {3, 5}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.42 - Normal Post declared Nested in While") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_42(), RelationshipASTs::getStmtCount3_42());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{1, 2}, {1, 3}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.43 - 3 calls sequential predeclared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_43(), RelationshipASTs::getStmtCount3_43());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.44 - 3 calls sequential post declared") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_44(), RelationshipASTs::getStmtCount3_44());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.45 - 3 calls forking from top") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_45(), RelationshipASTs::getStmtCount3_45());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.46 - 3 calls forking from bottom") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_46(), RelationshipASTs::getStmtCount3_46());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.47 - 3 calls forking from middle") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_47(), RelationshipASTs::getStmtCount3_47());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{ };
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.48 - 4 calls sequential call (mix of post and pre declared)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_48(), RelationshipASTs::getStmtCount3_48());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{8, 9}, {8, 10}, {8, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.49 - 4 calls - 1 - (2, 3, 4)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_49(), RelationshipASTs::getStmtCount3_49());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{9, 10}, {9, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.50 - 4 calls - (1, 2, 4) - 3") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_50(), RelationshipASTs::getStmtCount3_50());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{8, 9}, {8, 10}, {8, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.51 - 4 calls - 1 - (3, 4) - 2") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_51(), RelationshipASTs::getStmtCount3_51());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{9, 10}, {9, 11}, {9, 12}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.52 - 4 calls - 2 - 4 - (3, 1)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_52(), RelationshipASTs::getStmtCount3_52());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{7, 8}, {7, 9}, {7, 10}, {7, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.53 - 4 calls - (1, 2) - 3 - 4") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_53(), RelationshipASTs::getStmtCount3_53());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{9, 10}, {9, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.54 - 4 calls - (3, (2 - 4)) - 1") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_54(), RelationshipASTs::getStmtCount3_54());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{8, 9}, {8, 10}, {8, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 3.55 - 4 calls - 2 - ((1 - 4), 3)") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(RelationshipASTs::getAST3_55(), RelationshipASTs::getStmtCount3_55());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{9, 10}, {9, 11}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}

TEST_CASE("ParentsT 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor de = DesignExtractor(ComplexASTs::getAST4_1(), ComplexASTs::getStmtCount4_1());
	de.extractDesignElements();

	std::vector<std::pair<int, int>> expectedParentsT{
		{5, 6}, {5, 15}, {5, 16}, {5, 17},
		{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 14},
		{5, 7}, {5, 8}, {5, 9}, {5, 10}, {5, 14},
		{10, 11}, {10, 12}, {10, 13},
		{5, 11}, {5, 12}, {5, 13}, {6, 11}, {6, 12}, {6, 13}
	};
	std::sort(expectedParentsT.begin(), expectedParentsT.end());

	std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
	std::sort(actualParentsT.begin(), actualParentsT.end());

	REQUIRE(actualParentsT == expectedParentsT);
	EntityStager::clear();
}