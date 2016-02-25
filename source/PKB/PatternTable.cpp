#pragma once
#include<string>
#include<vector>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "Header\PatternTable.h"
#include "Header\VarTable.h"
#include "Header\Patterns.h"


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
		if (stmtLine.find("=") != std::string::npos) {
			int length = stmtLine.size() - 2;
			stmtLine = stmtLine.substr(2, length);
			while (stmtLine.back() == ';' || stmtLine.back() == '}') {
				stmtLine.pop_back();
			}
			stmtLine = Patterns::patternAssignment(stmtLine);
			std::size_t found = stmtLine.find(Patterns::patternAssignment(key));
			if (found != std::string::npos) {
				return true;
			}
		}
	}
	return false;
}
//----------------------getAssignWithVar---------------------
std::vector<int> PatternTable::getAssignWithVar(string variable, string testkey) {
	std::vector<int> ans;
	for (int i = 0; i < lineThatModifiedV.size(); i++) {
		stmtLine = getStatementLine(lineThatModifiedV.at(i));
		if (stmtLine.find("=") != std::string::npos) {
		    int in = static_cast<int>(stmtLine.find("="));
			int length = stmtLine.size();
			string op = stmtLine.substr(0,in);
			if (op.compare(variable) == 0) {
				length = length - 2;
				stmtLine.substr(2, length);
				while (stmtLine.back() == ';' || stmtLine.back() == '}') {
					stmtLine.pop_back();
				}
				stmtLine = Patterns::patternAssignment(stmtLine);
				std::size_t found = stmtLine.find(Patterns::patternAssignment(testkey));
				if (found != std::string::npos) {
					ans.push_back(lineThatModifiedV.at(i));
				}
			}
			
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
		if (stmtLine.find("=") != std::string::npos) {
			int length = stmtLine.size();
			length = length - 2;
			stmtLine.substr(2, length);
			while (stmtLine.back() == ';' || stmtLine.back() == '}') {
				stmtLine.pop_back();
			}
			stmtLine = Patterns::patternAssignment(stmtLine);
			std::size_t found = stmtLine.find(Patterns::patternAssignment(testkey));
			if (found != std::string::npos) {
				ans.push_back(lineThatModifiedV.at(i));
			}
		}
	}
	return ans;
}
