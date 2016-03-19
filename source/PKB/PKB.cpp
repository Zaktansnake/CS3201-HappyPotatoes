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

#include "./Header/PKB.h"
#include "./Header/ProcTable.h"
#include "./Header/VarTable.h"
#include "./Header/stmtTable.h"
#include "Header\CFG.h"

using namespace std;

static ifstream myFile;
static string str, word, procname;
static ostringstream oss;
stack<pair<string, int>> bracstack; // string -> {; int -> currentStmtLine
bool firstTime, firstLine;
static int stmtLine = 0;
	
static void procedure();
static void stmtLst();
static void assign();
static void calls(string procedureName);
static void stmt(int num);

static void findMethod(string file_contents);
vector<string> split(string str, char delimiter);
vector<string> splitTheString(string line);
static void calls(string procedurName, int stmtLine);
void stmtLineForPattern(vector<string> line);
void detectRightBracket();
static inline std::string &ltrim(std::string &s);
static inline std::string &rtrim(std::string &s);
static inline std::string &trim(std::string &s);

void PKB::create(string fileName) {
	firstTime = true;
	firstLine = true;
	myFile.open(fileName);
	stmtLine = 0;

	while (!myFile.eof()) {
		getline(myFile, str);
		findMethod(str);
        stmtLine++;
	}

	myFile.close();
	PKB::updateTables();
	
}

int PKB::getStmtNum() {
	return stmtLine - 1;
}

void findMethod(string file_contents) {
	istringstream iss(file_contents);

	if (file_contents.compare("") != 0) {
		iss >> word; // get the first word
		oss << iss.rdbuf(); // get the remain words
	}
	else {
		word = "";
	}

	if (firstLine) {
		if (word.compare("procedure") != 0) {
			cout << "Error: Structure. (procedure)" << endl;
			PKB::abort();
		}
		firstLine = false;
	}

	if (word.compare("procedure") == 0) {
		if (!firstTime && stmtLine > 0) {
			stmtLine--;
		}
		procedure();
	}
	else if (word.compare("if") == 0 || word.compare("else") == 0
		|| (word.compare("call") == 0) || (word.compare("while") == 0)) {
		stmtLst();
		stmtTable::addStmtTable(str, stmtLine);
	}
	else if (word.compare("") == 0) {
		if (!bracstack.empty()) {
			cout << "Error: Structure. (backStack problem)" << endl;
			PKB::abort();
		}

		firstTime = false;
		stmtLine--;
	}
	else if (word.compare("}") == 0) {
		vector<string> ans;
		if (file_contents.find("else") != std::string::npos) {
			stmt(1);
		} else {
			stmtLine--;
			detectRightBracket();
			bracstack.pop();
		}
		stmtTable::addStmtTable(str, stmtLine);
	}
	else {
		assign();
		stmtTable::addStmtTable(str, stmtLine);
	}
}

void procedure() {
	vector<string> v = splitTheString(str);
	if (v.size() > 3) {
		cout << "Error: Structure. (procedure size)" << endl;
		PKB::abort();
	}

	if (ProcTable::isContains(v[1])) {
		cout << "Error: Duplication of Procedure Name." << endl;
		PKB::abort();
	}
	else {
		if (v.size() <= 3) {
			if (v[2].compare("{") != 0) {
				cout << "Error: Structure. (procTable)" << endl;
				PKB::abort();
			}
			else {
				bracstack.push(make_pair("{", 0));
			}
		}
		procname = v[1];
		ProcTable::addTableData(v[1]);
		
	}
}

void stmtLst() {
	int num = 0;

	if (word.compare("if") == 0) {
		num = 0;
	}
	else if (word.compare("else") == 0) {
		num = 1;
	}
	else if (word.compare("while") == 0) {
		num = 2;
	}
	else if (word.compare("call") == 0) {
		num = 3;
	}

	stmt(num);
}

static void stmt(int num) {
	vector<string> v = splitTheString(str);

	switch (num) {
	case 0: // if
		if (v[2].compare("then") == 0 && (v[3].compare("{")) == 0) {
			VarTable::addDataToUses(v[1], stmtLine);
			VarTable::addDataToIfsTable(v[1], stmtLine);
			ProcTable::setProcUsesVar(procname, v[1]);
			bracstack.push(make_pair("{", stmtLine));
		}
		else {
			cout << "Error: Structure. (then)" << endl;
			PKB::abort();
		}

		break;
	case 1: // else
		stmtLine--;
		if (v.size() == 3) {
			vector<string> ans;
			detectRightBracket();
			bracstack.pop();
			bracstack.push(make_pair("{", -2));
		}
		else if (v.size() == 2) {
			if (v[1].compare("{") != 0) {
				cout << "Error: Structure. ({)" << endl;
				PKB::abort();
			}
			else {
				bracstack.push(make_pair("{", -2));
			}
		}

		break;
	case 2: // while
		if (v[2].compare("{") == 0) {
			VarTable::addDataToUses(v[1], stmtLine);
			ProcTable::setProcUsesVar(procname, v[1]);
			bracstack.push(make_pair("{", stmtLine));
			VarTable::addDataToWhileTable(v[1], stmtLine);
		}
		else {
			cout << "Error: Structure. ({)" << endl;
			PKB::abort();
		}

		break;
	case 3: // call
		calls(str, stmtLine);
		break;
	}
}

