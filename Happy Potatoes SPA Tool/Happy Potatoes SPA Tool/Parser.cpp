#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "PKB.h"
#include "TNode.h"
#include "Parser.h"

static ifstream myFile;
static int next_token;
static string line;

void Parser::parse(string filename)
{
	if (is_file_exist(filename)) {
		myFile.open(filename);
		if (!myFile.fail()){
			
		}
	} else {
		if (myFile.is_open()) {
			myFile.close();
		}
	}
}

int getToken() {
	// Reads and returns a token.
	int token = 0;
	char c = 0;

	switch (token) {
	case 0:
		break;
	default:
	
	}

	return 0;
}

int match(int token) {
	if (next_token == token) {
		getToken();
	} else {
		// throw exception
		//throw ParseException("Error in matching.");
		return -1;
	}
}

void program(int token) {
	next_token = getToken();
	//procedure();
	//buildCFG();
}

void procedure() {
	//Match(¡°procedure¡±)
	//Match(proc_name)
	//Match(¡°{ ¡±)
	//StmtLst()
	//Match(¡° }¡±)
}

void stmtLst() {
	// Proceed Stmt()
	// Match(¡°; ¡±),
	// If(next_token = ¡°
	// }¡±) stop.
	// Otherwise, StmtLst().
}

void stmt() {
	// Match(var_name)
	// Match(¡° = ¡±)
	// Match(var_name or const_value)
}

int parseExp(string exp) {
	// If ¡°token¡± is matched, GetExp().
	// Otherwise, returns - 1 (special value).
}

void ERecognizer(string exp) {
	// E()
	// parseExp(exp)
}

// detect file exists
bool is_file_exist(string name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

// detect file is empty
bool is_file_empty(ifstream file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

