#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class NestableRelationships {
private:
	std::unordered_set<std::string> uses;
	std::unordered_set<std::string> modifies;
	std::unordered_set<std::string> calls;
	std::unordered_set<int> children;

public:
	static NestableRelationships createEmpty();

	void addUses(std::string used);
	void addModifies(std::string modified);
	void addCalls(std::string procedure);
	void addChildren(int child);
	void removeChildren(std::unordered_set<int> unwantedChildren);
	void clearChildren();

	std::unordered_set<std::string> getUses();
	std::unordered_set<std::string> getModifies();
	std::unordered_set<std::string> getCalls();
	std::unordered_set<int> getChildren();

	int getUsesSize();
	int getModifiesSize();
	int getCallsSize();
	int getChildrenSize();

	void combine(NestableRelationships other);
};