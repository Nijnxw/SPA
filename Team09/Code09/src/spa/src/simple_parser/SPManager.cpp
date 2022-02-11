#include "DesignExtractor.h"
#include "Lexer.h"
#include "simple_parser/SPParser.h"
#include "SPManager.h"

#include <utility>

AST SPManager::parseFile(const std::string& filename) {
	std::ifstream inputStream(filename);
	if (!inputStream.is_open()) {
		throw std::runtime_error("File do not exist!\n");
	}

	Lexer lexer = Lexer(&inputStream);
	std::vector<Token*> tokens = lexer.tokenize();

	SPParser parser = SPParser(tokens);
	AST ast = parser.parseProgram();

	return ast;
}

void SPManager::extractDesign(AST ast) {
	DesignExtractor::extractDesignElements(std::move(ast));
	DesignExtractor::commit();
}
