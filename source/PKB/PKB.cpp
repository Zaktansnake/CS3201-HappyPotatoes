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

#include "./Header/PKB.h"
#include "./Header/ProcTable.h"
#include "./Header/VarTable.h"
#include "./Header/stmtTable.h"

using namespace std;

static ifstream myFile;
static string str, word, procname;
static ostringstream oss;
stack<pair<string, int>> bracstack;
bool firstTime, firstLine;
static int stmtLine = 0;

static void program();
static void procedure();
static void stmtLst();
static void assign();
static void calls(string procedureName);
static void stmt(int num);

static void findMethod(string file_contents);
vector<string> split(string str, char delimiter);
vector<string> splitTheString(string line);
bool is_number(const std::string& s);
static void calls(string procedurName, int stmtLine);
void stmtLineForPattern(vector<string> line);
void detectRightBracket(int options, vector<string> v);

void PKB::create(string fileName) {
	firstTime = true;
	firstLine = true;
	program();
	myFile.open(fileName);
	stmtLine = 0;
	while (!myFile.eof()) {
		getline(myFile, str);
		findMethod(str);
		if (stmtLine > 0) {
			//stmtTable::addStmtTable(str, stmtLine);
		}
		stmtLine++;
	}
	myFile.close();

	// parse the assign table to Patterns

	// update uses table one more time
}

int PKB::getStmtNum() {
    return stmtLine;
}

void findMethod(string file_contents) {

	istringstream iss(file_contents);
	if (file_contents.compare("") != 0) {
		iss >> word; // get the first word
		oss << iss.rdbuf(); // get the remain words
	} else {
		word = "";
	}

	if (firstLine) {
		if (word.compare("procedure") != 0) {
			cout << "Error: Structure. (procedure)" << endl;
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
		|| (word.compare("calls") == 0) || (word.compare("while") == 0)) {
		stmtLst();
	}
	else if (word.compare("") == 0) {
		if (!bracstack.empty()) {
			cout << "Error: Structure." << endl;
		}

		if (stmtLine > 0) {
			stmtLine--;
		}

		firstTime = false;
	}
	else if (word.compare("}") == 0) {
		stmtLine--;
		vector<string> ans;
		detectRightBracket(0, ans);
	} else {
		// save them into 2d array, pass to pql, to build tree
		assign();
	}
}

void program() {

}

void procedure() {
	vector<string> v = splitTheString(str);

	if (v.size() > 3) {
		cout << "Error: Structure." << endl;
	}

	if (ProcTable::isContains(v[1])) {
		cout << "Error: Duplication of Procedure Name." << endl;
	}
	else {
		ProcTable::addTableData(v[1], stmtLine);
		procname = v[1];
		if (v[2].compare("{") != 0) {
			cout << "Error: Structure." << endl;
		}
		else {
			bracstack.push(make_pair("{", 0));
		}
		
		if (stmtLine > 0) {
			stmtLine--;
		}
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

void assign() {
	string lineWithVar = str;
	vector<string> v;
	int ln = str.length() - 1;
	for (int n = 0; n <= ln; n++) {
		string letter(1, lineWithVar[n]);
		if (letter.compare(" ") != 0) {
			v.push_back(letter);
		}
	}

	stmtLineForPattern(v);

	for (int i = 0; i < v.size(); i++) {
		std::string var = v.at(i);

		if (var.compare("}") == 0) {
			//detectRightBracket(1, v);
			bracstack.pop();
		} else if (!is_number(var)) {
			if (i == 0) {
				VarTable::addDataToModifies(var, stmtLine);
				VarTable::addModifiesProcTable(procname, v[i]);
			} else if (var.compare("=") == 0 || var.compare("+") == 0 || var.compare("-") == 0 || var.compare(";") == 0 || var.compare("*") == 0){
				
			} else {
				VarTable::addDataToUses(var, stmtLine);
				VarTable::addUsesProcTable(procname, v[i]);
			}
		}
	}
}

static void stmt(int num) {
	vector<string> v = splitTheString(str);

	switch (num) {
	case 0: // if
		if (v[2].compare("then") == 0 && (v[3].compare("{")) == 0) {
			VarTable::addDataToUses(v[1], stmtLine);
			bracstack.push(make_pair("{", stmtLine));
		}
		else {
			cout << "Error: Structure. (then)" << endl;
		}
		break;
	case 1: // else
		stmtLine--;
		if (v[1].compare("{") != 0) {
			cout << "Error: Structure. ({)" << endl;
		}
		else {
			bracstack.push(make_pair("{", stmtLine));
		}
		break;
	case 2: // while
		if (v[2].compare("{") == 0) {
			VarTable::addDataToModifies(v[1], stmtLine);
			bracstack.push(make_pair("{", stmtLine));
			VarTable::addDataToWhileTable(v[2],stmtLine);
		}
		else {
			cout << "Error: Structure. ({)" << endl;
		}
		break;
	case 3: // call
		calls(str, stmtLine);
		break;
	}
}

static void calls(string str, int stmtLine) {
	vector<string> v = splitTheString(str);
	string procName = v[1].substr(0, v[1].size() - 1);
	ProcTable::addTableData(procName, stmtLine);
	// save procedure name, stmt #
	if (v.size() > 3) {
		//create a loop iterate all the [i]
		for (int i = 2; i < v.size(); i++) {
			if (i == 2) {
				if (v[2].compare("}") == 0) {
					bracstack.pop();
				}
			}
		}
	} else {
		//throw std::runtime_error("Error: Structure");
	}
}

// check string is a number
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}

vector<string> splitTheString(string line) {
	vector<string> v;
	istringstream buf(str);
	for (string word; buf >> word; )
		v.push_back(word);

	return v;
}

void stmtLineForPattern(vector<string> line) {
	std::string result;
	for (auto const& s : line) {
		if (s.compare(";") || s.compare("}")) {
			break;
		} else {
			result += s;
		}
	}

	VarTable::addDataToAssignTable(result, stmtLine);
}

// option: 0 -> only bracket
//			1 -> with variable
void detectRightBracket(int option,  vector<string> v) {
	pair<string, int> temp = bracstack.top();
	int tempStmtNum = stmtLine;

	if (option == 0) {
		tempStmtNum = tempStmtNum - 1;
	}

	if (temp.second != 0) {
		vector<string> tempArrayListLeft = VarTable::findVariableLeft(temp.second, tempStmtNum);

		for (int i = 0; i < tempArrayListLeft.size(); i++) {
			VarTable::addDataToModifies(tempArrayListLeft[i], temp.second);
		}

		if (option == 1) {
			// if "{" is same line with assign line
			VarTable::addDataToModifies(v[0], temp.second);
		}

		vector<string> tempArrayListRight = VarTable::findVariableRight(temp.second, tempStmtNum);

		for (int i = 0; i < tempArrayListRight.size(); i++) {
			VarTable::addDataToUses(tempArrayListRight[i], temp.second);
		}

		bracstack.pop();
	}
}