#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

#include "./Header/stmtTable.h";

using namespace std;


static int nestLevel = 0;
bool flagForNextLevel = false;
bool loopFlag;
int loopStatus;
// bool elseFlag = false;
// bool ifFlag = false;
int endLoopNo = 0;
bool isFirstElse = false;  // the first stmtNo after else do not have follow
std::vector<int> stmtLst;
int conditionStmtTable;
Follows follow;
Parent parent;
map<int,int> startAndEndOfProcedure;
stack<int> procedureStack;

bool isCondition(string stmtLine);

enum stmtType {
	IF = 1,
	ELSE,
	WHILE
};

// get reference to procedure table
static stmtTable* getFollowTable();

//add data
void stmtTable::setProcedure(string stmtLine, int stmtNo) {
	if (stmtLine.find("procedure ") != string::npos) {
		if (startAndEndOfProcedure.size() == 0) {
			startAndEndOfProcedure.insert(pair<int, int>(stmtNo + 1, -1));
			procedureStack.push(stmtNo+1);
		}
		else {
			startAndEndOfProcedure.insert(pair<int, int>(stmtNo + 1, -1));
			int index = procedureStack.top();
			procedureStack.pop();
			procedureStack.push(stmtNo+1);
			startAndEndOfProcedure.at(index) = stmtNo - 1;
		}
	}
}

// add data to stmtTable
void stmtTable::addStmtTable(string stmtLine, int stmtNo) {
	stmtLine.erase(std::remove(stmtLine.begin(), stmtLine.end(), '\t'), stmtLine.end());
	size_t endpos = stmtLine.find_last_not_of(" ");
	if (string::npos != endpos) {
		stmtLine = stmtLine.substr(0, endpos + 1);
	}
	size_t startpos = stmtLine.find_first_not_of(" ");
	if (string::npos != endpos) {
		stmtLine = stmtLine.substr(startpos);
	}
	// check if it is a condition stmt
	if (stmtLine.compare("{") != 0) {
		bool isCon = isCondition(stmtLine);
		loopFlag = false;
		//ifFlag = false;
		//elseFlag = false;

		if (isCon) {
			switch (conditionStmtTable) {
			case IF:
				flagForNextLevel = true;
				//	ifFlag = true;
				//	elseFlag = false;
				break;
			case ELSE:
				flagForNextLevel = false;
				//	ifFlag = false;
				//	elseFlag = true;
				//	stmtNo --;
				break;
			case WHILE:
				flagForNextLevel = true;
				//	ifFlag = false;
				//	elseFlag = false;
				break;
			}

			loopFlag = true;
		}

		endLoopNo = std::count(stmtLine.begin(), stmtLine.end(), '}');
		if (nestLevel <0) nestLevel = 0;
		addFollowTable(stmtLine, stmtNo, nestLevel);
		addParentTable(stmtLine, stmtNo, nestLevel);




		if (flagForNextLevel == true) {
			nestLevel++;
			flagForNextLevel = false;
		}
		if (conditionStmtTable == 2 && endLoopNo == 0) {
			nestLevel++;
		}

		// count the number of '}' --> one } means one condition loop end and minus the number of } from the nest level
		if (endLoopNo > 0 && conditionStmtTable != 2) {
			nestLevel = nestLevel - endLoopNo;
			if (nestLevel < 0) {
				nestLevel == 0;
			}
		}
	}
}

void stmtTable::addFollowTable(string stmtLine, int stmtNo, int nestLvl) {
     follow.setFollow(stmtLine,stmtNo,nestLvl, loopFlag, endLoopNo, conditionStmtTable);
}
void stmtTable::addParentTable(string stmtLine, int stmtNo, int nestLvl) {
	parent.setParent(stmtLine,stmtNo,nestLvl, loopFlag, endLoopNo, conditionStmtTable);
}
//-------------------------------------get answer of follow
std::vector<string> checkWithProcedure(int stmtNo, vector<int> ans) {
	std::vector<string>result;
	int start;
	int end;
	for (map<int, int>::iterator it = startAndEndOfProcedure.begin(); it != startAndEndOfProcedure.end(); ++it) {
		if (it->first <= stmtNo && it->second >= stmtNo) {
		   start = it->first;
		   end = it->second;
		   break;
		}
	}
		    
	for (int i = 0; i < ans.size(); i++) {
		int num = ans.at(i);
		if (start <= num && end >= num) {

			result.push_back(to_string(num));
		}
	}
	return result;
}


