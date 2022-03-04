#include "StmtProcTemplateStore.h"

template <typename T>
void StmtProcTemplateStore<T>::clear() {
	firstSynonymToSecondSynonyms.clear();
	secondSynonymToFirstSynonym.clear();
	relationshipPairs.clear();
	relationshipTPairs.clear();
	firstSynonymToSecondSynonymsT.clear();
	secondSynonymToFirstSynonymsT.clear();
}

template <typename T>
bool StmtProcTemplateStore<T>::addRelationship(T firstSynonym, T secondSynonym) {
	std::pair<T, T> pair;
	pair = std::make_pair(firstSynonym, secondSynonym);
	return relationshipPairs.insert(pair).second && PKBUtil::addToMapWithSet(firstSynonymToSecondSynonyms, firstSynonym, secondSynonym)
		&& secondSynonymToFirstSynonym.insert({ secondSynonym, firstSynonym }).second;
}

template <typename T>
bool StmtProcTemplateStore<T>::addRelationshipT(T firstSynonym, T secondSynonym) {
	std::pair<T, T> pair;
	pair = std::make_pair(firstSynonym, secondSynonym);
	return relationshipTPairs.insert(pair).second && PKBUtil::addToMapWithSet(firstSynonymToSecondSynonymsT, firstSynonym, secondSynonym)
		&& PKBUtil::addToMapWithSet(secondSynonymToFirstSynonymsT, secondSynonym, firstSynonym);
}

template <typename T>
bool StmtProcTemplateStore<T>::hasRelationship() {
	return firstSynonymToSecondSynonyms.size() > 0;
}

template <typename T>
bool StmtProcTemplateStore<T>::hasTRelationship() {
	return firstSynonymToSecondSynonymsT.size() > 0;
}

template <typename T>
bool StmtProcTemplateStore<T>::isRelationship(T firstSynonym, T secondSynonym) {
	if (firstSynonymToSecondSynonyms.count(firstSynonym) <= 0) {
		return false;
	}
	std::unordered_set<T> secondSynonyms = firstSynonymToSecondSynonyms[firstSynonym];
	return secondSynonyms.count(secondSynonym) > 0;
}

template <typename T>
bool StmtProcTemplateStore<T>::isTRelationship(T firstSynonym, T secondSynonym) {
	if (firstSynonymToSecondSynonymsT.count(firstSynonym) <= 0) {
		return false;
	}
	std::unordered_set<T> secondSynonyms = firstSynonymToSecondSynonymsT[firstSynonym];
	return secondSynonyms.count(secondSynonym) > 0;
}

template <typename T>
bool StmtProcTemplateStore<T>::isFirstSynonym(T firstSynonym) {
	return firstSynonymToSecondSynonyms.count(firstSynonym) > 0;
}

template <typename T>
bool StmtProcTemplateStore<T>::isSecondSynonym(T secondSynonym) {
	return secondSynonymToFirstSynonym.count(secondSynonym) > 0;
}

template <typename T>
bool StmtProcTemplateStore<T>::isFirstSynonymT(T firstSynonym) {
	return firstSynonymToSecondSynonymsT.count(firstSynonym) > 0;
}

template <typename T>
bool StmtProcTemplateStore<T>::isSecondSynonymT(T secondSynonym) {
	return secondSynonymToFirstSynonymsT.count(secondSynonym) > 0;
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getFirstSynonyms(T secondSynonym) {
	std::unordered_set<T> result;
	if (secondSynonymToFirstSynonym.count(secondSynonym) <= 0) {
		return result;
	}

	result.insert(secondSynonymToFirstSynonym[secondSynonym]);
	return result;
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getSecondSynonyms(T firstSynonym) {
	std::unordered_set<T> result;
	if (firstSynonymToSecondSynonyms.count(firstSynonym) <= 0) {
		return result;
	}

	return firstSynonymToSecondSynonyms[firstSynonym];
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getAllFirstSynonyms() {
	return PKBUtil::getKeySetFromMap(firstSynonymToSecondSynonyms);
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getAllSecondSynonyms() {
	return PKBUtil::getKeySetFromMap(secondSynonymToFirstSynonym);
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getFirstSynonymsT(T secondSynonym) {
	std::unordered_set<T> result;
	if (secondSynonymToFirstSynonymsT.count(secondSynonym) <= 0) {
		return result;
	}

	return secondSynonymToFirstSynonymsT[secondSynonym];
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getSecondSynonymsT(T firstSynonym) {
	std::unordered_set<T> result;
	if (firstSynonymToSecondSynonymsT.count(firstSynonym) <= 0) {
		return result;
	}

	return firstSynonymToSecondSynonymsT[firstSynonym];
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getAllFirstSynonymsT() {
	return PKBUtil::getKeySetFromMap(firstSynonymToSecondSynonymsT);
}

template <typename T>
std::unordered_set<T> StmtProcTemplateStore<T>::getAllSecondSynonymsT() {
	return PKBUtil::getKeySetFromMap(secondSynonymToFirstSynonymsT);
}

template <typename T>
std::tuple<std::vector<T>, std::vector<T>> StmtProcTemplateStore<T>::getAllRelationshipPairs() {
	return PKBUtil::convertSetPairsToVectorTuple(relationshipPairs);
}

template <typename T>
std::tuple<std::vector<T>, std::vector<T>> StmtProcTemplateStore<T>::getAllRelationshipTPairs() {
	return PKBUtil::convertSetPairsToVectorTuple(relationshipTPairs);
}

template class StmtProcTemplateStore<int>;
template class StmtProcTemplateStore<std::string>;