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

	static void setConstantValue();
	static vector<int> getConstantValue(string stmtNum);
	static vector<int> getAllConstantValues();


};

