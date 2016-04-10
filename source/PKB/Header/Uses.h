#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Uses
{
public:

	// add item to UsesTable
	static void addUsesTable(string varName, int stmtLine);

	// get UsesTable
	static std::vector<int> getUsesTable(string varName);
	static vector<string> getUseVariables(string stmtLine);

private:

	// constructors
	Uses();
	~Uses();

	static bool isContains(string varName);
	static int findPosition(string varName);
};