void assign() {
	vector<string> v;
	string lineWithVar = str;
	string tempLine;
	int ln = str.length() - 1;

	for (int n = 0; n <= ln; n++) {
		string letter(1, lineWithVar[n]);

		if (letter.compare(" ") != 0) {
			if (letter.compare("+") == 0 || letter.compare("-") == 0 || letter.compare("*") == 0 || letter.compare("(") == 0 || letter.compare(")") == 0 || letter.compare(";") == 0 || letter.compare("}") == 0 || letter.compare("=") == 0) {
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

	stmtLineForPattern(v);

	for (int i = 0; i < v.size(); i++) {
		std::string var = v.at(i);

		if (var.compare("}") == 0) {
			detectRightBracket();
			bracstack.pop();
		}
		else {
			if (i == 0) {
				VarTable::addDataToModifies(var, stmtLine);
				ProcTable::setProcModifiesVar(procname, v[i]);
			}
			else {
				if (var.compare("=") != 0 && var.compare("+") != 0 && var.compare("-") != 0 && var.compare(";") != 0 && var.compare("*") != 0 && var.compare("(") != 0 && var.compare(")") != 0 && var.compare("}") != 0 && var.compare(" ") != 0 && var.compare("' '") != 0 && var.compare("") != 0) {
					VarTable::addDataToUses(var, stmtLine);
					ProcTable::setProcUsesVar(procname, v[i]);
				}
			}
		}
	}
}

static void calls(string str, int stmtLine) {
	vector<string> v = splitTheString(str);
	string procName = v[1].substr(0, v[1].size() - 1);
	ProcTable::setCallsTable(procname, procName, stmtLine);
}

void PKB::updateTables() {
	// parse the assign table to Patterns
	// update uses table one more time
	VarTable::updateModifiesUsesTables();
	ProcTable::updateProcCallsTables();
	PKB::updateAllTables();

	//VarTable::printTables();
}

void PKB::updateAllTables() {
	std::vector<std::tuple<string, string, int>> AllCallsStmt = ProcTable::getCallsTable();
	int allCallsStmtSize = AllCallsStmt.size() - 1;
	for (int i = allCallsStmtSize; i >= 0 ; i--) {
		string procB = get<1>(AllCallsStmt[i]);
		int tempStmtLine = get<2>(AllCallsStmt[i]);

		vector<int> tempParent = stmtTable::getParent(tempStmtLine);

		for (int z = 0; z < tempParent.size(); z++) {
			cout << "tempStmtLine :: " << tempStmtLine << "  tempParent :: " << tempParent.size() << endl;
		}

		for (int j = 0; j < tempParent.size(); j++) {

			vector<string> tempModifies = ProcTable::getProcModifiesVar(procB);
			for (int i = 0; i < tempModifies.size(); i++) {
				VarTable::addDataToModifies(tempModifies[i], tempStmtLine);
				VarTable::addDataToModifies(tempModifies[i], tempParent[j]);
			}

			vector<string> tempUses = ProcTable::getProcUsesVar(procB);
			for (int i = 0; i < tempUses.size(); i++) {
				VarTable::addDataToUses(tempUses[i], tempStmtLine);
				VarTable::addDataToUses(tempUses[i], tempParent[j]);
			}

		}
	}
	stmtTable::printParent();
	VarTable::sortVarLeftAndRight();
}

vector<string> splitTheString(string line) {
	vector<string> v;
	istringstream buf(str);

	for (string word; buf >> word;) {
		v.push_back(word);
	}

	return v;
}

void stmtLineForPattern(vector<string> line) {
	std::string result;

	for (auto const& s : line) {
		if (s.compare(";") != 0 || s.compare("}") != 0) {
			result = result + " " + s;
		}
	}

	VarTable::addDataToAssignTable(result, stmtLine);
}

// option: 0 -> only bracket, 1 -> with variable
void detectRightBracket() {
	int currentParrentLine;
	pair<string, int> temp = bracstack.top();
	int tempStmtNum = stmtLine;

	if (temp.second > 0 && temp.second != 0) {
		currentParrentLine = temp.second;
	}

	if (temp.second > 0) {
		vector<string> tempArrayListLeft = VarTable::findVariableLeft(temp.second, tempStmtNum);

		for (int i = 0; i < tempArrayListLeft.size(); i++) {
			VarTable::addDataToModifies(tempArrayListLeft[i], temp.second);
		}

		vector<string> tempArrayListRight = VarTable::findVariableRight(temp.second, tempStmtNum);

		for (int i = 0; i < tempArrayListRight.size(); i++) {
			VarTable::addDataToUses(tempArrayListRight[i], temp.second);
		}
	} else {
		vector<string> tempArrayListLeft = VarTable::findVariableLeft(currentParrentLine, tempStmtNum);

		for (int i = 0; i < tempArrayListLeft.size(); i++) {
			VarTable::addDataToModifies(tempArrayListLeft[i], currentParrentLine);
		}

		vector<string> tempArrayListRight = VarTable::findVariableRight(currentParrentLine, tempStmtNum);

		for (int i = 0; i < tempArrayListRight.size(); i++) {
			VarTable::addDataToUses(tempArrayListRight[i], currentParrentLine);
		}
	}
}

void PKB::abort() {
	exit(-1);
}

// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

// check string is a number
bool PKB::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}
