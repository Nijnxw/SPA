#pragma once

#include "models/QueryClause.h"

/*
 * A wrapper class for the QueryClause class, each OptimizerClause represents an
 * edge between 2 synonyms in the adjacency list of the OptimizerGraph object.
 */
class OptimizerClause {
public:
	OptimizerClause() = default;
	OptimizerClause(const std::string& from, const std::string& to, int weight, const QueryClause& clause);

	std::string getFrom() const;
	std::string getTo() const;
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
	size_t operator()(const OptimizerClause& clause) const {
		return std::hash<QueryClause>()(clause.getClause());
	}
};
