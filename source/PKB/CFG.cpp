#include "./Header/CFG.h"
#include "Header/Parent.h"
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
CFG::CFG() {
}

CFG::~CFG() {
}

static int dummy = -1;

static int currentPro = 0;
static int currentP = 0;
std::vector<int> proRecord;  // record the procedure for each stmt
std::vector<std::vector<std::vector<int> >> CFGTable;
std::vector<std::vector<int>> CFGstmt;
std::vector<int> CFGline;

static int numOfStatement = 0;

std::vector<std::vector<int>> revCFGstmt;
std::vector<int> revCFGline;

std::map <string, int> procedureMap;
map<int, int> startEndOfProcedure;
int conditionstmt;
int prevStmtNo;
stack<int> conditionStack;
stack<int> parentStack;
stack<int> proStack;
stack <int> closingStack;
stack <int> clostingCondition;
stack <int> ifRecord;
//stack <int> starRecord;

bool flagNextLevelStart = false;
bool flagForElseStart = false;;
bool flagForClose = false;
bool flag = false;
bool flagForCorrectElseIf = false;
bool flagForNewProc = false;

int lastWhile = 0;
int lastIf = 0;
int lastElse = 0;

int endloop;

vector<int> resultStar;
map<int, int> resultStarMap;
map<int, int>::iterator itStar;


int setConditions(string stmtLine);
string trimString(string stmt);
bool checkProcedure(int s1, int s2);
int getEndProcNo(int s1);


void CFG::addRoot(string procedure, int stmtNo) {
	if (procedure.find("procedure ") != string::npos) {
		if (startEndOfProcedure.size() == 0) {
			startEndOfProcedure.insert(pair<int, int>(stmtNo + 1, -1));
			proStack.push(stmtNo + 1);
		}
		else {
			currentP++;
			startEndOfProcedure.insert(pair<int, int>(stmtNo + 1, -1));
			int index = proStack.top();
			proStack.pop();
			proStack.push(stmtNo + 1);
			startEndOfProcedure.at(index) = stmtNo;
			flagForNewProc = true;
		}
		CFGline.clear();
		if (CFGstmt.size() == 0) {
			CFGstmt.clear();
			CFGTable.push_back(CFGstmt);
		}
	}

	flagNextLevelStart = false;
	flagForElseStart = false;;
	flagForClose = false;
	flag = false;
	flagForCorrectElseIf = false;
	while (conditionStack.size() != 0) {
		conditionStack.pop();
	}
	
}

