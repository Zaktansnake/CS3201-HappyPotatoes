#pragma once
#include<map>
#include<string>
#include<vector>

using namespace std;

class PatternTable
{
public:
	
	//------------------isPattern-----------------
	//get data from var table 
	static std::vector<int> getVariable (string variable);
	static string getStatementLine(int stmtNo);
    static bool isPattern(string variable, string key);


	//----------------getAssign------------------------------------

	static std::vector<int> getAssignWithVar(string variable,string testkey);
	static std::vector<int> getAssign(string testkey);
	
	


};
