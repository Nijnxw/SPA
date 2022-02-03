#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

typedef std::unordered_map<std::string, std::vector<std::string>> Table;

class QueryResultTable {
private:
	Table table;
	bool booleanResult = false;
	// always order the headers in ascending order before converting each row value to space separated string
	std::unordered_set<std::string> stringifyRows() const;

public:
	QueryResultTable();
	QueryResultTable(Table& table);
	bool operator==(const QueryResultTable& other) const;
	Table getTable();
	bool getBooleanResult();
	void setBooleanResult(bool inputBool);

	// Overloaded add column to cater for different use cases
	template <typename It>
	bool addColumn(const std::string& header, const It& rows);
};
