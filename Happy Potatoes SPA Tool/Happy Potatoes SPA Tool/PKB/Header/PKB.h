#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef vector<string> PROC;
typedef vector<string> VAR;
typedef vector<int> STMT;

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
	bool isUses(VAR var, STMT stmt);
	bool isUses(VAR var, PROC proc);

	// return variables that used in stmtlist
	VAR getUses(STMT stmt);

	// return variables that used in procedure
	VAR getUses(PROC proc);

	// return stmtlst that used this variable
	std::vector<string> getUses(VAR var);

	// return procedure that used this variable
	std::vector<string> getUses(VAR var);

	// record statmentlst use variable
	void setUses(STMT stmt, VAR var);

	//record procedures that use this variable
	void setUses(PROC proc, VAR var);




	// PARENTS
	// check whether stmt1 followed stmt2
	bool isParent(STMT stmt1, STMT stmt2);

	// get the parent statment
	std::vector<string> getParent (STMT stmt);

	// get the child stmt
	std::vector<string> getChild(STMT stmt);
	void setParent(STMT stmt1, STMT stmt2);

	//FOLLOWS

	bool isFollow(STMT stmt1, STMT stmt2);
	void setFollow(STMT stmt1, STMT stmt2);
	std::vector<int> getFollower(STMT stmt);
	std::vector<int> getFollow(STMT stmt);

	//CALLS



	//VARTABLE

	//PROCTABLE

	// PATTERNS

public:
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
	static int setProcToCFG (PROC p, GNode* g);

};