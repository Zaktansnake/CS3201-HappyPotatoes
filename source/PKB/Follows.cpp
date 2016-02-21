#include "./Header/Follows.h"
#include "./Header/stmtTable.h"
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
Parent pa;

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
		for (int i = 0; i < endLoopNo; i++) {
			stmtListNo--;
			if (stmtListNo < 0) {
				stmtListNo = 0;
				break;
			}
		}
	}


}

std::vector<int> Follows::getFollow(int stmtNo) {
	std::vector<int> ans;
	ans.clear();
	int level = stmtRecord.at(stmtNo - 1); // get the nesting level of the vector
	if (level > levelList.size()) {
		cout << "Error. Wrong stmtRecord." << endl;
		abort();
	}
	std::vector<int> temp = levelList.at(level);
	for (int i = 0; i < temp.size(); i++) {
		if (temp.at(i) == stmtNo) {
			if (i == temp.size() - 1) {
				return ans;
			}
			else {
				if (isSameStmtList(stmtNo, temp.at(i + 1))) {
                    ans.push_back(temp.at(i+1));
				}
				else {
					return ans;
				}
			     
				return ans;
			}
			break;
		}
	}
}

std::vector<int> Follows::getFollowFan(int stmtNo) {
	std::vector<int> ans;
	ans.clear();
	int level = stmtRecord.at(stmtNo - 1); // get the nesting level of the vector
	if (level > levelList.size()) {
		cout << "Error. Wrong stmtRecord." << endl;
		abort();
	}
	std::vector<int> temp = levelList.at(level);
	for (int i = 0; i < temp.size(); i++) {
		if (temp.at(i) == stmtNo) {
			if (i - 1 < 0) {
				return ans;
			}
			else {
				if (isSameStmtList(stmtNo, temp.at(i - 1))) {
					ans.push_back(temp.at(i - 1));
				}
				else {
					return ans;
				}

				return ans;
			}
			break;
		}
	}
}

bool Follows::isFollows(int s1, int s2) {
	if (getFollow(s1).at(0) == s2) {
		return true;
	}
	else {
		return false;
	}
}

bool isSameStmtList(int s1, int s2) {
    std::vector<int> parentS1;
	std::vector<int> parentS2;
	parentS1 = pa.getParent(s1);
	parentS2 = pa.getParent(s2);
	if (parentS1.size() == 0 && parentS2.size() == 0) {
		return true;
	}
	else if (parentS1.size() != parentS2.size()) {
		return false;
	}
	else if (parentS1.at(0) == parentS2.at(0)) {
		return true;
	}
	else {
		return false;
	}
}
