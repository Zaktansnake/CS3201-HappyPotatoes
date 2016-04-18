#include "./Header/CFG.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

static int dummy = -2, prevStmtNum, tempElseNum;
map<int, vector<int>> CFGTable;
map<int, vector<int>> CFGReverseTable;
stack<pair<string, int>> openBracket; // string -> {; int -> currentStmtLine
stack<int> ifNumStack, beforeElseNumStack, whileNumStack;
bool elseStatus, whileStatus;
static int numOfStatement;

void checkBackBracket(int stmtNum);
int setConditions(string stmtLine);
string trimString(string stmt);


CFG::CFG() {
}

CFG::~CFG() {
}

void CFG::addRoot(string procedure, int stmtNo) {
	if (procedure.find("procedure ") != string::npos) {
		prevStmtNum = 0;
		openBracket.push(make_pair("{", -1));

		vector<int> tempResult;
		map<int, vector<int>>::iterator it;
		it = CFGTable.find(tempElseNum);
		if (it != CFGTable.end()) {
			tempResult = it->second;
			std::vector<int>::iterator itr = find(tempResult.begin(), tempResult.end(), stmtNo + 1);
			if (itr != tempResult.end()) {
				if (tempResult.size() == 1) {
					CFGTable.erase(it);
				}
				else {
					std::vector<int>::iterator position = std::find(tempResult.begin(), tempResult.end(), stmtNo+1);
					if (position != tempResult.end()) { // == myVector.end() means the element was not found
						tempResult.erase(position);
						CFGTable[tempElseNum] = tempResult;
					}
				}
			}
		}
		tempElseNum = 0;
	}
}

void CFG::addNextNode(int stmtNum, string stmtLine) {
	numOfStatement = stmtNum;
	try {
		if (setConditions(trimString(stmtLine)) == 0) {
			// normal assign
			if (prevStmtNum == 0) {
				prevStmtNum = stmtNum;
			}
			else {
				cout << "55 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
				CFGTable[prevStmtNum].push_back(stmtNum);
				CFGReverseTable[stmtNum].push_back(prevStmtNum);
				prevStmtNum = stmtNum;
			}
		}
		else if (setConditions(trimString(stmtLine)) == 1) {
			// if
			openBracket.push(make_pair("{", 1));
			ifNumStack.push(stmtNum);
			if (prevStmtNum == 0) {
				prevStmtNum = stmtNum;
			}
			else {
				cout << "68 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
				CFGTable[prevStmtNum].push_back(stmtNum);
				CFGReverseTable[stmtNum].push_back(prevStmtNum);
				prevStmtNum = stmtNum;
			}
		}
		else if (setConditions(trimString(stmtLine)) == 2) {
			//else
			openBracket.push(make_pair("{", 2));
			if (prevStmtNum == 0) {
				prevStmtNum = stmtNum;
			}
			else {
				if (elseStatus) {
					prevStmtNum = 0;
				}
				if (prevStmtNum > 0) {
					cout << "84 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
					CFGTable[prevStmtNum].push_back(stmtNum);
					CFGReverseTable[stmtNum].push_back(prevStmtNum);
					prevStmtNum = stmtNum;
				}
			}
		}
		else if (setConditions(trimString(stmtLine)) == 3) {
			// while
			openBracket.push(make_pair("{", 3));
			whileStatus = true;
			cout << "104 --- whileStatus :: " << whileStatus << " , " << stmtNum << endl;
			if (prevStmtNum == 0) {
				prevStmtNum = stmtNum;
			}
			else {
				cout << "97 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
				CFGTable[prevStmtNum].push_back(stmtNum);
				CFGReverseTable[stmtNum].push_back(prevStmtNum);
				prevStmtNum = stmtNum;
			}
			whileNumStack.push(stmtNum);
		}
		else if (setConditions(trimString(stmtLine)) == 4) {
			// close bracket
			checkBackBracket(stmtNum);
			if (openBracket.size() > 0) {
				pair<string, int> findCurrentStatus = openBracket.top();
				if (findCurrentStatus.second == 2) {
					elseStatus = true;
				}
			}

			if (whileNumStack.size() > 0) {
				whileStatus = true;
			}
		}
	}
	catch (exception &e) {
		cout << "Standard exception (for CFG): " << e.what() << endl;
	}
	catch (const std::out_of_range& oor) {
		cout << "out of range" << endl;
	}
}

