#include "catch.hpp"
#include "models/EntityType.h"
#include "models/AssignStatement.h"
#include "pkb/PKB.h"
#include "simple_parser/EntityStager.h"

#include <string>
#include <unordered_map>
#include <unordered_set>


TEST_CASE("Test EntityStager interaction with PKB") {
	EntityStager::clear();
	PKB::clearAllStores();

	EntityStager::stageProcedure("procedure");
	EntityStager::stageVariable("variable");
	EntityStager::stageConstant("123456");

	EntityStager::stageStatement(1);
	EntityStager::stageIfStatement(1, {"x"});
	EntityStager::stageWhileStatement(1, {"x"});
	EntityStager::stageReadStatement(1, "var1");
	EntityStager::stagePrintStatement(1, "var1");
	EntityStager::stageCallStatement(1, "testProgram");
	EntityStager::stageAssignStatement(1, "var1", "var2 + var3");

	EntityStager::stageFollows(1, 2);
	EntityStager::stageFollowsT(1, 2);
	EntityStager::stageParent(1, {2});
	EntityStager::stageParentT(1, {2});
	EntityStager::stageCalls("testProgram1", "testProgram2");
	EntityStager::stageCallsT("testProgram1", "testProgram2");

	std::unordered_set<std::string> varList;
	varList.insert("var1");
	varList.insert("var2");
	EntityStager::stageUsesStatements(1, varList);
	EntityStager::stageUsesProcedure("procedure", varList);
	EntityStager::stageModifiesStatements(1, varList);
	EntityStager::stageModifiesProcedure("procedure", varList);

	EntityStager::stageCFG({
		{1}, {2}, {3, 10}, {4, 7}, {5, 6}, {1}, {1}, {8, 9}, {1}, {1},
		{11, 14}, {12, 13}, {1}, {1}, {15, 16}, {1}, {1}
	});
	EntityStager::commit();

	std::unordered_set<std::string> expectedProc;
	expectedProc.insert("procedure");
	REQUIRE(PKB::getProcedures() == expectedProc);

	std::unordered_set<std::string> expectedVar;
	expectedVar.insert("variable");
	REQUIRE(PKB::getVariables() == expectedVar);

	std::unordered_set<std::string> expectedConstant;
	expectedConstant.insert("123456");
	REQUIRE(PKB::getConstants() == expectedConstant);

	std::unordered_set<int> expectedStmt;
	expectedStmt.insert(1);
	REQUIRE(PKB::getStatementNumbers() == expectedStmt);
	REQUIRE(PKB::getStatementsWithType(EntityType::READ) == expectedStmt);
	REQUIRE(PKB::getStatementsWithType(EntityType::PRINT) == expectedStmt);
	REQUIRE(PKB::getStatementsWithType(EntityType::IF) == expectedStmt);
	REQUIRE(PKB::getStatementsWithType(EntityType::WHILE) == expectedStmt);
	REQUIRE(PKB::getStatementsWithType(EntityType::CALL) == expectedStmt);

	AssignStatement expectedAssStmt(1, "var1", "var2 + var3");
	std::unordered_map<int, AssignStatement> expectedResult;
	expectedResult.insert({ 1, expectedAssStmt });
	REQUIRE(PKB::getAssignStatementsToStructs() == expectedResult);

	REQUIRE(PKB::isFollowsRelationship(1, 2));
	REQUIRE(PKB::isFollowsTRelationship(1, 2));
	REQUIRE(PKB::isParentRelationship(1, 2));
	REQUIRE(PKB::isParentTRelationship(1, 2));

	REQUIRE(PKB::getUsesStatements() == expectedStmt);
	REQUIRE(PKB::getModifiesStatements() == expectedStmt);

	std::unordered_set<std::string> expectedModVar = { "var1", "var2" };
	REQUIRE(PKB::getUsedVariables() == expectedModVar);
	REQUIRE(PKB::getModifiedVariables() == expectedModVar);

	REQUIRE(PKB::isCallsRelationship("testProgram1", "testProgram2"));
	REQUIRE(PKB::isCallsTRelationship("testProgram1", "testProgram2"));
	PKB::clearAllStores();
}