#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

class PatternTable
{
public:

	static std::vector<int> getModifiesVariable(string variable);
	static std::vector<int> getUsesVariable(string variable);
	static string getStatementLine(int stmtNo);
	static void setAssignTable();
	static void setAssignNum();

	static vector<int> getPatternAssignNum(string left, string right);
	static vector<string> getPatternWithVar(string left, string right);
	static bool isPattern(string variable, string key);

};