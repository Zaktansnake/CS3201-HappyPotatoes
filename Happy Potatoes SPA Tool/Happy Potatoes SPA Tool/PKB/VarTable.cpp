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
#include <iterator>

using namespace std;

vector<pair<int, string>> varTableLeft;  // (Modifies) int -> stmtLine, string -> variable
vector<pair<int, string>> varTableRight; // ()
map<string, vector<int>> whileTable;
map<int, string> assignTable;

void addToVarTable(int position, string varName, int stmtLine);
bool isContainsAssign(int stmtLine);
bool isContainsWhile(string stmtLine);

VarTable::VarTable(){
}

VarTable::~VarTable()
{
}

int VarTable::varTableLeftSize() {
	return varTableLeft.size();
}

int VarTable::varTableRightSize() {
	return varTableRight.size();
}

int VarTable::whileTableSize() {
	return whileTable.size();
}

int VarTable::assignTableSize() {
	return assignTable.size();
}


// ---------------------- while table ---------------------------------
void VarTable::addDataToWhileTable(string variable, int stmtNum) {
	whileTable[variable].push_back(stmtNum);
}

//----------------------- Assign Table ------------------------

void VarTable::addDataToAssignTable(string variable, int stmtNum) {
	assignTable.insert(pair<int, string>(stmtNum, variable));
}

string getAssignTable(int stmtNum) {
	string temp = "";

	std::map<int, string>::iterator it = assignTable.find(stmtNum);
	if (it == assignTable.end()) {
		// not found
	} else {
		// found
		temp = it->second;
	}
	
	return temp;
}

vector<int> VarTable::getAllAssign() {
	vector<int> ans;

	for (map<int, string>::iterator it = assignTable.begin(); it != assignTable.end(); ++it) {
		ans.push_back(it->first);
	}
	return ans;
}

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

vector<string> VarTable::getModifiesProc(string secondPerimeter) {
	vector<string> ans = Modifies::getModifiesProcTable(secondPerimeter);
	return ans;
}

vector<int> VarTable::getModifiesAssign(string secondPerimeter) {
	std::vector<int> ans = Modifies::getModifiesTable(secondPerimeter);
	vector<int> finalResult;

	for (map<int, string>::iterator it = assignTable.begin(); it != assignTable.end(); ++it) {
		finalResult.push_back(it->first);
	}

	std::sort(ans.begin(), ans.end());
	std::sort(finalResult.begin(), finalResult.end());

	std::vector<int> v_intersection;

	std::set_intersection(ans.begin(), ans.end(),
		finalResult.begin(), finalResult.end(),
		std::back_inserter(v_intersection));

	return v_intersection;
}

vector<int> VarTable::getModifiesStmt(string firstPerimeter) {
	return Modifies::getModifiesTable(firstPerimeter);
}

vector<int> VarTable::getModifiesWhile(string secondPerimeter) {
	vector<int> ans;
	if (!isContainsWhile(secondPerimeter)) {
		ans;
	}
	else {
		ans = whileTable.at(secondPerimeter);
	}
	return ans;
}

bool VarTable::isModifiesProc(string firstPerimeter, string secondPerimeter) {
	bool result;
	vector<string> tempVector = Modifies::getModifiesProcTable(firstPerimeter);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i].compare(secondPerimeter) == 0) {
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
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (isContainsAssign(numbValue)) {
		vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);
		if (tempVector.size() == 0) {
			result = false;
		} else {
			for (int i = 0; i < tempVector.size(); i++) {
				if (tempVector[i] == numbValue) {
					result = true;
					break;
				}
				else {
					result = false;
				}
			}
		}
		return result;
	} else {
		return false;
	}
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

	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (!isContainsWhile(secondPerimeter)) {
		return false;
	} else {
		vector<int> ans = whileTable.at(secondPerimeter);
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == numbValue) {
				return true;
			}
		}
		return false;
	}
}

bool isContainsAssign(int stmtLine) {
	auto search =  assignTable.find(stmtLine);
	if (search != assignTable.end()) {
		return true;
	} else {
		return false;
	}
}

bool isContainsWhile(string variable) {
	auto search = whileTable.find(variable);
	if (search != whileTable.end()) {
		return true;
	}
	else {
		return false;
	}
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

vector<int> VarTable::getUsesAssig(string secondPerimeter) {

	std::vector<int> ans = Uses::getUsesTable(secondPerimeter);
	vector<int> finalResult;

	for (map<int, string>::iterator it = assignTable.begin(); it != assignTable.end(); ++it) {
		finalResult.push_back(it->first);
	}

	std::sort(ans.begin(), ans.end());
	std::sort(finalResult.begin(), finalResult.end());

	std::vector<int> v_intersection;

	std::set_intersection(ans.begin(), ans.end(),
		finalResult.begin(), finalResult.end(),
		std::back_inserter(v_intersection));

	return v_intersection;
}

vector<int> VarTable::getUsesStmt(string stmt1) {
	// stmt1 -> stmtLine
	return Uses::getUsesTable(stmt1);
}

vector<int> VarTable::getUsesWhile(string stmt1) {
	// stmt1 -> stmtLine
	vector<int> ans;
	if (!isContainsWhile(stmt1)) {
		ans;
	}
	else {
		ans = whileTable.at(stmt1);
	}
	return ans;
}

bool VarTable::isUsesProc(string firstPerimeter, string secondPerimeter) {
	bool result;
	vector<string> tempVector = Uses::getUsesProcTable(secondPerimeter);
	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i].compare(firstPerimeter) == 0) {
				result = true;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

bool VarTable::isUsesAssign(string firstPerimeter, string secondPerimeter) {
	bool result;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (isContainsAssign(numbValue)) {
		vector<int> tempVector = Uses::getUsesTable(secondPerimeter);
		if (tempVector.size() == 0) {
			result = false;
		}
		else {
			for (int i = 0; i < tempVector.size(); i++) {
				if (tempVector[i] == numbValue) {
					result = true;
					break;
				}
				else {
					result = false;
				}
			}
		}
		return result;
	}
	else {
		return false;
	}
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

bool VarTable::isUsesWhile(string firstPerimeter, string secondPerimeter) {
	bool result;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (!isContainsWhile(secondPerimeter)) {
		return false;
	}
	else {
		vector<int> ans = whileTable.at(secondPerimeter);
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == numbValue) {
				return true;
			}
		}
		return false;
	}
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
