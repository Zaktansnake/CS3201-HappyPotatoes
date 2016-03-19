#include <string>
#include <stack>
#include <map>

#include "./Header/Parent.h"
#include "./Header/PKB.h"

using namespace std;

map<int, int> Parent::AnsMap;  //map<stmt#, index>
std::vector<std::vector<int> > arrAns;
std::stack<string> loopParent;
std::stack<int> loopStmtNo;
std::stack<int> loopStatus;
map<int, string> stmtstring;
static int conditions;
bool firstCloseBracketOfIf = false;

void setToParent(string stmtLine, int stmtNo);
void deleteParent(int endloop);
void deleteStmtNo(int endloop);

Parent::Parent() {
}

Parent::~Parent() {
}

void Parent::setParent(string stmtLine, int stmtNo, int nestLevel, bool loopFlag, int endLoop, int condition) {
	int index = 0;
	int parent;
	conditions = condition;
	std::vector<int> temp;
	if (stmtLine.compare("}") != 0) {
		stmtstring.insert(pair<int, string>(stmtNo, stmtLine));
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
		}
	}

	if (endLoop > 0) {
		deleteParent(endLoop);
		deleteStmtNo(endLoop);
	}
}

void deleteParent(int endloop) {
    
	for (int i = 0; i < endloop; i++) {
		if (!loopParent.empty()) {
			loopParent.pop();
		}
		if (loopParent.empty()) {
			break;
		}
	}
}

void deleteStmtNo(int endloop) {
	while (endloop > 0) {
		if (!loopStmtNo.empty()) {
			loopStmtNo.pop();
		}
		endloop--;
		if (loopStmtNo.empty()) {
			break;
		}
	}
}

void setToParent(string stmtLine, int stmtNo) {
	loopParent.push(stmtLine);
	loopStmtNo.push(stmtNo);
	if (conditions == 1) {  // this is if statement
	    loopParent.push(stmtLine);
		loopStmtNo.push(stmtNo);
	}
}

bool Parent::isParent(int stmt1, int stmt2) {
	std::vector<int> temp;
	temp = getParent(stmt2);

	if (std::find(temp.begin(), temp.end(), stmt1) != temp.end()) {
		return true;
	}
	return false;

}


std::vector<int> Parent::getParent(int stmtNo) {
    int index = 0;

	map<int, int>::iterator iter;
    std::vector<int> result;
	
	if (stmtNo > AnsMap.size()) {
		return result;
	}
    iter = AnsMap.find(stmtNo);
	if (iter != AnsMap.end()) {
		index = iter->second;
	}
	else {
		return result;
	}
	if (index != 0) {
        result.push_back(index);
	}
	return result;
}

std::vector<int> Parent::getChild(int stmtNo) {
    std::vector<int> result;
	int index;
	if (stmtNo > AnsMap.size()) {
		return result;
	}
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


std::vector<int> Parent::getParentForWhile(int stmtNo) {
	std::vector<int> temp = getParent(stmtNo);
	std::vector<int> ans;
	if (stmtNo > AnsMap.size()) {
		return ans;
	}
	for (int i = 0; i< temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtstring.find(index);
		string line;
		if (iter != stmtstring.end()) {
			line = iter->second;
			if (line.find("while") != std::string::npos || line.find("While") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
	}
	return ans;

}
std::vector<int> Parent::getChildForWhile(int stmtNo) {
	std::vector<int> temp = getChild(stmtNo);
	std::vector<int> ans;
	if (stmtNo > AnsMap.size()) {
		return ans;
	}
	for (int i = 0; i< temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtstring.find(index);
		string line;
		if (iter != stmtstring.end()) {
			line = iter->second;
			if (line.find("while") != std::string::npos || line.find("While") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
	}
	return ans;

}
std::vector<int> Parent::getParentForAssign(int stmtNo) {

	std::vector<int> temp = getParent(stmtNo);
	std::vector<int> ans;
	if (stmtNo > AnsMap.size()) {
		return ans;
	}
	for (int i = 0; i< temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtstring.find(index);
		string line;
		if (iter != stmtstring.end()) {
			line = iter->second;
			if (line.find("=") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
	}
	return ans;
}
std::vector<int> Parent::getChildForAssign(int stmtNo) {
	std::vector<int> temp = getChild(stmtNo);
	std::vector<int> ans;
	if (stmtNo > AnsMap.size()) {
		return ans;
	}
	for (int i = 0; i< temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtstring.find(index);
		string line;
		if (iter != stmtstring.end()) {
			line = iter->second;
			if (line.find("=") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
	}
	return ans;
}