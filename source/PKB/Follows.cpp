#include "./Header/PKB.h"
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
std::vector<int> positionInLevelList;
std::vector<int> stmtListTable;
std::map<int,string> stmtString;
std::stack<int> stackforCondition;
std::map<int, int> stmtlistMap; // store the stmtlist especially for if-else for all stmtline
Parent pa;

static int stmtListNo = 1;  // same level same stmtList, change with loop

bool isSameStmtList(int s1, int s2);

Follows::Follows() {
}
Follows::~Follows() {
}

// if ifFlag = true and elseFlag = true --> in else statement
// if ifFlag = true and elseFlag = flase --> in if then statement
void Follows::setFollow(string stmtLine, int stmtNo, int nestLvl, bool loopFlag, int endLoopNo, int conditions) {
	if (stmtLine.size() != endLoopNo && conditions != 2) {
        stmtRecord.push_back(nestLvl);
		
			int si;
			if (levelList.size() == nestLvl) {
				si = 0;
			}
			else {
				si = levelList.at(nestLvl).size();
		    }
			positionInLevelList.push_back(si);
		
	}
	
	std::vector<int> temp;
	if (conditions != 0) { // if stmtment
	   int num = stmtNo + 1;
	   stmtlistMap.insert(pair<int, int> (num, -1));
	}
//	else if (conditions == 2) {
//		int num = stmtNo + 1;
//		stmtlistMap.insert(pair<int, int>(num, -1));
//	}
	
	if (loopFlag) {
		
		    int i = stmtNo + 1;
			stackforCondition.push(i);
	}
	int size = stmtLine.size();
	if (stmtLine.size() != endLoopNo && conditions != 2) {
	//	if (elseFlag == false) {    // else { is not count as one stmt line
          stmtString.insert(std::pair<int,string>(stmtNo,stmtLine));
	//	}
        // begin of table, levelList is empty
		if (levelList.empty()) {
			temp.push_back(stmtNo);
			levelList.push_back(temp);
		//	positionInLevelList.push_back(0);
			temp.clear();
		}
		else {  // if the level list is not empty
			if (levelList.size() <= nestLvl) {    // if levellist size is smaller than nestlevel, means, this is new level
				temp.push_back(stmtNo);
				levelList.push_back(temp);
		//		positionInLevelList.push_back(0);

			}
			else {
				temp = levelList.at(nestLvl);
				temp.push_back(stmtNo);
				levelList.at(nestLvl) = temp;
		//		positionInLevelList.push_back(levelList.at(nestLvl).size());
			}
		}
		stmtListTable.push_back(stmtListNo);
	}
	if (loopFlag && endLoopNo == 0) {  // this is a loop node
		stmtListNo++;
	}
	else if (endLoopNo > 0) {
		
		for (int i = 0; i < endLoopNo; i++) {
			stmtListNo--;
			if (stmtListNo < 0) {
				stmtListNo = 1;
				break;
			}
			if (stackforCondition.size() != 0) {
			    int index ;
				if (conditions == 2 && endLoopNo > 0) {
					int temp = stackforCondition.top();
					stackforCondition.pop();
					index = stackforCondition.top();
					stackforCondition.pop();
					stackforCondition.push(temp);
				}
				else {
                    index = stackforCondition.top();
					stackforCondition.pop();
				}
                
			    stmtlistMap.at(index) = stmtNo;
			    
			}
			

		}
	}
	
}

