#include "./Header/Follows.h"
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

std::vector<std::vector<int> > levelList; //store stmtNo based on nesting level number from 1 to n
std::vector<std::vector<int> > ansList; //store ans for stmtNo 1 to end
std::vector<int> stmtRecord;
std::vector<int> stmtListTable;
std::stack<int> loopStack;

static int stmtListNo = 1;  // same level same stmtList, change with loop

bool isSameStmtList(int s1, int s2);

Follows::Follows()
{
}
Follows::~Follows()
{
}

void Follows::setFollow(string stmtLine, int stmtNo, int nestLvl, bool loopFlag, int endLoopNo) {
	stmtRecord.push_back(nestLvl);
    std::vector<int> temp;
	if (levelList.empty()) {
	    temp.push_back(stmtNo);
		levelList.push_back(temp);
	}
	else {
		if (levelList.size() < nestLvl) {
			temp.push_back(stmtNo);
			levelList.push_back(temp);

		}
		else {
			levelList.at(nestLvl).push_back(stmtNo);
		}
	}
	stmtListTable.push_back(stmtListNo);
	if (loopFlag && endLoopNo == 0) {  // this is a loop node
		stmtListNo++;
	}
	else if (!loopFlag && endLoopNo > 0) {
		for (int i = 0; i < endLoopNo; i++) {
			stmtListNo --;
		}
	}
	
	
}

std::vector<int> getAns(int stmtNo) {
    bool checkStmtList = false;
	int ans = 0;
    int level = stmtRecord.at(stmtNo-1); // get the nesting level of the vector
	if (level > levelList.size()) {
		throw exception ("Error, stmtRecord wrong");
		abort();
	}
	std::vector<int> temp = levelList.at(level);
	for (int i = 0; i < temp.size(); i++) {
		if (temp.at(i) == stmtNo) {
		    ans = temp.at(i+1);
            checkStmtList = isSameStmtList(stmtNo, ans);
			break;
		}
	}
	if (checkStmtList) {
		return {ans};
	}
	else {
		return {NULL};
	}
}

bool Follows::isFollows(int s1, int s2) {
	if (getAns(s1).at(0) == s2) {
		return true;
	}
	else {
		return false;
	}
}

bool isSameStmtList(int s1, int s2) {
	if (stmtListTable.at(s1 - 1) == stmtListTable.at(s2 - 1)) {
		return true;
	}
	else {
		return false;
	}
}
