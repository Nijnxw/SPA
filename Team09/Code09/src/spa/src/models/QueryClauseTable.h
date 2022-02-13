#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

typedef std::unordered_map<std::string, std::vector<std::string>> Table;

class QueryClauseTable {
private:
	Table table;
	bool booleanResult = false;

public:
	QueryClauseTable();
	QueryClauseTable(const Table& table);
	bool operator==(const QueryClauseTable& other) const;
	Table getTable();
	bool getBooleanResult();
	void setBooleanResult(bool inputBool);

	// Overloaded add column to cater for different use cases
	template<typename It>
	bool addColumn(const std::string& header, const It& rows);
};
