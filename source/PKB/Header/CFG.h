#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;
class CFG
{
public:
	// constructors
	CFG();
	~CFG();

	static void addRoot (std::string root);
	static void addNextNode (int stmtNo, string stmt);

	static int getChildNode (int stmtNo);
	static int getParentNode (int stmtNo);
	static int getLeftNode (int stmtNo);
	static int getRightNode (int stmtNo);

private : 
    bool isConditions (string stmt);
	void countCloseLoop (string stmt);
};