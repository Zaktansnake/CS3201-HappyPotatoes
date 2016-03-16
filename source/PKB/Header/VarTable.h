#pragma once

#include <map>
#include <iostream>
#include <vector>

using namespace std;

class Modifies;
class Uses;

class VarTable
{
public:
	// constructor
	~VarTable();

	// printTable
	static void printTables();

	// Update the Tables after parser is done
	static void updateModifiesUsesTables();

	// getSize
	static int  varTableLeftSize();
	static int  varTableRightSize();
	static int whileTableSize();
	static int assignTableSize();

	static vector<int> getAllStmt();
	static vector<int> getAllAssign();
	static vector<int> getAllWhile();
	static vector<int> getAllIfs();

	static vector<string> findVariableLeft(int stmtLine1, int stmtLine2);
	static vector<string> findVariableRight(int stmtLine1, int stmtLine2);

	//----------------------- While Table -------------------------
	static void addDataToWhileTable(string variable, int stmtNum);

	//----------------------- Assign Table ------------------------
	static void addDataToAssignTable(string variable, int stmtNum);
	static string VarTable::getAssignTable(int stmtNum);

	//----------------------- Modifies -------------------------------
	// get ModifiesTable
	static std::vector<int> getModifiesTable(string varName);

	// add ModifiesTable
	static void addDataToModifies(string varName, int stmtLine);

	// add ModifiesProcTable
	static void addModifiesProcTable(string varName, string procedure);

	static vector<string> getModifiesProc(string secondPerimeter);
	static vector<string> getModifiesVariable(string firstPerimeter);
	static vector<int>  getModifiesAssign(string secondPerimeter);
	static vector<int>	getModifiesWhile(string secondPerimeter);
	static vector<int> getModifiesStmt(string firstPerimeter);
	static bool isModifiesProc(string firstPerimeter, string secondPerimeter);
	static bool isModifiesAssign(string firstPerimeter, string secondPerimeter);
	static bool isModifiesStmt(string firstPerimeter, string secondPerimeter);
	static bool isModifiesWhile(string firstPerimeter, string secondPerimeter);

	//---------------------------- Uses -------------------------
	// get UsesTable
	static std::vector<int> getUsesTable(string varName);

	// add UsesTable
	static void addDataToUses(string varName, int stmtLine);

	// add UsesProcedureTable
	static void addUsesProcTable(string procedure, string varName);

	static vector<string> getUsesProc(string secondPerimeter);
	static vector<string> getUsesVariable(string firstPerimeter);
	static vector<int> getUsesAssig(string secondPerimeter);
	static vector<int> getUsesStmt(string secondPerimeter);
	static vector<int> getUsesWhile(string secondPerimeter);
	static bool isUsesProc(string firstPerimeter, string secondPerimeter);
	static bool isUsesAssign(string firstPerimeter, string secondPerimeter);
	static bool isUsesStmt(string firstPerimeter, string secondPerimeter);
	static bool isUsesWhile(string firstPerimeter, string secondPerimeter);


private:
	// constructor
	VarTable();

	static vector<int> setStmt();
	static vector<int> setAssign();
};