std::vector<int> Follows::getFollow(int stmtNo) {
	std::vector<int> ans;
	ans.clear();
	if (stmtNo >= stmtRecord.size()) {
		return ans;
	}
	int level = stmtRecord.at(stmtNo-1); // get the nesting level of the vector
	if (level > levelList.size()) {
		cout << "Error. Wrong stmtRecord." << endl;
		PKB::abort();
	}
	std::vector<int> temp = levelList.at(level);
	int position = positionInLevelList.at(stmtNo-1)+1; // get the position in the levellist
	int postPos;
	if (temp.size() > position) {
       postPos = temp.at(position);
	   if (isSameStmtList(stmtNo, postPos)) {
		   if (stmtNo != postPos) {
			   ans.push_back((postPos));
		   }

	   }
	}
	
	/*for (int i = 0; i < temp.size(); i++) {
		if (temp.at(i) == stmtNo) {
			if (i == temp.size() - 1) {
				return ans;
			}
			else {
				if (isSameStmtList(stmtNo, temp.at(i + 1))) {
					if (stmtNo != temp.at(i + 1)) {
                        ans.push_back(temp.at(i+1));
					}
                    
				}
				else {
					return ans;
				}
			     
				return ans;
			}
			break;
		}
	}*/
	return ans;
}

std::vector<int> Follows::getFollowFan(int stmtNo) {
	std::vector<int> ans;
	ans.clear();
	if (stmtNo >= stmtRecord.size()) {
		return ans;
	}
	int level = stmtRecord.at(stmtNo - 1); // get the nesting level of the vector
	if (level > levelList.size()) {
		cout << "Error. Wrong stmtRecord." << endl;
		PKB::abort();
	}
	std::vector<int> temp = levelList.at(level);
	int position = positionInLevelList.at(stmtNo - 1) - 1; // get the position in the levellist
	int postPos;
	if (temp.size() > position) {
		postPos = temp.at(position);
		if (isSameStmtList(stmtNo, postPos)) {
			if (stmtNo != postPos) {
				ans.push_back((postPos));
			}

		}
	}
	return ans;
}

std::vector<int> Follows::getFollowFanStar(int stmtNo) {
	std::vector<int> ans;
	ans.clear();
	if (stmtNo >= stmtRecord.size()) {
		return ans;
	}
	int level = stmtRecord.at(stmtNo - 1); // get the nesting level of the vector
	if (level > levelList.size()) {
		cout << "Error. Wrong stmtRecord." << endl;
		PKB::abort();
	}
	std::vector<int> temp = levelList.at(level);
	int position = positionInLevelList.at(stmtNo - 1); // get the position in the levellist
	int postPos;
	if (temp.size() > position) {
		for (int i = 0; i < position; i++) {
		    postPos = temp.at(i);
			if (isSameStmtList(stmtNo, postPos)) {
				if (stmtNo != postPos) {
                   ans.push_back(postPos);
				}
				
			}
		}
	}
	return ans;
}

std::vector<int> Follows::getFollowStar(int stmtNo) {
	std::vector<int> ans;
	ans.clear();
	if (stmtNo >= stmtRecord.size()) {
		return ans;
	}
	int level = stmtRecord.at(stmtNo - 1); // get the nesting level of the vector
	if (level > levelList.size()) {
		cout << "Error. Wrong stmtRecord." << endl;
		PKB::abort();
	}
	std::vector<int> temp = levelList.at(level);
	int position = positionInLevelList.at(stmtNo - 1) + 1; // get the position in the levellist
	int postPos;
	if (temp.size() > position) {
		for (int i = position; i < temp.size(); i++) {
			postPos = temp.at(i);
			if (isSameStmtList(stmtNo, postPos)) {
				if (stmtNo != postPos) {
					ans.push_back(postPos);
				}

			}
		}
	}
	return ans;
}

bool Follows::isFollows(int s1, int s2) {
	if (getFollow(s1).size() == 0) {
		return false;
	}
	if (getFollow(s1).at(0) == s2) {
		return true;
	}
	else {
		return false;
	}
}

bool Follows::isFollowsStar(int s1, int s2) {
	vector<int> temp = getFollowStar(s1);
	if (temp.size()==1 && temp.front() == 0) {
		return false;
	}
	else {
		for (int i = 0; i < temp.size(); i++) {
			if (temp.at(i) == s2) {
				return true;
			}
		}
	}
	return false;
	
}

