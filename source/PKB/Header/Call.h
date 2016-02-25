#pragma once

#include <string>
#include "PKB.h";

using namespace std;

class Call
{
public:
	// constructors
	Call();
	~Call();
	void setCall(string procName, int index);
	std::vector<string> getCall(int index);

	// print out the call answer table
	void PrintProcTable();
};