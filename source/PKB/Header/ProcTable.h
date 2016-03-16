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

	static void updateProcCallsTables();

	//add data
	static void addTableData(string procName);
	static void setCallsTable(string proc1, string proc2, int stmtLine);

	static void addProcModifiesVar(string procName, string variable);
	static vector<string> getProcModifiesVar(string procName);

	static void addProcUsesVar(string procName, string variable);
	static vector<string> getProcUsesVar(string procName);

	int findPosition (string ProcName);

	// get the size of proctable
	int getSize();

	// check if the table contains procedure
	static bool isContains (string procName);

private:   
	// constructor
	ProcTable();
};