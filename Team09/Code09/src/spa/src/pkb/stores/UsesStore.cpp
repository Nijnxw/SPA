#include "UsesStore.h"

std::unordered_set<int> usesStatements;
std::unordered_set<std::string> usedVariables;
std::unordered_map<int, std::unordered_set<std::string>> statementNumberToVariablesUsed;
std::unordered_map<std::string, std::unordered_set<int>> variableToStatementNumbersUsedBy;
std::unordered_map<std::string, std::unordered_set<std::string>> procedureToVariablesUsed;
std::unordered_map<std::string, std::unordered_set<std::string>> variableToProceduresUsedBy;

UsesStore::UsesStore() {}

void UsesStore::clear() {
	usesStatements.clear();
	usedVariables.clear();
	statementNumberToVariablesUsed.clear();
	variableToStatementNumbersUsedBy.clear();
	procedureToVariablesUsed.clear();
	variableToProceduresUsedBy.clear();
}

// ============ STORE METHODS ==============
bool UsesStore::addUsesStatement(int statementNumber, StatementType statementType, std::unordered_set<std::string> variables) {
	//Populates the modifiedVariables, modifiesStatements, usesStatements, usedVariables using keyset of variableToStatementNumbersUsedBy, statementNumberToVariablesUsed, statementNumberToVariablesModifiedand variableToStatementNumbersModifiedBy
	return true; // TODO: Implement functionality.
}

bool UsesStore::addUsesProcedure(std::string procedure, StatementType statementType, std::unordered_set<std::string> variables) {
	return true; // TODO: Implement functionality.
}

// ============ GETTER METHOD ==============
bool UsesStore::getUsesBoolean(std::string LHS, std::string RHS) {
	// Procedure name has to start with a letter
	if (isalpha(LHS.at(0))) {
		// e.g. Uses("cs3203", "x")
		return getVariablesUsedByProcedure(LHS).count(RHS);
	}
	else {
		// e.g. Uses("9", "x")
		return getVariablesUsedByStatement(std::stoi(LHS)).count(RHS);
	}
}

QueryResultTable UsesStore::getUses(std::string LHS, std::string RHS, UsesLHSTypeEnum LHSType, UsesRHSTypeEnum RHSType, SelectEnum select) {
	// Different evaluation for different input types. Possible design consideration point, instead of leaving the generation of the result set 
	// to the evaluator, by putting the logic to the PKB, we decrease the coupling, changes to the PKB data structure for example will not require
	// a change to the evaluator. Also, this moving the logic to the PKB would decrease the complexity of the QE to focus on more important aspects
	// such as the combining of multiple clauses and optimisation. Drawback is the additional logic and typing needed in the PKB and also additional
	// user requirements would require a change in the PKB to support additional Uses usage. Alternative would be a PKB with a lot of exposed APIs.

	if (RHSType == VARIABLE_NAME) {
		return getUsesByVariable(LHS, RHS, LHSType);
	}
	else if (RHSType == SYNONYM_VARIABLE) {
		return getUsesBySynonym(LHS, RHS, LHSType, select);
	}
}
// ============ HELPER METHODS ==============
QueryResultTable UsesStore::getUsesByVariable(std::string LHS, std::string RHS, UsesLHSTypeEnum LHSType) {
	QueryResultTable queryResult;
	
	// Uses(_, "x")
	switch(LHSType) {
	case SYNONYM_STMT: {
			// stmt s; Uses(s, "x")
			queryResult.addColumn(LHS, getStatementsUsingVariable(RHS));
			break;
		}
		case SYNONYM_ASSIGN: {
			std::unordered_set<std::string> resultSet;
			/*
			std::unordered_set<std::string> assignStmts(getAssignStatements());
			std::unordered_set<int> stmtUsingVar(getStatementsUsingVariable(RHS));
			
			for (auto i = a.begin(); i != a.end(); i++) {
				if (b.find(*i) != b.end()) c.insert(*i);
			}

			for (const auto& elem : s) {
				if ()
			}
			*/
			queryResult.addColumn(LHS, resultSet);
			break;
		}
		case SYNONYM_PRINT:
			break;

		case SYNONYM_CALL:
			break;

		case SYNONYM_IF:
			break;

		case SYNONYM_WHILE:
			break;
	}
		return result;
}

QueryResultTable UsesStore::getUsesBySynonym(std::string LHS, std::string RHS, UsesLHSTypeEnum LHSType, SelectEnum select) {

}


std::unordered_set<std::string> getVariablesUsedByStatement(int stmtNo) {
	return statementNumberToVariablesUsed.at(stmtNo);
}

std::unordered_set<std::string> getVariablesUsedByProcedure(std::string procName) {
	return procedureToVariablesUsed.at(procName);
}

std::unordered_set<int> getStatementsUsingVariable(std::string variable) {
	return variableToStatementNumbersUsedBy.at(variable);
}

//TODO: update h file with methods, helper methods should be private
//TODO: add error handling
//TODO: Consider passing references to avoid creating strings