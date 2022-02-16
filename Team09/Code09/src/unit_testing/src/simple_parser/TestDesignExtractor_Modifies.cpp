#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "RelationshipASTs.h"

#include <string>
#include <unordered_set>
#include <vector>

//TODO
//TEST_CASE("Modifies 3.1 - Single Read") {
//	EntityStager::clear();
//	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
//		{2, {"x"}}
//	};
//	std::sort(expectedModifies.begin(), expectedModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
//	std::sort(actualModifies.begin(), actualModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	REQUIRE(actualModifies == expectedModifies);
//	EntityStager::clear();
//}
//
//TEST_CASE("Modifies 3.2 - Single Read") {
//	EntityStager::clear();
//	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
//		{2, {"x"}}
//	};
//	std::sort(expectedModifies.begin(), expectedModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
//	std::sort(actualModifies.begin(), actualModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	REQUIRE(actualModifies == expectedModifies);
//	EntityStager::clear();
//}
//
//TEST_CASE("Modifies 3.3 - Single Advanced Assign") {
//	EntityStager::clear();
//	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
//		{2, {"x"}}
//	};
//	std::sort(expectedModifies.begin(), expectedModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
//	std::sort(actualModifies.begin(), actualModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	REQUIRE(actualModifies == expectedModifies);
//	EntityStager::clear();
//}
//
//TEST_CASE("Modifies 3.4 - Single Advanced Assign") {
//	EntityStager::clear();
//	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
//		{2, {"x"}}
//	};
//	std::sort(expectedModifies.begin(), expectedModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
//	std::sort(actualModifies.begin(), actualModifies.end(),
//		[](auto& left, auto& right) {return left.first < right.first; });
//
//	REQUIRE(actualModifies == expectedModifies);
//	EntityStager::clear();
//}

TEST_CASE("Modifies 3.5 - 2 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_5());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.6 - 2 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_6());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.7 - 2 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_7());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{2, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.8 - 3 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_8());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.9 - 3 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_9());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"y"}}, {3, {"z"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.10 - 3 basic statements") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_10());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {3, {"x"}},
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.11 - 2 basic statements + 1 container - while at end of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_11());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {3, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.12 - 2 basic statements + 1 container - while at start of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_12());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.13 - 2 basic statements + 1 container - while at middle of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_13());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.14 - 2 basic statements + 1 container - if at end of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_14());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {3, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.15 - 2 basic statements + 1 container - if at start of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_15());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.16 - 2 basic statements + 1 container - if at middle of procedure") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_16());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.17 - 2 container statements same nesting level") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_17());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.18 - 1 container - 3 basic statements - while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_18());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x"}}, {2, {"x"}}, {4, {"x"}},
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.19 - 1 container - 3 basic statements - if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_19());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y"}}, {2, {"x"}}, {4, {"x"}}, {5, {"y"}}, {7, {"y"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.20 - 2 nesting levels; 1 basic statement per level - if-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_20());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"y"}}, {4, {"y"}},
		{5, {"z"}}, {6, {"y"}},{7, {"y"}},
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.21 - 2 nesting levels; 1 basic statement per level - if-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_21());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"y"}}, {4, {"y"}},
		{6, {"z"}}, {7, {"z"}}, {8, {"z"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.22 - 2 nesting levels; 1 basic statement per level - while-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_22());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x", "z"}}, {3, {"x"}}, {4, {"z"}}, {5, {"y"}},
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.23 - 2 nesting levels; 1 basic statement per level - while-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_23());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y"}}, {2, {"x"}}, {3, {"x"}}, {4, {"y"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.24 - 2 nest levels; 3 statements per nest level - if-while perm 1") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_24());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x", "y"}}, {4, {"y"}}, {6, {"x"}}, {7, {"x"}},
		{8, {"x", "y"}}, {9, {"y"}}, {11, {"x"}}, {12, {"z"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.25 - 2 nest levels; 3 statements per nest level - if-while perm 2") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_25());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x", "y"}}, {3, {"y"}}, {5, {"x"}}, {6, {"x"}}, {7, {"x"}},
		{8, {"z"}}, {10, {"x", "y"}}, {11, {"y"}}, {13, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.26 - 2 nest levels; 3 statements per nest level - if-while perm 3") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_26());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x", "y"}}, {5, {"y"}}, {7, {"x"}},
		{8, {"z"}}, {9, {"x", "y"}}, {10, {"y"}}, {12, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.27 - 2 nest levels; 3 statements per nest level - while-if loc 1") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_27());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x", "y", "z"}}, {3, {"y"}}, {5, {"x"}},
		{6, {"z"}}, {8, {"z"}}, {9, {"x"}}, {10, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.28 - 2 nest levels; 3 statements per nest level - while-if loc 2") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_28());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x", "y", "z"}}, {4, {"y"}}, {6, {"x"}},
		{7, {"z"}}, {9, {"z"}}, {10, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.29 - 2 nest levels; 3 statements per nest level - while-if loc 3") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_29());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x", "y", "z"}}, {5, {"y"}}, {7, {"x"}},
		{8, {"z"}}, {10, {"z"}},
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.30 - 3 levels of nesting - 1 stmt per nest level - if-if-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_30());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"y"}}, {4, {"z"}}, {5, {"z"}},
		{8, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.31 - 3 levels of nesting - 1 stmt per nest level - while-while-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_31());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "y", "z"}}, {2, {"y", "z"}}, {3, {"z"}},
		{4, {"z"}}, {5, {"y"}}, {6, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.32 - 3 levels of nesting - 1 stmt per nest level - while-if-while") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_32());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"w", "x", "y", "z"}}, {2, {"w", "y", "z"}}, {3, {"z"}}, {4, {"z"}},
		{5, {"y"}}, {6, {"w"}}, {7, {"w"}}, {8, {"w"}}, {9, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}

TEST_CASE("Modifies 3.33 - 3 levels of nesting - 1 stmt per nest level - if-while-if") {
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_33());

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies{
		{1, {"x", "z"}}, {2, {"z"}}, {3, {"z"}}, {4, {"z"}},
		{7, {"x"}}
	};
	std::sort(expectedModifies.begin(), expectedModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	std::vector<std::pair<int, std::unordered_set<std::string>>> actualModifies = EntityStager::getStagedModifiesStatement();
	std::sort(actualModifies.begin(), actualModifies.end(),
		[](auto& left, auto& right) {return left.first < right.first; });

	REQUIRE(actualModifies == expectedModifies);
	EntityStager::clear();
}
