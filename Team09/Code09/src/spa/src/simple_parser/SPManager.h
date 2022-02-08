#pragma once

#include <string>
#include "models/simple_parser/AST.h"

class SPManager {
public:
	static AST parseFile(std::string filename);
	static void extractDesign(AST ast);
};
