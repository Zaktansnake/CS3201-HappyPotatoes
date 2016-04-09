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
	static std::vector<string> stmtTable::getFollow(int stmtNo);
	static std::vector<string> stmtTable::getFollowFan(int stmtNo);
	static bool isFollow(int s1, int s2);

	static std::vector<string> stmtTable::getFollowForWhile(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanForWhile (int stmtNo);
	static std::vector<string> stmtTable::getFollowForAssign (int stmtNo);
	static std::vector<string> stmtTable::getFollowFanForAssign(int stmtNo);
	static std::vector<string> stmtTable::getFollowForIf(int stmtNo);
	static std::vector<string> stmtTable::getFollowFanForIf(int stmtNo);

	// get data from parent
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
};