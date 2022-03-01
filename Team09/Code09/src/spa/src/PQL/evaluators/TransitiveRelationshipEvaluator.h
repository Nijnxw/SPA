#pragma once

#include <string>

#include "../../models/RelationRef.h"
#include "../../models/EntityType.h"
#include "../../models/QueryClauseResult.h"

class TransitiveRelationshipEvaluator {
public:
    // virtual and =0 makes this an interface and does not require this method to be defined.
    virtual QueryClauseResult getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
        bool isBooleanResult) = 0;
};