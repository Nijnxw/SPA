#include "QueryClauseTable.h"

QueryClauseTable::QueryClauseTable() {}

QueryClauseTable::QueryClauseTable(Table& table) : table(table), booleanResult(table.size() != 0) {}

bool QueryClauseTable::operator==(const QueryClauseTable& other) const {
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

	std::unordered_set<std::string> thisRowStrings = stringifyRows();
	std::unordered_set<std::string> otherRowStrings = other.stringifyRows();
	return thisRowStrings == otherRowStrings;
}

template<typename T>
std::string toString(const T& value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<typename It>
bool QueryClauseTable::addColumn(const std::string& header, const It& rows) {
	if (rows.size() == 0) return false;
	setBooleanResult(true);
	std::vector<std::string> v;
	for (const auto& it: rows) {
		v.push_back(toString(it));
	}
	table[header] = v;
	return true;
}

Table QueryClauseTable::getTable() {
	return table;
}

bool QueryClauseTable::getBooleanResult() {
	return booleanResult;
}

void QueryClauseTable::setBooleanResult(bool inputBool) {
	booleanResult = inputBool;
}

std::unordered_set<std::string> QueryClauseTable::stringifyRows() const {
	std::vector<std::string> headers;
	std::unordered_set<std::string> rows;

	for (const auto& col: table) {
		headers.push_back(col.first);
	}
	std::sort(headers.begin(), headers.end());

	auto numRows = table.at(headers.front()).size();
	for (auto i = 0; i < numRows; i++) {
		std::string row;
		for (const auto& header: headers) {
			row += table.at(header).at(i);
			if (header != headers.back()) {
				row += " ";
			}
		}
		rows.emplace(row);
	}
	return rows;
}

template bool QueryClauseTable::addColumn<std::unordered_set<std::string>>(const std::string& header,
																		   const std::unordered_set<std::string>& rows);
template bool
QueryClauseTable::addColumn<std::unordered_set<int>>(const std::string& header, const std::unordered_set<int>& rows);
template bool
QueryClauseTable::addColumn<std::vector<std::string>>(const std::string& header, const std::vector<std::string>& rows);
template bool QueryClauseTable::addColumn<std::vector<int>>(const std::string& header, const std::vector<int>& rows);
