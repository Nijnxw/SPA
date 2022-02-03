#include <string>
#include "QueryUtils.h"

/*
 * Searches for common attributes and select tuples from both tables where the values for the common attributes are the
 * same then performs a cross-product between those tuples. The resulting table's headers is a union of both tables'
 * headers.
 */
Table QueryUtils::hashJoin(const Table& firstTable, const Table& secondTable) {
	const std::vector <std::string> commonTableHeaders = getCommonHeaders(firstTable, secondTable);

	// can't hash join (natural join) if no common headers
	if (commonTableHeaders.empty()) {
		Table joinedTable;
		return joinedTable;
	}

	Table shorterTable;
	Table longerTable;
	auto firstTableNumRows = firstTable.at(commonTableHeaders.front()).size();
	auto secondTableNumRows = secondTable.at(commonTableHeaders.front()).size();

	if (firstTableNumRows < secondTableNumRows) {
		shorterTable = firstTable;
		longerTable = secondTable;
	} else {
		shorterTable = secondTable;
		longerTable = firstTable;
	}

	auto groupedCommonTuples = extractCommonTuples(commonTableHeaders, shorterTable, longerTable);
	std::unordered_set <std::pair<int, int>, pair_hash> pairedTuples;
	for (const auto& keyVal: groupedCommonTuples) {
		const auto& group = keyVal.second;
		crossProduct(group.first, group.second, pairedTuples);
	}

	return {joinRows(pairedTuples, shorterTable, longerTable, commonTableHeaders)};
}

/*
 * Performs an intersection between the table headers of two tables.
 */
std::vector <std::string>
QueryUtils::getCommonHeaders(const Table& firstTable, const Table& secondTable) {
	std::vector <std::string> commonHeaders;

	if (firstTable.size() < secondTable.size()) {
		for (auto& col: firstTable) {
			if (secondTable.count(col.first) != 0) {
				commonHeaders.push_back(col.first);
			}
		}
	} else {
		for (auto& col: secondTable) {
			if (firstTable.count(col.first) != 0) {
				commonHeaders.push_back(col.first);
			}
		}
	}

	return commonHeaders;
}

std::vector <std::string>
QueryUtils::getUniqueHeaders(const Table& firstTable, const Table& secondTable) {
	std::vector <std::string> uniqueHeaders;
	for (const auto& col: firstTable) {
		if (secondTable.count(col.first) == 0) {
			uniqueHeaders.push_back(col.first);
		}
	}

	for (const auto& col: secondTable) {
		if (firstTable.count(col.first) == 0) {
			uniqueHeaders.push_back(col.first);
		}
	}

	return uniqueHeaders;
}

/*
 * Groups the tuples of two tables by the common values. Returns the intermediate data structure before the
 * cross-product of tuples from the tables. The unordered_set<int> represents the set of row numbers from a table after
 * grouping.
 */
QueryUtils::GroupedTable QueryUtils::extractCommonTuples(const std::vector <std::string>& commonHeaders,
														 const Table& firstTable,
														 const Table& secondTable) {
	// grouped tables is pre cross-product (int represent row number)
	QueryUtils::GroupedTable groupedTables;

	auto firstTableNumRows = firstTable.at(commonHeaders.front()).size();
	for (auto i = 0; i < firstTableNumRows; i++) {
		std::string commonTupleVal = selectTupleToString(commonHeaders, i, firstTable);

		if (groupedTables.count(commonTupleVal) != 0) {
			groupedTables[commonTupleVal].first.insert(i);
		} else {
			groupedTables[commonTupleVal] = {{i},
											 {}};
		}
	}

	auto secondTableNumRows = secondTable.at(commonHeaders.front()).size();
	for (auto i = 0; i < secondTableNumRows; i++) {
		std::string commonTupleVal = selectTupleToString(commonHeaders, i, secondTable);
		if (groupedTables.count(commonTupleVal) != 0) {
			groupedTables[commonTupleVal].second.insert(i);
		}
	}

	return groupedTables;
}

/*
 * Returns a string representation of selected values within a tuple. Each value is separated by a single whitespace
 */
std::string
QueryUtils::selectTupleToString(const std::vector <std::string>& headers, size_t rowNum, const Table& table) {
	std::string stringRep;
	for (auto& col: headers) {
		stringRep += table.at(col).at(rowNum);
		if (col != headers.back()) {
			stringRep += " ";
		}
	}

	return stringRep;
}

void
QueryUtils::crossProduct(const std::unordered_set<int>& firstTupleSet, const std::unordered_set<int>& secondTupleSet,
						 std::unordered_set <std::pair<int, int>, pair_hash>& tuplePairings) {
	for (auto firstRowNum: firstTupleSet) {
		for (auto secondRowNum: secondTupleSet) {
			tuplePairings.emplace(firstRowNum, secondRowNum);
		}
	}
}

Table QueryUtils::joinRows(const std::unordered_set <std::pair<int, int>, pair_hash>& tuplePairings,
						   const Table& firstTable, const Table& secondTable,
						   const std::vector <std::string>& commonHeaders) {
	Table joinedTable;
	std::vector<std::string> uniqueHeaders = getUniqueHeaders(firstTable, secondTable);

	for (const auto& pair: tuplePairings) {
		for (const auto& uniqueHeader: uniqueHeaders) {
			if (firstTable.count(uniqueHeader) != 0) {
				joinedTable[uniqueHeader].push_back(firstTable.at(uniqueHeader).at(pair.first));
			} else {
				joinedTable[uniqueHeader].push_back(secondTable.at(uniqueHeader).at(pair.second));
			}
		}

		for (const auto& commonHeader: commonHeaders) {
			// doesn't matter which table because values are common
			joinedTable[commonHeader].push_back(firstTable.at(commonHeader).at(pair.first));
		}
	}

	return joinedTable;
}