void CFG::addNextNode(int stmtNo, string stmt) {
	numOfStatement = stmtNo;
	CFGline.clear();
	int parentForElseIf = -1;
	stmt = trimString(stmt);
	conditionstmt = setConditions(stmt);
	CFGline.clear();
	if (stmt.compare("}") != 0 && stmt.find("else ") == string::npos) {
		proRecord.push_back(currentP);
	}
	endloop = std::count(stmt.begin(), stmt.end(), '}');
	if (flagForClose && stmt.size() != endloop) {
		if (conditionstmt == 3) {
			if (parentStack.size() != 0) {
				parentForElseIf = parentStack.top();
			}
			parentStack.push(stmtNo);
			conditionStack.push(conditionstmt);
			if (closingStack.size() != 0) {
				int prev = closingStack.top();
				closingStack.pop();
				int prevCon = clostingCondition.top();
				clostingCondition.pop();
				if (prevCon == 3) {  // follow fan is a while loop
					CFGline = CFGTable.at(currentPro).at(prev);
					CFGline.push_back(stmtNo);
					CFGstmt.at(prev) = CFGline;
					CFGTable.at(currentPro) = CFGstmt;
				}
				else {
				//	CFGline.push_back(dummy);
				//	CFGstmt.push_back(CFGline);
				//	CFGTable.at(currentPro) = CFGstmt;

					if (prevCon == 2) {
						CFGline.push_back(dummy);
						CFGstmt.push_back(CFGline);
						CFGTable.at(currentPro) = CFGstmt;
					}
					else {
						if (parentForElseIf != -1) {
							CFGline = CFGTable.at(currentPro).at(parentForElseIf);
							CFGline.push_back(stmtNo);
							CFGstmt.at(parentForElseIf) = CFGline;
							CFGTable.at(currentPro) = CFGstmt;
						}
						else {
							CFGline.push_back(dummy);
							CFGstmt.push_back(CFGline);
							CFGTable.at(currentPro) = CFGstmt;
						}
						
					}

				}


				// need to complete.......................................
			}
		}
		else if (conditionstmt == 2) { // prev is end else
			if (endloop > 0) {
				int parent = parentStack.top();
				parentStack.push(parent);
				conditionStack.push(conditionstmt);
				int prev = closingStack.top();
				closingStack.pop();
				int con = clostingCondition.top();
				clostingCondition.pop();
				if (con == 3) {
					CFGline = CFGTable.at(currentPro).at(prev);
					CFGline.push_back(stmtNo);
					CFGstmt.at(prev) = CFGline;
					CFGTable.at(currentPro) = CFGstmt;
				}
				else {

					// need to complete.....................................

				}
				// need to complete......................................
			}
			else {
				int parent = ifRecord.top();
				ifRecord.pop();
				parentStack.push(parent);
			//	if (conditionstmt == 2) {
		//			conditionStack.push(1);
	//				flagForCorrectElseIf = false;
	//			}
	//			else {
                    conditionStack.push(1);
					flagForCorrectElseIf = true;
		//		}
				
				flag = true;
				
			}


		}
		else if (conditionstmt == 1) {
			if (parentStack.size() != 0) {
				parentForElseIf = parentStack.top();
			}
			else {
				parentForElseIf = -1;
			}
			parentStack.push(stmtNo);
			conditionStack.push(conditionstmt);
			if (closingStack.size() != 0) {
				int prev = closingStack.top();
				closingStack.pop();
				int prevCon = clostingCondition.top();
				clostingCondition.pop();
				if (prevCon == 3) {  // follow fan is a while loop
					CFGline = CFGTable.at(currentPro).at(prev);
					CFGline.push_back(stmtNo);
					CFGstmt.at(prev) = CFGline;
					CFGTable.at(currentPro) = CFGstmt;
				}
				if (prevCon == 2) {
					CFGline.push_back(dummy);
					CFGstmt.push_back(CFGline);
					CFGTable.at(currentPro) = CFGstmt;
				}
				else {
					if (parentForElseIf != -1) {
						CFGline = CFGTable.at(currentPro).at(parentForElseIf);
						CFGline.push_back(stmtNo);
						CFGstmt.at(parentForElseIf) = CFGline;
						CFGTable.at(currentPro) = CFGstmt;
					}
					else {
						CFGline.push_back(dummy);
						CFGstmt.push_back(CFGline);
						CFGTable.at(currentPro) = CFGstmt;
					}
					
				}

				// need to complete.......................................
			}

		}
		else if (conditionstmt == 0 && stmt.size() != endloop) {
			if (closingStack.size() != 0) {
				int prev = closingStack.top();
				closingStack.pop();
				int con = clostingCondition.top();
				clostingCondition.pop();
				if (con == 3) {
					CFGline = CFGTable.at(currentPro).at(prev);
					CFGline.push_back(stmtNo);
					CFGstmt.at(prev) = CFGline;
					CFGTable.at(currentPro) = CFGstmt;
				}
				else {
					// need to complete.......................................
					if (!flagForCorrectElseIf) {
						CFGline.push_back(dummy);
						CFGstmt.push_back(CFGline);
						CFGTable.at(currentPro) = CFGstmt;
					}


				}
			}
			

		}
		if (!flag) {
			flagForClose = false;
		}
		else {
			flagForClose = true;
			flag = false;
		}

	}
	else {
		if (conditionstmt == 0 && stmt.size() != endloop && flagForNewProc == false) {  // normal statement
			CFGline.push_back(stmtNo);
			CFGstmt.push_back(CFGline);
			CFGTable.at(currentPro) = CFGstmt;

		}
		else if (conditionstmt == 1) {
			if (!flagForNewProc) {
				parentStack.push(stmtNo);
				conditionStack.push(conditionstmt);
				CFGline.push_back(stmtNo);
				CFGstmt.push_back(CFGline);
				CFGTable.at(currentPro) = CFGstmt;
			}
			else {
				parentStack.push(stmtNo);
				conditionStack.push(conditionstmt);
			}


		}
		else if (conditionstmt == 2) {
			int parent = parentStack.top();
			parentStack.push(parent);
			conditionStack.push(conditionstmt);
		}
		else if (conditionstmt == 3) {
			if (!flagForNewProc) {
				parentStack.push(stmtNo);
				conditionStack.push(conditionstmt);
				CFGline.push_back(stmtNo);
				CFGstmt.push_back(CFGline);
				CFGTable.at(currentPro) = CFGstmt;
			}
			else {
				parentStack.push(stmtNo);
				conditionStack.push(conditionstmt);
			}

		}
	}
	flagForNewProc = false;
	if (endloop > 0) {
		int currentNo;
		flagForClose = true;
		for (int i = 0; i < endloop; i++) {
			if (parentStack.size() == 0) {
				while (closingStack.size() != 0) {
					closingStack.pop();
					clostingCondition.pop();
				}
				while (ifRecord.size() != 0) {
					ifRecord.pop();
				}
				flagForClose = false;
				flagForCorrectElseIf = false;
				flag = false;
				flagNextLevelStart = false;
				break;
			}
			int parent = parentStack.top();
			parentStack.pop();
			int con = conditionStack.top();
			conditionStack.pop();
			int index = CFGstmt.size();
			if (con == 3) { // end while, set the current node back to its parent
				if (closingStack.size() == 0) { // current node it the stmtNo
					currentNo = stmtNo;
				}
				else if (clostingCondition.top() != 3) {
					currentNo = stmtNo;
					closingStack.pop();
					clostingCondition.pop();
				}
				else {
					currentNo = closingStack.top();
					closingStack.pop();
					clostingCondition.pop();
				}
				closingStack.push(parent);
				clostingCondition.push(con);
				if (index == stmtNo) {
					CFGline.push_back(parent);
					CFGstmt.push_back(CFGline);
					CFGTable.at(currentPro) = CFGstmt;
				}
				else {
					CFGline = CFGstmt.at(currentNo);
					CFGline.push_back(parent);
					CFGstmt.at(currentNo) = CFGline;
					CFGTable.at(currentPro) = CFGstmt;
				}
			}
			else if (con == 2) {  
				
					closingStack.push(stmtNo);
					clostingCondition.push(con);
					CFGline = CFGTable.at(currentPro).at(parent);
					CFGline.push_back(stmtNo + 1);
					CFGstmt.at(parent) = CFGline;
					CFGTable.at(currentPro) = CFGstmt;
			

			}
			else if (con == 1) {
				if (!flagForCorrectElseIf) {
					CFGline.push_back(dummy);
					CFGstmt.push_back(CFGline);
					CFGTable.at(currentPro) = CFGstmt;
					ifRecord.push(parent);
				}
				else {
					CFGline = CFGTable.at(currentPro).at(parent);
					if (CFGline.size() == 2 && (CFGline.at(0) != -1 && CFGline.at(1) != -1)) {
					      flagForCorrectElseIf = false;
					}
					else {
                         CFGline.push_back(stmtNo);
					     CFGstmt.at(parent) = CFGline;
					     CFGTable.at(currentPro) = CFGstmt;
					     flagForCorrectElseIf = false;
					}
					
				}

				closingStack.push(stmtNo);
				clostingCondition.push(con);


			}
		}
	}
}

