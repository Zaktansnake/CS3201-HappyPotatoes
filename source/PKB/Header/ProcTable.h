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
	static void setCallsTable(string proc1, string proc2, int stmtLine);

	static vector<string> getNextProcedure(string proc1);
	static vector<string> getNextProcedureTransitive(string proc1);
	static vector<string> getParentProcedure(string proc2);
	static vector<string> getParentProcedureTransitive(string proc2);
	bool isProcToProc(string proc1, string proc2);
	bool isProcToProcTransitive(string proc1, string proc2);

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


	int getProcTableSize();	// get the size of proctable

	int findPosition(string ProcName);
	static bool isContains (string procName);  // check if the table contains proceduce

private:   
	// constructor
	ProcTable();
};