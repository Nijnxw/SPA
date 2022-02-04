#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "pkb/PKB.h"
#include "models/EntityType.h"

#include <memory>
#include <vector>

class DesignExtractor {
public:
	DesignExtractor();

	static bool extractDesignElements(AST ast);
};
