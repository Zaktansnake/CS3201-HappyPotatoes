#include <string>
#include <stack>
#include <map>

#include "./Header/Parent.h"
#include "./Header/PKB.h"

using namespace std;

map<int, int> Parent::AnsMap;  //map<stmt#, index>
map<int, vector<int>> Parent::AnsStarMap;
map<int, vector<int>> Parent::ChildMap;
map<int, vector<int>> Parent::ChildStarMap;
std::vector<std::vector<int> > arrAns;
std::stack<string> loopParent;
std::stack<int> loopStmtNo;
std::stack<int> loopStatus;
map<int, string> stmtstring;
static int conditions;
bool firstCloseBracketOfIf = false;

void setToParent(string stmtLine, int stmtNo);
void storeChildStar (int stmtNo);
void storeParentStar(int stmtNo);
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
	if (stmtLine.compare("}") != 0 && conditions !=2) {
		stmtstring.insert(pair<int, string>(stmtNo, stmtLine));
		if (loopFlag && endLoop == 0) {   // when there is a condition stmt and it is not end stmt for loop
										  // check whether ths stmt is a child of other stmt
			if (loopStmtNo.empty()) {   // it do not have any parent. set the default parent to 0 into ansMap
				parent = 0;
			}
			else {
				parent = loopStmtNo.top();
			}
			setToParent(stmtLine, stmtNo);  //set it become a parent
			AnsMap.insert(pair<int, int>(stmtNo, parent));
			if (parent != 0 && conditions!=2) {
			vector <int> childtemp;
			childtemp.clear();
				map<int, vector<int>>::iterator itera;
				itera = ChildMap.find(parent);
				if (itera != ChildMap.end()) {
					if (itera->first == parent) {
                         childtemp = ChildMap.at(parent);
					     childtemp.push_back(stmtNo);
					     itera->second = childtemp;
					}
					else {
						childtemp.push_back(stmtNo);
						ChildMap.insert(pair<int, vector<int>>(parent, childtemp));
					}
					
				}
				else {
				 childtemp.push_back(stmtNo);
                 ChildMap.insert(pair<int,vector<int>>(parent,childtemp));
				}
				
			}
			storeParentStar(stmtNo);
			storeChildStar(stmtNo);
		}
		else {
			// if there is not a loop condition 
			//check whether this stmt is a child of other stmt
			//if yes, add parent to the child 
			// else, let parent be none
			if (loopStmtNo.empty()) {   // it do not have any parent. set the default parent to 0 into ansMap
				parent = 0;
			}
			else {
				parent = loopStmtNo.top();
			}

			AnsMap.insert(pair<int, int>(stmtNo, parent));
			if (parent != 0) {
				vector <int> childtemp;
				childtemp.clear();
				map<int, vector<int>>::iterator itera;
				itera = ChildMap.find(parent);
				if (itera != ChildMap.end()) {
					if (itera->first == parent) {
						childtemp = ChildMap.at(parent);
						childtemp.push_back(stmtNo);
						itera->second = childtemp;
					}
					else {
						childtemp.push_back(stmtNo);
						ChildMap.insert(pair<int, vector<int>>(parent, childtemp));
					}

				}
				else {
					childtemp.push_back(stmtNo);
					ChildMap.insert(pair<int, vector<int>>(parent, childtemp));
				}

			}
			storeParentStar(stmtNo);
			storeChildStar(stmtNo);
		}
	}

	if (endLoop > 0) {
		deleteParent(endLoop);
		deleteStmtNo(endLoop);
	}
}

void storeChildStar(int stmtNo) {
	stack<int> temp = loopStmtNo; // copy the parent stack into a temp stack
	// for each stmtno, the stmt in the stack are its parent star
	vector<int> childs;
	int index;
	while (temp.size() != 0) {
	   childs.clear();
	   index = temp.top();
	   map<int, vector<int>>::iterator iterchilds;
	   iterchilds = Parent::ChildStarMap.find(index);
	   if (iterchilds != Parent::ChildStarMap.end() && index != stmtNo) { // find it
		   if (iterchilds->first == index) {
		      childs = iterchilds->second;
			  if (stmtNo != childs.back()) {
				  childs.push_back(stmtNo);
				  iterchilds->second = childs;
			  }
		   }
	   }
	   else {
		   if (index != stmtNo) {
			   childs.push_back(stmtNo);
			   Parent::ChildStarMap.insert(pair<int, vector<int>>(index, childs));
		   }
	       
	   }
	   temp.pop();
	}
	
}

