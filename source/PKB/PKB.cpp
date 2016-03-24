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
#include "./Header/PatternTable.h"
#include "Header\CFG.h"

using namespace std;

static ifstream myFile;
static string str, word, procname;
static ostringstream oss;
stack<pair<string, int>> bracstack; // string -> {; int -> currentStmtLine
stack<int> ifStmtNum, afterElseStmtNum;
bool firstTime, firstLine;
static int stmtLine = 0, afterElseStartNum = 0; // ifParentStmtNum -> very first "if" stmtNum
static string tempLine;
	
static void procedure();
static void stmtLst();
static void assign();
static void calls(string procedureName);
static void stmt(int num);

void getProgramLine(string lineFromSource);
static void findMethod(string file_contents);
vector<string> split(string str, char delimiter);
vector<string> splitTheString(string line);
static void calls(string procedurName, int stmtLine);
void stmtLineForPattern(vector<string> line);
void detectRightBracket();
vector<int> getAllParents(vector<int> v);
static inline std::string &ltrim(std::string &s);
static inline std::string &rtrim(std::string &s);
static inline std::string &trim(std::string &s);

int PKB::getStmtNum() {
	return stmtLine - 1;
}

void PKB::create(string fileName) {
	firstTime = true;
	firstLine = true;
	myFile.open(fileName);
	stmtLine = 0;

	while (!myFile.eof()) {
		getline(myFile, str);
		getProgramLine(str);
	}

	myFile.close();
	PKB::updateTables();
	
}

void findMethod(string lineFromSample) {

	str = lineFromSample;
	if (str.find("{") != std::string::npos) {
		str = trim(str.erase(str.size() - 1));
		if (str.find("{") == std::string::npos) {
			str = str + " {";
		}
	}

	istringstream iss(trim(str));

	if (str.compare("") != 0) {
		iss >> word; // get the first word
		oss << iss.rdbuf(); // get the remain words
	}

	if (firstLine) {
		if (word.compare("procedure") != 0) {
			cout << "Error: Structure. (procedure)" << endl;
			PKB::abort();
		}
		firstLine = false;
		firstTime = false;
	}

	if (word.compare("procedure") == 0) {
		if (!firstTime && stmtLine > 0) {
			if (!bracstack.empty()) {
				cout << "Error: Structure. (backStack problem)" << endl;
				PKB::abort();
			}
			afterElseStartNum = 0;
			stmtLine--;
		}
		procedure();
		stmtTable::setProcedure(str, stmtLine);
	}
	else if (word.compare("if") == 0 || word.compare("else") == 0 || word.compare("call") == 0 || word.compare("while") == 0) {
		stmtLst();
		stmtTable::addStmtTable(str, stmtLine);
	}
	else if (word.compare("}") == 0 || str.find("}") != std::string::npos) {
		vector<string> ans;
		if (str.find("else") != std::string::npos) {
			stmt(1);
			stmtTable::addStmtTable(str, stmtLine);
		}
		else {
			stmtLine--;
			string lineWithVar = str;
			int ln = str.length() - 1;
			for (int n = 0; n <= ln; n++) {
				string letter(1, lineWithVar[n]);
				if (letter.compare("}") == 0) {
					detectRightBracket();
					bracstack.pop();
					stmtTable::addStmtTable(letter, stmtLine);
				}
			}
		}
	}
	else {
		assign();
		stmtTable::addStmtTable(str, stmtLine);
	}

	stmtLine++;
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
			ifStmtNum.push(stmtLine);
			bracstack.push(make_pair("{", stmtLine));
		}
		else {
			cout << "Error: Structure. (then)" << endl;
			PKB::abort();
		}

		break;
	case 1: // else
		stmtLine--;
		if (v.size() <= 3) {
			if (v.size() == 3) {
				if (v[0].compare("}") != 0 && v[2].compare("}") != 0) {
					cout << "Error: Structure. ({)" << endl;
					PKB::abort();
				}
				vector<string> ans;
				detectRightBracket();
				bracstack.pop();
			}
			else if (v.size() == 2) {
				if (v[1].compare("{") != 0) {
					cout << "Error: Structure. ({)" << endl;
					PKB::abort();
				}
			}
			bracstack.push(make_pair("{", -2));
			afterElseStartNum = stmtLine + 1;
			afterElseStmtNum.push(afterElseStartNum);

			break;
		}
		else {
			cout << "Error: Structure. else" << endl;
			PKB::abort();
		}
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
					if (!PKB::is_number(var)) {
						VarTable::addDataToUses(var, stmtLine);
						ProcTable::setProcUsesVar(procname, v[i]);
					}
					else {
						//upadate to ConstantTable(var, stmtLine)
					}
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
	VarTable::updateModifiesUsesTables();
	ProcTable::updateProcCallsTables();
	PKB::updateAllTables();
	PatternTable::updatePatternTable();

	VarTable::printTables();

	//stmtTable::printParent();
	//PatternTable::getPatternAssignNum("_","_\"x+y+1\"_");
	//PatternTable::getPatternAssignNum("Romeo", "\"Romeo-1\"");
	//PatternTable::getPatternAssignNum("Romeo", "\"Romeo\"");
}

