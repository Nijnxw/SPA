#pragma once

enum class RelationRef {
	MODIFIES,
	USES,
	PARENT,
	PARENT_T,
	FOLLOWS,
	FOLLOWS_T,
	PATTERN_A
};

inline const char* ToString(RelationRef ref) {
	switch (ref) {
		case RelationRef::MODIFIES:
			return "Modifies";
		case RelationRef::USES:
			return "Uses";
		case RelationRef::PARENT:
			return "Parent";
		case RelationRef::PARENT_T:
			return "Parent*";
		case RelationRef::FOLLOWS:
			return "Follows";
		case RelationRef::FOLLOWS_T:
			return "Follows*";
		case RelationRef::PATTERN_A:
			return "PatternA";
		default:
			return "";
	}
}
