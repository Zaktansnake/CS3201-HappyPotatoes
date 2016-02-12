#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef vector<string> PROC;
typedef vector<string> VAR;
typedef vector<int> STMT;
typedef int PROG_LINE;

class TNode;
class GNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer
class ProcTable;

class PKB {
private:


public:

	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST(PROC p);
	static int setProcToCFG(PROC p, GNode* g);

	static void create(string fileName);


private:
	
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


};