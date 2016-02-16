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
	void addStmtTable (string stmtLine, int stmtNo);
	// add data to follow table
	void addFollowTable(string stmtLine, int stmtNo, int nestLevel);
	// add data to parent table
	void addParentTable(string stmtLine, int stmtNo, int nestLevel);

	// get data
	std::vector<int> getFollow (int stmtNo);
	std::vector<int> getParent (int stmtNo);

};


