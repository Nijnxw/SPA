#pragma once

#include <string>
#include <unordered_set>

class DesignRelationships {
private:
	std::unordered_set<std::string> uses;
	std::unordered_set<std::string> modifies;
	DesignRelationships();

public:
	static DesignRelationships createEmpty();

	void addUses(std::string used);
	void addModifies(std::string modified);

	std::unordered_set<std::string> getUses();
	std::unordered_set<std::string> getModifies();

	int getUsesSize();
	int getModifiesSize();

	void combine(DesignRelationships other);
};