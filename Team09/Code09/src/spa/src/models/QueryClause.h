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

private:
	RelationRef clauseType;
	std::string clauseSynonym;
	std::vector<QueryArgument> arguments;
	std::unordered_set<std::string> usedSynonyms;
};
