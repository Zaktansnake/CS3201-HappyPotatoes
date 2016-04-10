#ifndef MODIFIES_H
#define MODIFIES_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Modifies
{
public:

	// add item to ModifiesTable
	static void addModifiesTable(string varName, int stmtLine);

	// get ModifiesTable
	static std::vector<int> getModifiesTable(string varName);
	static vector<string> getModVariables(string stmtLine);

private:
	int index;
	vector<int> ansModifiesTable;

	// constructors
	Modifies();
	~Modifies();

	static bool isContains(string varName);
	static int findPosition(string varName);
};

#endif