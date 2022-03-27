#pragma once

enum class AttributeRef {
	STMT_NO,
	PROC_NAME,
	VAR_NAME,
	VALUE,
	NONE
};

inline const char* ToString(AttributeRef ref) {
	switch (ref) {
		case AttributeRef::STMT_NO:
			return ".stmt#";
		case AttributeRef::PROC_NAME:
			return ".procName";
		case AttributeRef::VAR_NAME:
			return ".varName";
		case AttributeRef::VALUE:
			return ".value";
		default:
			return "";
	}
}
