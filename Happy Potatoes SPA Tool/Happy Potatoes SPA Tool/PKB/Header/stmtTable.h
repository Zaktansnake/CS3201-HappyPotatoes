#pragma once
#include<map>
#include<string>
#include<vector>
#include "Follows.h";
#include "Parent.h";

using namespace std;

class stmtTable
{
public:
	 stmtTable();
	 ~stmtTable();

	// get reference to procedure table
	//static stmtTable* getFollowTable();

	//add data
	static void addStmtTable (string stmtLine, int stmtNo);
	// add data to follow table
	static void addFollowTable(string stmtLine, int stmtNo, int nestLevel);
	// add data to parent table
	static void addParentTable(string stmtLine, int stmtNo, int nestLevel);

	//get data 

	static std::vector<int> stmtTable::getFollow(int stmtNo);
	static bool isFollow(int s1, int s2);
	static std::vector<int> stmtTable::getParent(int stmtNo);
	static bool isParent(int s1, int s2);

	
};


