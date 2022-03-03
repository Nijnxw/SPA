#pragma once

#include "pkb/stores/StmtProcTemplateStore.h"

class ProcProcStore : public StmtProcTemplateStore<std::string> {
public:
	ProcProcStore();
};