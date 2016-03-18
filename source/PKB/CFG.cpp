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
std::vector<std::vector<int> > CFGTable;
std::map <string, int> procedureMap;
int condition;

void setRoot(std::string procedure) {
   map<string, int>::iterator iter;
   iter = procedureMap.find(procedure);
   if (iter == procedureMap.end()) {
      procedureMap.insert(pair<string,int>(procedure,currentPro++));
   }
}

void addNextNode(int stmtNo, string stmt) {
	if (CFGTable.size() == 0) {
		
	}
	else {
		if (isCondition(stmt)) {
			if (condition == 1) {    // if statement

			}
			else if (condition == 2) {    // else statement

			}
			else if (condition == 3) {    // while statement

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

