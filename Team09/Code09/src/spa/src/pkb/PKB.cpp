#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <PKB.h>

PKB::PKB() {}

void PKB::clearAllStores() {
	EntityStore::clear();
	FollowsStore::clear();
	ParentStore::clear();
	UsesStore::clear();
	ModifiesStore::clear();
}