void CFG::reverCFG() {
	// CFGTable, revCFGTable

	vector<vector<int>> temp = CFGTable.at(currentPro);
	vector<vector<int>> arr(numOfStatement + 2);
	vector<int> prevRecord;
	vector<int> ::iterator ite;
	for (int i = 0; i < temp.size(); i++) {
		for (ite = temp.at(i).begin(); ite != temp.at(i).end(); ite++) {
			if (*ite == -1) {  // if it is the end node
				prevRecord = arr[numOfStatement + 1]; // store at the back
				prevRecord.push_back(i);
				arr[numOfStatement + 1] = prevRecord;

			}
			else {
				prevRecord = arr[*ite];
				prevRecord.push_back(i);
				arr[*ite] = prevRecord;
			}

		}
	}
	revCFGstmt = arr;
}

int setConditions(string stmtLine) {
	if (stmtLine.find("if") != std::string::npos) {
		conditionstmt = 1;

	}
	else if (stmtLine.find("else") != std::string::npos) {
		conditionstmt = 2;

	}
	else if (stmtLine.find("while") != std::string::npos) {
		conditionstmt = 3;

	}
	else {
		conditionstmt = 0;
	}
	return conditionstmt;
}

string trimString(string stmt) {
	stmt.erase(remove(stmt.begin(), stmt.end(), '\t'), stmt.end());
	size_t endpos = stmt.find_last_not_of(" ");
	if (string::npos != endpos) {
		stmt = stmt.substr(0, endpos + 1);
	}
	size_t startpos = stmt.find_first_not_of(" ");
	if (string::npos != endpos) {
		stmt = stmt.substr(startpos);
	}
	return stmt;
}

