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

	static vector<string> getPatternAssignNum(string left, string right);
	static vector<string> getPatternIfsNum(string left);
	static vector<string> getPatternWhileNum(string left);
	static bool isPattern(string variable, string key);

	static vector<string> getPatternWithType(string type, string left, string right);

	static void updatePatternTable();

private:

	static vector<int> getPatternResult(string line1, string line2, bool leftUnderScore, bool rightUnderScore);
	static int checkLocationUnderscore(string line1, string line2);
	static vector<int> setLeftAns(string line1, bool left);
	static vector<int> setRightAns(string line2, bool right);
	static vector<string> convertIntToString(vector<int> temp);
	static string PatternTable::addSpacesIntoString(string line);

};