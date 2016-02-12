#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <algorithm>
#include <locale>  
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "./Header/PKB.h"
#include "./Header/TNode.h"

using namespace std;

static ifstream myFile;
static string str;

static void program();
static void procedure();
static void stmtLst();
static void assign();
static void calls();
static void stmt();

static void findMethod(string file_contents);
vector<string> split(string str, char delimiter);
bool is_number(const std::string& s);
static void getNextWord();

// Create AST node
void create(string fileName) {
	program();
	myFile.open(fileName);
	while (myFile >> str) {
		findMethod(str);
	}
	myFile.close();
}

void findMethod(string file_contents) {

	if (file_contents.compare("procedure") == 0) {
		procedure();
	} else if (file_contents.compare("if") == 0) {
		stmtLst();
	} else if (file_contents.compare("else") == 0) {
		stmtLst();
		getNextWord();
		if (str.compare("{") != 0){
			throw std::runtime_error("Error: wrong Structure");
		} else {
			getNextWord();
			findMethod(str);
		}
	}else if (file_contents.compare("calls") == 0) {
		calls();
	} else if (file_contents.compare("while") == 0) {
		stmt();
	}
	else {
		// add myFile.getLine();
		// ammend??
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
}

void procedure() {
	TNode* proc;
	getNextWord();
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
		// proc = new TNode(PROCEDURE, procIdx);  // insert name to node
		// TNode* stmtLst
	getNextWord();
	if (str.compare("{") == 0) {
		// set first child
		getNextWord();
		findMethod(str);
	}

}

void stmtLst() {
	TNode* stmtLst;
	stmt();
	if (str.compare(";")) {
		//continue
	}
}

void assign() {
	/* while (getNextWord() && str.compare("}") == 0) {
	nextNode = stmt();
	curNode->setRightSibling(nextNode);
	curNode = nextNode;
	}
	*/
}

static void calls() {
	// save procedure name, stmt #
}

static void stmt() {
	TNode* stmt;
	enum tokenType {
		TIF = 0,
		TELSE,
		TWHILE,
		TCALL,
	};

	int line = 0;

	switch (line) {
	case 0:
		// TNode *stmtLst, *curNode, *nextNode;
		getNextWord();
		// stmtLst = new TNode(str);
		// set x:variable
		// add to VarTable
		// set then node
		getNextWord();
		if (str.compare("then")) {
			// assign node
			getNextWord();
			if (str.compare("{")) {
				getNextWord();
				findMethod(str);
			}
		}
		else {
			throw std::runtime_error("Error: then");
		}

		//curNode = stmt();
		//stmtLst->setFirstChild(curNode);

		break;
	case 1: // else
		if (str.compare("{")) {
			getNextWord();
			findMethod(str);
		}
		break;
	case 2: // while
		if (str.compare("{")) {
			getNextWord();
			findMethod(str);
		}
		case 3: // call
			calls();
			break;
	}

}


// is number
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}

void getNextWord() {
	str = myFile.get();
}