/*
bool checkProcedure(int s1, int s2) {

int start = 0;
int end = 0;
if (s1 == s2) {
return false;
}
for (map<int, int>::iterator it = startEndOfProcedure.begin(); it != startEndOfProcedure.end(); ++it) {
if (it->first <= s1 && it->second >= s1) {
start = it->first;
end = it->second;
break;
}
else if (it->first <= s1 && it->second == -1) {
start = it->first;
end = it->second;
break;
}
}
if (start <= s2 && end >= s2) {
return true;
}
else if (start <= s2 && end == -1) {
return true;
}
else {
return false;
}

}
*/
vector<int> CFG::getNext(int stmtNo) {
	
	vector<int> result;
	if (stmtNo > numOfStatement) {
	   return result;
	}
	vector<int> temp;
	temp = CFGTable.at(currentPro).at(stmtNo);
	for (int i = 0; i < temp.size(); i++) {
		//		if (checkProcedure(stmtNo, temp.at(i))) {
		if (temp.at(i) == -1) {
			return result;
		}
		result.push_back(temp.at(i));
		//		}
	}
	return result;

}

//.....................................................................
// this method can be optimized ........................................
vector<int> CFG::getPrev(int stmtNo) {
	
	vector<int>result;
	if (stmtNo > numOfStatement) {
		return result;
	}
	vector<int>temp = revCFGstmt.at(stmtNo);
	result = temp;
	return result;


	/*	vector<int> result;
	vector<int> temp;
	vector<int> temp2;
	vector<vector<int>> records;
	bool isPrv = false;
	records = CFGTable.at(currentPro);
	for (int i = 0; i < records.size(); i++) {
	temp2 = records.at(i);
	for (int j = 0; j < temp2.size(); j++) {
	if (temp2.at(j) == stmtNo) {
	isPrv = true;
	break;
	}
	}
	if (isPrv) {
	temp.push_back(i);
	isPrv = false;
	}
	}
	for (int i = 0; i < temp.size(); i++) {
	if (checkProcedure(temp.at(i), stmtNo)) {
	result.push_back(temp.at(i));
	}
	}
	return result;
	*/
}


// check is Next
bool CFG::isNext(int stmtNo1, int stmtNo2) {
     if (stmtNo1 > numOfStatement|| stmtNo2 > numOfStatement) {
		return false;
	}
	vector<int> temp;
	temp = CFGTable.at(currentPro).at(stmtNo1);
	for (int i = 0; i < temp.size(); i++) {
		if (temp.at(i) == stmtNo2) {
			return true;
		}
	}
	return false;

}


bool CFG::isNextStar(int s1, int s2) {
	if (s1 > numOfStatement || s2 > numOfStatement) {
		return false;
	}
	bool* visited = new bool[CFGTable.at(currentPro).size()]();
	stack <int> stack;
	bool ans = false;
	stack.push(s1);
	vector<int> ::iterator it;

	while (!stack.empty()) {
		int top = stack.top();
		stack.pop();
		visited[top] = true;
		for (it = CFGTable.at(currentPro).at(top).begin(); it != CFGTable.at(currentPro).at(top).end(); it++) {
			if (!visited[*it]) {
				stack.push(*it);
				if (*it == s2) {
					ans = true;
					return ans;
				}
			}
		}
	}
	return ans;



	//need to complete
}

vector<int> CFG::getNextStar(int stmtNo) {
	
	bool* visited = new bool[CFGTable.at(currentPro).size()]();
	stack <int> stack;
	vector<int> ans;
	if (stmtNo > numOfStatement) {
		return ans;
	}
	stack.push(stmtNo);
	vector<int> ::iterator it;

	while (!stack.empty()) {
		int top = stack.top();
		stack.pop();
		visited[top] = true;
		for (it = CFGTable.at(currentPro).at(top).begin(); it != CFGTable.at(currentPro).at(top).end(); it++) {
			if (!visited[*it]) {
				stack.push(*it);
				ans.push_back(*it);
			}
		}
	}
	return ans;
}

