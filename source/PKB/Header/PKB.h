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

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer
class ProcTable;
class stmtTable;

class PKB {
public:

	static void create(string fileName);
	static int getStmtNum ();

	static void abort();

private:

};