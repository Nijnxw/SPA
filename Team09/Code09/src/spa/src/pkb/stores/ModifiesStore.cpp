#include "ModifiesStore.h"

ModifiesStore::ModifiesStore()
	: StmtVarStore(), ProcVarStore() {}

void ModifiesStore::clear() {
	stmtInRelationship.clear();
	varInRelationship.clear();
	procInRelationship.clear();
	stmtToVarRelationship.clear();
	varToStmtRelationship.clear();
	procToVarRelationship.clear();
	varToProcRelationship.clear();
}