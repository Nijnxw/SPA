#include "QueryClauseResult.h"
#include "util/QueryUtils.h"

QueryClauseResult::QueryClauseResult(bool boolResult) : booleanResult(boolResult) {}

QueryClauseResult::QueryClauseResult(const Table& table) : table(table), booleanResult(table.size() != 0) {}

bool QueryClauseResult::operator==(const QueryClauseResult& other) const {
	bool diffNumHeaders = table.size() != other.table.size();
	bool bothZero = table.size() == 0 && other.table.size() == 0;
	if (bothZero) {
		return true;
	}
	if (diffNumHeaders || booleanResult != other.booleanResult) {
		return false;
	}

	std::vector<std::string> thisHeaders;
	for (const auto& col: table) {
		thisHeaders.push_back(col.first);
		if (other.table.count(col.first) == 0) {
			return false;
		}
	}

	auto thisNumRows = table.at(thisHeaders.front()).size();
	auto otherNumRows = other.table.at(thisHeaders.front()).size();

	if (thisNumRows != otherNumRows) {
		return false;
	}

	std::unordered_set<std::string> thisRowStrings = QueryUtils::stringifyRows(table);
	std::unordered_set<std::string> otherRowStrings = QueryUtils::stringifyRows(other.table);
	return thisRowStrings == otherRowStrings;
}

template<typename T>
std::string toString(const T& value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<typename It>
bool QueryClauseResult::addColumn(const std::string& header, const It& rows) {
	if (rows.size() == 0) return false;
	setBooleanResult(true);
	std::vector<std::string> v;
	for (const auto& it: rows) {
		v.push_back(toString(it));
	}
	table[header] = v;
	return true;
}

Table QueryClauseResult::getTable() const {
	return table;
}

bool QueryClauseResult::containsValidResult() const {
	return booleanResult || !table.empty();
}

void QueryClauseResult::setBooleanResult(bool inputBool) {
	booleanResult = inputBool;
}

template bool QueryClauseResult::addColumn<std::unordered_set<std::string>>(const std::string& header,
																			const std::unordered_set<std::string>& rows);
template bool
QueryClauseResult::addColumn<std::unordered_set<int>>(const std::string& header, const std::unordered_set<int>& rows);
template bool
QueryClauseResult::addColumn<std::vector<std::string>>(const std::string& header, const std::vector<std::string>& rows);
template bool QueryClauseResult::addColumn<std::vector<int>>(const std::string& header, const std::vector<int>& rows);
