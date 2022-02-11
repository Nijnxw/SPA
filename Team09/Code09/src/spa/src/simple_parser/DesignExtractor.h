#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/WhileNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignRelationships.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

class DesignExtractor {
public:
	DesignExtractor();

	static void extractDesignElements(AST ast);
	static void commit();
};
