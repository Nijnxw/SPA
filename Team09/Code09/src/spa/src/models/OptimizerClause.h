#pragma once

#include "QueryClause.h"

/*
 * A wrapper class for the QueryClause class, each OptimizerClause represents an
 * edge between 2 synonyms in the adjacency list of the OptimizerQuery object.
 */
class OptimizerClause {
public:
	OptimizerClause(const std::string& from, const std::string& to, int weight, QueryClause& clause);

	std::string getFrom();
	std::string getTo();
	int getWeight() const;
	QueryClause getClause() const;
	bool operator<(const OptimizerClause& other) const;
	bool operator==(const OptimizerClause& other) const;

private:
	std::string from;
	std::string to;
	int weight;
	QueryClause clause;
};

template<>
struct std::hash<OptimizerClause> {
	size_t operator()(const OptimizerClause& clause) {
		return std::hash<QueryClause>()(clause.getClause());
	}
};
