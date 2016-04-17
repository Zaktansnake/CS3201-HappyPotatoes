#include "./Header/CFG.h"
#include "Header/Parent.h"
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

static int dummy = -2, prevStmtNum;
map<int, vector<int>> CFGTable;
stack<pair<string, int>> openBracket; // string -> {; int -> currentStmtLine
stack<int> ifNumStack, beforeElseNumStack, whileNumStack;
bool elseStatus;

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

		map<int, vector<int>>::iterator it;
		it = CFGTable.find(stmtNo);
		if (it != CFGTable.end()) {
			cout << "blahblahblah" << endl;
			CFGTable.erase(it);
		}
	}
}

void CFG::addNextNode(int stmtNum, string stmtLine) {

	try {
		if (setConditions(trimString(stmtLine)) == 0) {
			// normal assign
			if (prevStmtNum == 0) {
				prevStmtNum = stmtNum;
			}
			else {
				cout << "44 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
				CFGTable[prevStmtNum].push_back(stmtNum);
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
				cout << "57 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
				CFGTable[prevStmtNum].push_back(stmtNum);
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
					cout << "73 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
					CFGTable[prevStmtNum].push_back(stmtNum);
					prevStmtNum = stmtNum;
				}
			}
		}
		else if (setConditions(trimString(stmtLine)) == 3) {
			// while
			openBracket.push(make_pair("{", 3));
			if (prevStmtNum == 0) {
				prevStmtNum = stmtNum;
			}
			else {
				cout << "86 :: " << prevStmtNum << " :: " << stmtNum << " :: " << stmtNum << endl;
				CFGTable[prevStmtNum].push_back(stmtNum);
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
		}
	}
	catch (exception &e) {
		cout << "Standard exception (for CFG): " << e.what() << endl;
	}
}

void checkBackBracket(int stmtNum) {
	pair<string, int> temp = openBracket.top();
	int ifStmt = 0, whileStmt = 0;
	if (temp.second == 1) {
		//if
		int ifStmt = ifNumStack.top();
		cout << "66 :: " << ifStmt << " :: " << stmtNum + 1 << " :: " << stmtNum << endl;
		CFGTable[ifStmt].push_back(stmtNum + 1);
		ifNumStack.pop();
		cout << "beforeElseNumStack.push() :: " << stmtNum << endl;
		beforeElseNumStack.push(stmtNum);
		elseStatus = true;
		openBracket.pop();
	}
	else if (temp.second == 2) {
		// else
		int elseNum = beforeElseNumStack.top();
		openBracket.pop();
		if (openBracket.size() > 0) {
			temp = openBracket.top();
			cout << "136 :: " << temp.second << endl;
			if (temp.second > 0) {
				if (temp.second == 3) {
					// is inside while
					whileStmt = whileNumStack.top();
					cout << "141 :: " << elseNum << " :: " << whileStmt << " :: " << stmtNum << endl;
					CFGTable[elseNum].push_back(whileStmt);
				}
			}
			else {
				cout << "138 :: " << elseNum << " :: " << stmtNum + 1 << " :: " << stmtNum << endl;
				CFGTable[elseNum].push_back(stmtNum+1);
			}
		}
		beforeElseNumStack.pop();
		elseStatus = false;
	}
	else if (temp.second == 3) {
		// while
		whileStmt = whileNumStack.top();
		cout << "158 :: " << prevStmtNum << " :: " << whileStmt << endl;
		CFGTable[prevStmtNum].push_back(whileStmt);
		prevStmtNum = whileStmt;
		whileNumStack.pop();
		openBracket.pop();
	}
	else {
		cout << "165 :: " << prevStmtNum << " :: " << temp.second << endl;
		//CFGTable[prevStmtNum].push_back(temp.second);
		prevStmtNum = temp.second;
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
	return result;
}

vector<int> CFG::getPrev(int stmtNo) {
	vector<int>result;
	return result;
}

bool CFG::isNext(int stmtNo1, int stmtNo2) {
	return false;
}

bool CFG::isNextStar(int s1, int s2) {
	return false;
}

vector<int> CFG::getNextStar(int stmtNo) {
	vector<int> ans;
	return ans;
}

vector<int> CFG::getPrevStar(int stmtNo) {
	vector<int> ans;
	return ans;
}

vector<string> CFG::getNextString(int stmtNo) {
	vector<int> result;
	map<int, vector<int>>::iterator it;
	it = CFGTable.find(stmtNo);
	if (it != CFGTable.end()) {
		result = it->second;
	}
	return CFG::convertIntToString(result);
}

vector<string> CFG::getPrevString(int stmtNo) {
	vector<string>result;
	return result;
}

vector<string> CFG::getNextStarString(int stmtNo) {
	vector<string> ans;
	return ans;
}

vector<string> CFG::getPrevStarString(int stmtNo) {
	vector<string> ans;
	return ans;
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
