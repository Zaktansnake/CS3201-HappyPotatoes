#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

class Calls;

class ProcTable
{
public:
	// constructors
	~ProcTable();

	static vector<string> getAllProcedures();
	static void updateProcCallsTables();

	static void addTableData(string procName);
	static void setProcStmtNum(string procName, int stmtNum);
	static void setCallsTable(string proc1, string proc2, int stmtLine);
	static std::vector<std::tuple<string, string, int>> getCallsTable();

	static vector<string> getNextProcedure(string proc1);
	static vector<string> getNextProcedureTransitive(string proc1);
	static vector<string> getParentProcedure(string proc2);
	static vector<string> getParentProcedureTransitive(string proc2);
	static bool isProcToProc(string proc1, string proc2);
	static bool isProcToProcTransitive(string proc1, string proc2);

	// Modifies
	static void setProcModifiesVar(string procName, string variable);

	static vector<string> getProcModifiesVar(string procName);
	static vector<string> getModifiesProc(string secondPerimeter);
	static bool isModifiesProc(string firstPerimeter, string secondPerimeter);

	// Uses
	static void setProcUsesVar(string procName, string variable);

	static vector<string> getProcUsesVar(string procName);
	static vector<string> getUsesProc(string secondPerimeter);
	static bool isUsesProc(string firstPerimeter, string secondPerimeter);

	static int getProcTableSize();	// get the size of proctable

	int findPosition(string ProcName);
	static bool isContains (string procName);  // check if the table contains proceduce


	static vector<string> getProcWithType(string type, string value);
	static vector<string> getParentProcWithType(string type, string value);
	static vector<string> getProcTransitiveWithType(string type, string value);
	static vector<string> getParentProcTransitiveWithType(string type, string value);

private:   
	// constructor
	ProcTable();

	static void updateProcWithModAndUses();
	static void updateAllTransitiveTables();
	static void updateCallsTransitive();
	static void updateParentProcTransitive();

	static vector<string> convertIntToString(vector<int> temp);

};