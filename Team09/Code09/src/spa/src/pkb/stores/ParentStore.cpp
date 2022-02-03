#include "ParentStore.h"

std::unordered_map<int, std::unordered_set<int>> parentToChildren;
std::unordered_map<int, int> childToParent;
std::unordered_map<int, int> parentTPairs;
std::unordered_map<int, std::unordered_set<int>> parentToChildrenT;
std::unordered_map<int, std::unordered_set<int>> childToParentsT;

ParentStore::ParentStore() {}

void ParentStore::clear() {
	parentStatements.clear();
	childStatements.clear();
	parentToChildren.clear();
	childToParent.clear();
	parentToChildrenT.clear();
	childToParentsT.clear();
}

bool ParentStore::addParent(int parent, int child) {
	return PKBUtil::addToMapWithSet(parentToChildren, parent, child) && childToParent.insert({child, parent}).second;
}

bool ParentStore::addParentT(int parent, int child) {
	return parentTPairs.insert({ parent, child }).second && PKBUtil::addToMapWithSet(parentToChildrenT, parent, child) && PKBUtil::addToMapWithSet(childToParentsT, child, parent);
}

QueryResultTable ParentStore::getParent(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	QueryResultTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		queryResult = getParentByStatementNumber(LHS, RHS, RHSType);
		break;
	case EntityType::STMT:
		queryResult = getParentByStatementVariable(LHS, RHS, RHSType);
		break;
	case EntityType::WILD:
		queryResult = getParentByUnderscore(RHS, RHSType);
		break;
	default:
		break;
	}

	return queryResult;
}

QueryResultTable ParentStore::getParentByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent(1, 2) 
		if (isParentRelationship(LHS, RHS)) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent(1, s)
		if (isParent(std::stoi(LHS))) {
			queryResult.addColumn(RHS, getChildren(LHS));
		}
		break;
	case EntityType::WILD: // Parent(1, _)
		if (isParent(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryResultTable ParentStore::getParentByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent(s, 2)
		if (isChild(std::stoi(RHS))) {
			std::vector<int> parent;
			parent.push_back(getParent(RHS));
			queryResult.addColumn(LHS, parent);
		}
		break;
	case EntityType::STMT: // Parent(s1, s2)
		auto [parents, children] = getAllParentPairs();
		queryResult.addColumn(LHS, parents);
		queryResult.addColumn(RHS, children);
		break;
	case EntityType::WILD: // Parent(s, _)
		queryResult.addColumn(LHS, getAllParents());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryResultTable ParentStore::getParentByUnderscore(std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent(_, 2)
		if (isChild(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent(_, s)
		queryResult.addColumn(LHS, getAllChildren());
		break;
	case EntityType::WILD: // Parent(_, _)
		if (hasParentRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryResultTable ParentStore::getParentT(std::string& LHS, std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult)
{
	QueryResultTable queryResult;

	switch (LHSType) {
	case EntityType::INT:
		queryResult = getParentTByStatementNumber(LHS, RHS, RHSType);
		break;
	case EntityType::STMT:
		queryResult = getParentTByStatementVariable(LHS, RHS, RHSType);
		break;
	case EntityType::WILD:
		queryResult = getParentTByUnderscore(RHS, RHSType);
		break;
	default:
		break;
	}

	return queryResult;
}

QueryResultTable ParentStore::getParentTByStatementNumber(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent*(1, 2) 
		if (isParentTRelationship(LHS, RHS)) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent*(1, s)
		if (isParentT(std::stoi(LHS))) {
			queryResult.addColumn(RHS, getChildrenT(LHS));
		}
		break;
	case EntityType::WILD: // Parent*(1, _)
		if (isParentT(std::stoi(LHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

QueryResultTable ParentStore::getParentByStatementVariable(std::string& LHS, std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent*(s, 2)
		if (isChildT(std::stoi(RHS))) {
			std::vector<int> parent;
			parent.push_back(getParentT(RHS));
			queryResult.addColumn(LHS, parent);
		}
		break;
	case EntityType::STMT: // Parent*(s1, s2)
		auto [parents, children] = getAllParentTPairs();
		queryResult.addColumn(LHS, parents);
		queryResult.addColumn(RHS, children);
		break;
	case EntityType::WILD: // Parent*(s, _)
		queryResult.addColumn(LHS, getAllParentsT());
		break;
	default:
		break;
	}

	return queryResult;
}
QueryResultTable ParentStore::getParentTByUnderscore(std::string& RHS, EntityType RHSType) {
	QueryResultTable queryResult;

	switch (RHSType) {
	case EntityType::INT: // Parent*(_, 2)
		if (isChildT(std::stoi(RHS))) {
			queryResult.setBooleanResult(true);
		}
		break;
	case EntityType::STMT: // Parent*(_, s)
		queryResult.addColumn(LHS, getAllChildrenT());
		break;
	case EntityType::WILD: // Parent*(_, _)
		if (hasParentTRelationship()) {
			queryResult.setBooleanResult(true);
		}
		break;
	default:
		break;
	}

	return queryResult;
}

bool ParentStore::hasParentRelationship() {
	return parentToChildren.size() > 0;
}

bool ParentStore::hasParentTRelationship() {
	return parentToChildrenT.size() > 0;
}

bool ParentStore::isParentRelationship(int parent, int child) {
	if (parentToChildren.count(parent) <= 0) {
		return false;
	}
	std::unordered_set<int> children = parentToChildren[parent];
	return children.count(child) > 0;
}

bool ParentStore::isParentTRelationship(int parent, int child) {
	if (parentToChildrenT.count(parent) <= 0) {
		return false;
	}
	std::unordered_set<int> children = parentToChildrenT[parent];
	return children.count(child) > 0;
}

bool ParentStore::isParent(int parent) {
	return parentToChildren.count(parent) > 0;
}

bool ParentStore::isChild(int child) {
	return childToParent.count(child) > 0;
}

bool ParentStore::isParentT(int parent) {
	return parentToChildrenT.count(parent) > 0;
}

bool ParentStore::isChildT(int child) {
	return childToParentsT.count(child) > 0;
}

std::unordered_set<int> ParentStore::getChildren(int parent) {
	return parentToChildren[parent];
}

int ParentStore::getParent(int child) {
	return childToParent[child];
}

std::unordered_set<int> ParentStore::getAllChildren() {
	return PKBUtil::getKeySetFromMap(childToParent);
}

std::unordered_set<int> ParentStore::getAllParents() {
	return PKBUtil::getKeySetFromMap(parentToChildren);
}

std::unordered_set<int> ParentStore::getChildrenT(int parent) {
	return parentToChildrenT[parent];
}

std::unordered_set<int> ParentStore::getParentT(int child) {
	return childToParentsT[child];
}

std::unordered_set<int> ParentStore::getAllChildrenT() {
	return PKBUtil::getKeySetFromMap(childToParentsT);
}

std::unordered_set<int> ParentStore::getAllParentsT() {
	return PKBUtil::getKeySetFromMap(parentToChildrenT);
}

std::tuple<std::vector<int>, std::vector<int>> ParentStore::getAllParentPairs() {
	return PKBUtil::convertMapToVectorTuple(parentToChildren);
}

std::tuple<std::vector<int>, std::vector<int>> ParentStore::getAllParentTPairs() {
	return PKBUtil::convertMapToVectorTuple(parentTPairs);
}