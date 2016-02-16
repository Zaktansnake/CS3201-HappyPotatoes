#include "./Header/Parent.h"
#include "Header\PKB.h"
#include <string>
#include <stack>
#include <map>

using namespace std;

map<int, int> Parent::AnsMap;  //map<stmt#, index>
std::vector<std::vector<int> > arrAns;
std::stack<string> loopParent;
std::stack<int> loopStmtNo;

Parent::Parent()
{
}


Parent::Parent()
{
}
void Parent::setParent(string stmtLine, int stmtNo, int nestLevel, bool loopFlag, int endLoop) {
  // check whether is is a loop parent "while""if""else"
    int index = 0;
	std::vector<int> temp;
	if (loopFlag && endLoop == 0) {
		setToParent(stmtLine,stmtNo);
	}
	else {
	    //first call
		if (AnsMap.empty()) {
		    int parent = loopStmtNo.top();
			if (arrAns.empty()) {
			   index = 0;
			}
			AnsMap.insert(pair<int, int>(parent, index));
			temp.push_back(stmtNo);
			arrAns.push_back(temp);
		}
		else {  // not first call
		    int parent = loopStmtNo.top();
			map<int, int>::iterator iter;
			iter = AnsMap.find(parent);
			if (iter != AnsMap.end()) {
				index = iter->second;
			}
			else {
				throw exception("Error: parent not found");
			}
			arrAns.at(index).push_back(stmtNo);

			if (endLoop > 0) {
				deleteParent(endLoop);
				deleteStmtNo(endLoop);
			}
		}
	}

}

void deleteParent(int endloop) {
	for (int i = 0; i < endloop; i++) {
		loopParent.pop();
	}
}
void deleteStmtNo(int endloop) {
	while (endloop > 0) {
		loopStmtNo.pop();
		endloop--;
	}
}
void setToParent(string stmtLine, int stmtNo) {
	loopParent.push(stmtLine);
	loopStmtNo.push(stmtNo);
}


std::vector<int> Parent::getAns(int stmtNo) {
    int index = 0;
	map<int, int>::iterator iter;
	iter = AnsMap.find(stmtNo);
	if (iter != AnsMap.end()) {
		index = iter->second;
	}
	else {
		throw exception("Error: parent not found");
	}

	return arrAns.at(index);
}