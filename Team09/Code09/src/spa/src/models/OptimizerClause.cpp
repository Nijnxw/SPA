#include "OptimizerClause.h"

OptimizerClause::OptimizerClause(const std::string& from, const std::string& to, int weight, QueryClause& clause)
	: from(
	from), to(to), weight(weight), clause(clause) {}

std::string OptimizerClause::getFrom() {
	return from;
}

std::string OptimizerClause::getTo() {
	return to;
}

int OptimizerClause::getWeight() const {
	return weight;
}

QueryClause OptimizerClause::getClause() const {
	return clause;
}

bool OptimizerClause::operator<(const OptimizerClause& other) const {
	return weight < other.weight;
}

bool OptimizerClause::operator==(const OptimizerClause& other) const {
	return clause == other.clause && weight == other.weight;
}
