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

	static void addRoot (std::string root, int stmtNo);
	static void addNextNode (int stmtNo, string stmt);

	
	static vector<int> getNext (int stmtNo);
	static vector<int> getPrev (int stmtNo);
	static bool isNext (int stmtNo1, int stmtNo2);

private : 
    bool isConditions (string stmt);
	void countCloseLoop (string stmt);
};