#include "QueryResultTable.h"

QueryResultTable::QueryResultTable() {}
QueryResultTable::QueryResultTable(std::unordered_map<std::string, std::vector<std::string>>& table) : table(table), booleanResult(true) {}

template<typename T>
std::string toString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <typename It>
bool QueryResultTable::addColumn(std::string header, const It& rows) {
	if (rows.size() == 0) return false;
	setBooleanResult(true);
	std::vector<std::string> v;
	for (const auto& it : rows) {
		v.push_back(toString(it));
	}
	table[header] = v;
	return true;
}

std::unordered_map<std::string, std::vector<std::string>> QueryResultTable::getTable() {
	return table;
}

bool QueryResultTable::getBooleanResult() {
	return booleanResult;
}

void QueryResultTable::setBooleanResult(bool inputBool) {
	booleanResult = inputBool;
}

template bool QueryResultTable::addColumn<std::unordered_set<std::string>>(std::string header, const std::unordered_set<std::string>& rows);
template bool QueryResultTable::addColumn<std::unordered_set<int>>(std::string header, const std::unordered_set<int>& rows);
template bool QueryResultTable::addColumn<std::vector<std::string>>(std::string header, const std::vector<std::string>& rows);
template bool QueryResultTable::addColumn<std::vector<int>>(std::string header, const std::vector<int>& rows);
