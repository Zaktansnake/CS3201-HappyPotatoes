#pragma once

class TNode;

class AST
{
public:
	AST();
	~AST();
	static TNode* getParent();
	static void setParent();
	TNode getFirstChild();
	void setFirstChild(TNode P, TNode C);
	TNode createTNodeProc();
	TNode getTNodeProc();
	void setAsRoot(TNode);
	TNode createTNodeStmtLst();
	TNode getTNodeStmtLst();
};

