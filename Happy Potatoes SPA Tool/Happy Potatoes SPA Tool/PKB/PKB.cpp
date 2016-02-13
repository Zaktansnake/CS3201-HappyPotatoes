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

#include "./Header/PKB.h"
#include "./Header/TNode.h"
#include "./Header/ProcTable.h"

using namespace std;

static ifstream myFile;
static string str, word;
static ostringstream oss;
stack<string> bracstack;
bool firstTime;

static void program();
static void procedure();
static void stmtLst();
static void assign();
static void calls(string procedureName);
static void stmt(int num);

static void findMethod(string file_contents);
vector<string> split(string str, char delimiter);
bool is_number(const std::string& s);

void PKB::create(string fileName) {
	firstTime = true;
	program();
	myFile.open(fileName);
	while (!myFile.eof()) {
		getline(myFile, str);
		cout << str << endl;
		findMethod(str);
	}
	myFile.close();
}

void findMethod(string file_contents) {

	istringstream iss(file_contents);
	iss >> word; // get the first word
	oss << iss.rdbuf(); // get the remain words

	if (word.compare("procedure") == 0) {
		if (!firstTime) {
			if (!bracstack.empty()) {
				throw std::runtime_error("Error: Structure");
			}
		}
		procedure();
		firstTime = false;
	} else if (word.compare("if") == 0 || word.compare("else") == 0 
		|| (word.compare("calls") == 0) || (word.compare("while") == 0)) {
		stmtLst();
	} else {
		// save them into 2d array, pass to pql, to build tree
		assign();
	}
}

void program() {
	TNode* program;
	/*TNode* program = new TNode(TPROGRAM); // set program
	TNode* firstProc = procedure();			// set first procedure
	program->setFirstChild(firstProc);		// program -> 1st Proc
	TNode* prevProc;
	while (next_token != EOF) {
	prevProc = currProc;					// build the lists
	prevProc->setRightSibling(procedure());  // find another procedures
	}*/
	//buildCFG();
	//checkCalls();
}

void procedure() {
	TNode* proc;
	string str = oss.str();
	istringstream iss{ str };

	// if ProcTable contains value
		// throw std::runtime_error("Error: Duplication of Procedure Name");
		/*if (ProcTable::getProcTable()->getProcIndex(temp) != -1) {
		if (input.is_open()) {
		input.close();
		}
		PKBParser::cleanUp();
		}*/
		// else
			// add to ProcTable
			// int procIdx = ProcTable::getProcTable()->insertProc(temp);
			// TNode* proc;
			// proc = new TNode(procIdx, PROCEDURE_NAME);  // insert name to node
			// create TNode* stmtLst
	oss << iss.rdbuf(); // get the remain words
	if (oss.str().compare("{") != 0) {
		throw std::runtime_error("Error: Structure");
	} else {
		bracstack.push("{");
	}
}

void stmtLst() {
	TNode* stmtLst;
	int num = 0;
	if (word.compare("if") == 0) {
		num = 0;
	} else if (word.compare("else") == 0) {
		num = 1;
	} else if (word.compare("while") == 0) {
		num = 2;
	} else if (word.compare("call") == 0) {
		num = 3;
	}
	stmt(num);

}

void assign() {
	// save them to a table
	vector<string> v;
	istringstream buf(str);
	for (string word; buf >> word; )
		v.push_back(word);

	for (int i = 0; i < v.size(); i++) {
		std::string var = v.at(i);
		if (isalpha(var.at(i))) {
			// check whether exists
			// save to varTable
		} else if (v[i].compare("}")) {
			bracstack.pop();
		}
	}
}

static void stmt(int num) {
	TNode* stmt;
	vector<string> v;
	istringstream buf(oss.str());
	for (string word; buf >> word; )
		v.push_back(word);

	switch (num) {
	case 0:
		// TNode *stmtLst, *curNode, *nextNode;
		// stmtLst = new TNode(str);
		// set v[0]
		// add to VarTable
		// set then node
		if (v[1].compare("then") == 0 && (v[2].compare("{")) == 0) {
			// assign node
			bracstack.push("{");
		}
		else {
			throw std::runtime_error("Error: then");
		}
		//curNode = stmt();
		//stmtLst->setFirstChild(curNode);

		break;
	case 1: // else
		if (v[0].compare("{") != 0) {
			throw std::runtime_error("Error: Structure");
		} else {
			bracstack.push("{");
		}
		break;
	case 2: // while
		if (v[1].compare("{") == 0) {
			// v[0]-> varTable
		} else {
			bracstack.push("{");
		}
		break;
	case 3: // call
		calls(v[0]);
		break;
	}
}

static void calls(string procedurName) {
	// save procedure name, stmt #
	ProcTable::addTableData(procedurName);
}

// is number
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}

bool lettersOnly(std::string text)
{
	for (int i = 0; i<text.length(); i++)
	{
		if (!isalpha(text.at(i)))
			return false;
	}
	return true;
}