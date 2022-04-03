
#include "QueryResultProjector.h"
#include "util/QueryUtils.h"


std::unordered_set<std::string> QueryResultProjector::formatResult(Table& res, Query& query) {

	if (query.isBooleanQuery()) {
		if (res.empty()) {
			return {"FALSE"};
		}
		return {"TRUE"};
	}

	const std::vector<QueryArgument>& selectSyn = query.getResultSynonyms();
	std::vector<std::string> colHeaders;
	for (const auto& syn: selectSyn) {
		colHeaders.push_back(syn.toString());
	}

	return QueryUtils::stringifyRows(res, colHeaders);
}
