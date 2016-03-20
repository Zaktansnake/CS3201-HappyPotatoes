#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

#include "Header\PatternTable.h"
#include "Header\VarTable.h"
#include "Header\Patterns.h"

using namespace std;

map<int, string> AllAssignsTable;
vector<int> AllAssignLineNum;
std::vector<int>lineThatModifiedV;
string stmtLine;

int checkLocationUnderscore(string line1, string line2);

void PatternTable::setAssignTable() {
	AllAssignsTable = VarTable::getAssignTable();
}

void PatternTable::setAssignNum() {
	AllAssignLineNum = VarTable::getAllAssign();
}

// get variable from MODIFIES
std::vector<int> PatternTable::getModifiesVariable(string variable) {
	return VarTable::getModifiesAssign(variable);
}

// get variable from USES
std::vector<int> PatternTable::getUsesVariable(string variable) {
	return VarTable::getUsesAssig(variable);
}

string PatternTable::getStatementLine(int stmtNo) {
	return VarTable::getAssignLine(stmtNo);
}

bool PatternTable::isPattern(string variable, string key) {
	return false;
}

vector<int> PatternTable::getPatternAssignNum(string left, string right) {
	vector<int> ans;
	int condition = checkLocationUnderscore(left, right);

	if (condition == 1) {
		// (_,_)
		// return all assign num
	}
	else if (condition = 2) {
		// (_,"x+y+1")
		// Uses -> find out which lines using variable
		// ans.pushBack(ans)
	}
	else if (condition = 3) {
		// (_,_"x+y+1"_)
		// Uses -> find out which lines using variable
		// ans.pushBack(ans)
	}
	else if (condition = 4) {
		// ("x",_"x+y+1"_)
		// Modifies -> get the variable's stmtNum -> union with assigNum
		// Uses -> find out which lines using variable
	}
	else if (condition = 5) {
		// ("x","x+y+1")
		// Modifies -> get the variable's stmtNum -> union with assignNum
		// Uses -> find out which lines using variable
	}
	else if (condition = 6) {
		// ("x",_)
		// Modifies -> get the variable's stmtNum -> union with assignNum
	}

	return ans;
}

vector<string> PatternTable::getPatternWithVar(string left, string right) {
	vector<string> ans;

	return ans;
}

int checkLocationUnderscore(string line1, string line2) {
	int result = 0;

	if (line1.compare("_") == 0 && line2.compare("_") == 0) {
		// (_,_)
		result = 1;
	}
	else if (line1.compare("_") == 0 && line2.substr(0, 1).compare("_") != 0 && line2.substr(line2.size() - 1).compare("_") != 0) {
		// (_,"x+y+1")
		result = 2;
	}
	else if (line1.compare("_") == 0 && line2.substr(0, 1).compare("_") == 0 && line2.substr(line2.size() - 1).compare("_") == 0) {
		// (_,_"x+y+1"_)
		result = 3;
	}
	else if (line1.compare("_") != 0 && line2.substr(0, 1).compare("_") == 0 && line2.substr(line2.size() - 1).compare("_") == 0) {
		// ("x",_"x+y+1"_)
		result = 4;
	}
	else if (line1.compare("_") != 0 && line2.substr(0, 1).compare("_") != 0 && line2.substr(line2.size() - 1).compare("_") != 0) {
		// ("x","x+y+1")
		result = 5;
	}
	else if (line1.compare("_") != 0 && line2.compare("_") == 0) {
		// ("x",_)
		result = 6;
	}

	return result;
}
