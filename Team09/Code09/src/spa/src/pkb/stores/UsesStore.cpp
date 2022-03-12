#include "UsesStore.h"

UsesStore::UsesStore()
	: StmtVarStore(), ProcVarStore() {}

void UsesStore::clear() {
	stmtInRelationship.clear();
	varInRelationship.clear();
	procInRelationship.clear();
	stmtToVarRelationship.clear();
	varToStmtRelationship.clear();
	procToVarRelationship.clear();
	varToProcRelationship.clear();
}