#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Modifies
{
public:
	Modifies();
	~Modifies();

	// get ModifiesTable
	static std::vector<int> getModifiesTable(string varName);

	// add item to ModifiesTable
	static void addModifiesTable(string varName, int stmtLine);

	static bool isContains(string varName);

private:

	static int findPosition(string varName);
};

