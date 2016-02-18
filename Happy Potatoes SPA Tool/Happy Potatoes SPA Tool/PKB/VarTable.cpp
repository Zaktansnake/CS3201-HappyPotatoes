#include "./Header/VarTable.h"
#include "./Header/Modifies.h"
#include "./Header/Uses.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, string>> varTableLeft;  // (Modifies) int -> stmtLine, string -> variable
vector<pair<int, string>> varTableRight; // ()
map<string, vector<int>> whileTable;
map<string, vector<int>> assignTable;

void addToVarTable(int position, string varName, int stmtLine);

VarTable::VarTable(){
}

VarTable::~VarTable()
{
}

// ---------------------- while table ---------------------------------




// ------------------------ Modifies ----------------------------------

// stmtLine1 = parent; stmtLine2 = the position of bracket end
vector<string> VarTable::findVariableLeft(int stmtLine1, int stmtLine2) {
	vector<string> ans;

	for (int i = 0; i < varTableLeft.size(); i++) {
		pair<int, string> tempVector =  varTableLeft.at(i);

		if (tempVector.first > stmtLine1 && tempVector.first < stmtLine2) {
			if (!ans.empty()) {
				if (std::find(ans.begin(), ans.end(), tempVector.second) != ans.end()) {
					
				} else {
					ans.push_back(tempVector.second);
				}
			} else {
				ans.push_back(tempVector.second);
			}
		}
	}

	return ans;
}

vector<int> VarTable::getModifiesTable(string varName) {
	return Modifies::getModifiesTable(varName);
}

void VarTable::addDataToModifies(string varName, int stmtLine) {
	addToVarTable(1, varName, stmtLine);
	Modifies::addModifiesTable(varName, stmtLine);
}

void VarTable::addModifiesProcTable(string varName, string procedure) {
	return Modifies::addModifiesProcedureTable(varName, procedure);
}

//--------------------------- PQL -------------------------------------

vector<string> VarTable::getModifiesProc(string secondPerimeter) {
	vector<string> ans = Modifies::getModifiesProcTable(secondPerimeter);
	return ans;
}

vector<int>  VarTable::getModifiesAssign(string secondPerimeter) {
	vector<int> ans = Modifies::getModifiesTable(secondPerimeter);
	return ans;
}

vector<int> VarTable::getModifiesStmt(string firstPerimeter) {
	return Modifies::getModifiesTable(firstPerimeter);
}

vector<int> VarTable::getModifiesWhile(string secondPerimeter) {
	return Modifies::getModifiesTable(secondPerimeter);
}

bool VarTable::isModifiesProc(string firstPerimeter, string secondPerimeter) {
	bool result;
	vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(firstPerimeter) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

bool VarTable::isModifiesAssign(string firstPerimeter, string secondPerimeter) {
	bool result;
	vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(firstPerimeter) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

bool VarTable::isModifiesStmt(string firstPerimeter, string secondPerimeter) {
	bool result;
	vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(firstPerimeter) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

bool VarTable::isModifiesWhile(string firstPerimeter, string secondPerimeter) {
	bool result;
	vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(firstPerimeter) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}


//-------------------------------Uses---------------------------

vector<string> VarTable::findVariableRight(int stmtLine1, int stmtLine2) {
	vector<string> ans;

	for (int i = 0; i < varTableRight.size(); i++) {
		pair<int, string> tempVector = varTableRight.at(i);

		int temp = stmtLine2 - stmtLine1;

		if (temp == 1) {
			if (tempVector.first == stmtLine2) {
				ans.push_back(tempVector.second);
			}
		}
		else if (tempVector.first > stmtLine1 && tempVector.first < stmtLine2) {
			if (std::find(ans.begin(), ans.end(), tempVector.second) != ans.end()) {

			}
			else {
				ans.push_back(tempVector.second);
			}
		}
	}

	return ans;
}

//--------------------------- PQL SIDE ----------------------------------

vector<string> VarTable::getUsesProc(string stmt1) {
	// stmt1 -> variable
	return Uses::getUsesProcTable(stmt1);
}

vector<int> VarTable::getUsesAssig(string stmt1) {
	// stmt1 -> stmtLine
	return Uses::getUsesTable(stmt1);
}

vector<int> VarTable::getUsesStmt(string stmt1) {
	// stmt1 -> stmtLine
	return Uses::getUsesTable(stmt1);
}

vector<int> VarTable::getUsesWhile(string stmt1) {
	// stmt1 -> stmtLine
	return Uses::getUsesTable(stmt1);
}

bool VarTable::isUsesProc(string stmtLine, string variable) {
	bool result;
	vector<int> tempVector = Uses::getUsesTable(variable);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(stmtLine) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

bool VarTable::isUsesAssign(string stmtLine, string variable) {
	bool result;
	vector<int> tempVector = Uses::getUsesTable(variable);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(stmtLine) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

bool VarTable::isUsesStmt(string stmtLine, string variable) {
	bool result;
	vector<int> tempVector = Uses::getUsesTable(variable);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(stmtLine) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

bool VarTable::isUsesWhile(string stmtLine, string variable) {
	bool result;
	vector<int> tempVector = Uses::getUsesTable(variable);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(stmtLine) >> numbValue;
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}


vector<int> VarTable::getUsesTable(string varName) {
	return Uses::getUsesTable(varName);
}

void VarTable::addDataToUses(string varName, int stmtLine) {
	addToVarTable(2, varName, stmtLine);
	Uses::addUsesTable(varName, stmtLine);
}

void VarTable::addUsesProcTable(string varName, string procedure) {
	return Uses::addUsesProcedureTable(varName,procedure);
}

// add the var to varTableLeft or varTableRight
void addToVarTable(int position, string varName, int stmtLine) {
	if (position == 1) {
		varTableLeft.push_back(make_pair(stmtLine, varName));
	} else if (position == 2) {
		varTableRight.push_back(make_pair(stmtLine, varName));
	}
}
