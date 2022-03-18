#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/RelationshipASTs.h"
#include "asts/ComplexASTs.h"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

TEST_CASE("CFG 3.1 - Single Read") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_1(), RelationshipASTs::getStmtCount3_1());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.2 - Single Print") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_2(), RelationshipASTs::getStmtCount3_2());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.3 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_3(), RelationshipASTs::getStmtCount3_3());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.4 - Single Advanced Assign") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_4(), RelationshipASTs::getStmtCount3_4());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.5 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5(), RelationshipASTs::getStmtCount3_5());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {2}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.6 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6(), RelationshipASTs::getStmtCount3_6());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {2}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.7 - 2 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7(), RelationshipASTs::getStmtCount3_7());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {2}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.8 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8(), RelationshipASTs::getStmtCount3_8());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {3}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.9 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9(), RelationshipASTs::getStmtCount3_9());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {3}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.10 - 3 basic statements") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10(), RelationshipASTs::getStmtCount3_10());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {3}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11(), RelationshipASTs::getStmtCount3_11());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {4}, {3}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {3}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12(), RelationshipASTs::getStmtCount3_12());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 3}, {1}, {4}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {4}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13(), RelationshipASTs::getStmtCount3_13());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 4}, {2}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {4}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14(), RelationshipASTs::getStmtCount3_14());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {4, 5}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {4, 5}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15(), RelationshipASTs::getStmtCount3_15());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 3}, {4}, {4}, {5}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {5}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16(), RelationshipASTs::getStmtCount3_16());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 4}, {5}, {5}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {5}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.17 - 2 container statements same nesting level") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17(), RelationshipASTs::getStmtCount3_17());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 3}, {1}, {4, 5}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {4, 5}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.18 - 1 container - 3 basic statements - while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18(), RelationshipASTs::getStmtCount3_18());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {4}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.19 - 1 container - 3 basic statements - if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19(), RelationshipASTs::getStmtCount3_19());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 5}, {3}, {4}, {}, {6}, {7}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {4, 7}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20(), RelationshipASTs::getStmtCount3_20());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 5}, {3}, {4}, {3}, {6}, {7}, {6}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {3, 6}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21(), RelationshipASTs::getStmtCount3_21());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 6}, {3}, {4, 5}, {}, {}, {7}, {8, 9}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {4, 5, 8, 9}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22(), RelationshipASTs::getStmtCount3_22());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 4}, {5}, {5}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23(), RelationshipASTs::getStmtCount3_23());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 4}, {2}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24(), RelationshipASTs::getStmtCount3_24());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 8}, {3}, {4, 7}, {5}, {6}, {3}, {},
		{9, 12}, {10}, {11}, {8}, {13}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {7, 13}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25(), RelationshipASTs::getStmtCount3_25());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 8}, {3, 6}, {4}, {5}, {2}, {7}, {},
		{9}, {10}, {11}, {12}, {13}, {10}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {7, 10}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26(), RelationshipASTs::getStmtCount3_26());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 8}, {3}, {4}, {5}, {6}, {7}, {4},
		{9}, {10, 13}, {11}, {12}, {9}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {4, 13}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27(), RelationshipASTs::getStmtCount3_27());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 6}, {4}, {5}, {9}, {7}, {8},
		{9}, {10}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28(), RelationshipASTs::getStmtCount3_28());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {4, 7}, {5}, {6}, {10}, {8},
		{9}, {10}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29(), RelationshipASTs::getStmtCount3_29());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {4}, {5, 8}, {6}, {7}, {1},
		{9}, {10}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30(), RelationshipASTs::getStmtCount3_30());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 9}, {3, 4}, {8}, {5, 6}, {7}, {7}, {8}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {8, 9}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31(), RelationshipASTs::getStmtCount3_31());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 6}, {4, 5}, {3}, {2}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32(), RelationshipASTs::getStmtCount3_32());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 6}, {4, 5}, {3}, {9}, {7, 8}, {6}, {9}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33(), RelationshipASTs::getStmtCount3_33());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2, 8}, {3, 7}, {4, 5}, {6}, {6}, {2}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {7, 8}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.34 - Complex two procedure") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_34(), RelationshipASTs::getStmtCount3_34());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 14}, {2, 8}, {3, 6}, {4}, {5}, {2}, {7}, {}, {9}, {10}, {11}, {12}, {13}, {10},
		{15}, {16, 19}, {17, 18}, {16}, {22}, {20, 21}, {19}, {22}, {14}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {7, 10}}, 
		{"testProgram2", {14}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.35 - Normal Post Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_35(), RelationshipASTs::getStmtCount3_35());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 4}, {2}, {3}, {}, {5}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {3}},
		{"testProgram2", {5}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.36 - Normal Pre Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_36(), RelationshipASTs::getStmtCount3_36());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3}, {2}, {}, {4}, {5}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {5}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.37 - Normal Pre declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_37(), RelationshipASTs::getStmtCount3_37());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3}, {2}, {}, {4, 6}, {5}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {5, 6}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.38 - Normal Pre declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_38(), RelationshipASTs::getStmtCount3_38());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3}, {2}, {}, {4, 5}, {}, {6}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {4, 6}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.39 - Normal Post declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_39(), RelationshipASTs::getStmtCount3_39());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 5}, {2, 4}, {3}, {}, {}, {6}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {3, 4}},
		{"testProgram2", {6}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.40 - Normal Post declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_40(), RelationshipASTs::getStmtCount3_40());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 5}, {2, 3}, {}, {4}, {}, {6}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2, 4}},
		{"testProgram2", {6}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.41 - Normal Pre declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_41(), RelationshipASTs::getStmtCount3_41());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 2}, {}, {3}, {4}, {5}, {3}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {1}},
		{"testProgram2", {3}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.42 - Normal Post declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_42(), RelationshipASTs::getStmtCount3_42());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 5}, {2, 4}, {3}, {1}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {4}},
		{"testProgram2", {5}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.43 - 3 calls sequential predeclared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_43(), RelationshipASTs::getStmtCount3_43());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3, 6}, {2}, {}, {4}, {5}, {}, {7}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {5}},
		{"testProgram3", {7}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.44 - 3 calls sequential post declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_44(), RelationshipASTs::getStmtCount3_44());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 4, 7}, {2}, {3}, {}, {5}, {6}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {3}},
		{"testProgram2", {6}},
		{"testProgram3", {7}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.45 - 3 calls forking from top") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_45(), RelationshipASTs::getStmtCount3_45());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 5, 7}, {2}, {3}, {4}, {}, {6}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {4}},
		{"testProgram2", {6}},
		{"testProgram3", {7}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.46 - 3 calls forking from bottom") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_46(), RelationshipASTs::getStmtCount3_46());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3, 5}, {2}, {}, {4}, {}, {6}, {7}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {4}},
		{"testProgram3", {7}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.47 - 3 calls forking from middle") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_47(), RelationshipASTs::getStmtCount3_47());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3, 7}, {2}, {}, {4}, {5}, {6}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {6}},
		{"testProgram3", {7}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.48 - 4 calls sequential call (mix of post and pre declared)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_48(), RelationshipASTs::getStmtCount3_48());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 4, 7, 8}, {2}, {3}, {}, {5}, {6}, {}, {}, {9, 10}, {}, {11}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {3}},
		{"testProgram2", {6}},
		{"testProgram3", {7}},
		{"testProgram4", {9, 11}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.49 - 4 calls - 1 - (2, 3, 4)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_49(), RelationshipASTs::getStmtCount3_49());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 6, 8, 9}, {2}, {3}, {4}, {5}, {}, {7}, {}, {}, {10, 11}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {5}},
		{"testProgram2", {7}},
		{"testProgram3", {8}},
		{"testProgram4", {10, 11}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.50 - 4 calls - (1, 2, 4) - 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_50(), RelationshipASTs::getStmtCount3_50());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 4, 7, 8}, {2}, {3}, {}, {5}, {6}, {}, {}, {9, 11}, {10}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {3}},
		{"testProgram2", {6}},
		{"testProgram3", {7}},
		{"testProgram4", {10, 11}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.51 - 4 calls - 1 - (3, 4) - 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_51(), RelationshipASTs::getStmtCount3_51());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 5, 7, 9}, {2}, {3}, {4}, {}, {6}, {}, {8}, {}, {10, 12}, {11}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {4}},
		{"testProgram2", {6}},
		{"testProgram3", {8}},
		{"testProgram4", {11, 12}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.52 - 4 calls - 2 - 4 - (3, 1)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_52(), RelationshipASTs::getStmtCount3_52());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3, 6, 7}, {2}, {}, {4}, {5}, {}, {}, {8, 10}, {9}, {}, {11}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {5}},
		{"testProgram3", {6}},
		{"testProgram4", {9, 11}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.53 - 4 calls - (1, 2) - 3 - 4") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_53(), RelationshipASTs::getStmtCount3_53());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 4, 7, 9}, {2}, {3}, {}, {5}, {6}, {}, {8}, {}, {10, 11}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {3}},
		{"testProgram2", {6}},
		{"testProgram3", {8}},
		{"testProgram4", {10, 11}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.54 - 4 calls - (3, (2 - 4)) - 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_54(), RelationshipASTs::getStmtCount3_54());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 3, 6, 8}, {2}, {}, {4}, {5}, {}, {7}, {}, {9, 10}, {}, {11}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {2}},
		{"testProgram2", {5}},
		{"testProgram3", {7}},
		{"testProgram4", {9, 11}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.55 - 4 calls - 2 - ((1 - 4), 3)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_55(), RelationshipASTs::getStmtCount3_55());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1, 4, 8, 9}, {2}, {3}, {}, {5}, {6}, {7}, {}, {}, {10, 11}, {}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram1", {3}},
		{"testProgram2", {7}},
		{"testProgram3", {8}},
		{"testProgram4", {10, 11}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.56 - 3 if forks converging into single statement") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_56(), RelationshipASTs::getStmtCount3_56());

	std::vector<std::unordered_set<int>> expectedCFG {
		{1}, {2, 9}, {3, 6}, {4, 5}, {16}, {16}, {7, 8}, {16}, {16},
		{10, 13}, {11, 12}, {16}, {16}, {14, 15}, {16}, {16}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {16}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 3.57 - 3 if forks converging to while statement") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_57(), RelationshipASTs::getStmtCount3_57());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3, 10}, {4, 7}, {5, 6}, {1}, {1}, {8, 9}, {1}, {1},
		{11, 14}, {12, 13}, {1}, {1}, {15, 16}, {1}, {1}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {1}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}

TEST_CASE("CFG 4.1 - Complex AST") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(ComplexASTs::getAST4_1(), ComplexASTs::getStmtCount4_1());

	std::vector<std::unordered_set<int>> expectedCFG{
		{1}, {2}, {3}, {4}, {5}, {6, 15}, {7, 18}, {8}, {9}, {10},
		{11, 13}, {12}, {14}, {14}, {6}, {16},  {17}, {18}, {}
	};
	std::vector<std::unordered_set<int>> actualCFG = EntityStager::getCFG();
	REQUIRE(expectedCFG == actualCFG);

	std::unordered_map<std::string, std::unordered_set<int>> expectedMappings{
		{"testProgram", {18}}
	};
	std::unordered_map<std::string, std::unordered_set<int>> actualMappings = EntityStager::getStagedProcToLastStmts();
	REQUIRE(expectedMappings == actualMappings);
}