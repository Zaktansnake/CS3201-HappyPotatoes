#pragma once

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <locale>  
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "./Header/PKB.h"
#include "./Header/TNode.h"
#include "./Header/Parser.h"

using namespace std;

static ifstream myFile;
static int next_token;
static string text;

static TNode* program();
static int getToken();
static int match(int token);
static TNode* procedure();
static TNode* stmtLst();
static TNode* stmt();
static VarTable* varTable;
static bool is_number(const std::string& s);

enum tokenType {
	TPROGRAM = 0, //main program
	TPROCEDURE, //"procedure"
	TPNAME, //proc_name
	TLBRAC, //"{"
	TRBRAC, //"}"
	TLRBRAC, //"("
	TRRBRAC, //")"
	TSEMICOLON,
	TEQUAL,
	TVARNAME,
	TCONSTANT, //const_value
	TIF,
	TELSE,
	TTHEN,
	TWHILE,
	TPLUS,
	TMINUS,
	TTIMES,
	TCALL,
	TASSIGN
};

void Parser::parse(string filename)
{
	if (is_file_exist(filename)) {
		myFile.open(filename);
		if (!myFile.fail()){
			program();
		}
	} else {
		if (myFile.is_open()) {
			myFile.close();
		}
	}
}

/* Reads and returns a token. */
int getToken() {
	int line = 0;
	// text.assign("")
	char c;
	string text;

	while (1) {

		try {
			c = myFile.get();
		}
		catch (ifstream::failure e) {
			//return TEOF;
		}

		switch (line) {
		case 0: //character
			if (text.compare("procedure") == 0) return TPROCEDURE;
			if (text.compare("if") == 0) return TIF;
			if (text.compare("else") == 0) return TELSE;
			if (text.compare("then") == 0) return TTHEN;
			if (text.compare("while") == 0) return TWHILE;
			if (text.compare("call") == 0) return TCALL;
			else throw std::runtime_error("Error: Matching");
			break;
		case 1: //symbol
			if (text.compare("{") == 0) return TLBRAC;
			if (text.compare("}") == 0) return TRBRAC;
			if (text.compare("+") == 0) return TPLUS;
			if (text.compare("-") == 0) return TMINUS;
			if (text.compare("*") == 0) return TTIMES;
			if (text.compare("=") == 0) return TEQUAL;
			if (text.compare(";") == 0) return TSEMICOLON;
			if (text.compare("(") == 0) return TLRBRAC;
			if (text.compare(")") == 0) return TRRBRAC;
			else throw std::runtime_error("Error: Matching");
			break;
		case 2: //digit
			if (!is_number(text)) {
				throw std::runtime_error("Error: Matching");
			}
			else {
				// text += c
			}
			break;
		}
	
	}

	return 0;
}

int match(int token) {
	if (next_token == token) {
		getToken();
	}
	else {
		// throw exception
		throw std::runtime_error("Error: Matching");
		return -1;
	}
}

TNode* program() {
	next_token = getToken();
	TNode* program = new TNode(TPROGRAM); // set program
	TNode* firstProc = procedure();			// set first procedure
	program->setFirstChild(firstProc);		// program -> 1st Proc
	TNode* prevProc;
	while (next_token != EOF) {
		prevProc = currProc;					// build the lists
		prevProc->setRightSibling(procedure());  // find another procedures
	}
	//buildCFG();
	//checkCalls();
	return program;
}

TNode* procedure() {
	//TNode* proc;
	match(TPROCEDURE);
	//string temp;
	//temp.assign(text);
	match(TPNAME);
	//check duplication of name
	//go to ProcTable, find the name
	// if is duplicated, clean procTable, throw error
	if (ProcTable::getProcTable()->getProcIndex(temp) != -1) {
		if (input.is_open()) {
			input.close();
		}
		PKBParser::cleanUp();
		throw std::runtime_error("Error: Duplication of Procedure Name");
	}
	//int procIdx = ProcTable::getProcTable()->insertProc(temp);
	proc = new TNode(PROCEDURE, procIdx);  // insert name to node
	// stmtLst
	// int root = StmtTable::getStmtTable()->getSize()+1;
	match(TLBRAC);
	// proc->setFirstChild(stmtLst()); // set first child
	match(TRBRAC);
	//CFG stuff
}

TNode* stmtLst() {
	// TNode *stmtLst, *curNode, *nextNode;
	// stmtLst = new TNode(STMTLST);
	//curNode = stmt();
	//stmtLst->setFirstChild(curNode);
	/* while (next_token != TRBRACE) {
		nextNode = stmt();
		curNode->setRightSibling(nextNode);
		curNode = nextNode;
	} 
	return stmtLst;
	*/
	match(TSEMICOLON);
	if (next_token == TRBRAC) {

	}
	else {
		stmtLst();
	}
}

TNode* stmt() {

	switch (next_token) {
	case TASSIGN:
		match(TVARNAME);
		match(TEQUAL);
		match(TVARNAME | TCONSTANT);
		break;
	case TCALL:
		match(TSEMICOLON);
		break;
	case TWHILE:
		break;
	case TIF:
		break;
	default:
		// throw error msg
	}
	return stmt;
}



// detect file exists
bool is_file_exist(string file) {
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}

// detect file is empty
bool is_file_empty(ifstream file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

// is number
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}


