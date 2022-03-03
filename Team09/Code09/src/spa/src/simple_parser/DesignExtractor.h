#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/CallNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/WhileNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/NestableRelationships.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class DesignExtractor {
private:
	static inline std::unordered_map<std::string, NestableRelationships> procCache;

public:
	DesignExtractor();
	static bool isCached(std::string procName);
	static NestableRelationships retrieve(std::string procName);
	static void cache(std::string procName, NestableRelationships rs);

	static void extractDesignElements(AST ast);
	static void commit();
};
