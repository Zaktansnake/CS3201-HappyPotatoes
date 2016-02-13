#pragma once
#include<map>
#include<string>
#include<vector>
#include "AST.h"
#include "Call.h"
#include "TNode.h"

using namespace std;

class ProcTable
{
public:
//	ProcTable();
	~ProcTable();

    // get reference to procedure table
	static ProcTable* getProcTable();

	//add data
	static void addTableData(string procName);

	// get data
	int getProcIndex (string key);
	std::vector<string> getCallAns(int index);
	string getProcName (int index);
	TNode* getProcNode (int index);

	//get the size of proctable
	int getSize();

	//delete data
	void RemoveProcData();

	//print proc data
	void PrintProcTable();

private: 
    static std::map<string, int> ProcMap;
	static std::vector<string> ProcIndex;
	ProcTable();
};