void checkBackBracket(int stmtNum) {
	pair<string, int> temp = openBracket.top();
	int ifStmt = 0, whileStmt = 0;
	if (temp.second == 1) {
		//if
		int ifStmt = ifNumStack.top();
		cout << "128 :: " << ifStmt << " :: " << stmtNum + 1 << " :: " << stmtNum << endl;
		CFGTable[ifStmt].push_back(stmtNum + 1);
		CFGReverseTable[stmtNum+1].push_back(ifStmt);
		ifNumStack.pop();
		beforeElseNumStack.push(stmtNum);
		elseStatus = true;
		openBracket.pop();
	}
	else if (temp.second == 2) {
		// else
		int elseNum = beforeElseNumStack.top();
		cout << "whileStatus :: " << whileStatus << endl;
		cout << "elseNum :: " << elseNum << endl;
		openBracket.pop();
		if (openBracket.size() > 0) {
			temp = openBracket.top();
			cout << "142 :: " << temp.second << endl;
			if (temp.second > 0) {
				if (temp.second == 3) {
					// is inside while
					whileStmt = whileNumStack.top();
					cout << "147 :: " << elseNum << " :: " << whileStmt << " :: " << stmtNum << endl;
					CFGTable[elseNum].push_back(whileStmt);
					CFGReverseTable[whileStmt].push_back(elseNum);
				}
				else if(temp.second == 1) {
					cout << "168 :: " << whileStmt << endl;
					if (whileStatus) {
						map<int, vector<int>>::iterator it;
						it = CFGTable.find(elseNum);
						if (it == CFGTable.end()) {
							whileStmt = whileNumStack.top();
							cout << "174 :: " << elseNum << " :: " << whileStmt << " :: " << stmtNum + 1 << endl;
							CFGTable[elseNum].push_back(whileStmt);
							CFGReverseTable[whileStmt].push_back(elseNum);
							tempElseNum = elseNum;
						}
					}
				}
			}
			else {
				cout << "157 :: " << elseNum << " :: " << stmtNum + 1 << " :: " << stmtNum << endl;
				CFGTable[elseNum].push_back(stmtNum+1);
				CFGReverseTable[stmtNum+1].push_back(elseNum);
				tempElseNum = elseNum;
			}
		}
		beforeElseNumStack.pop();
		elseStatus = false;
	}
	else if (temp.second == 3) {
		// while
		whileStmt = whileNumStack.top();
		cout << "163 :: " << prevStmtNum << " :: " << whileStmt << endl;
		CFGTable[prevStmtNum].push_back(whileStmt);
		CFGReverseTable[whileStmt].push_back(prevStmtNum);
		prevStmtNum = whileStmt;
		whileNumStack.pop();
		openBracket.pop();
		whileStatus = false;
	}
	else {
		cout << "170 :: " << prevStmtNum << " :: " << temp.second << endl;
		//CFGTable[prevStmtNum].push_back(temp.second);
		openBracket.pop();
	}
}


