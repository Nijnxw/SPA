#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "pkb/util/PKBUtil.cpp"
#include <models/QueryResultTable.h>
#include <models/EntityType.h>

class ParentStore {
private:
	static std::unordered_map<int, std::unordered_set<int>> parentToChildren;
	static std::unordered_map<int, int> childToParent;
	static std::unordered_map<int, int> parentTPairs;
	static std::unordered_map<int, std::unordered_set<int>> parentToChildrenT;
	static std::unordered_map<int, std::unordered_set<int>> childToParentsT;

	static bool hasParentRelationship();
	static bool hasParentTRelationship();

	static bool isParentRelationship(int parent, int child);
	static bool isParentTRelationship(int parent, int child);
	static bool isParent(int parent);
	static bool isChild(int child);
	static bool isParentT(int parent);
	static bool isChildT(int child);

	static std::unordered_set<int> getChildren(int parent);
	static int getParent(int child);
	static std::unordered_set<int> getAllChildren();
	static std::unordered_set<int> getAllParents();

	static std::unordered_set<int> getChildrenT(int parent);
	static std::unordered_set<int> getParentsT(int child);
	static std::unordered_set<int> getAllChildrenT();
	static std::unordered_set<int> getAllParentsT();

	static std::tuple<std::vector<int>, std::vector<int>> getAllParentPairs();
	static std::tuple<std::vector<int>, std::vector<int>> getAllParentTPairs();

	static QueryResultTable getParentByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getParentByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getParentByUnderscore(std::string& RHS, EntityType RHSType);

	static QueryResultTable getParentTByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getParentTByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType);
	static QueryResultTable getParentTByUnderscore(std::string& RHS, EntityType RHSType);

public:
	ParentStore();

	static void clear();

	// Called by SP and DE
	static bool addParent(int parent, int child);
	static bool addParentT(int parent, int child);

	// Called by QE
	static QueryResultTable getParent(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryResultTable getParentT(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
};