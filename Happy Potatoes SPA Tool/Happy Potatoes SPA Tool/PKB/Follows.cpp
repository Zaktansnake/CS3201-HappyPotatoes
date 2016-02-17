#include "./Header/Follows.h"
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

std::vector<std::vector<int> > levelList; //store stmtNo based on nesting level number from 1 to n
std::vector<std::vector<int> > ansList; //store ans for stmtNo 1 to end
std::vector<int> stmtRecord; // record all the nesting level in order
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
		temp.clear();
	}
	else {
		if (levelList.size() <= nestLvl) {
			temp.push_back(stmtNo);
			levelList.push_back(temp);

		}
		else {
			temp = levelList.at(nestLvl);
			temp.push_back(stmtNo);
			levelList.at(nestLvl) = temp;
		}
	}
	stmtListTable.push_back(stmtListNo);
	if (loopFlag && endLoopNo == 0) {  // this is a loop node
		stmtListNo++;
	}
	else if (!loopFlag && endLoopNo > 0) {
		for (int i = 0; i <= endLoopNo; i++) {
			stmtListNo--;
			if (stmtListNo < 0) {
				stmtListNo = 0;
				break;
			}
		}
	}


}

std::vector<int> Follows::getAns(int stmtNo) {
	bool checkStmtList = false;
	std::vector<int> ans;
	ans.clear();
	int level = stmtRecord.at(stmtNo - 1); // get the nesting level of the vector
	if (level > levelList.size()) {
		throw exception("Error, stmtRecord wrong");
		abort();
	}
	std::vector<int> temp = levelList.at(level);
	for (int i = 0; i < temp.size(); i++) {
		if (temp.at(i) == stmtNo) {
			if (i == temp.size() - 1) {
				return {0};
			}
			else {
			     ans.push_back(temp.at(i+1));
				return ans;
			}
			break;
		}
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

bool isSameStmtList(int s1, int s2, int level) {
    bool s1Boll = false; 
	bool s2Bool = false;
	std::vector<int> temp = levelList.at(level);
	for (int i = 0; i < levelList.at(level).size(); i++){
	   
    }
}