void PKB::updateAllTables() {

	std::vector<std::tuple<string, string, int>> AllCallsStmt = ProcTable::getCallsTable();
	int allCallsStmtSize = AllCallsStmt.size() - 1;
	for (int i = allCallsStmtSize; i >= 0 ; i--) {
		string procB = get<1>(AllCallsStmt[i]);
		int tempStmtLine = get<2>(AllCallsStmt[i]);

		vector<int> getAllParent = getAllParents(stmtTable::getParent(tempStmtLine));
		if (getAllParent.size() > 0) {
			for (int j = 0; j < getAllParent.size(); j++) {
				vector<string> tempModifies = ProcTable::getProcModifiesVar(procB);
				for (int i = 0; i < tempModifies.size(); i++) {
					VarTable::addDataToModifies(tempModifies[i], tempStmtLine);
					if (getAllParent[j] != 0) {
						VarTable::addDataToModifies(tempModifies[i], getAllParent[j]);
					}
				}

				vector<string> tempUses = ProcTable::getProcUsesVar(procB);
				for (int i = 0; i < tempUses.size(); i++) {
					VarTable::addDataToUses(tempUses[i], tempStmtLine);
					if (getAllParent[j] != 0) {
						VarTable::addDataToUses(tempUses[i], getAllParent[j]);
					}
				}
			}
		}
		else {
			vector<string> tempModifies = ProcTable::getProcModifiesVar(procB);
			for (int i = 0; i < tempModifies.size(); i++) {
				VarTable::addDataToModifies(tempModifies[i], tempStmtLine);
			}
			vector<string> tempUses = ProcTable::getProcUsesVar(procB);
			for (int i = 0; i < tempUses.size(); i++) {
				VarTable::addDataToUses(tempUses[i], tempStmtLine);
			}
		}
	}
	VarTable::sortVarLeftAndRight();
}

vector<int> getAllParents(vector<int> v) {
	vector<int> toReturn;
	while (v.size() != 0) {
		toReturn.push_back(v.at(0));
		v = stmtTable::getParent(v.at(0));
	}
	return toReturn;
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

void detectRightBracket() {
	int currentParentLine = 0;
	pair<string, int> temp = bracstack.top();
	int tempStmtNum = stmtLine;

	if (temp.second > 0 && temp.second != 0) {
		currentParentLine = temp.second; // if stmtNum 
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
		if (ifStmtNum.size() > 0 && afterElseStmtNum.size() > 0) {
			int currentIfStmtNum = ifStmtNum.top(); // current parent of "if" stmtNum
			int currentElseFirstStartNum = afterElseStmtNum.top(); //current "else" first start num
			vector<string> tempArrayListLeft = VarTable::findVariableLeft(currentElseFirstStartNum, tempStmtNum);
			vector<string> tempArrayListRight = VarTable::findVariableRight(currentElseFirstStartNum, tempStmtNum);
			if (tempArrayListLeft.size() > 0 && tempArrayListRight.size() > 0) {
				for (int i = 0; i < tempArrayListLeft.size(); i++) {
					if (currentParentLine != 0) {
						VarTable::addDataToModifies(tempArrayListLeft[i], currentParentLine);
					}
					VarTable::addDataToModifies(tempArrayListLeft[i], currentIfStmtNum);
				}

				for (int i = 0; i < tempArrayListRight.size(); i++) {
					if (currentParentLine != 0) {
						VarTable::addDataToUses(tempArrayListRight[i], currentParentLine);
					}
					VarTable::addDataToUses(tempArrayListRight[i], currentIfStmtNum);
				}
			}

			ifStmtNum.pop();
			afterElseStmtNum.pop();
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

void getProgramLine(string lineFromSource) {

	if (lineFromSource.compare("") != 0) {
		// found ";" "{" "}"
		if (lineFromSource.find_last_of("{") != std::string::npos) {
			if (lineFromSource.find("}") != std::string::npos) {
				if (lineFromSource.find("else") != std::string::npos) {
					findMethod(lineFromSource);
				}
				else {
					std::size_t found;
					if (lineFromSource.find("while") != std::string::npos) {
						found = lineFromSource.find("while");
					}
					else if (lineFromSource.find("if") != std::string::npos) {
						found = lineFromSource.find("if");
					}
					string normalLine = lineFromSource.substr(found);
					findMethod("}");
					findMethod(normalLine);
				}
			}
			else {
				tempLine += lineFromSource;
				findMethod(tempLine);
				tempLine = "";
			}
		}
		else if (lineFromSource.find("}") != std::string::npos) {
			if (lineFromSource.find(";") != std::string::npos) {
				std::size_t foundSemiColon = lineFromSource.find(";");
				string normalLine = lineFromSource.substr(0, foundSemiColon + 1);
				string bracket = lineFromSource.substr(foundSemiColon + 1);
				findMethod(normalLine);
				findMethod(bracket);
			}
			else if (lineFromSource.find("else") != std::string::npos) {
				findMethod(lineFromSource);
			}
			else {
				findMethod(lineFromSource);
			}
		}
		else if (lineFromSource.find(";") != std::string::npos) {
			// calls or normal assignment statement
			findMethod(lineFromSource);
		}
		else {
			tempLine = lineFromSource + " ";
		}
	}
}