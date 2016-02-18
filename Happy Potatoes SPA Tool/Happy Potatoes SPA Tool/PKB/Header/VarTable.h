#pragma once

#include <map>
#include <iostream>
#include<vector>

using namespace std;

class Modifies;
class Uses;

class VarTable
{
public:
	~VarTable();

	static vector<string> findVariableLeft(int stmtLine1, int stmtLine2);

	static vector<string> findVariableRight(int stmtLine1, int stmtLine2);

	// get ModifiesTable
	static std::vector<int> getModifiesTable(string varName);

	// add ModifiesTable
	static void addDataToModifies(string varName, int stmtLine);

	// add ModifiesProcTable
	static void addModifiesProcTable(string varName, string procedure);

	static bool isModifiesBoolean(string firstPerimeter, string secondPerimeter);
	static vector<string> getModifiesPV(string firstPerimeter);
	static vector<string> getModifiesVariable(string firstPerimeter);
	static vector<string> getModifiesProc(string firstPerimeter);
	static vector<int> getModifiesStmt(string firstPerimeter);
	static vector<int> getModifiesAssg(string firstPerimeter);

	//---------------------------- Uses -------------------------

	// is Uses -> return Boolean
	static bool isUsesBoolean(string stmt1, string stmt2);

	// is Uses -> return vector, stmt1 -> number, return variable
	static vector<string> isUsesVariable(string stmt1);

	// is Uses -> return vector, stmt1 -> procName, return variable
	static vector<string> isUsesProcTable(string stmt1);

	static vector<int> getUsesStmt(string stmt1);
	static vector<int> getUsesAssg(string stmt1);
	static vector<string> getUsesProc(string stmt1);

	// get UsesTable
	static std::vector<int> getUsesTable(string varName);

	// add UsesTable
	static void addDataToUses(string varName, int stmtLine);

	// add UsesProcedureTable
	static void addUsesProcTable(string procedure, string varName);

private:
	
	VarTable();
};

