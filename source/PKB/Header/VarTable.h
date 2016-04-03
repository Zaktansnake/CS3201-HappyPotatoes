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

	static void sortVarLeftAndRight();

	// Update the Tables after parser is done
	static void updateModifiesUsesTables();

	// getSize
	static int varTableLeftSize();
	static int varTableRightSize();
	static int whileTableSize();
	static int assignTableSize();

	static vector<int> getAllStmt();
	static vector<int> getAllAssign();
	static vector<int> getAllWhile();
	static vector<int> getAllIfs();
	static vector<pair<int, string>> getModifiesInPair();
	static vector<pair<int, string>> getUsesInPair();

	static vector<string> findVariableLeft(int stmtLine1, int stmtLine2);
	static vector<string> findVariableRight(int stmtLine1, int stmtLine2);

	//----------------------- IFS Table -------------------------
	static void addDataToIfsTable(string variable, int stmtNum);
	static vector<int> getAssignFromIfsTable(string variable);

	//----------------------- While Table -------------------------
	static void addDataToWhileTable(string variable, int stmtNum);
	static vector<int> getAssignFromWhileTable(string variable);

	//----------------------- Assign Table ------------------------
	static void addDataToAssignTable(string variable, int stmtNum);
	static string getAssignLine(int stmtNum);
	static map<int, string> getAssignTable();

	//----------------------- Modifies -------------------------------
	static std::vector<int> getModifiesTable(string varName); // get ModifiesTable
	static void addDataToModifies(string varName, int stmtLine); // add ModifiesTable

	static vector<string> getModifiesVariable(string firstPerimeter);
	static vector<int>  getModifiesAssign(string secondPerimeter);
	static vector<int>	getModifiesWhile(string secondPerimeter);
	static vector<int> getModifiesStmt(string firstPerimeter);
	static bool isModifiesAssign(string firstPerimeter, string secondPerimeter);
	static bool isModifiesStmt(string firstPerimeter, string secondPerimeter);
	static bool isModifiesWhile(string firstPerimeter, string secondPerimeter);

	// Uses
	static std::vector<int> getUsesTable(string varName);  // get UsesTable
	static void addDataToUses(string varName, int stmtLine);  // add UsesTable

	static vector<string> getUsesVariable(string firstPerimeter);
	static vector<int> getUsesAssig(string secondPerimeter);
	static vector<int> getUsesStmt(string secondPerimeter);
	static vector<int> getUsesWhile(string secondPerimeter);
	static bool isUsesAssign(string firstPerimeter, string secondPerimeter);
	static bool isUsesStmt(string firstPerimeter, string secondPerimeter);
	static bool isUsesWhile(string firstPerimeter, string secondPerimeter);

private:
	// constructor
	VarTable();

	static vector<int> setAssign();

};