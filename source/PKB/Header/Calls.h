#pragma once

#include <string>
#include "PKB.h";

using namespace std;

class Calls
{
public:

	static void setCallProcedure(string mainProcedure, string procedure, int stmtLine);
	static std::vector<std::tuple<string, string, int>> getCallsTable();
	static std::unordered_set< std::pair<string, string>> getCallsSet();
	static void printCallsTable();

	////CALLS
	//// return the procedure set that called by proc
	//std::vector<string> getCalls(PROC proc);

	// return true proc1 calls proc2 otherwise, false
	bool isCalls(string proc1, string proc2);

private:
};