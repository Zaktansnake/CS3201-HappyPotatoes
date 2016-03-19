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

static int currentPro = 0;
std::vector<std::vector<std::vector<int> >> CFGTable;
std::vector<std::vector<int>> CFG;
std::vector<int> CFGline;
std::map <string, int> procedureMap;
int condition;
stack <int> conditionStack;
stack <int> conditionStmtNo;
stack <int> ifCondition;
stack <int> elseCondition;
stack <int> whileCondition;
stack <int> dummyNodeStack;
int endloop = 0;
int prevStmtNo = 0;
std::vector<string> totalStmtLine;
bool elseFlag = false;
int dummyStmtNo = -1;
bool flagForNextOfLoop = false;
bool flagForNextOfLoopBackWhile = false;
int prevLoop = 0;

void setRoot(std::string procedure) {
	map<string, int>::iterator iter;
	iter = procedureMap.find(procedure);
	if (iter == procedureMap.end()) {
		procedureMap.insert(pair<string, int>(procedure, currentPro++));
		prevStmtNo = 0;
	}
}

void addNextNode(int stmtNo, string stmt) {
	CFGline.clear();
	totalStmtLine.push_back(stmt); // use to store the whole procedure stmtline as reference later
	// check if there is flag shows prev stmt is end of loop
	if (flagForNextOfLoop) {   // prev is the end of else
		while (dummyNodeStack.size() != 0) {
			int index = dummyNodeStack.top();

			
		}
	    
		flagForNextOfLoop = false;
	}

	if (flagForNextOfLoopBackWhile) {
		CFGline.push_back(whileCondition.top());
		whileCondition.pop();
		CFG.push_back(CFGline);
		CFGTable.at(currentPro) = CFG;
	}

	// decide on conditions
	if (stmt.find("if") != std::string::npos) {
		condition = 1;

	}
	else if (stmt.find("else") != std::string::npos) {
		condition = 2;

	}
	else if (stmt.find("while") != std::string::npos) {
		condition = 3;

	}
	else {
		condition = 0;
	}
	// there are four condition, with loop, normal stmt, with } , only }
	// with loop
	
	if (condition != 0) {
		CFGline.push_back(stmtNo);
		CFG.push_back(CFGline);
		if (CFGTable.size() == 0) {      // if the CFGtable is empty just push back the CFG
			CFGTable.push_back(CFG);
		}
		else {
            CFGTable.at(currentPro) = CFG;   // else replace the new CFG to old CFG
		}

		// push to loop stack
	    conditionStack.push(condition);
		conditionStmtNo.push(stmtNo);
		prevStmtNo = stmtNo;
	}

	endloop = std::count(stmt.begin(), stmt.end(), '}'); // count if there is } in the string
	if (endloop > 0 && stmt.size() != endloop) {   // it is stmtment contains }
		for (int i = 0; i < endloop; i++) {
			if (conditionStack.size() == 0) {   //if it is empty stack --> no condition stmt, end procedure
				break;
			}
			if (conditionStack.top() == 1) {  // it is if stmt
				ifCondition.push(conditionStmtNo.top());
				dummyNodeStack.push(stmtNo);
				conditionStmtNo.pop();
				conditionStack.pop();
				// get the current line into the table
				CFGline.push_back(stmtNo);
				CFG.push_back(CFGline);
				CFGTable.at(currentPro) = CFG;
				CFGline.clear();
				prevStmtNo = stmtNo;
			}
			else if (conditionStack.top() == 2) {
				elseCondition.push(conditionStmtNo.top());
				dummyNodeStack.push(stmtNo);
				conditionStmtNo.pop();
				conditionStack.pop();
				flagForNextOfLoop = true;   // which means next line will be the prev of endif and endElse
											// get the current line into the table
				CFGline.push_back(stmtNo);
				CFG.push_back(CFGline);
				CFGTable.at(currentPro) = CFG;
				CFGline.clear();
				prevStmtNo = stmtNo;
			}
			else if (conditionStack.top() == 3) {
				flagForNextOfLoopBackWhile = true;
				whileCondition.push(stmtNo);
				CFGline.push_back(stmtNo);  // add the line as normal
				CFG.push_back(CFGline);
				CFGTable.at(currentPro) = CFG;
				CFGline.clear();
				prevStmtNo = stmtNo;
			}
		}
	}
	else if (endloop > 0 && stmt.size() == endloop) {  // only contains}
		for (int i = 0; i < endloop; i++) {
			if (conditionStack.size() == 0) {   //if it is empty stack --> no condition stmt, end procedure
				break;
			}
			if (conditionStack.top() == 1) {   // end if
				ifCondition.push(conditionStmtNo.top());
				dummyNodeStack.push(prevStmtNo);
				conditionStmtNo.pop();
				conditionStack.pop();
			}
			else if (conditionStack.top() == 2) {   // end else
				elseCondition.push(conditionStmtNo.top());
				dummyNodeStack.push(prevStmtNo);
				conditionStmtNo.pop();
				conditionStack.pop();
				flagForNextOfLoop = true;
			}
			else if (conditionStack.top() == 3) {   // end while
				flagForNextOfLoopBackWhile = true;
				whileCondition.push(prevStmtNo);
			}
		}
	}

	if (condition == 0 && endloop == 0) {  // normal stmt
		CFGline.push_back(stmtNo);
		CFG.push_back(CFGline);
		CFGTable.at(currentPro) = CFG;
		CFGline.clear();
		prevStmtNo = stmtNo;
	}
}

void setConditions(string stmtLine) {
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

