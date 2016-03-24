#pragma once

#include <string>
#include <map>
#include "PKB.h";

using namespace std;

class Parent
{
public:
	// constructors
	Parent();
	~Parent();

	void setParent(string stmtLine, int stmtNo, int nestLevel, bool loopFlag, int endLopp, int condition);
	std::vector<int> getParent(int stmtNo);
	std::vector<int> getParentStar(int stmtNo);  // to get all its parents
	std::vector<int> getChild(int stmtNo);

	std::vector<int> Parent::getParentForWhile(int stmtNo);
	std::vector<int> Parent::getChildForWhile(int stmtNo);
	std::vector<int> Parent::getParentForAssign(int stmtNo);
	std::vector<int> Parent::getChildForAssign(int stmtNo);
	std::vector<int> Parent::getParentForIf(int stmtNo);
	std::vector<int> Parent::getChildForIf(int stmtNo);

	bool isParent(int stmt1, int stmt2);

	static std::map<int, int> AnsMap;
	static std::map<int, vector<int>> AnsStarMap;




	// print out the call answer table
//	void PrintProcTable();
};