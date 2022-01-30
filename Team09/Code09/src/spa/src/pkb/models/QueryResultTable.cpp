#include "QueryResultTable.h"

#include <unordered_map>
#include <unordered_set>

QueryResultTable::QueryResultTable()

std::unordered_map<string, std::vector<string>>QueryResultTable::table;

std::unordered_map<string, std::vector<string>> QueryResultTable::getTable() {
	return table;
}

bool QueryResultTable::addColumn(string header, unordered_set<string> rows) {
	std::vector<string> v(s.begin(), s.end());
	table.emplace(header, v);
	return true;
}

bool QueryResultTable::addColumn(string header, unordered_set<int> rows) {
	std::vector<string> v();
	for_each(rows.begin(),
		rows.end(),
		[&](const auto& row) {
			v.push_back(row);
		});
	table.emplace(header, v);
	return true;
}
