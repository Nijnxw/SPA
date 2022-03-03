#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../models/EntityType.h"
#include "../../models/QueryClauseResult.h"
#include "../util/PKBUtil.cpp"

class Store {
public:
    // virtual and =0 makes this an interface and does not require this method to be defined.
    virtual void clear() = 0;
};