#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class QueryResultTable {
private:
	std::unordered_map<std::string, std::vector<std::string>>table;

public:
	std::unordered_map<std::string, std::vector<std::string>> getTable();
	bool addColumn(std::string header, std::unordered_set<int> rows);
	bool addColumn(std::string header, std::unordered_set<std::string> rows);

};
