#include "DesignExtractor.h"
#include "Lexer.h"
#include "Parser.h"
#include "SPManager.h"

#include <utility>

AST SPManager::parseFile(std::string filename) {
	std::ifstream inputStream(filename);
	if (!inputStream.is_open()) {
		throw std::runtime_error("File do not exist!\n");
	}

	Lexer lexer = Lexer(&inputStream);
	std::vector<Token*> tokens = lexer.tokenize();

	Parser parser = Parser(tokens);
	AST ast = parser.parseProgram();

	return ast;
}

void SPManager::extractDesign(AST ast) {
	DesignExtractor::extractDesignElements(std::move(ast));
	DesignExtractor::commit();
}
