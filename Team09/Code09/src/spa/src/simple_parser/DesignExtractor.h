#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"

#include <memory>
#include <vector>

class DesignExtractor {
public:
	DesignExtractor();

	static void extractDesignElements(AST ast);
	static void commit();
};