int setConditions(string stmtLine) {
	int conditionStmt;
	if (stmtLine.find("if") != std::string::npos) {
		conditionStmt = 1;
	}
	else if (stmtLine.find("else") != std::string::npos) {
		conditionStmt = 2;
	}
	else if (stmtLine.find("while") != std::string::npos) {
		conditionStmt = 3;
	}
	else if (stmtLine.find("}") != std::string::npos) {
		conditionStmt = 4;
	}
	else {
		conditionStmt = 0;
	}
	return conditionStmt;
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


vector<int> CFG::getNext(int stmtNo) {
	vector<int> result;
	map<int, vector<int>>::iterator it;
	it = CFGTable.find(stmtNo);
	if (it != CFGTable.end()) {
		result = it->second;
	}
	return result;
}

vector<int> CFG::getPrev(int stmtNo) {
	vector<int>result;
	map<int, vector<int>>::iterator it;
	it = CFGReverseTable.find(stmtNo);
	if (it != CFGReverseTable.end()) {
		result = it->second;
	}
	return result;
}

bool CFG::isNext(int stmtNo1, int stmtNo2) {
	vector<int> ans;
	map<int, vector<int>>::iterator it;
	it = CFGTable.find(stmtNo1);
	if (it != CFGTable.end()) {
		ans = it->second;
	}
	if (ans.size() > 0) {
		std::vector<int>::iterator position = std::find(ans.begin(), ans.end(), stmtNo2);
		if (position != ans.end()) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool CFG::isNextStar(int stmtNo1, int stmtNo2) {
	try {
		if (stmtNo1 > numOfStatement || stmtNo2 > numOfStatement) {
			return false;
		}

		bool* visited = new bool[CFGTable.size()]();
		stack <int> stack;
		bool ans = false;
		bool goBackItSelf = false;
		stack.push(stmtNo1);

		vector<int> tempResult;
		map<int, vector<int>>::iterator itr;
		itr = CFGTable.find(tempElseNum);
		if (itr != CFGTable.end()) {
			tempResult = itr->second;
			std::vector<int>::iterator it;
			while (!stack.empty()) {
				int top = stack.top();
				stack.pop();
				visited[top] = true;
				for (it = tempResult.begin(); it != tempResult.end(); it++) {
					if (*it == stmtNo2) {
						if (goBackItSelf == false) {
							goBackItSelf = true;
							return true;
						}
					}
					if (!visited[*it]) {
						stack.push(*it);
						if (*it == stmtNo2) {
							ans = true;
							return ans;
						}
					}
				}
			}
		}
		return ans;
	}
	catch (exception &e) {
		//cout << "Standard exception (for findMethod): " << e.what() << endl;
	}
	catch (const std::out_of_range& oor) {
		// cout << "out of range""<<endl;
	}
	return false;
}

vector<int> CFG::getNextStar(int stmtNo) {
	vector<int>ans;
	try {
		bool* visited = new bool[CFGTable.size()]();
		stack <int> stack;
		bool goBackItSelf = false;

		if (stmtNo > numOfStatement) {
			return ans;
		}
		stack.push(stmtNo);

		vector<int> tempResult;
		map<int, vector<int>>::iterator itr;
		itr = CFGTable.find(tempElseNum);
		if (itr != CFGTable.end()) {
			tempResult = itr->second;
			std::vector<int>::iterator it;
			while (!stack.empty()) {
				int top = stack.top();
				stack.pop();
				visited[top] = true;
				for (it = tempResult.begin(); it != tempResult.end(); it++) {
					if (*it == stmtNo) {
						if (goBackItSelf == false) {
							ans.push_back(*it);
							goBackItSelf = true;
						}
					}
					if (!visited[*it]) {
						stack.push(*it);
						ans.push_back(*it);
					}
				}
			}
		}
		return ans;
	}
	catch (exception &e) {
		cout << "Standard exception (for findMethod): " << e.what() << endl;
	}
	catch (const std::out_of_range& oor) {
		cout << "out of range" << endl;
	}
}

vector<int> CFG::getPrevStar(int stmtNo) {
	vector<int>result;
	
	return result;
}

vector<string> CFG::getNextString(int stmtNo) {
	return CFG::convertIntToString(CFG::getNext(stmtNo));
}

vector<string> CFG::getPrevString(int stmtNo) {
	return CFG::convertIntToString(CFG::getPrev(stmtNo));
}

vector<string> CFG::getNextStarString(int stmtNo) {
	return CFG::convertIntToString(CFG::getNextStar(stmtNo));
}

vector<string> CFG::getPrevStarString(int stmtNo) {
	return CFG::convertIntToString(CFG::getPrevStar(stmtNo));
}


std::vector<string> CFG::convertIntToString(vector<int> temp) {
	vector<string> result;
	if (!temp.empty()) {
		for (int i = 0; i < temp.size(); i++) {
			result.push_back(to_string(temp.at(i)));
		}
	}
	return result;
}


void CFG::printCFGTable() {
	cout << endl;
	cout << "CFG Table :: " << endl;
	for (map<int, vector<int>>::iterator ii = CFGTable.begin(); ii != CFGTable.end(); ++ii) {
		cout << (*ii).first << ": ";
		vector<int> inVect = (*ii).second;
		for (unsigned j = 0; j < inVect.size(); j++) {
			cout << inVect[j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
