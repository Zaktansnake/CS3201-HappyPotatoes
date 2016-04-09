#pragma once

#include <map>
#include <string>
#include <vector>
#include "Follows.h";
#include "Parent.h";

using namespace std;

class stmtTable
{
public:
	// constructors
	 stmtTable();
	 ~stmtTable();

	// get reference to procedure table
	//static stmtTable* getFollowTable();

	// add data
	static void addStmtTable (string stmtLine, int stmtNo);
	static void setProcedure(string stmtLine, int stmtNo);
	
	// add data to follow table
	static void addFollowTable(string stmtLine, int stmtNo, int nestLevel);
	
	// add data to parent table
	static void addParentTable(string stmtLine, int stmtNo, int nestLevel);

	// get data from follow

	static std::vector<string> stmtTable::getFollowWithType(string type, string stmtNo);
	static std::vector<string> stmtTable::getFollowFanWithType(string type, string stmtNo);
	static std::vector<string> stmtTable::getFollowFanStarWithType(string type, string stmtNo);
	static std::vector<string> stmtTable::getFollowStarWithType(string type, string stmtNo);

	
	static std::vector<string> stmtTable::getFollow(int stmtNo);
	static std::vector<string> stmtTable::getFollowFan(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanStar(int stmtNo);
	static std::vector<string> stmtTable::getFollowStar(int stmtNo);
	static bool isFollow(int s1, int s2);

	static std::vector<string> stmtTable::getFollowForWhile(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanForWhile (int stmtNo);
	static std::vector<string> stmtTable::getFollowForAssign (int stmtNo);
	static std::vector<string> stmtTable::getFollowFanForAssign(int stmtNo);
	static std::vector<string> stmtTable::getFollowForIf(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanForIf(int stmtNo);

	static std::vector<string> stmtTable::getFollowStarForWhile(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanStarForWhile(int stmtNo);
	static std::vector<string> stmtTable::getFollowStarForAssign(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanStarForAssign(int stmtNo);
	static std::vector<string> stmtTable::getFollowStarForIf(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanStarForIf(int stmtNo);

	// get data from parent
	static std::vector<string> stmtTable::getParentWithType(string type, string stmtNo);
	static std::vector<string> stmtTable::getChildWithType(string type, string stmtNo);
	static std::vector<string> stmtTable::getParentStarWithType(string type, string stmtNo);
	static std::vector<string> stmtTable::getChildStarWithType(string type, string stmtNo);


	static std::vector<string> stmtTable::getParent(int stmtNo);
	static std::vector<string> stmtTable::getChild(int stmtNo);
	static std::vector<string> stmtTable::getParentStar(int stmtNo);
	static std::vector<string> stmtTable::getChildStar(int stmtNo);
	static bool isParent(int s1, int s2);

	static std::vector<string> stmtTable::getParentForWhile(int stmtNo);
	static std::vector<string> stmtTable::getChildForWhile(int stmtNo);
	static std::vector<string> stmtTable::getParentForAssign(int stmtNo);
	static std::vector<string> stmtTable::getChildForAssign(int stmtNo);
	static std::vector<string> stmtTable::getParentForIf(int stmtNo);
	static std::vector<string> stmtTable::getChildForIf(int stmtNo);

	static std::vector<string> stmtTable::getParentStarForWhile(int stmtNo);
	static std::vector<string> stmtTable::getChildStarForWhile(int stmtNo);
	static std::vector<string> stmtTable::getParentStarForAssign(int stmtNo);
	static std::vector<string> stmtTable::getChildStarForAssign(int stmtNo);
	static std::vector<string> stmtTable::getParentStarForIf(int stmtNo);
	static std::vector<string> stmtTable::getChildStarForIf(int stmtNo);
};