vector<int> CFG::getPrevStar(int stmtNo) {
	bool* visited = new bool[CFGTable.at(currentPro).size()]();
	stack <int> stack;
	vector<int> ans;
	if (stmtNo > numOfStatement) {
		return ans;
	}
	stack.push(stmtNo);
	vector<int> ::iterator it;

	while (!stack.empty()) {
		int top = stack.top();
		stack.pop();
		visited[top] = true;
		for (it = revCFGstmt.at(top).begin(); it != revCFGstmt.at(top).end(); it++) {
			if (!visited[*it]) {
				stack.push(*it);
				if (*it != 0) {
					ans.push_back(*it);
				}

			}
		}
	}
	return ans;
}

/*
int getEndProcNo(int s1) {
int start = 0;
int end = 0;
for (map<int, int>::iterator it = startEndOfProcedure.begin(); it != startEndOfProcedure.end(); ++it) {
if (it->first <= s1 && it->second >= s1) {
start = it->first;
end = it->second;
}
else if (it->first <= s1 && it->second == -1) {
start = it->first;
end = CFGTable.at(currentPro).size()-1;
}
}
return end;
}
*/

// for return vector<string> ------------------------------------------------------------------

vector<string> CFG::getNextString(int stmtNo) {

	vector<string> result;
	if (stmtNo > numOfStatement) {
		return result;
	}
	vector<int> temp;
	temp = CFGTable.at(currentPro).at(stmtNo);
	for (int i = 0; i < temp.size(); i++) {
		//		if (checkProcedure(stmtNo, temp.at(i))) {
		if (temp.at(i) == -1) {
			return result;
		}
		result.push_back(to_string(temp.at(i)));
		//		}
	}
	return result;

}


vector<string> CFG::getPrevString(int stmtNo) {

	vector<string>result;
	if (stmtNo > numOfStatement) {
		return result;
	}
	vector<int>temp = revCFGstmt.at(stmtNo);
	for (int i = 0; i < temp.size(); i++) {
		result.push_back(to_string(temp.at(i)));
	}
	return result;
	/*	vector<int> result;
	vector<int> temp;
	vector<int> temp2;
	vector<vector<int>> records;
	bool isPrv = false;
	records = CFGTable.at(currentPro);
	for (int i = 0; i < records.size(); i++) {
	temp2 = records.at(i);
	for (int j = 0; j < temp2.size(); j++) {
	if (temp2.at(j) == stmtNo) {
	isPrv = true;
	break;
	}
	}
	if (isPrv) {
	temp.push_back(i);
	isPrv = false;
	}
	}
	for (int i = 0; i < temp.size(); i++) {
	if (checkProcedure(temp.at(i), stmtNo)) {
	result.push_back(temp.at(i));
	}
	}
	return result;
	*/
}


vector<string> CFG::getNextStarString(int stmtNo) {
	bool* visited = new bool[CFGTable.at(currentPro).size()]();
	stack <int> stack;
	vector<string> ans;
	if (stmtNo > numOfStatement) {
		return ans;
	}
	stack.push(stmtNo);
	vector<int> ::iterator it;

	while (!stack.empty()) {
		int top = stack.top();
		stack.pop();
		visited[top] = true;
		for (it = CFGTable.at(currentPro).at(top).begin(); it != CFGTable.at(currentPro).at(top).end(); it++) {
			if (!visited[*it]) {
				stack.push(*it);
				ans.push_back(to_string(*it));
			}
		}
	}
	return ans;
}


vector<string> CFG::getPrevStarString(int stmtNo) {
	bool* visited = new bool[CFGTable.at(currentPro).size()]();
	stack <int> stack;
	vector<string> ans;
	if (stmtNo > numOfStatement) {
		return ans;
	}
	stack.push(stmtNo);
	vector<int> ::iterator it;

	while (!stack.empty()) {
		int top = stack.top();
		stack.pop();
		visited[top] = true;
		for (it = revCFGstmt.at(top).begin(); it != revCFGstmt.at(top).end(); it++) {
			if (!visited[*it]) {
				stack.push(*it);
				if (*it != 0) {
					ans.push_back(to_string(*it));
				}

			}
		}
	}
	return ans;
}




