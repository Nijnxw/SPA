#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "util/PKBUtils.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"

class WithEvaluator {
public:
	WithEvaluator();

	QueryClauseResult
		getWith(const std::string& LHSVal, EntityType LHSEntType, AttributeRef LHSAttrType, const std::string& RHSVal, EntityType RHSEntType, 
			AttributeRef RHSAttrType, bool isBooleanResul);
private:
	QueryClauseResult getWithByStrOrInt(
		const std::string& strOrIntVal, EntityType strOrIntType, const std::string& attrVal, EntityType attrEntType, AttributeRef attrRefType, bool isBooleanResult);
	QueryClauseResult getWithByAttrRef(const std::string& LHSVal, EntityType LHSEntType, AttributeRef LHSAttrType, const std::string& RHSVal, EntityType RHSEntType,
		AttributeRef RHSAttrType, bool isBooleanResult);
	std::unordered_set<std::string> getAttrRefStrSet(EntityType entType, AttributeRef attrType);
	EntityType getAttrRefType(EntityType entType, AttributeRef attrRef);
	std::unordered_set<std::string> getRevMapFromAttr(EntityType entType, std::string attr);

};
