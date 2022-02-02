#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

class QueryResultTable {
private:
	std::unordered_map<std::string, std::vector<std::string>> table;
	bool booleanResult = false;

public:
	QueryResultTable();
	QueryResultTable(std::unordered_map<std::string, std::vector<std::string>>& table);
	std::unordered_map<std::string, std::vector<std::string>> getTable();
	bool getBooleanResult();
	void setBooleanResult(bool inputBool);

	// Overloaded add column to cater for different use cases
	template <typename It>
	bool addColumn(std::string header, const It& rows);
};
