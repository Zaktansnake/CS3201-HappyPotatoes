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

bool checkStringSize(string line2, string tempLine);
string removeDoubleQuote(string s);
string removeUnderScore(string s);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

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

	left = removeUnderScore(removeDoubleQuote(left));
	right = removeUnderScore(removeDoubleQuote(right));

	if (condition == 1) {
		// (_,_)
		ans = AllAssignLineNum;
	}
	else if (condition == 2) {
		// (_,"x+y+1")
		ans = getPatternResult(left, right, true, false);
	}
	else if (condition == 3) {
		// (_,_"x+y+1"_)
		ans = getPatternResult(left, right, true, true);
	}
	else if (condition == 4) {
		// ("x",_"x+y+1"_)
		ans = getPatternResult(left, right, false, true);
	}
	else if (condition == 5) {
		// ("x","x+y+1")
		ans = getPatternResult(left, right, false, false);
	}
	else if (condition == 6) {
		// ("x",_)
		ans = getPatternResult(left, right, false, true);
	}

	return ans;
}

vector<int> PatternTable::getPatternIfsNum(string left, string middle, string right) {}

vector<int> PatternTable::getPatternWhileNum(string left, string right) {}

vector<int> PatternTable::getPatternResult(string line1, string line2, bool left, bool right) {

	string tempLine;
	vector<int> ans;
	vector<int> leftAns = setLeftAns(line1, left);

	for (int i = 0; i < leftAns.size(); i++) {
		tempLine = AllAssignsTable[leftAns[i]];

		std::vector<std::string> splitX = split(tempLine, '=');
		splitX[1] = splitX[1].erase(0, 1);
		splitX[1] = splitX[1].erase(splitX[1].size() - 2);

		// check line2 contains "+" || "-" || "-" -> only consists of variable
		if (line2.find("+") == std::string::npos && line2.find("-") == std::string::npos && line2.find("*") == std::string::npos) {
			if (right) {
				vector<int> rightAns = setRightAns(line1, left);
				if (leftAns.size() > 0 && rightAns.size() > 0) {
					std::vector<int> v_intersection;
					std::set_intersection(leftAns.begin(), leftAns.end(),
						rightAns.begin(), rightAns.end(),
						std::back_inserter(v_intersection));
					return v_intersection;
				}
			}
			else {
				if (checkStringSize(line2, splitX[1])) {
					ans.push_back(leftAns[i]);
				}
			}
		}
		else {
			if (checkStringSize(line2, splitX[1])) {
				ans.push_back(leftAns[i]);
			}
			else {
				bool finalResult = Patterns::compareAssignments(splitX[1], line2);
				if (finalResult == true) {
					ans.push_back(leftAns[i]);
				}
			}
		}
	}

	
	return ans;
}

int PatternTable::checkLocationUnderscore(string line1, string line2) {
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

vector<int> PatternTable::setLeftAns(string line1, bool left) {
	vector<int> leftAns;
	if (left) {
		leftAns = AllAssignLineNum;
	}
	else {
		leftAns = PatternTable::getModifiesVariable(line1);
	}
	return leftAns;
}

vector<int> PatternTable::setRightAns(string line2, bool right) {
	string tempLine = removeDoubleQuote(removeUnderScore(line2));
	vector<int> rightAns;
	if (right == true) {
		if (line2.compare("_") == 0) {
			rightAns = AllAssignLineNum;
		}
	} else {
		rightAns = PatternTable::getUsesVariable(line2);
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

bool checkStringSize(string line2, string tempLine) {
	std::string::iterator end_pos = std::remove(line2.begin(), line2.end(), ' ');
	line2.erase(end_pos, line2.end());

	std::string::iterator end_pos2 = std::remove(tempLine.begin(), tempLine.end(), ' ');
	tempLine.erase(end_pos2, tempLine.end());

	if (line2.size() == tempLine.size()) {
		return true;
	}
	else {
		return false;
	}
}

void PatternTable::updatePatternTable() {
	setAssignTable();
	setAssignNum();
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}