#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer
class ProcTable;
class stmtTable;

class PKB {
public:

	static void create(string fileName);
	static int getStmtNum ();
	static bool is_number(const std::string& s);
	static void abort();

private:

	static void updateTables();
	static void updateAllTables();

};