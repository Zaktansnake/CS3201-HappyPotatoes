#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Uses
{
public:
	// constructors
	Uses();
	~Uses();

	// get UsesTable
	static std::vector<int> getUsesTable(string varName);
	static std::vector<string> Uses::getUsesProcTable(string procName);

	// add item to UsesTable
	static void addUsesTable(string varName, int stmtLine);
	static void addUsesProcedureTable(string procedure, string varName);

	static bool isContains(string varName);
	static int findPosition(string varName);

private:
};