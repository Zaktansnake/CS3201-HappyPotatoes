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

void setToParent(string stmtLine, int stmtNo);
void deleteParent(int endloop);
void deleteStmtNo(int endloop);

Parent::Parent()
{
}


Parent::~Parent()
{
}

void Parent::setParent(string stmtLine, int stmtNo, int nestLevel, bool loopFlag, int endLoop) {
  // check whether is is a loop parent "while""if""else"
    int index = 0;
	int parent;
	std::vector<int> temp;
	if (loopFlag && endLoop == 0) {   // when there is a condition stmt and it is not end stmt for loop
		
		// check whether ths stmt is a child of other stmt
		if (loopStmtNo.empty()) {   // it do not have any parent. set the default parent to 0 into ansMap
		   parent = 0;
		//   index = arrAns.size();
		}
		else {
			parent = loopStmtNo.top();
		}
		setToParent(stmtLine, stmtNo);  //set it become a parent
		AnsMap.insert(pair<int, int>(stmtNo, parent));   
	}
	else {
	    // if there is not a loop condition 
		//check whether this stmt is a child of other stmt
		//if yes, add parent to the child 
		// else, let parent be none
		if (loopStmtNo.empty()) {   // it do not have any parent. set the default parent to 0 into ansMap
			parent = 0;
			//   index = arrAns.size();
		}
		else {
			parent = loopStmtNo.top();
		}
		AnsMap.insert(pair<int, int>(stmtNo, parent));
		

		if (endLoop > 0) {
			deleteParent(endLoop);
			deleteStmtNo(endLoop);
		}
	}
}



void deleteParent(int endloop) {
	for (int i = 0; i < endloop; i++) {
		loopParent.pop();
		if (loopParent.empty()) {
			break;
		}
	}
}

void deleteStmtNo(int endloop) {
	while (endloop > 0) {
		loopStmtNo.pop();
		endloop--;
		if (loopParent.empty()) {
			break;
		}
	}
}

void setToParent(string stmtLine, int stmtNo) {
	loopParent.push(stmtLine);
	loopStmtNo.push(stmtNo);
}

bool Parent::isParent(int stmt1, int stmt2) {
	std::vector<int> temp;
	temp = getAns(stmt2);
	if (std::find(temp.begin(), temp.end(), stmt1) != temp.end()) {
		return true;
	}
	return false;

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
		abort();
	}
    std::vector<int> result;
	if (index != 0) {
        result.push_back(index);
	}
	return result;
}

std::vector<int> Parent::getChild(int stmtNo) {
     
    std::vector<int> result;
	int index;
	for (int i = 1; i <= AnsMap.size(); i++) {
		map<int, int>::iterator iter;
		iter = AnsMap.find(i);
		if (iter != AnsMap.end()) {
			index = iter ->second;
			if (index == stmtNo) {
			   result.push_back(iter->first);
			
			}
		}

	}
	return result;
}