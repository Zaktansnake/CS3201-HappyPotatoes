#include "./Header/CFG.h"
#include <string>
#include <map>
#include <vector>
#include <stack>

using namespace std;
CFG::CFG() {
}

CFG::~CFG() {
}

int setConditions(string stmtLine);

static int currentPro = 0;
std::vector<std::vector<std::vector<int> >> CFGTable;
std::vector<std::vector<int>> CFG;
std::vector<int> CFGline;
std::map <string, int> procedureMap;
map<int, int> startAndEndOfProcedure;
int condition;
int prevStmtNo;
stack<int> conditionStack;
stack<int> parentStack;
stack<int> procedureStack;
bool flagForNextLevel;
bool flagForElseStart;
int endloopNo;


void setRoot(string procedure, int stmtNo ) {
	if (procedure.find("procedure ") != string::npos) {
		if (startAndEndOfProcedure.size() == 0) {
			startAndEndOfProcedure.insert(pair<int, int>(stmtNo + 1, -1));
			procedureStack.push(stmtNo + 1);
		}
		else {
			startAndEndOfProcedure.insert(pair<int, int>(stmtNo + 1, -1));
			int index = procedureStack.top();
			procedureStack.pop();
			procedureStack.push(stmtNo + 1);
			startAndEndOfProcedure.at(index) = stmtNo - 1;
		}
	}
}

void addNextNode(int stmtNo, string stmt) {
	condition = setConditions(stmt);
	CFGline.clear();
	endloopNo = std::count(stmt.begin(), stmt.end(), '}');
	if (condition == 0 && endloopNo == 0) {   // normal statement
		if (flagForElseStart) {
		   int parent = parentStack.top();
		   CFGline = CFGTable.at(currentPro).at(parent);
		   CFGline.push_back(stmtNo);
		   CFG.at(parent) = CFGline;
		   CFGTable.at(currentPro) = CFG;
		   flagForElseStart = false;
		}
		else {
			CFGline.push_back(stmtNo);
			CFG.push_back(CFGline);
			CFGTable.at(currentPro) = CFG;
		}
		
	}
	else if (condition == 1) {  // if statement
	    conditionStack.push(condition);
		parentStack.push(stmtNo);
		CFGline.push_back(stmtNo);
		CFG.push_back(CFGline);
		CFGTable.at(currentPro) = CFG;
		flagForNextLevel = true;

	}
	else if (condition == 2) {   // else statement, set the else statement next to the if statement
	   conditionStack.push(condition);
	   int parent = parentStack.top();
	   parentStack.push(parent);
	   flagForElseStart = true;

	}
	else if (condition == 3) {   // while statement
		flagForNextLevel = true;
		conditionStack.push(condition);
		parentStack.push(stmtNo);
		CFGline.push_back(stmtNo);
		CFG.push_back(CFGline);
		CFGTable.at(currentPro) = CFG;
		flagForNextLevel = true;
	}

	if (endloopNo > 0) {
		for (int i = 0; i < endloopNo; i++) {
			if (conditionStack.top() == 2) { // it is in the while statement
											 // set the current line back to the while
				int parent = parentStack.top();
				CFGline.push_back(parent);
				CFG.push_back(CFGline);
				CFGTable.at(currentPro) = CFG;
				parentStack.pop();
				conditionStack.pop();

			}
			else {
			    parentStack.pop();
				conditionStack.pop();
			}
		}
	}

}

vector<int> CFG::getNext(int stmtNo) {

     vector<int> result;
	 return result;

}

vector<int> CFG::getPrev(int stmtNo) {

	vector<int> result;
	return result;

}

bool CFG::isNext(int stmt1, int stmt2) {
	return false;
}

int setConditions(string stmtLine) {
	if (stmtLine.find("if") != std::string::npos) {
		condition = 1;
		
	}
	else if (stmtLine.find("else") != std::string::npos) {
		condition = 2;
		
	}
	else if (stmtLine.find("while") != std::string::npos) {
		condition = 3;
	
	}
	else {
		condition = 0;
	}
}

