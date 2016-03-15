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
	// get ModifiesTable
	static std::vector<int> getModifiesTable(string varName);
	static std::vector<string> getModifiesProcTable(string procName);

	// add item to ModifiesTable
	static void addModifiesTable(string varName, int stmtLine);
	static void addModifiesProcedureTable(string procedure, string varName);

	//NEED TO DELETE AFTER TESTING
	static void printMap01();

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