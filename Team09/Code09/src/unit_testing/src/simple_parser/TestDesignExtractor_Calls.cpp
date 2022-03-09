#include "catch.hpp"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"
#include "asts/ComplexASTs.h"
#include "asts/RelationshipASTs.h"

#include <memory>
#include <vector>

TEST_CASE("Calls 3.35 - Normal Post Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_35());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram2"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.36 - Normal Pre Declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_36());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram1"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.37 - Normal Pre declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_37());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram1"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.38 - Normal Pre declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_38());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram1"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.39 - Normal Post declared Nested in If") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_39());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram2"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.40 - Normal Post declared Nested in Else") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_40());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram2"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.41 - Normal Pre declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_41());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram1"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.42 - Normal Post declared Nested in While") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_42());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram2"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.43 - 3 calls sequential predeclared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_43());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram1"}, {"testProgram3", "testProgram2"},
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.44 - 3 calls sequential post declared") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_44());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram2"}, {"testProgram2", "testProgram3"},
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.45 - 3 calls forking from top") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_45());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram2"}, {"testProgram1", "testProgram3"},
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.46 - 3 calls forking from bottom") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_46());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram3", "testProgram1"}, {"testProgram3", "testProgram2"},
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.47 - 3 calls forking from middle") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_47());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram1"}, {"testProgram2", "testProgram3"},
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.48 - 4 calls sequential call (mix of post and pre declared)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_48());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram3"}, {"testProgram2", "testProgram1"}, {"testProgram4", "testProgram2"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.49 - 4 calls - 1 - (2, 3, 4)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_49());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram2"}, {"testProgram1", "testProgram3"}, {"testProgram1", "testProgram4"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.50 - 4 calls - (1, 2, 4) - 3") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_50());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram3"}, {"testProgram2", "testProgram3"}, {"testProgram4", "testProgram3"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.51 - 4 calls - 1 - (3, 4) - 2") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_51());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram3"}, {"testProgram1", "testProgram4"},
		{"testProgram3", "testProgram2"}, {"testProgram4", "testProgram2"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.52 - 4 calls - 2 - 4 - (3, 1)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_52());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram4"}, {"testProgram4", "testProgram3"},
		{"testProgram4", "testProgram1"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.53 - 4 calls - (1, 2) - 3 - 4") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_53());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram1", "testProgram3"}, {"testProgram2", "testProgram3"},
		{"testProgram3", "testProgram4"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.54 - 4 calls - (3, (2 - 4)) - 1") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_54());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram3", "testProgram1"}, {"testProgram2", "testProgram4"},
		{"testProgram4", "testProgram1"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}

TEST_CASE("Calls 3.55 - 4 calls - 2 - ((1 - 4), 3)") {
	EntityStager::clear();
	DesignExtractor::extractDesignElements(RelationshipASTs::getAST3_55());

	std::vector<std::pair<std::string, std::string>> expectedCalls{
		{"testProgram2", "testProgram1"}, {"testProgram2", "testProgram3"},
		{"testProgram1", "testProgram4"}
	};
	std::sort(expectedCalls.begin(), expectedCalls.end());

	std::vector<std::pair<std::string, std::string>> actualCalls = EntityStager::getStagedCalls();
	std::sort(actualCalls.begin(), actualCalls.end());

	REQUIRE(actualCalls == expectedCalls);
	EntityStager::clear();
}