#pragma once
#include<map>
#include<string>
#include<vector>
#include "AST.h"
#include "Call.h"

using namespace std;

class ProcTable
{
public:
//	ProcTable();
	~ProcTable();

    // get reference to procedure table
	static ProcTable* getProcTable();

	//add data
	static void addTableData(string procName, int stmtLine);

	// get data
	int getProcIndex (string key);
	std::vector<string> getCallAns(string procName);
	int getProgLine (string procName);
	int findPosition (string ProcName);
	string getProcName (int index);
	//TNode* getProcNode (int index);

	//get the size of proctable
	int getSize();

	//delete data
	void RemoveProcData();

	//check if the table contains procedure
	static bool isContains (string procName);

	//print proc data
	void PrintProcTable();

private: 
    static std::map<string, int> ProcMap;   //procName, index of the procName in the map
	static std::vector<string> ProcIndex;   // store the index of map
	ProcTable();
};

