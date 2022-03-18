#pragma once

#include "pkb/stores/Store.h"

template <typename T> class StmtProcTemplateStore : public Store {
private:
	std::unordered_map<T, std::unordered_set<T>> firstSynonymToSecondSynonyms;
	std::unordered_map<T, std::unordered_set<T>> secondSynonymToFirstSynonyms;
	std::unordered_set<std::pair<T, T>, PKBUtils::pairHashFunction> relationshipPairs;
	std::unordered_set<std::pair<T, T>, PKBUtils::pairHashFunction> relationshipTPairs;
	std::unordered_map<T, std::unordered_set<T>> firstSynonymToSecondSynonymsT;
	std::unordered_map<T, std::unordered_set<T>> secondSynonymToFirstSynonymsT;
public:
	void clear();

	/* Setters called by SP and DE */
	bool addRelationship(T firstSynonym, T secondSynonym);
	bool addRelationshipT(T firstSynonym, T secondSynonym);

	/* Getters called by QE */
	bool hasRelationship();
	bool hasTRelationship();

	bool isRelationship(T firstSynonym, T secondSynonym);
	bool isTRelationship(T firstSynonym, T secondSynonym);
	bool isFirstSynonym(T firstSynonym);
	bool isSecondSynonym(T secondSynonym);
	bool isFirstSynonymT(T firstSynonym);
	bool isSecondSynonymT(T secondSynonym);

	std::unordered_set<T> getFirstSynonyms(T secondSynonym);
	std::unordered_set<T> getSecondSynonyms(T firstSynonym);
	std::unordered_set<T> getAllFirstSynonyms();
	std::unordered_set<T> getAllSecondSynonyms();

	std::unordered_set<T> getFirstSynonymsT(T secondSynonym);
	std::unordered_set<T> getSecondSynonymsT(T firstSynonym);
	std::unordered_set<T> getAllFirstSynonymsT();
	std::unordered_set<T> getAllSecondSynonymsT();

	std::tuple<std::vector<T>, std::vector<T>> getAllRelationshipPairs();
	std::tuple<std::vector<T>, std::vector<T>> getAllRelationshipTPairs();
};