#include <string>
#include "QueryUtils.h"

/*
 * Searches for common attributes and select tuples from both tables where the values for the common attributes are the
 * same then performs a cross-product between those tuples. The resulting table's headers is a union of both tables'
 * headers.
 */
Table QueryUtils::hashJoin(const Table& firstTable, const Table& secondTable) {
	std::unordered_set<std::string> commonTableHeaders = getCommonHeaders(firstTable, secondTable);
	Table resultTable = initialiseTable(firstTable, secondTable);

	auto firstTableCol = firstTable.begin()->second;
	size_t numFirstTableRows = firstTableCol.size();
	auto secondTableCol = secondTable.begin()->second;
	size_t numSecondTableRows = secondTableCol.size();

	// can't hash join (natural join) if no common headers
	if (commonTableHeaders.empty() || numFirstTableRows == 0 || numSecondTableRows == 0) {
		return {};
	}

	if (numFirstTableRows < numSecondTableRows) {
		hashJoinHelper(commonTableHeaders, firstTable, numFirstTableRows, secondTable, numSecondTableRows, resultTable);
	} else {
		hashJoinHelper(commonTableHeaders, secondTable, numSecondTableRows, firstTable, numFirstTableRows, resultTable);
	}

	return resultTable;
}

void QueryUtils::hashJoinHelper(const std::unordered_set<std::string>& commonTableHeaders, const Table& firstTable,
								size_t numFirstTableRows, const Table& secondTable, size_t numSecondTableRows,
								Table& resultTable) {
	std::unordered_map<std::string, std::unordered_set<int>> commonValuesMap;
	for (auto i = 0; i < numFirstTableRows; i++) {
		std::string commonValueTuple = selectTupleToString(commonTableHeaders, i, firstTable);
		commonValuesMap[commonValueTuple].emplace(i);
	}

	for (auto i = 0; i < numSecondTableRows; i++) {
		std::string commonValueTuple = selectTupleToString(commonTableHeaders, i, secondTable);

		if (commonValuesMap.count(commonValueTuple) == 0) {
			continue;
		}
		const std::unordered_set<int>& crossRows = commonValuesMap.at(commonValueTuple);
		for (auto rowNum: crossRows) {
			for (const auto& keyVal: firstTable) {
				resultTable[keyVal.first].emplace_back(keyVal.second.at(rowNum));
			}
			for (const auto& keyVal: secondTable) {
				if (firstTable.count(keyVal.first) > 0) {
					continue;
				}
				resultTable[keyVal.first].emplace_back(keyVal.second.at(i));
			}
		}
	}
}

/*
 * Performs cartesian product between 2 tables. Returns empty if any table is empty or if the tables share some common
 * header(s).
 */
Table QueryUtils::crossProduct(const Table& firstTable, const Table& secondTable) {
	const std::unordered_set<std::string> commonTableHeaders = getCommonHeaders(firstTable, secondTable);
	Table resultTable = initialiseTable(firstTable, secondTable);

	if (firstTable.empty() || secondTable.empty() || !commonTableHeaders.empty()) {
		return {};
	}

	const auto& firstTableCol = firstTable.begin()->second;
	auto numFirstTableRows = firstTableCol.size();
	const auto& secondTableCol = secondTable.begin()->second;
	auto numSecondTableRows = secondTableCol.size();

	for (auto i = 0; i < numFirstTableRows; i++) {
		for (auto j = 0; j < numSecondTableRows; j++) {
			for (const auto& keyVal: firstTable) {
				const auto& colVals = keyVal.second;
				resultTable[keyVal.first].emplace_back(colVals.at(i));
			}
			for (const auto& keyVal: secondTable) {
				const auto& colVals = keyVal.second;
				resultTable[keyVal.first].emplace_back(colVals.at(j));
			}
		}
	}

	return resultTable;
}

/*
 * Performs an intersection between the table headers of two tables.
 */
std::unordered_set<std::string>
QueryUtils::getCommonHeaders(const Table& firstTable, const Table& secondTable) {
	std::unordered_set<std::string> commonHeaders;

	if (firstTable.size() < secondTable.size()) {
		for (auto& col: firstTable) {
			if (secondTable.count(col.first) != 0) {
				commonHeaders.insert(col.first);
			}
		}
	} else {
		for (auto& col: secondTable) {
			if (firstTable.count(col.first) != 0) {
				commonHeaders.insert(col.first);
			}
		}
	}

	return commonHeaders;
}

Table QueryUtils::initialiseTable(const Table& firstTable, const Table& secondTable) {
	Table newTable;
	for (const auto& keyVal: firstTable) {
		newTable[keyVal.first];
	}
	for (const auto& keyVal: secondTable) {
		newTable[keyVal.first];
	}
	return newTable;
}

/*
 * Returns a string representation of selected values within a tuple. Each value is separated by a single whitespace
 */
std::string
QueryUtils::selectTupleToString(const std::unordered_set<std::string>& headers, size_t rowNum, const Table& table) {
	std::string stringRep;
	auto col = headers.begin();
	while (col != headers.end()) {
		const auto& colValues = table.at(*col);
		stringRep += colValues.at(rowNum);
		col++;
		if (col != headers.end()) {
			stringRep += " ";
		}
	}

	return stringRep;
}

std::unordered_set<std::string>
QueryUtils::stringifyRows(const Table& table, const std::vector<std::string>& colOrder) {
	std::unordered_set<std::string> rows;

	if (colOrder.empty()) {
		return rows;
	}

	for (const auto& col: colOrder) {
		if (table.count(col) == 0) {
			return rows;
		}
	}

	const auto& tableCol = table.begin()->second;
	auto numTableRows = tableCol.size();
	for (auto i = 0; i < numTableRows; i++) {
		std::string row;
		for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
			const auto& colValues = table.at(*it);
			row += colValues.at(i);
			if (next(it) != colOrder.end()) {
				row += " ";
			}
		}
		rows.insert(row);
	}
	return rows;
}


std::unordered_set<std::string> QueryUtils::stringifyRows(const Table& table) {
	std::vector<std::string> headers;
	for (const auto& col: table) {
		headers.push_back(col.first);
	}
	std::sort(headers.begin(), headers.end());
	return stringifyRows(table, headers);
}
