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
stack <int> dummyNodeStack;
int endloop = 0;
int prevStmtNo = 0;
std::vector<string> totalStmtLine;
bool elseFlag = false;
int dummyStmtNo = -1;

bool isCondition(string stmtLine);

void setRoot(std::string procedure) {
   map<string, int>::iterator iter;
   iter = procedureMap.find(procedure);
   if (iter == procedureMap.end()) {
      procedureMap.insert(pair<string,int>(procedure,currentPro++));
	  prevStmtNo = 0;
   }
}

void addNextNode(int stmtNo, string stmt) {
    CFGline.clear();
	CFG.clear();
	if (CFGTable.size() == 0) {
		CFGline.push_back(stmtNo);
		CFG.push_back(CFGline);
		CFGTable.push_back(CFG);
		prevStmtNo = stmtNo;
		totalStmtLine.push_back(stmt);
	}
	else {
		if (isCondition(stmt)) {   // if it is condition statement with {
		    conditionStack.push(condition);
			if (condition == 2) {  // it is else stmt
			     // there is no statement no for else stmt
				 elseFlag = true;
				 conditionStmtNo.push(stmtNo+1);
			}
			else {
                 conditionStmtNo.push(stmtNo);
			}
			
			CFGline.push_back(stmtNo);
			CFG.push_back(CFGline);
			CFGTable.at(currentPro) = CFG;
			prevStmtNo = stmtNo;

		}
		else {   // if it is not condition statement
			endloop = std::count(stmt.begin(), stmt.end(), '}'); // count if there is } in the string

			if (endloop > 0) {
				for (int i = 0; i < endloop; i++) {
					if (conditionStmtNo.top() == prevStmtNo) {  // it is while or if stmtment in previously
						CFGline.push_back(stmtNo);
						CFG.push_back(CFGline);
						CFGTable.at(currentPro) = CFG;
						prevStmtNo = stmtNo;
						if (conditionStack.top() == 3) { // it is under while stmt
						   conditionStack.pop();
						   int index = conditionStmtNo.top();
						   conditionStmtNo.pop();
						   CFGline.clear();
						   CFG.clear();
						   CFGline.push_back(index);
						   CFG.push_back(CFGline);
						   CFGTable.at(currentPro) = CFG;
						}
					}
					else if (conditionStmtNo.top() == stmtNo) {   // it is else previously
						conditionStmtNo.pop();                     // remove the else stmtno
						conditionStack.pop();                      // remove the stack no  --> so only left if
						CFGline = CFGTable.at(currentPro).at(conditionStmtNo.top()); // save previously vector int CFGLine
						CFGline.push_back(stmtNo);                 // add the current stmtNo to the back of if
						CFG.at(conditionStmtNo.top()) = CFGline;
						CFGTable.at(currentPro) = CFG;
					}
					else {     // end of if stmt or else stmt
					    CFGline.push_back(dummyStmtNo);
						CFG.push_back(CFGline);
						CFGTable.at(currentPro) = CFG;
						dummyNodeStack.push(stmtNo);

					}
				}
			}
			else {   // no } in the string

				if (conditionStmtNo.top() == prevStmtNo) {  // it is while or if stmtment in previously
					CFGline.push_back(stmtNo);
					CFG.push_back(CFGline);
					CFGTable.at(currentPro) = CFG;
					prevStmtNo = stmtNo;
				}
				else if (conditionStmtNo.top() == stmtNo) {   // it is else previously
					conditionStmtNo.pop();                     // remove the else stmtno
					conditionStack.pop();                      // remove the stack no  --> so only left if
					CFGline = CFGTable.at(currentPro).at(conditionStmtNo.top()); // save previously vector int CFGLine
					CFGline.push_back(stmtNo);                 // add the current stmtNo to the back of if
					CFG.at(conditionStmtNo.top()) = CFGline;
					CFGTable.at(currentPro) = CFG;
					prevStmtNo = stmtNo;
				}
				else {     // normal line
					CFGline.push_back(stmtNo);
					CFG.push_back(CFGline);
					CFGTable.at(currentPro) = CFG;
					prevStmtNo = stmtNo;

				}

			}

		}

	}
}


bool isCondition(string stmtLine) {
	if (stmtLine.find("if") != std::string::npos) {
		condition = 1;
		return true;
	}
	else if (stmtLine.find("else") != std::string::npos) {
		condition = 2;
		return true;
	}
	else if (stmtLine.find("while") != std::string::npos) {
		condition = 3;
		return true;
	}
	return false;
}

