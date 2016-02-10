#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;

class TNode;
class GNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
private:
	// AST
	// CFG
	// USES
	// PARENTS
	//FOLLOWS
	//CALLS
	//VARTABLE
	//PROCTABLE
	// PATTERNS

public:
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
	static int setProcToCFG (PROC p, GNode* g);

};