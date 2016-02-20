#pragma once
#include<string>
#include<vector>
#include <algorithm>
#include <string>
#include <vector>
#include "./Header/PatternTable.h"
#include "./Header/VarTable.h"
#include "./Header/Patterns.h"


using namespace std;
std::vector<int>lineThatModifiedV;
string stmtLine;

// -----------------isPattern--------------------------
std::vector<int> PatternTable::getVariable(string variable) {
    return VarTable::getModifiesTable(variable);
}
string PatternTable::getStatementLine(int stmtNo) {
    return VarTable::getAssignTable(stmtNo);
}
bool PatternTable::isPattern(string variable, string key) {
    lineThatModifiedV = getVariable(variable);
	for (int i = 0; i < lineThatModifiedV.size(); i++) {
	     stmtLine = getStatementLine(lineThatModifiedV.at(i));
		 std::size_t found = stmtLine.find(Patterns::patternAssignment(key));
		 if (found != std::string::npos) {
			 return true;
		 }
		 else {
			 return false;
		 }
	}
}
	//----------------------getAssignWithVar---------------------
std::vector<int> PatternTable::getAssignWithVar(string variable, string testkey) {
   std::vector<int> ans;
	 for (int i = 0; i < lineThatModifiedV.size(); i++) {
		 stmtLine = getStatementLine(lineThatModifiedV.at(i));
		 std::size_t found = stmtLine.find(Patterns::patternAssignment(testkey));
		 if (found != std::string::npos) {
			 ans.push_back(lineThatModifiedV.at(i));
		 }
	}
	return ans;
}

//----------------------getAssign---------------------------------
std::vector<int> PatternTable::getAssign(string testkey) {
    std::vector<int> ans;
    lineThatModifiedV = VarTable::getAllAssign();
	for (int i = 0; i < lineThatModifiedV.size(); i++) {
		stmtLine = getStatementLine(lineThatModifiedV.at(i));
		std::size_t found  = stmtLine.find(Patterns::patternAssignment(testkey));
		if (found != std::string::npos) {
		   ans.push_back(lineThatModifiedV.at(i));
		}
	}
	return ans;
}
