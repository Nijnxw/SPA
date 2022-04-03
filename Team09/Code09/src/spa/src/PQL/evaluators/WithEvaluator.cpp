#include "WithEvaluator.h"

WithEvaluator::WithEvaluator() {}

QueryClauseResult
WithEvaluator::getWith(const std::string& LHSVal, EntityType LHSEntType, AttributeRef LHSAttrType, const std::string& RHSVal, EntityType RHSEntType, AttributeRef RHSAttrType, bool isBooleanResult) {
	if (LHSEntType == EntityType::STRING || LHSEntType == EntityType::INT) {
		return getWithByStrOrInt(LHSVal, LHSEntType, RHSVal, RHSEntType, RHSAttrType, isBooleanResult);
	} else if (RHSEntType == EntityType::STRING || RHSEntType == EntityType::INT) {
		return getWithByStrOrInt(RHSVal, RHSEntType, LHSVal, LHSEntType, LHSAttrType, isBooleanResult);
	} else { // Both Attr Ref
		return getWithByAttrRef(LHSVal, LHSEntType, LHSAttrType, RHSVal, RHSEntType, RHSAttrType, isBooleanResult);
	}
}

QueryClauseResult WithEvaluator::getWithByStrOrInt( // Both String and Int will be passed as Strings from QP
	const std::string& strOrIntVal, EntityType strOrIntType, const std::string& attrVal, EntityType attrEntType, AttributeRef attrRefType, bool isBooleanResult) {
	QueryClauseResult queryResult;
	// Basic comparison if match
	if (strOrIntType == EntityType::STRING && attrEntType == EntityType::STRING
		|| strOrIntType == EntityType::INT && attrEntType == EntityType::INT) {
		queryResult.setBooleanResult(strOrIntVal == attrVal);
	}
	// Integer = Integer-type AttrRef
	else if (strOrIntType == EntityType::INT && getAttrRefType(attrEntType, attrRefType) == EntityType::INT) {
		std::unordered_set<std::string> resultSet;
		if (getAttrRefIntSet(attrEntType, attrRefType).count(std::stoi(strOrIntVal))) {
			resultSet.insert(strOrIntVal);
			queryResult.addColumn(attrVal, resultSet);
		}
	}
	// String = String-type AttrRef
	else if (strOrIntType == EntityType::STRING && getAttrRefType(attrEntType, attrRefType) == EntityType::STRING) {
		if (getAttrRefStrSet(attrEntType, attrRefType).count(strOrIntVal)) {
			queryResult.addColumn(attrVal, getRevMapFromAttr(attrEntType, strOrIntVal));
		}
	}
	return queryResult;
}

QueryClauseResult WithEvaluator::getWithByAttrRef(const std::string& LHSVal, EntityType LHSEntType, AttributeRef LHSAttrType, const std::string& RHSVal, EntityType RHSEntType, 
	AttributeRef RHSAttrType, bool isBooleanResult) {

	QueryClauseResult queryResult;
	if (getAttrRefType(LHSEntType, LHSAttrType) != getAttrRefType(RHSEntType, RHSAttrType)) {
		return queryResult;
	} else if (getAttrRefType(LHSEntType, LHSAttrType) == EntityType::INT) {
		std::vector<int> resSet;
		if (LHSEntType == RHSEntType) {
			resSet = PKBUtils::convertUnorderedSetToVector(getAttrRefIntSet(LHSEntType, LHSAttrType));
		} else {
			resSet = PKBUtils::convertUnorderedSetToVector(PKBUtils::unorderedSetIntersection(
				getAttrRefIntSet(LHSEntType, LHSAttrType), getAttrRefIntSet(RHSEntType, RHSAttrType), isBooleanResult));
		}
		if (!resSet.empty()) {
			queryResult.addColumn(LHSVal, resSet);
			queryResult.addColumn(RHSVal, resSet);
		}
	} else if (getAttrRefType(LHSEntType, LHSAttrType) == EntityType::STRING) {
		std::vector<std::string> LHSResSet;
		std::vector<std::string> RHSResSet;
		std::unordered_set<std::string> commonStrs;
		if (LHSEntType == RHSEntType) {
			std::unordered_set<std::string> commonStrs = getAttrRefStrSet(LHSEntType, LHSAttrType);
			for (const auto& str : commonStrs) {
				std::vector<std::string> vec = PKBUtils::convertUnorderedSetToVector(getRevMapFromAttr(LHSEntType, str));
				std::tuple<std::vector<std::string>, std::vector<std::string>> crossedVec = PKBUtils::computeCartesianProduct(vec, vec, isBooleanResult);
				LHSResSet.insert(LHSResSet.end(), std::get<0>(crossedVec).begin(), std::get<0>(crossedVec).end());
				RHSResSet.insert(RHSResSet.end(), std::get<1>(crossedVec).begin(), std::get<1>(crossedVec).end());
			}
		} else {
			const std::unordered_set<std::string>& commonStrs = PKBUtils::unorderedSetIntersection(
				getAttrRefStrSet(LHSEntType, LHSAttrType),
				getAttrRefStrSet(RHSEntType, RHSAttrType));
			for (const auto& str : commonStrs) {
				std::vector<std::string> LHSvec = PKBUtils::convertUnorderedSetToVector(getRevMapFromAttr(LHSEntType, str));
				std::vector<std::string> RHSvec = PKBUtils::convertUnorderedSetToVector(getRevMapFromAttr(RHSEntType, str));
				std::tuple<std::vector<std::string>, std::vector<std::string>> crossedVec = PKBUtils::computeCartesianProduct(LHSvec, RHSvec, isBooleanResult);
				LHSResSet.insert(LHSResSet.end(), std::get<0>(crossedVec).begin(), std::get<0>(crossedVec).end());
				RHSResSet.insert(RHSResSet.end(), std::get<1>(crossedVec).begin(), std::get<1>(crossedVec).end());
			}
		}
		if (!LHSResSet.empty()) {
			queryResult.addColumn(LHSVal, LHSResSet);
		}
		if (!RHSResSet.empty()) {
			queryResult.addColumn(RHSVal, RHSResSet);
		}
	}
	return queryResult;
}