std::vector<string> stmtTable::getFollow(int stmtNo) {
    std::vector<int> ans = follow.getFollow(stmtNo);
	std::vector<string> result;
	result = checkWithProcedure(stmtNo,ans);
    return result;
}

std::vector<string> stmtTable::getFollowFan(int stmtNo) {
	std::vector<int> ans = follow.getFollowFan(stmtNo);
	std::vector<string> result;
	result = checkWithProcedure(stmtNo, ans);
	return result;
}

bool stmtTable::isFollow(int s1, int s2) {
	if (follow.isFollows(s1, s2)) {
		vector<int>temp;
		temp.push_back(s2);
		vector<string> ans = checkWithProcedure(s1, temp);
		if (ans.size() == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}
std::vector<string> stmtTable::getFollowForWhile(int stmtNo) {
	std::vector<string> result;
	std::vector<int> ans = follow.getFollowForWhile(stmtNo);
	result = checkWithProcedure(stmtNo, ans);
	return result;
}
std::vector<string> stmtTable::getFollowFanForWhile(int stmtNo) {
	std::vector<string> result;
	std::vector<int> ans = follow.getFollowFanForWhile(stmtNo);
	result = checkWithProcedure(stmtNo, ans);
	return result;
}
std::vector<string> stmtTable::getFollowForAssign(int stmtNo) {
	std::vector<string> result;
	std::vector<int> ans = follow.getFollowForAssign(stmtNo);
	result = checkWithProcedure(stmtNo, ans);
	return result;
}
std::vector<string> stmtTable::getFollowFanForAssign(int stmtNo) {
	std::vector<string> result;
	std::vector<int> ans = follow.getFollowFanForAssign(stmtNo);
	result = checkWithProcedure(stmtNo, ans);
	return result;
}
std::vector<string> stmtTable::getFollowForIf(int stmtNo) {
	std::vector<string> result;
	std::vector<int> ans = follow.getFollowForIf(stmtNo);
	result = checkWithProcedure(stmtNo, ans);
	return result;
}
std::vector<string> stmtTable::getFollowFanForIf(int stmtNo) {
	std::vector<string> result;
	std::vector<int> ans = follow.getFollowFanForIf(stmtNo);
	result = checkWithProcedure(stmtNo, ans);
	return result;
}



// get data from parent
std::vector<int> stmtTable::getParent(int stmtNo) {
	std::vector<int> ans = parent.getParent(stmtNo);
    return ans;
}

std::vector<int> stmtTable::getChild(int stmtNo) {
	std::vector<int> ans = parent.getChild(stmtNo);
	return ans;
}

std::vector<int> stmtTable::getParentStar(int stmtNo) {
	std::vector<int> ans = parent.getParentStar(stmtNo);
	return ans;
}

bool stmtTable::isParent(int s1, int s2) {
	return parent.isParent(s1,s2);
}

std::vector<int> stmtTable::getParentForWhile(int stmtNo) {
	std::vector<int> ans = parent.getParentForWhile(stmtNo);
	return ans;
}
std::vector<int> stmtTable::getChildForWhile(int stmtNo) {
	std::vector<int> ans = parent.getChildForWhile(stmtNo);
	return ans;
}
std::vector<int> stmtTable::getParentForAssign(int stmtNo) {
	std::vector<int> ans = parent.getParentForAssign(stmtNo);
	return ans;
}

std::vector<int> stmtTable::getChildForAssign(int stmtNo) {
	std::vector<int> ans = parent.getChildForAssign(stmtNo);
	return ans;
}

std::vector<int> stmtTable::getParentForIf(int stmtNo) {
	std::vector<int> ans = parent.getParentForAssign(stmtNo);
	return ans;
}

std::vector<int> stmtTable::getChildForIf(int stmtNo) {
	std::vector<int> ans = parent.getChildForAssign(stmtNo);
	return ans;
}




// check condition
bool isCondition(string stmtLine) {
	if (stmtLine.find("if") != std::string::npos) {
		conditionStmtTable = 1;
		return true;
	}
	else if (stmtLine.find("else") != std::string::npos) {
		conditionStmtTable = 2;
		return true;
	}
	else if (stmtLine.find("while") != std::string::npos) {
		conditionStmtTable = 3;
		return true;
	}
	conditionStmtTable = 0;
	return false;
}