#include "QueryResultTable.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "QueryResultTable.h"

QueryResultTable::QueryResultTable() {}

std::unordered_map<string, std::vector<std::string>> QueryResultTable::getTable() {
	return table;
}

bool QueryResultTable::getBooleanResult() {
	return booleanResult;
}

void QueryResultTable::setBooleanResult(bool inputBool) {
	booleanResult = inputBool;
}

bool QueryResultTable::addColumn(std::string header, std::unordered_set<std::string> rows) {
	if (rows.size() == 0) break;
	getBooleanResult(true);
	table[header] = std::vector<std::string>(rows.begin(), rows.end());
	return true;
}

bool QueryResultTable::addColumn(std::string header, std::unordered_set<int> rows) {
	if (rows.size() == 0) break;
	getBooleanResult(true);
	std::vector<std::string> v;
	std::transform(std::begin(rows),
		std::end(rows),
		std::back_inserter(v),
		[](int i) { return std::to_string(i); });
	table[header] = v;
	return true;
}

bool QueryResultTable::addColumn(std::string header, std::vector<std::string> rows) {
	if (rows.size() == 0) break;
	getBooleanResult(true);
	table[header] = rows;
	return true;
}

bool QueryResultTable::addColumn(std::string header, std::vector<int> rows) {
	if (rows.size() == 0) break;
	getBooleanResult(true);
	std::vector<std::string> v;

	std::transform(std::begin(rows),
		std::end(rows),
		std::back_inserter(v),
		[](int i) { return std::to_string(i); });

	table[header] = v;
	return true;
}
