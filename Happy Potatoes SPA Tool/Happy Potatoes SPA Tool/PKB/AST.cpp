#include "./Header/AST.h"

AST::AST()
{
}

AST::~AST()
{
}

TNode getFirstChild();
void setFirstChild(TNode P, TNode C);
TNode createTNodeProc();
TNode getTNodeProc();
void setAsRoot(TNode);
TNode createTNodeStmtLst();
TNode getTNodeStmtLst();