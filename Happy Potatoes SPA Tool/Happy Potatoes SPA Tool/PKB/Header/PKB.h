#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;
typedef basic_string<char> VAR;

class TNode;
class GNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer
class ProcTable;

class PKB {
private:
	// AST

	// get the Parent node
	TNode getParent();

	//set current node as parent node
	void setParent();

	//get first child
	TNode getFirstChild();

	//set the current node as child
	void setFirstChild(TNode p, TNode c);

	// create AST node for procedure 
    void createTNodeProc();

	// get TNode for procedure
	TNode getTNodeProc();

	//set TNode as root of AST
	void setAsRoot(TNode node);

	//create TNode statement
	void createTNodeStmtLst();
	// get the stmtlst() of Tnode
	TNode getTNodeStmtLst();



	// CFG
	GNode getNext();

	void setNext();

	GNode getPred();

	void setPred ();

	GNode getSuccessor();

	void setSuccessor();


	// USES
	bool isUses(VAR var, stat st);

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