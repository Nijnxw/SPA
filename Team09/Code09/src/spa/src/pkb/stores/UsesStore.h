#pragma once

#include "pkb/stores/StmtVarStore.h"
#include "pkb/stores/ProcVarStore.h"

class UsesStore : public StmtVarStore, public ProcVarStore {
public:
	UsesStore();
	void clear();
};
