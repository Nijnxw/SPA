#pragma once

#include <string>
#include <unordered_set>

class DesignRelationships {
private:
	std::unordered_set<std::string> uses;
	std::unordered_set<std::string> modifies;
	std::unordered_set<int> children;

public:
	static DesignRelationships createEmpty();

	void addUses(std::string used);
	void addModifies(std::string modified);
	void addChildren(int child);

	std::unordered_set<std::string> getUses();
	std::unordered_set<std::string> getModifies();
	std::unordered_set<int> getChildren();

	int getUsesSize();
	int getModifiesSize();
	int getChildrenSize();

	void combine(DesignRelationships other);
};