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


	static void CFG::addRoot (string root, int stmtNo);
	static void CFG::addNextNode (int stmtNo, string stmt);
	static void CFG::reverCFG ();

	
	static vector<int> getNext (int stmtNo);
	static vector<int> getPrev (int stmtNo);
	static bool isNext (int stmtNo1, int stmtNo2);
	static bool isNextStar (int stmtNo1, int stmtNo2);
	static vector<int> getNextStar( int stmtNo);
	static vector<int> getPrevStar (int stmtNo);

	static vector<string> getNextString(int stmtNo);
	static vector<string> getPrevString(int stmtNo);
	static vector<string> getNextStarString(int stmtNo);
	static vector<string> getPrevStarString(int stmtNo);
	
private : 
    bool checkConditions (string stmt);
	void countCloseLoop (string stmt);
	

};