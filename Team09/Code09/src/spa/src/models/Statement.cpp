#include "Statement.h"

Statement::Statement(int statementNumber)
	: statementNumber(statementNumber) {}

int Statement::getStatementNumber() {
	return statementNumber;
}
