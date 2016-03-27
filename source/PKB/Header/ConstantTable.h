#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ConstantTable
{
public:
	ConstantTable();
	~ConstantTable();

	// add item to ConstantTable
	static void setConstantValue(string constantValue, int stmtLine);
	static vector<int> getConstantValue(string stmtNum);
	static vector<int> getAllConstantValues();

	static void printMap03();

private:

	static bool isContains(int constantValue);
	static int findPosition(int constantValue);


};

