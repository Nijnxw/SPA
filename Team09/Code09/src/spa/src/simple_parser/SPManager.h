#pragma once

#include "SPLexer.h"
#include "DesignExtractor.h"
#include "models/simple_parser/AST.h"
#include "simple_parser/SPParser.h"

#include <iostream>
#include <string>
#include <utility>

class SPManager {
public:
	static inline int stmtCount = 0;
	static AST parseFile(const std::string& filename);
	static void extractDesign(AST ast);
};
