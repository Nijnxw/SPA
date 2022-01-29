#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "models/AssignStatement.h"
#include "stores/EntityStore.h"
#include "stores/FollowsStore.h"
#include "stores/ParentStore.h"
#include "stores/UsesStore.h"
#include "stores/ModifiesStore.h"

class PKB {
public:
	PKB();

	static void clearAllStores();
};