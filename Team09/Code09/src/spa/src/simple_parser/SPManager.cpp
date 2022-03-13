#include "SPManager.h"

AST SPManager::parseFile(const std::string& filename) {
	try {
		std::ifstream inputStream(filename);
		if (!inputStream.is_open()) {
			throw std::runtime_error("File do not exist!\n");
		}

		Lexer lexer = Lexer(&inputStream);
		std::vector<SPToken*> tokens = lexer.tokenize();

		SPParser parser = SPParser(tokens);
		AST ast = parser.parseProgram();

		stmtCount = parser.getStmtCount();

		return ast;
	} catch (const std::exception& e) {
		std::cout << e.what();
		exit(EXIT_FAILURE);
	}
}

void SPManager::extractDesign(AST ast) {
	DesignExtractor::extractDesignElements(std::move(ast), stmtCount);
	DesignExtractor::commit();
}
