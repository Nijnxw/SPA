#pragma once

class Statement {
protected:
    int statementNumber;

public:
    Statement(int statementNumber);

    int getStatementNumber();
};