#pragma once

class TNode;

class AST
{
public:
	AST();
	~AST();
	static TNode* getParent();
	static void setParent();
	static TNode* getFirstChild();
	static void setFirstChild(TNode P, TNode C);
	static TNode* createTNodeProc();
	static TNode* getTNodeProc();
	static void setAsRoot(TNode);
	static TNode* getRoot();
	static TNode* createTNodeStmtLst();
	static TNode* getTNodeStmtLst();

};

