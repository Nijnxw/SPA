#include "ComplexASTs.h"

ComplexASTs::ComplexASTs() {}

AST ComplexASTs::getAST4_1() {
	/*
     *  procedure testProgram {
     * 1   read x;
     * 2   read y;
     * 3   length = x * x + y * y;
     * 4   t = 30;
     * 5   if ((x >= 0) && (y >= 0)) then {
     * 6     while (x != 0) {
     * 7       tan = y / x;
     * 8       sin = y / length * cos;
     * 9       cos = x / length * sin;
     * 10      if (((sin * sin + cos * cos) == 1) || (!(tan != (sin / cos)))) then {
     * 11        x = y / 2;
     * 12        y = x / 2;
     *         } else {
     * 13        x = 0;
     *         }
     * 14      length = x * x + y * y;
     *       }
     *     } else {
     * 15    x = 10;
     * 16    y = 10;
     * 17    length = x * x + y * y;
     *     }
     * 18  print length;
     *   }
	 */

	//variables
    std::shared_ptr<VariableNode> t = std::make_shared<VariableNode>("t");
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> length = std::make_shared<VariableNode>("length");
    std::shared_ptr<VariableNode> tan = std::make_shared<VariableNode>("tan");
    std::shared_ptr<VariableNode> cos = std::make_shared<VariableNode>("cos");
    std::shared_ptr<VariableNode> sin = std::make_shared<VariableNode>("sin");

    //constants
    std::shared_ptr<ConstantNode> thirty = std::make_shared<ConstantNode>("30");
    std::shared_ptr<ConstantNode> zero = std::make_shared<ConstantNode>("0");
    std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");
    std::shared_ptr<ConstantNode> two = std::make_shared<ConstantNode>("2");
    std::shared_ptr<ConstantNode> ten = std::make_shared<ConstantNode>("10");

    //innermost if - lines 10 to 13

    //if - LHS
    ExprNode sinTimesSin = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, sin, sin);
    ExprNode cosTimesCos = std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, cos, cos);
    RelFactorNode sinTimeSinPlusCosTimesCos = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, sinTimesSin, cosTimesCos);
    std::shared_ptr<RelExprNode> innerIfRelLhs = std::make_shared<RelExprNode>(sinTimeSinPlusCosTimesCos, ComparatorOperator::EQ, one);
    std::shared_ptr<PredicateNode> innerIfLhs = std::make_shared<PredicateNode>(innerIfRelLhs);

    //if - RHS inner NEQ comparison
    RelFactorNode sinDivideCos = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, sin, cos);
    std::shared_ptr<RelExprNode> innerIfRelRhs = std::make_shared<RelExprNode>(tan, ComparatorOperator::NEQ, sinDivideCos);
    std::shared_ptr<PredicateNode> innerInnerIfNeq = std::make_shared<PredicateNode>(innerIfRelRhs);
    std::shared_ptr<PredicateNode> innerIfRhs = std::make_shared<PredicateNode>(ConditionalOperator::NOT, innerInnerIfNeq);

    //if - merged complete predicate
    std::shared_ptr<PredicateNode> innerPred = std::make_shared<PredicateNode>(innerIfLhs, ConditionalOperator::OR, innerIfRhs);

    //then stmt list
    std::vector<std::shared_ptr<StmtNode>> innerIfThenStmtList{
        std::make_shared<AssignNode>(
            11, x, 
            std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, y, two),
            "y 2 /"),
        std::make_shared<AssignNode>(
            12, y,
            std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, x, two),
            "x 2 /"),
    };

    //else stmt list
    std::vector<std::shared_ptr<StmtNode>> innerIfElseStmtList{
        std::make_shared<AssignNode>(13, x, zero, "0")
    };
    
    //inner if construction
    std::shared_ptr<IfNode> innerIf = std::make_shared<IfNode>(10, innerPred, innerIfThenStmtList, innerIfElseStmtList);

    //while node (6 - 14)
    std::shared_ptr<RelExprNode>  whileRel = std::make_shared<RelExprNode>(x, ComparatorOperator::NEQ, zero);
    std::shared_ptr<PredicateNode> whilePred = std::make_shared<PredicateNode>(whileRel);
    std::vector<std::shared_ptr<StmtNode>> whileStmtList{
        std::make_shared<AssignNode>(
            7, tan,
            std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE, y, x),
            "y x /"),
        std::make_shared<AssignNode>(
            8, sin,
            std::make_shared<BinaryOperatorNode>(
                BinaryOperator::DIVIDE, y,
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, length, cos)),
            "y length / cos *"),
        std::make_shared<AssignNode>(
            9, cos,
            std::make_shared<BinaryOperatorNode>(
                BinaryOperator::DIVIDE, x,
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, length, sin)),
            "x length / sin *"),
        innerIf,
        std::make_shared<AssignNode>(
            14, length,
            std::make_shared<BinaryOperatorNode>(
                BinaryOperator::PLUS,
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, x),
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, y, y)),
            "x x * y y * +")
    };

    //outer if
    //predicate
    std::shared_ptr<RelExprNode> outerIfRelLhs = std::make_shared<RelExprNode>(x, ComparatorOperator::GTE, zero);
    std::shared_ptr<PredicateNode> predOuterIfRelLhs = std::make_shared<PredicateNode>(outerIfRelLhs);

    std::shared_ptr<RelExprNode> outerIfRelRhs = std::make_shared<RelExprNode>(y, ComparatorOperator::GTE, zero);
    std::shared_ptr<PredicateNode> predOuterIfRelRhs = std::make_shared<PredicateNode>(outerIfRelLhs);

    std::shared_ptr<PredicateNode> outerIfPred = std::make_shared<PredicateNode>(predOuterIfRelLhs, ConditionalOperator::AND, predOuterIfRelRhs);

    std::vector<std::shared_ptr<StmtNode>> outerIfThenStmtList{
        std::make_shared<WhileNode>(6, whilePred, whileStmtList) //nested while construction
    };

    std::vector<std::shared_ptr<StmtNode>> outerIfElseStmtList{
        std::make_shared<AssignNode>(15, x, ten, "10"),
        std::make_shared<AssignNode>(16, y, ten, "10"),
        std::make_shared<AssignNode>(
            17, length,
            std::make_shared<BinaryOperatorNode>(
                BinaryOperator::PLUS,
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, x),
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, y, y)),
            "x x * y y * +")
    };

    //outer if construction
    std::shared_ptr<IfNode> outerIf = std::make_shared<IfNode>(5, outerIfPred, outerIfThenStmtList, outerIfElseStmtList);

    //construct main program flow
    std::vector<std::shared_ptr<StmtNode>> stmtList{
        std::make_shared<ReadNode>(1, x),
        std::make_shared<ReadNode>(2, y),
        std::make_shared<AssignNode>(
            3, length,
            std::make_shared<BinaryOperatorNode>(
                BinaryOperator::PLUS,
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, x, x),
                std::make_shared<BinaryOperatorNode>(BinaryOperator::TIMES, y, y)),
            "x x * y y * +"),
        std::make_shared<AssignNode>(4, t, thirty, "30"),
        outerIf,
        std::make_shared<PrintNode>(18, length)

    };
    std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
    std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
    return std::make_shared<ProgramNode>(procList);
}