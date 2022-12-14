#pragma once

#include <string>

#include "../../models/EntityType.h"
#include "../../models/QueryClauseResult.h"

class PatternEvaluator {
public:
    // virtual and =0 makes this an interface and does not require this method to be defined.
    virtual QueryClauseResult getPattern(const std::string& LHS, const std::string& RHS, const std::string& clauseSyn, EntityType LHSType, EntityType RHSType,
        bool isBooleanResult) = 0;
};