std::vector<int> Follows::getFollowForWhile(int stmtNo) {
	std::vector<int> temp = getFollow(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("while") != std::string::npos || line.find("While") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}
std::vector<int> Follows::getFollowFanForWhile(int stmtNo) {
	std::vector<int> temp = getFollowFan(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("while") != std::string::npos || line.find("While") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}
std::vector<int> Follows::getFollowForAssign(int stmtNo) {
	std::vector<int> temp = getFollow(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find(" = ") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}
std::vector<int> Follows::getFollowFanForAssign(int stmtNo) {
	std::vector<int> temp = getFollowFan(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("=") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}

std::vector<int> Follows::getFollowForIf(int stmtNo) {
	std::vector<int> temp = getFollow(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("if ") != std::string::npos || line.find("If") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}
std::vector<int> Follows::getFollowFanForIf(int stmtNo) {
	std::vector<int> temp = getFollowFan(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("if ") != std::string::npos || line.find("If ") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}

std::vector<int> Follows::getFollowStarForWhile(int stmtNo) {
	std::vector<int> temp = getFollowStar(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("while") != std::string::npos || line.find("While") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}
std::vector<int> Follows::getFollowFanStarForWhile(int stmtNo) {
	std::vector<int> temp = getFollowFanStar(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("while") != std::string::npos || line.find("While") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}

std::vector<int> Follows::getFollowStarForAssign(int stmtNo) {
	std::vector<int> temp = getFollowStar(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find(" = ") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}
std::vector<int> Follows::getFollowFanStarForAssign(int stmtNo) {
	std::vector<int> temp = getFollowFanStar(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("=") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}

std::vector<int> Follows::getFollowStarForIf(int stmtNo) {
	std::vector<int> temp = getFollowStar(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("if ") != std::string::npos || line.find("If") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}
std::vector<int> Follows::getFollowFanStarForIf(int stmtNo) {
	std::vector<int> temp = getFollowFanStar(stmtNo);
	std::vector<int> ans;
	for (int i = 0; i < temp.size(); i++) {
		int index = temp.at(i);
		map<int, string>::iterator iter;
		iter = stmtString.find(index);
		string line;
		if (iter != stmtString.end()) {
			line = iter->second;
			if (line.find("if ") != std::string::npos || line.find("If ") != std::string::npos) {
				ans.push_back(temp.at(i));
			}
		}
		else {
		}

	}
	return ans;
}



bool isSameStmtList(int s1, int s2) {
	std::vector<int> parentS1;
	std::vector<int> parentS2;
	parentS1 = pa.getParent(s1);
	parentS2 = pa.getParent(s2);
	int start = 0;
	int end = 0 ;
	bool result = false;
	if (s1 == s2) {
		return false;
	}
	if (parentS1.size() == 0 && parentS2.size() == 0) {
		return true;
	}
	if (parentS1.size() != parentS2.size()) {
		return false;
	}
	if ((parentS1.at(0) == parentS2.at(0))) {
		for (map<int, int>::iterator it = stmtlistMap.begin(); it != stmtlistMap.end(); ++it) {
			if (it->first <= s1 && it->second >= s1) {
				if (it->first > start) {
					start = it->first;
					end = it->second;
					result = true;
				}
			}
		}
		if (result && start <= s2 && end >= s2) {  // it is in the same stmtlist
			return true;
		}
		
	}
	return false;
//	if (parentS1.size() == 0 && parentS2.size() == 0) {
//	    return true;
//	}
//	else if (parentS1.size() != parentS2.size()) {
//		return false;
//	}
//	else if (parentS1.at(0) == parentS2.at(0)) {
//		return true;
//	}
//	else {
//		return false;
//	}
}

void Follows::PrintProcTable() {
	for (map<int, int>::iterator it = stmtlistMap.begin(); it != stmtlistMap.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}

}