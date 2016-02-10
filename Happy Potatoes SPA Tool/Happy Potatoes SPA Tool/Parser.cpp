#pragma once

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <locale>  
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "PKB.h"
#include "TNode.h"
#include "Parser.h"

static ifstream myFile;
static istream in;
static int next_token;
static string text;

enum tokenType {
	TPROGRAM = 0,
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
	TCALL
};


void Parser::parse(string filename)
{
	if (is_file_exist(filename)) {
		myFile.open(filename);
		if (!myFile.fail()){
			procedure();
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

	while (in>>c) {
		if (c == '}') break;
		text += c;
	}

	in >> line;

	if (!in) throw std::runtime_error("readValue: can't parse integer");

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
		} else {
		
		}
		break;
	}

	return 0;
}

int match(int token) {
	if (next_token == token) {
		getToken();
	} else {
		// throw exception
		throw std::runtime_error("Error: Matching");
		return -1;
	}
}

void program(int token) {
	next_token = getToken();
	procedure();
	//buildCFG();
}

void procedure() {
	match(TPROCEDURE);
	match(TPNAME);
	match(TLBRAC);
	stmtLst();
	match(TRBRAC);
}

void stmtLst() {
	stmt();
	match(TSEMICOLON);
	if (next_token == TRBRAC) {
		return;
	} else {
		stmtLst();
	}
}

void stmt() {
	match(TVARNAME);
	match(TEQUAL);
	match(TVARNAME|TCONSTANT);
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

// is number
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}
