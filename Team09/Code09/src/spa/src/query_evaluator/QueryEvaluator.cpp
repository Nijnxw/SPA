#include <unordered_set>
#include "QueryEvaluator.h"

std::unordered_map<std::string, std::vector<std::string>> QueryEvaluator::evaluate(Query& query) {
    std::vector<std::unordered_map<std::string, std::vector<std::string>>> clauseResults;
    const std::vector<QueryArgument>& resultSynonyms = query.getResultSynonyms();
    std::unordered_set<QueryArgument> unusedSynonyms(resultSynonyms.begin(), resultSynonyms.end());

    for (const auto& stc: query.getSuchThatClauses()) {
        // get clause handler function to evaluate individual clause

        for (const auto& arg: stc.getArguments()) {
            unusedSynonyms.erase(arg);
        }
    }

    for (const auto& pc: query.getPatternClauses()) {
        // get pattern handler function to evaluate clause

        for (const auto& arg: pc.getArguments()) {
            unusedSynonyms.erase(arg);
        }
    }

    std::unordered_map<std::string, std::vector<std::string>> dummyReturn;
    return dummyReturn;
}
