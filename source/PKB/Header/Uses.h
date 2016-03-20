#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Uses
{
public:

	// get UsesTable
	static std::vector<int> getUsesTable(string varName);

	// add item to UsesTable
	static void addUsesTable(string varName, int stmtLine);

	static void printMap02();

private:

	// constructors
	Uses();
	~Uses();

	static bool isContains(string varName);
	static int findPosition(string varName);
};