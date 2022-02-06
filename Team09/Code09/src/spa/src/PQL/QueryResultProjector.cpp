
#include "QueryResultProjector.h"
#include "util/QueryUtils.h"

std::list<std::string> QueryResultProjector::formatResult(Table& res, std::vector<QueryArgument>& selectSyn) {
	std::vector<std::string> colHeaders;
	for (const auto& syn: selectSyn) {
		colHeaders.push_back(syn.getValue());
	}

	return QueryUtils::stringifyRows(res, colHeaders);
}
