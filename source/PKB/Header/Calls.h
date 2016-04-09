#pragma once

#include <string>
#include "PKB.h";

using namespace std;

class Calls
{
public:

	static void setCallProcedure(string mainProcedure, string procedure, int stmtLine);
	static std::vector<std::tuple<string, string, int>> getCallsTable();
	static std::unordered_set<std::pair<string, string>> getCallsSet();

private:
};