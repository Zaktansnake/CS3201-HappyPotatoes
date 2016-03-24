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

	
	static int getNext (int stmtNo);
	static int getPrev (int stmtNo);
	static int isNext (int stmtNo1, int stmtNo2);

private : 
    bool isConditions (string stmt);
	void countCloseLoop (string stmt);
};