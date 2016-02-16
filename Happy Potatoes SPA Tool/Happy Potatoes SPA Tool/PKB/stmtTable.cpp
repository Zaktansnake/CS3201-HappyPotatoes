#pragma once
#include<string>
#include<vector>
#include <algorithm>
#include "Header\stmtTable.h";


using namespace std;
static int nestLevel = 0;
bool flagForNextLevel = false;
bool loopFlag;
int endLoopNo = 0;
bool isFirstElse = false;  // the first stmtNo after else do not have follow
std::vector<int> stmtLst;
int condition;
Follows follow;
Parent parent;

enum stmtType {
	IF = 1,
	ELSE,
	WHILE
};

// get reference to procedure table
	static stmtTable* getFollowTable();

//add data
void stmtTable::addStmtTable(string stmtLine, int stmtNo) {
    // check if it is a condition stmt
	bool isCon = isCondition(stmtLine);
	loopFlag = false;
	if (isCon) {
		switch (condition) {
			case IF: 
				flagForNextLevel = true;
			    break;
			case ELSE:
				flagForNextLevel = true;
			    break;
			case WHILE:
			    flagForNextLevel = true;
				break;
		}
		loopFlag = true;
	}
	endLoopNo = std::count(stmtLine.begin(), stmtLine.end(), '}');
	addFollowTable(stmtLine, stmtNo, nestLevel);
	addParentTable(stmtLine,stmtNo, nestLevel);
	if (flagForNextLevel == true) {
		nestLevel ++ ;
	} 
	// count the number of '}' --> one } means one condition loop end and minus the number of } from the nest level
	nestLevel = nestLevel - endLoopNo;
	if (nestLevel < 0) {
		throw exception("extra } in the program");
		abort();
	}
}

void stmtTable::addFollowTable(string stmtLine, int stmtNo, int nestLvl) {
     follow.setFollow(stmtLine,stmtNo,nestLvl, loopFlag, endLoopNo);
}
void stmtTable::addParentTable(string stmtLine, int stmtNo, int nestLvl) {
	parent.setParent(stmtLine,stmtNo,nestLvl, loopFlag, endLoopNo);
}

std::vector<int> stmtTable::getFollow(int stmtNo) {
    return follow.getAns(stmtNo);
}
std::vector<int> stmtTable::getParent(int stmtNo) {
    return parent.getAns(stmtNo);
}

bool isCondition(string stmtLine) {
	if (stmtLine.find("if") != std::string::npos) {
	    condition = 1;
		return true;

	}
	else if (stmtLine.find("else") != std::string::npos) {
	    condition = 2;
		return true;

	}
	else if (stmtLine.find("while") != std::string::npos) {
	    condition = 3;
		return true;

	}
	return false;
}


