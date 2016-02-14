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
#include "./Header/Parser.h"

using namespace std;

static ifstream myFile;
static int next_token;
static string str;
static string file_contents;
static int statusFile;

static bool is_file_empty(ifstream file);
static bool is_file_exist(string file);
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

int Parser::parse(string fileName)
{
	if (is_file_exist(fileName)) {
		myFile.open(fileName);
		if (!myFile.fail()) {
			PKB::create(fileName);
			statusFile = 1;
		}
	}
	else {
		if (myFile.is_open()) {
			myFile.close();
		}
		statusFile = -1;
	}
	
	return statusFile;
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
