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
	std::vector<string> getParentStar(int stmtNo);  // to get all its parents
	std::vector<string> getChildStar(int stmtNo);  // to get all its childs
	std::vector<int> getParentStarInt(int stmtNo);  // to get all its parents
	std::vector<int> getChildStarInt(int stmtNo);  // to get all its childs
	std::vector<int> getChild(int stmtNo);

	std::vector<string> Parent::getParentForWhile(int stmtNo);
	std::vector<string> Parent::getChildForWhile(int stmtNo);
	std::vector<string> Parent::getParentForAssign(int stmtNo);
	std::vector<string> Parent::getChildForAssign(int stmtNo);
	std::vector<string> Parent::getParentForIf(int stmtNo);
	std::vector<string> Parent::getChildForIf(int stmtNo);

	std::vector<string> Parent::getParentStarForWhile(int stmtNo);
	std::vector<string> Parent::getChildStarForWhile(int stmtNo);
	std::vector<string> Parent::getParentStarForAssign(int stmtNo);
	std::vector<string> Parent::getChildStarForAssign(int stmtNo);
	std::vector<string> Parent::getParentStarForIf(int stmtNo);
	std::vector<string> Parent::getChildStarForIf(int stmtNo);

	bool isParent(int stmt1, int stmt2);
	bool isParentStar(int stmt1, int stmt2);

	static std::map<int, int> AnsMap;
	static std::map<int, vector<int>> AnsStarMap;
	static map<int, vector<int>> ChildMap;
	static std::map<int, vector<int>> ChildStarMap;




	// print out the call answer table
//	void PrintProcTable();
};