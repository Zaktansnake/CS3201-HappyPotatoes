#pragma once

#include <map>
#include <iostream>
#include "./TNode.h"

using namespace std;

class VarTable
{
public:
	~VarTable();

	// get reference to procedure table
	static VarTable* getVarTable();

	//add data
	static void addTableData(string varName);

	// get data
	int getVarIndex(string key);

	std::vector<string> getUsesAns(int index);
	std::vector<string> getModifiesAns(int index);
	std::vector<string> getFollowsAns(int index);
	std::vector<string> getAffectsAns(int index);
	std::vector<string> getParentsAns(int index);

	string getVarName(int index);
	TNode* getVarNode(int index);

	//get the size of proctable
	int getSize();

	//delete data
	void RemoveVarData();

	//print proc data
	void PrintVarTable();


private:
	static std::map<string, int> VarMap;
	static std::vector<string> VarIndex;
	VarTable();
};

