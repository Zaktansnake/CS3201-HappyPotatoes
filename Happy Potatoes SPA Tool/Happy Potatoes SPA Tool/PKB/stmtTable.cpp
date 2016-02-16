#pragma once
#include<map>
#include<string>
#include<vector>
#include "Header\stmtTable.h"

using namespace std;
static int nestLevel = 0;
bool flagForNextLevel = false;
bool isFirstElse = false;  // the first stmtNo after else do not have follow
std::vector<int> stmtLst;
int condition;
Follows follow;

enum stmtType {
	IF = 1,
	ELSE,
	WHILE,
	ASSIGN
};


class stmtTable
{
public:
	stmtTable();
	~stmtTable();

	// get reference to procedure table
	//static stmtTable* getFollowTable();

	//add data
	void  stmtTable::addStmtTable(string stmtLine, int stmtNo) {
	// check whether it is condition line 
	// if it is condition line, nestLevel+1, else nestLevel not change
	    int temp = nestLevel;
		isCondition(stmtLine); 
		
		switch (condition) {
			case IF: 
			  flagForNextLevel = true;
			  break;
			case ELSE:
			  isFirstElse = true;
			 // addElse(stmtLine, stmtNo);
			  break;
			case WHILE:
			  flagForNextLevel = true;
			//  addWhile(stmtLine, stmtNo);
			  break;
			default: break;
			  
		}
		if (isFirstElse = false) {
			addFollowTable(stmtLine, stmtNo, nestLevel);
			if (flagForNextLevel == true) {
				nestLevel++;
				flagForNextLevel = false;
			}
			// get the previous stmtno's nestlevel, if 
			int prevLevel = follow.getPrevLevelStmt(stmtNo);
			if (preLevel - nestLevel == 1) {
				addParentTable(stmtLine, stmtNo, nestLevel);
			}

			if (stmtLine.find("}") != string::npos) {  //found "}"
				nestLevel--;
			}
		}
		
		

	}

	int isCondition(string stmtLine) {
		if (stmtLine.find("if") != string::npos) {
			return 1;
		}
		else if (stmtLine.find("else") != string::npos) {
			return 2;
		}
		else if (stmtLine.find("while") != string::npos) {
			return 3;
		}
		else {
		    return 4;
		}
	}


	void stmtTable::addFollowTable(string stmtLine, int stmtNo, int nestLvl) {
	    
	    
	}
	void stmtTable::addParentTable(string stmtLine, int stmtNo, int nestLvl) {

	}

	// get data
	std::vector<int> getFollow(int stmtLine);
	std::vector<int> getParent(int stmtLine);
};


