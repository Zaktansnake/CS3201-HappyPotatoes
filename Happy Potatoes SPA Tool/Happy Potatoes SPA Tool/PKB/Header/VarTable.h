#pragma once

#include <map>
#include <iostream>
#include<vector>

using namespace std;

class Modifies;

class VarTable
{
public:
	~VarTable();

	// get ModifiesTable
	static std::vector<int> getModifiesTable(string varName);

	// add ModifiesTable
	static void addDataToModifies(string varName, int stmtLine);

	// get UsesTable
	static std::vector<int> getUsesTable(string varName);

	// add UsesTable
	static void addDataToUses(string varName, int stmtLine);

private:
	
	VarTable();
};

