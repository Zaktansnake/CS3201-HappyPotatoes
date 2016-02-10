#ifndef Parser_h
#define Parser_h

#pragma once
#include <string>
#include <map>
#include <memory>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class PKB;

class Parser {

private:
	static bool is_file_empty(ifstream file);
	static bool is_file_exist(string file);

public:
	static TNode* program();
	static int getToken();
	static int match(int token);
	static TNode* procedure();
	static TNode* stmtLst();
	static TNode* stmt();
	static VarTable* varTable;
	static void parse(string filename);

};


#endif