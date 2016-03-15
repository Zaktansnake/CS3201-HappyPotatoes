#pragma once

#include <string>
#include "PKB.h";

using namespace std;

class Calls
{
public:

	void setCall(string procName, int index);
	std::vector<string> getCall(int index);

	////CALLS
	//// return the procedure set that called by proc
	//std::vector<string> getCalls(PROC proc);

	//// set the call relationship between proc1 and proc2
	//void setCalls(PROC proc1, PROC proc2);

	//// return true proc1 calls proc2 otherwise, false
	//bool isCalls(PROC proc1, PROC proc2);

private:
};