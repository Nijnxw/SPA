#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "AssignStatement.h"
#include "EntityStore.h"
#include "FollowsStore.h"
#include "ParentStore.h"
#include "UsesStore.h"
#include "ModifiesStore.h"

class PKB {
public:
	PKB();

	static void clearAllStores();
};