std::unordered_set<int> WithEvaluator::getAttrRefIntSet(EntityType RHSType, AttributeRef RHSAttr) {
	if (RHSType == EntityType::CONST && RHSAttr == AttributeRef::VALUE) {
		const std::unordered_set<std::string>& constantStrs = PKB::getConstants();
		std::unordered_set<int> constants;
		for (const auto& constantStr : constantStrs) {
			constants.insert(std::stoi(constantStr));
		}
		return constants;
	} else if (RHSAttr == AttributeRef::STMT_NO) {
		return PKB::getStatementsWithType(RHSType);
	}
	return {};
}

std::unordered_set<std::string> WithEvaluator::getAttrRefStrSet(EntityType entType, AttributeRef attrRef) {
	if (attrRef == AttributeRef::PROC_NAME) {
		if (entType == EntityType::PROC) {
			return PKB::getProcedures();
		} else if (entType == EntityType::CALL) {
			return PKB::getAllCallees();
		}
	} else if (attrRef == AttributeRef::VAR_NAME) {
		if (entType == EntityType::VAR) {
			return PKB::getVariables();
		} else if (entType == EntityType::READ) {
			return PKB::getReadVariables();
		} else if (entType == EntityType::PRINT) {
			return PKB::getPrintVariables();
		}
	}
	return {};
}

EntityType WithEvaluator::getAttrRefType(EntityType entType, AttributeRef attrRef) {
	if (entType == EntityType::PROC && attrRef == AttributeRef::PROC_NAME || entType == EntityType::CALL && attrRef == AttributeRef::PROC_NAME
		|| entType == EntityType::VAR && attrRef == AttributeRef::VAR_NAME || entType == EntityType::READ && attrRef == AttributeRef::VAR_NAME
		|| entType == EntityType::PRINT && attrRef == AttributeRef::VAR_NAME
		) {
		return EntityType::STRING;
	} else if (entType == EntityType::STMT && attrRef == AttributeRef::STMT_NO ||
			   entType == EntityType::CONST && attrRef == AttributeRef::VALUE
			   || entType == EntityType::READ && attrRef == AttributeRef::STMT_NO ||
			   entType == EntityType::PRINT && attrRef == AttributeRef::STMT_NO
			   || entType == EntityType::CALL && attrRef == AttributeRef::STMT_NO ||
			   entType == EntityType::WHILE && attrRef == AttributeRef::STMT_NO
			   || entType == EntityType::IF && attrRef == AttributeRef::STMT_NO ||
			   entType == EntityType::ASSIGN && attrRef == AttributeRef::STMT_NO
		) {
		return EntityType::INT;
	}
	return EntityType::INVALID;
}

std::unordered_set<std::string> WithEvaluator::getRevMapFromAttr(EntityType entType, std::string attr) {
	if (entType == EntityType::CALL && PKB::getProceduresToCallStatements().count(attr)) {
		return PKB::getProceduresToCallStatements().at(attr);
	} else if (entType == EntityType::READ && PKB::getVariablesToReadStatements().count(attr)) {
		return PKB::getVariablesToReadStatements().at(attr);
	} else if (entType == EntityType::PRINT && PKB::getVariablesToPrintStatements().count(attr)) {
		return PKB::getVariablesToPrintStatements().at(attr);
	}
	return {attr};
}
