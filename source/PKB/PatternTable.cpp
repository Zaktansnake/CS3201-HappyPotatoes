#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>

#include "Header\PatternTable.h"
#include "Header\VarTable.h"
#include "Header\Patterns.h"

using namespace std;

map<int, string> AllAssignsTable;
vector<int> AllAssignLineNum;

int checkLocationUnderscore(string line1, string line2);
vector<int> getPatternResult(string line1, string line2, bool leftUnderScore, bool rightUnderScore);
vector<string> getPatternResultWithVar(string line1, string line2, bool leftUnderScore, bool rightUnderScore);
string removeDoubleQuote(string s);
string removeUnderScore(string s);
vector<int> setLeftAns(string line1, bool left);
vector<int> setRightAns(string line2, bool right);

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
		ans = AllAssignLineNum;
	}
	else if (condition = 2) {
		// (_,"x+y+1")
		// Uses -> find out which lines using variable
		// ans.pushBack(ans)
		ans = getPatternResult(left, right, true, false);
	}
	else if (condition = 3) {
		// (_,_"x+y+1"_)
		// Uses -> find out which lines using variable
		// ans.pushBack(ans)
		ans = getPatternResult(left, right, true, true);
	}
	else if (condition = 4) {
		// ("x",_"x+y+1"_)
		// Modifies -> get the variable's stmtNum -> union with assigNum
		// Uses -> find out which lines using variable
		ans = getPatternResult(left, right, false, true);
	}
	else if (condition = 5) {
		// ("x","x+y+1")
		// Modifies -> get the variable's stmtNum -> union with assignNum
		// Uses -> find out which lines using variable
		ans = getPatternResult(left, right, false, false);
	}
	else if (condition = 6) {
		// ("x",_)
		// Modifies -> get the variable's stmtNum -> union with assignNum
		ans = getPatternResult(left, right, false, true);
	}

	return ans;
}

vector<string> PatternTable::getPatternWithVar(string left, string right) {
	vector<string> ans;

	return ans;
}

vector<int> getPatternResult(string line1, string line2, bool left, bool right) {

	string tempLine;
	string testKey = removeUnderScore(removeDoubleQuote(line2));
	vector<int> ans;
	vector<int> leftAns = setLeftAns(line1, left);
	vector<int> rightAns = setRightAns(line2, left);

	std::sort(leftAns.begin(), leftAns.end());
	std::sort(rightAns.begin(), rightAns.end());
	std::vector<int> v_intersection;
	std::set_intersection(leftAns.begin(), leftAns.end(),
		rightAns.begin(), rightAns.end(),
		std::back_inserter(v_intersection));

	cout << leftAns.size() << endl;
	cout << rightAns.size() << endl;
	cout << v_intersection.size() << endl;
	
	for (int i = 0; i < v_intersection.size(); i++) {
		tempLine = AllAssignsTable[v_intersection[i]];

		cout << "tempLine :: " <<  tempLine << endl;

		if (tempLine.find("=") != std::string::npos) {
			int length = tempLine.size();
			length = length - 2;
			tempLine.substr(2, length);

			while (tempLine.back() == ';' || tempLine.back() == '}') {
				tempLine.pop_back();
			}

			tempLine = Patterns::patternAssignment(tempLine);
			std::size_t found = tempLine.find(Patterns::patternAssignment(testKey));

			if (found != std::string::npos) {
				ans.push_back(v_intersection[i]);
			}
		}
	}

	return ans;
}

vector<string> getPatternResultWithVar(string line1, string line2, bool left, bool right) {}

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

vector<int> setLeftAns(string line1, bool left) {
	vector<int> leftAns;
	if (left == true) {
		leftAns = AllAssignLineNum;
	}
	else if (left == false) {
		leftAns = PatternTable::getModifiesVariable(removeDoubleQuote(line1));
	}
	return leftAns;
}

vector<int> setRightAns(string line2, bool right) {
	string tempLine = removeDoubleQuote(removeUnderScore(line2));
	vector<int> rightAns;
	if (right == true) {
		if (line2.compare("_") == 0) {
			rightAns = AllAssignLineNum;
		}
		else {
			rightAns = PatternTable::getUsesVariable(tempLine.substr(0, 1));
		}
	}
	else if (right == false) {
		rightAns = PatternTable::getUsesVariable(tempLine.substr(0, 1));
	}
	return rightAns;
}

string removeDoubleQuote(string s) {
	if (s.front() == '"') {
		s.erase(0, 1); // erase the first character
		s.erase(s.size() - 1); // erase the last character
		return s;
	}
	else {
		return s;
	}
}

string removeUnderScore(string s) {
	if (s.front() == '_') {
		s.erase(0, 1); // erase the first character
		s.erase(s.size() - 1); // erase the last character
		return s;
	}
	else {
		return s;
	}
}

void PatternTable::updatePatternTable() {
	setAssignTable();
	setAssignNum();
}