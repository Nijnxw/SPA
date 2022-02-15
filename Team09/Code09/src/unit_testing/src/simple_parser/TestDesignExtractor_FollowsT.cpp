#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "RelationshipASTs.h"

#include <memory>
#include <vector>

//TEST_CASE("FollowsT 3.1 - Single Read") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1());
//	std::vector<std::pair<int, int>> expectedFollowsT{};
//	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);
//	EntityStager::clear();
//}
//
//TEST_CASE("FollowsT 3.2 - Single Read") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2());
//	std::vector<std::pair<int, int>> expectedFollowsT{};
//	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);
//	EntityStager::clear();
//}
//
//TEST_CASE("FollowsT 3.3 - Single Advanced Assign") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3());
//	std::vector<std::pair<int, int>> expectedFollowsT{};
//	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);
//	EntityStager::clear();
//}
//
//TEST_CASE("FollowsT 3.4 - Single Advanced Assign") {
//	EntityStager::clear();
//	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4());
//	std::vector<std::pair<int, int>> expectedFollowsT{};
//	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);
//	EntityStager::clear();
//}

TEST_CASE("FollowsT 3.5 - 2 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.6 - 2 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.7 - 2 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.8 - 3 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2}, {2, 3}, {1, 3} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.9 - 3 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2}, {2, 3}, {1, 3} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.10 - 3 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2}, {2, 3}, {1, 3} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2}, {2, 3}, {1, 3} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 3}, {3, 4}, {1, 4} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2}, {2, 4}, {1, 4} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2}, {2, 3}, {1, 3} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 4}, {4, 5}, {1, 5} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 2}, {2, 5}, {1, 5} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.17 - 2 container statements same nesting level") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17());

	std::vector<std::pair<int, int>> expectedFollowsT{ {1, 3} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.18 - 1 container - 3 basic statements - while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18());

	std::vector<std::pair<int, int>> expectedFollowsT{ {2, 3}, {3, 4}, {2, 4} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.19 - 1 container - 3 basic statements - if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19());

	std::vector<std::pair<int, int>> expectedFollowsT{ 
		{2, 3}, {3, 4}, {2, 4}, {5, 6}, {6, 7}, {5, 7}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20());

	std::vector<std::pair<int, int>> expectedFollowsT{ {2, 3}, {5, 6} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21());

	std::vector<std::pair<int, int>> expectedFollowsT{ {2, 3}, {6, 7} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22());

	std::vector<std::pair<int, int>> expectedFollowsT{ {2, 5} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23());

	std::vector<std::pair<int, int>> expectedFollowsT{ {2, 4} };
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{2, 3}, {4, 5}, {5, 6}, {4, 6}, {3, 7}, {2, 7}, {8, 12}, {9, 10}, {10, 11}, {9, 11}, {12, 13}, {8, 13}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{2, 6}, {3, 4}, {4, 5}, {3, 5}, {6, 7}, {2, 7}, {8, 9}, {9, 10}, {8, 10}, {11, 12}, {12, 13}, {11, 13}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{2, 3}, {3, 4}, {2, 4}, {5, 6}, {6, 7}, {5, 7}, {8, 9}, {10, 11}, {11, 12}, {10, 12}, {9, 13}, {8, 13}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{2, 9}, {9, 10}, {2, 10}, {3, 4}, {4, 5}, {3, 5}, {6, 7}, {7, 8}, {6, 8}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{2, 3}, {3, 10}, {2, 10}, {4, 5}, {5, 6}, {4, 6}, {7, 8}, {8, 9}, {7, 9}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{2, 3}, {3, 4}, {2, 4}, {5, 6}, {6, 7}, {5, 7}, {8, 9}, {9, 10}, {8, 10}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{4, 7}, {2, 8}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{3, 5}, {2, 6}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{3, 5}, {2, 9}, {6, 8}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}

TEST_CASE("FollowsT 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33());

	std::vector<std::pair<int, int>> expectedFollowsT{
		{3, 6}, {2, 7}
	};
	std::sort(expectedFollowsT.begin(), expectedFollowsT.end());

	std::vector<std::pair<int, int>> actualFollows = EntityStager::getStagedFollowsT();
	std::sort(actualFollows.begin(), actualFollows.end());

	REQUIRE(actualFollows == expectedFollowsT);
	EntityStager::clear();
}
