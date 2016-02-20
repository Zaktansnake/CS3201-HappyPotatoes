#pragma once
#include<string>
#include<vector>
#include <algorithm>
#include "./Header/stmtTable.h";


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

bool isCondition(string stmtLine);

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
		flagForNextLevel = false;
	} 
	// count the number of '}' --> one } means one condition loop end and minus the number of } from the nest level
	if (endLoopNo > 0) {
		nestLevel = nestLevel - endLoopNo;
	}

}

void stmtTable::addFollowTable(string stmtLine, int stmtNo, int nestLvl) {
     follow.setFollow(stmtLine,stmtNo,nestLvl, loopFlag, endLoopNo);
}
void stmtTable::addParentTable(string stmtLine, int stmtNo, int nestLvl) {
	parent.setParent(stmtLine,stmtNo,nestLvl, loopFlag, endLoopNo);
}

std::vector<int> stmtTable::getFollow(int stmtNo) {
    std::vector<int> ans = follow.getFollow(stmtNo);
    return ans;
}

std::vector<int> stmtTable::getFollowFan(int stmtNo) {
	std::vector<int> ans = follow.getFollowFan(stmtNo);
	return ans;
}

bool stmtTable::isFollow(int s1, int s2) {
	return follow.isFollows(s1,s2);
}
std::vector<int> stmtTable::getParent(int stmtNo) {
	std::vector<int> ans = parent.getParent(stmtNo);
    return ans;
}

std::vector<int> stmtTable::getChild(int stmtNo) {
	std::vector<int> ans = parent.getChild(stmtNo);
	return ans;
}

bool stmtTable::isParent(int s1, int s2) {
	return parent.isParent(s1,s2);
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


