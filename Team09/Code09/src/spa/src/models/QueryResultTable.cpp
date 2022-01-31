#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "QueryResultTable.h"

QueryResultTable::QueryResultTable()

std::unordered_map<string, std::vector<std::string>>QueryResultTable::table;

std::unordered_map<string, std::vector<std::string>>QueryResultTable::getTable() {
	return table;
}

bool QueryResultTable::addColumn(std::string header, unordered_set<std::string> rows) {
	table[header] = std::vector<std::string>(rows.begin(), rows.end());
	return true;
}

bool QueryResultTable::addColumn(std::string header, unordered_set<int> rows) {
	std::vector<std::string> v;

	std::transform(std::begin(rows),
		std::end(rows),
		std::back_inserter(v),
		[](int i) { return std::to_string(i); });

	table[header] = v;
	return true;
}