void storeParentStar(int stmtNo) {
    stack<int> temp = loopStmtNo;
	vector<int> ans;
	bool flag = false;
	while (loopStmtNo.size() != 0) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == loopStmtNo.top()) {
				loopStmtNo.pop();
				flag = true;
				break;
			}
		}
		if (!flag) {
			if (loopStmtNo.size() > 0) {
				if (loopStmtNo.top() != stmtNo) {
					ans.push_back(loopStmtNo.top());
					loopStmtNo.pop();
				}
				else {
					loopStmtNo.pop();
				}
			}
			
			
		}
		flag = false;
		
	}
	Parent::AnsStarMap.insert(pair<int,vector<int>>(stmtNo,ans));
	loopStmtNo = temp;
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
	if (conditions != 2) {
        loopParent.push(stmtLine);
	    loopStmtNo.push(stmtNo);
	}
	
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
bool Parent::isParentStar(int stmt1, int stmt2) {
	std::vector<int> temp;
	temp = getParentStarInt(stmt2);

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
	map<int, vector<int>>::iterator iter;
	
	iter = ChildMap.find(stmtNo);
	if (iter != ChildMap.end()) {
		result = iter->second;
	}

	/*int index;
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
	}*/
	return result;
}

std::vector<string> Parent::getParentStar(int stmtNo) {
	map<int, vector<int>>::iterator iter;
	std::vector<string> result;
	std::vector<int> temp;

	if (stmtNo > AnsStarMap.size()) {
		return result;
	}
	iter = AnsStarMap.find(stmtNo);
	if (iter != AnsStarMap.end()) {
		temp = (iter->second);
		for (int i = 0; i < temp.size(); i++) {
			result.push_back(to_string(temp.at(i)));
		}
	}
	else {
		return result;
	}
	return result;
}

std::vector<string> Parent::getChildStar(int stmtNo) {
	map<int, vector<int>>::iterator iter;
	std::vector<string> result;
	std::vector<int> temp;

	iter = ChildStarMap.find(stmtNo);
	if (iter != ChildStarMap.end()) {  // find it 
		if (iter->first == stmtNo) {
			temp = iter->second;
			for (int i = 0; i < temp.size(); i++) {
				result.push_back(to_string(temp.at(i)));
			}
		}	
	}
	return result;
}


std::vector<int> Parent::getParentStarInt(int stmtNo) {
	map<int, vector<int>>::iterator iter;
	std::vector<int> result;
	std::vector<int> temp;

	if (stmtNo > AnsStarMap.size()) {
		return result;
	}
	iter = AnsStarMap.find(stmtNo);
	if (iter != AnsStarMap.end()) {
		temp = (iter->second);
		for (int i = 0; i < temp.size(); i++) {
			result.push_back(temp.at(i));
		}
	}
	else {
		return result;
	}
	return result;
}

std::vector<int> Parent::getChildStarInt(int stmtNo) {
	map<int, vector<int>>::iterator iter;
	std::vector<int> result;
	std::vector<int> temp;

	iter = ChildStarMap.find(stmtNo);
	if (iter != ChildStarMap.end()) {  // find it 
		if (iter->first == stmtNo) {
			temp = iter->second;
			for (int i = 0; i < temp.size(); i++) {
				result.push_back(temp.at(i));
			}
		}
	}
	return result;
}


std::vector<string> Parent::getParentForWhile(int stmtNo) {
	std::vector<int> temp = getParent(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string( temp.at(i)));
			}
		}
	}
	return ans;

}
std::vector<string> Parent::getChildForWhile(int stmtNo) {
	std::vector<int> temp = getChild(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string( temp.at(i)));
			}
		}
	}
	return ans;

}
std::vector<string> Parent::getParentForAssign(int stmtNo) {

	std::vector<int> temp = getParent(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;
}
std::vector<string> Parent::getChildForAssign(int stmtNo) {
	std::vector<int> temp = getChild(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;
}

std::vector<string> Parent::getParentForIf(int stmtNo) {
	std::vector<int> temp = getParent(stmtNo);
	std::vector<string> ans;
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
			if (line.find("If ") != std::string::npos || line.find("if ") != std::string::npos) {
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;

}
std::vector<string> Parent::getChildForIf(int stmtNo) {
	std::vector<int> temp = getChild(stmtNo);
	std::vector<string> ans;
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
			if (line.find("if ") != std::string::npos || line.find("If ") != std::string::npos) {
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;

}

//-------------------------for star-------------------------------------------------------------
std::vector<string> Parent::getParentStarForWhile(int stmtNo) {
	std::vector<int> temp = getParentStarInt(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;

}
std::vector<string> Parent::getChildStarForWhile(int stmtNo) {
	std::vector<int> temp = getChildStarInt(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;

}
std::vector<string> Parent::getParentStarForAssign(int stmtNo) {

	std::vector<int> temp = getParentStarInt(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;
}
std::vector<string> Parent::getChildStarForAssign(int stmtNo) {
	std::vector<int> temp = getChildStarInt(stmtNo);
	std::vector<string> ans;
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
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;
}

std::vector<string> Parent::getParentStarForIf(int stmtNo) {
	std::vector<int> temp = getParentStarInt(stmtNo);
	std::vector<string> ans;
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
			if (line.find("If ") != std::string::npos || line.find("if ") != std::string::npos) {
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;

}
std::vector<string> Parent::getChildStarForIf(int stmtNo) {
	std::vector<int> temp = getChildStarInt(stmtNo);
	std::vector<string> ans;
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
			if (line.find("if ") != std::string::npos || line.find("If ") != std::string::npos) {
				ans.push_back(to_string(temp.at(i)));
			}
		}
	}
	return ans;
}
