#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <algorithm>
#include <locale>  
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
#include <functional> 
#include <cctype>
#include <locale>
#include <exception>
#include <iterator>
#include <set>

#include "Header\PatternTable.h"
#include "Header\VarTable.h"
#include "Header\Patterns.h"

using namespace std;

map<int, string> AllAssignsTable;
vector<int> AllAssignLineNum;

bool checkStringSize(string line2, string tempLine);
string removeDoubleQuotePattern(string s);
string removeUnderScore(string s);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

static inline std::string &trim(std::string &s);
static inline std::string &rtrim(std::string &s);
static inline std::string &ltrim(std::string &s);

vector<string> PatternTable::getPatternWithType(string type, string left, string right) {
	vector<string> finalResult;

	if (type.compare("ASSIGN") == 0) {
		finalResult = PatternTable::getPatternAssignNum(left, right);
	}
	else if (type.compare("IF") == 0) {
		finalResult = PatternTable::getPatternIfsNum(left);
	}
	else if (type.compare("WHILE") == 0) {
		finalResult = PatternTable::getPatternWhileNum(left);
	}

	return finalResult;
}


void PatternTable::setAssignTable() {
	AllAssignsTable = VarTable::getAssignTable();
}

void PatternTable::setAssignNum() {
	AllAssignLineNum = VarTable::getAllAssign();
}

// get variable from MODIFIES
std::vector<int> PatternTable::getModifiesVariable(string variable) {
	return VarTable::getModifiesAssignInt(variable);
}

// get variable from USES
std::vector<int> PatternTable::getUsesVariable(string variable) {
	return VarTable::getUsesAssigInt(variable);
}

string PatternTable::getStatementLine(int stmtNo) {
	return VarTable::getAssignLine(stmtNo);
}

bool PatternTable::isPattern(string variable, string key) {

	vector<string> ans = PatternTable::getPatternAssignNum(variable, key);

	if (ans.size() > 0){
		return true;
	}
	return false;
}

vector<string> PatternTable::getPatternAssignNum(string left, string right) {
	vector<int> ans;
	int condition = checkLocationUnderscore(left, right);
	left = removeUnderScore(removeDoubleQuotePattern(left));
	right = removeUnderScore(removeDoubleQuotePattern(right));

	if (condition == 1) {
		ans = AllAssignLineNum;
	}
	else if (condition == 2) {
		ans = getPatternResult(left, right, true, false);
	}
	else if (condition == 3) {
		ans = getPatternResult(left, right, true, true);
	}
	else if (condition == 4) {
		ans = getPatternResult(left, right, false, true);
	}
	else if (condition == 5) {
		ans = getPatternResult(left, right, false, false);
	}
	else if (condition == 6) {
		ans = getPatternResult(left, right, false, true);
	}

	return PatternTable::convertIntToString(ans);
}

vector<string> PatternTable::getPatternIfsNum(string left) {
	vector<int> ans = VarTable::getAssignFromIfsTable(left);
	return PatternTable::convertIntToString(ans);
}

vector<string> PatternTable::getPatternWhileNum(string left) {
	vector<int> ans = VarTable::getAssignFromWhileTable(left);
	return PatternTable::convertIntToString(ans);
}

vector<int> PatternTable::getPatternResult(string line1, string line2, bool left, bool right) {

	string tempLine;
	vector<int> ans;
	vector<int> leftAns = setLeftAns(line1, left);

	if (line2.find("+") != std::string::npos || line2.find("-") != std::string::npos || line2.find("*") != std::string::npos) {
		line2 = PatternTable::addSpacesIntoString(line2);
		trim(line2);
	}

	for (int i = 0; i < leftAns.size(); i++) {

		tempLine = AllAssignsTable[leftAns[i]];
		std::vector<std::string> splitX = split(tempLine, '=');
		splitX[1] = splitX[1].erase(0, 1);
		splitX[1] = splitX[1].erase(splitX[1].size() - 2);

		if (line2.find("+") == std::string::npos && line2.find("-") == std::string::npos && line2.find("*") == std::string::npos) {
	
			if (right) {
				vector<int> rightAns = setRightAns(line2, right);
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
				line2 = removeDoubleQuotePattern(line2);
				std::size_t foundWord = splitX[1].find((line2));
				if (splitX[1].size() > line2.size() && foundWord != std::string::npos) {
					bool finalResult = Patterns::compareAssignments(splitX[1], line2, leftAns[i]);
					if (finalResult == true) {
						ans.push_back(leftAns[i]);
					}
				}
			}
		}
	}

	return ans;
}

int PatternTable::checkLocationUnderscore(string line1, string line2) {
	int result = 0;
	if (line1.compare("_") == 0 && line2.compare("_") == 0) {

		result = 1;
	}
	else if (line1.compare("_") == 0 && line2.substr(0, 1).compare("_") != 0 && line2.substr(line2.size() - 1).compare("_") != 0) {
		result = 2;
	}
	else if (line1.compare("_") == 0 && line2.substr(0, 1).compare("_") == 0 && line2.substr(line2.size() - 1).compare("_") == 0) {
		result = 3;
	}
	else if (line1.compare("_") != 0 && line2.size()!= 1 && line2.substr(0, 1).compare("_") == 0 && line2.substr(line2.size() - 1).compare("_") == 0) {

		result = 4;
	}
	else if (line1.compare("_") != 0 && line2.size() != 1 && line2.substr(0, 1).compare("_") != 0 && line2.substr(line2.size() - 1).compare("_") != 0) {

		result = 5;
	}
	else if (line1.compare("_") != 0 && line2.compare("_") == 0) {

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
	string tempLine = removeDoubleQuotePattern(removeUnderScore(line2));
	vector<int> rightAns;
	if (right == true) {
		if (tempLine.compare("_") == 0) {
			rightAns = AllAssignLineNum;
		}
		else {
			rightAns = PatternTable::getUsesVariable(tempLine);
		}
	} else {
		rightAns = PatternTable::getUsesVariable(tempLine);
	}
	return rightAns;
}

string removeDoubleQuotePattern(string s) {
	if (s.front() == '"') {
		s.erase(0, 1); 
		s.erase(s.size() - 1); 
		return s;
	}
	else {
		return s;
	}
}

string removeUnderScore(string s) {
	if (s.front() == '_' && s.back() == '_' && s.size() != 1) {
		s.erase(0, 1); 
		s.erase(s.size() - 1); 
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
		if (line2.compare(tempLine) == 0) {
			return true;
		}
		else {
			return false;
		}
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

vector<string> PatternTable::convertIntToString(vector<int> temp) {
	vector<string> result;
	if (!temp.empty()) {
		for (int i = 0; i < temp.size(); i++) {
			result.push_back(to_string(temp.at(i)));
		}
	}
	return result;
}

string PatternTable::addSpacesIntoString(string line) {
	vector<string> v;
	string lineWithVar = line;
	string tempLine, result;
	int ln = line.length() - 1;

	for (int n = 0; n <= ln; n++) {
		string letter(1, lineWithVar[n]);

		if (letter.compare(" ") != 0) {
			if (letter.compare("+") == 0 || letter.compare("-") == 0 || letter.compare("*") == 0 || letter.compare("(") == 0
				|| letter.compare(")") == 0 ) {
				tempLine = trim(tempLine);
				v.push_back(tempLine);
				v.push_back(letter);
				tempLine = "";
			}
			else {
				tempLine += letter;
			}
		}
	}

	v.push_back(tempLine);

	for (auto const& s : v) {
		result = result  + " " + s;
	}

	return result;
}

static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}