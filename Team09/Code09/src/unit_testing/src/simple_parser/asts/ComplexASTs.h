#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/WhileNode.h"

#include <memory>
#include <string>
#include <vector>

class ComplexASTs {
private:
	ComplexASTs();
public:
	static AST getAST4_1();
	static int getStmtCount4_1();
};