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

	static void sortVarLeftAndRight();

	// Update the Tables after parser is done
	static void updateModifiesUsesTables();

	// getSize
	static int varTableLeftInPairSize();
	static int varTableRightInPairSize();
	static int whileTableSize();
	static int assignTableSize();

	static vector<int> getAllStmt();
	static vector<int> getAllAssign();
	static vector<int> getAllWhile();
	static vector<int> getAllIfs();
	static vector<string> getAllVariables();
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
	static void addDataToModifies(string varName, int stmtLine); // add ModifiesTable

	static std::vector<int> getModifiesTable(string varName); // get ModifiesTable
	static vector<int> getModifiesAssignInt(string secondPerimeter);
	static vector<string> getModifiesVariable(string firstPerimeter);
	static vector<string> getModifiesAssign(string secondPerimeter);
	static vector<string> getModifiesWhile(string secondPerimeter);
	static vector<string> getModifiesStmt(string secondPerimeter);
	static vector<string> getModifiesIfs(string secondPerimeter);
	static bool isModifiesProcedure(string firstPerimeter, string secondPerimeter);
	static bool isModifiesAssign(string firstPerimeter, string secondPerimeter);
	static bool isModifiesStmt(string firstPerimeter, string secondPerimeter);
	static bool isModifiesWhile(string firstPerimeter, string secondPerimeter);
	static bool isModifiesIfs(string firstPerimeter, string secondPerimeter);

	// Uses
	static void addDataToUses(string varName, int stmtLine);  // add UsesTable

	static std::vector<int> getUsesTable(string varName);  // get UsesTable
	static vector<int> getUsesAssigInt(string secondPerimeter);
	static vector<string> getUsesVariable(string firstPerimeter);
	static vector<string> getUsesAssig(string secondPerimeter);
	static vector<string> getUsesStmt(string secondPerimeter);
	static vector<string> getUsesWhile(string secondPerimeter);
	static vector<string> getUsesIfs(string secondPerimeter);
	static bool isUsesProcedure(string firstPerimeter, string secondPerimeter);
	static bool isUsesAssign(string firstPerimeter, string secondPerimeter);
	static bool isUsesStmt(string firstPerimeter, string secondPerimeter);
	static bool isUsesWhile(string firstPerimeter, string secondPerimeter);
	static bool isUsesIfs(string firstPerimeter, string secondPerimeter);


	static vector<string> getModifiesWithType(string type, string value);
	static vector<string> getModifiedWithType(string type, string value);
	static vector<string> getUsesWithType(string type, string value);
	static vector<string> getUsedWithType(string type, string value);


private:
	// constructor
	VarTable();

	static vector<int> setAssign();
	static void setAllVariables(string variable);

	static vector<string> convertIntToString(vector<int> temp);

};