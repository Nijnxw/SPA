#include "QueryClause.h"

QueryClause::QueryClause(RelationRef clauseType, std::vector<QueryArgument>& arguments,
						 std::unordered_set<std::string>& usedSynonyms, const std::string& clauseSynonym) : clauseType(
	clauseType), arguments(arguments), usedSynonyms(usedSynonyms), clauseSynonym(clauseSynonym) {}

RelationRef QueryClause::getClauseType() const {
	return clauseType;
}

const std::string& QueryClause::getClauseSynonym() const {
	return clauseSynonym;
}

const std::vector<QueryArgument>& QueryClause::getArguments() const {
	return arguments;
}

const std::unordered_set<std::string>& QueryClause::getUsedSynonyms() const {
	return usedSynonyms;
}

bool QueryClause::operator==(const QueryClause& other) const {
	bool isRelationRefEqual = clauseType == other.getClauseType();
	bool isclauseSynonymEqual = clauseSynonym == other.getClauseSynonym();
	bool isArgumentsEqual = arguments == other.arguments;
	bool isUsedSynonymsEqual = usedSynonyms == other.usedSynonyms;
	return isRelationRefEqual && isclauseSynonymEqual && isArgumentsEqual && isUsedSynonymsEqual;
}

bool QueryClause::containsCommonSynonym(QueryClause& other) const {
	for (const auto& syn: other.usedSynonyms) {
		if (usedSynonyms.count(syn) > 0) {
			return true;
		}
	}
	return false;
}

bool QueryClause::containsSynonym(QueryArgument& synonym) const {
	return usedSynonyms.count(synonym.getValue()) > 0;
}
