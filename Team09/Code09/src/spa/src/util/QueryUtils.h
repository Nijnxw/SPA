#pragma once

#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include "models/QueryClauseResult.h"

struct PairHash {
	template<class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

class QueryUtils {
	typedef std::unordered_map<std::string, std::pair<std::unordered_set<int>, std::unordered_set<int>>> GroupedTable;

public:
	static Table hashJoin(const Table& firstResult, const Table& secondResult);
	static Table crossProduct(const Table& firstResult, const Table& secondResult);

	static std::unordered_set<std::string> stringifyRows(const Table& table, const std::vector<std::string>& colOrder);
	// always order the headers in ascending order before converting each row value to space separated string
	static std::unordered_set<std::string> stringifyRows(const Table& table);

private:
	static std::unordered_set<std::string> getCommonHeaders(const Table& firstTable, const Table& secondTable);
	static Table initialiseTable(const Table& firstTable, const Table& secondTable);

	static std::string
	selectTupleToString(const std::unordered_set<std::string>& headers, size_t rowNum, const Table& table);
	static void
	hashJoinHelper(const std::unordered_set<std::string>& commonTableHeaders, const Table& firstTable,
				   size_t numFirstTableRows, const Table& secondTable, size_t numSecondTableRows, Table& resultTable);
};
