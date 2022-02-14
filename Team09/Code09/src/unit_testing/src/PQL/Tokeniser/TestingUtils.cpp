#include <vector>
#include "PQL/PQLToken.h"

static bool tokenComparator(PQLToken* t1, PQLToken* t2) {
	return t1->getTokenType() == t2->getTokenType() && t1->getValue() == t2->getValue();
}

static bool compareVectors(const std::vector<PQLToken*> output, const std::vector<PQLToken*> expected) {
	return std::equal(output.begin(), output.end(),
					  expected.begin(), expected.end(),
					  tokenComparator);
}