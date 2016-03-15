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


	//// USES
	//bool isUses(VAR var, STMT stmt);
	//bool isUses(VAR var, PROC proc);

	//// return variables that used in stmtlist
	//VAR getUses(STMT stmt);

	//// return variables that used in procedure
	//VAR getUses(PROC proc);

	//// return procedure that used this variable
	//std::vector<string> getUses(VAR var);

	//// record statmentlst use variable
	//void setUses(STMT stmt, VAR var);

	////record procedures that use this variable
	//void setUses(PROC proc, VAR var);



	//NEED TO DELETE AFTER TESTING
	static void printMap02();

private:
};