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
	/*
	// AST
	// CFG
	GNode getNext();
	void setNext();
	GNode getPred();
	void setPred();
	GNode getSuccessor();
	void setSuccessor();


	// USES
	bool isUses(VAR var, STMT stmt);
	bool isUses(VAR var, PROC proc);

	// return variables that used in stmtlist
	VAR getUses(STMT stmt);

	// return variables that used in procedure
	VAR getUses(PROC proc);

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
	std::vector<string> getParent(STMT stmt);

	// get the child stmt
	std::vector<string> getChild(STMT stmt);

	// record the parent relationship between two stmtlst
	void setParent(STMT stmt1, STMT stmt2);

	//FOLLOWS
	// check whether stmt1 is follow stmt2
	bool isFollow(STMT stmt1, STMT stmt2);

	//set follow relationship between stmt1 and stmt2
	void setFollow(STMT stmt1, STMT stmt2);

	// return a statmentlist that followed by stmt
	std::vector<int> getFollower(STMT stmt);

	// return a statmentlist that stmt followed 
	std::vector<int> getFollow(STMT stmt);

	//CALLS
	// return the procedure set that called by proc
	std::vector<string> getCalls(PROC proc);

	// set the call relationship between proc1 and proc2
	void setCalls(PROC proc1, PROC proc2);

	// return true proc1 calls proc2 otherwise, false
	bool isCalls(PROC proc1, PROC proc2);

	// Modifies

	// return true is Modifies(var, stmt) otherwise, false
	bool isModified(VAR var, STMT stmt);

	// return true is Modifies(var, proc) otherwise, false
	bool isModified(VAR var, PROC proc);
	std::vector<string> getModifies(STMT stmt);
	std::vector<string> getModifies(PROC proc);
	// std::vector<int> getModifies (VAR var);
	std::vector<string> getModifies(VAR var);

	//record Modifies(STMT, var)
	void setModifies(STMT stmt, VAR var);

	//record Modifies(PROC var);
	void setModifies(PROC proc, VAR var);

	//Next
	// return true is Next(l1, l2) otherwise, false
	bool isNext(PROG_LINE l1, PROG_LINE l2);

	// return the next program line of l
	int getNext(PROG_LINE l);

	// Record Next(l1, l2)
	void setNext(PROG_LINE l1, PROG_LINE l2);


	//Affect
	//return true if Affect(stmt1, stmt2) otherwise, false
	bool isAffect(STMT stmt1, STMT stmt2);

	//return a set of stmtlst that Affect(stmt1, _)
	std::vector<int> getAffect(STMT stmt1);

	//return a set of stmtlst that Affect(_,stmt1)
	std::vector<int> getAffected(STMT stmt1);

	//VARTABLE

	//PROCTABLE

	// PATTERNS

	*/

public:
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
	static int setProcToCFG (PROC p, GNode* g);

	static void create(string fileName);

};