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
	void addFollowTable(int stmtNo, int nestLevel);
	void addParentTable(int stmtNo, int nestLevel);

	// get data
	std::vector<int> getFollow (int stmtNo);
	std::vector<int> getParent (int stmtNo);

};


