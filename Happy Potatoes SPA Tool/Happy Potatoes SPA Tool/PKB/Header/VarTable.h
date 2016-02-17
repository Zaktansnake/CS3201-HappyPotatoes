#pragma once

#include <map>
#include <iostream>
#include<vector>

using namespace std;

class Modifies;
class Uses;

class VarTable
{
public:
	~VarTable();

	static vector<string> findVariableLeft(int stmtLine1, int stmtLine2);

	static vector<string> findVariableRight(int stmtLine1, int stmtLine2);

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

