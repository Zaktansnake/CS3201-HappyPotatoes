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

	// getSize
	static int  varTableLeftSize();
	static int  varTableRightSize();
	static int whileTableSize();
	static int assignTableSize();

	static vector<int> getAllAssign();


	static vector<string> findVariableLeft(int stmtLine1, int stmtLine2);

	static vector<string> findVariableRight(int stmtLine1, int stmtLine2);

	//----------------------- While Table -------------------------
	static void addDataToWhileTable(string variable, int stmtNum);

	//----------------------- Assign Table ------------------------
	static void addDataToAssignTable(string variable, int stmtNum);
	static string getAssignTable(int stmtNum);

	//----------------------- Modifies -------------------------------

	// get ModifiesTable
	static std::vector<int> getModifiesTable(string varName);

	// add ModifiesTable
	static void addDataToModifies(string varName, int stmtLine);

	// add ModifiesProcTable
	static void addModifiesProcTable(string varName, string procedure);

	static vector<string> getModifiesProc(string secondPerimeter);
	static vector<int>  getModifiesAssign(string secondPerimeter);
	static vector<int>	getModifiesWhile(string secondPerimeter);
	static vector<int> getModifiesStmt(string firstPerimeter);
	static bool isModifiesProc(string firstPerimeter, string secondPerimeter);
	static bool isModifiesAssign(string firstPerimeter, string secondPerimeter);
	static bool isModifiesStmt(string firstPerimeter, string secondPerimeter);
	static bool isModifiesWhile(string firstPerimeter, string secondPerimeter);

	//---------------------------- Uses -------------------------

	static vector<string> getUsesProc(string secondPerimeter);
	static vector<int> getUsesAssig(string secondPerimeter);
	static vector<int> getUsesStmt(string secondPerimeter);
	static vector<int> getUsesWhile(string secondPerimeter);
	static bool isUsesProc(string stmt1, string stmt2);
	static bool isUsesAssign(string stmt1, string stmt2);
	static bool isUsesStmt(string stmt1, string stmt2);
	static bool isUsesWhile(string stmt1, string stmt2);

	// get UsesTable
	static std::vector<int> getUsesTable(string varName);

	// add UsesTable
	static void addDataToUses(string varName, int stmtLine);

	// add UsesProcedureTable
	static void addUsesProcTable(string procedure, string varName);

private:
	
	VarTable();
};

