#pragma once

enum class BinaryOperator {
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    MODULO,
};

enum class ComparatorOperator {
    GT,
    GTE,
    LT,
    LTE,
    EQ,
    NEQ
};

enum class ConditionalOperator {
	NONE,
    AND,
    OR,
    NOT,
};