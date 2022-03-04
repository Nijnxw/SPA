#pragma once

#include "pkb/stores/StmtVarStore.h"
#include "pkb/stores/ProcVarStore.h"

class ModifiesStore : public StmtVarStore, public ProcVarStore {
public:
	ModifiesStore();
	void clear();
};
