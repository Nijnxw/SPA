#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class QueryResultTable {
private:
	std::unordered_map<std::string, std::vector<std::string>> table;
	bool booleanResult = false;

public:
	std::unordered_map<std::string, std::vector<std::string>> getTable();
	bool getBooleanResult();
	bool setBooleanResult(bool inputBool);

	// Overloaded add column to cater for different use cases
	bool addColumn(std::string header, std::unordered_set<std::string> rows);
	bool addColumn(std::string header, std::unordered_set<int> rows);
	bool addColumn(std::string header, std::vector<std::string> rows);
	bool addColumn(std::string header, std::vector<int> rows);
};
