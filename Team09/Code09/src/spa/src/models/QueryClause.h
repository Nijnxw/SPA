#pragma once

#include <vector>
#include <unordered_set>
#include "EntityType.h"
#include "QueryArgument.h"
#include "RelationRef.h"

class QueryClause {
public:
	QueryClause(RelationRef clauseType, std::vector<QueryArgument>& arguments,
				std::unordered_set<std::string>& usedSynonyms, const std::string& clauseSynonym = "");

	RelationRef getClauseType() const;
	const std::string& getClauseSynonym() const;
	const std::vector<QueryArgument>& getArguments() const;
	const std::unordered_set<std::string>& getUsedSynonyms() const;
	bool containsSynonym(QueryArgument& synonym) const;
	bool containsCommonSynonym(QueryClause& other) const;
	bool operator==(const QueryClause& other) const;

private:
	RelationRef clauseType;
	std::string clauseSynonym;
	std::vector<QueryArgument> arguments;
	std::unordered_set<std::string> usedSynonyms;
};

template<>
struct std::hash<QueryClause> {
	size_t operator()(const QueryClause& clause) {
		size_t hash = std::hash<std::string>()(ToString(clause.getClauseType()));
		for (const auto& arg: clause.getArguments()) {
			hash = hash ^ std::hash<std::string>()(arg.getValue());
		}
		return hash;
	}
};
