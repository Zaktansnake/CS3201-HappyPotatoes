#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>

#include "./Header/PKB.h"
#include "./Header/VarTable.h"
#include "./Header/Modifies.h"
#include "./Header/Uses.h"

using namespace std;

// (Modifies) int -> stmtLine, string -> variable
vector<pair<int, string>> varTableLeft;
// (Uses) int -> stmtLine, string -> variable
vector<pair<int, string>> varTableRight;
// (While) string -> variable name, vector<int> -> stmtLine
map<string, vector<int>> whileTable;
// (Assign) int -> stmtLine, string -> line
map<int, string> assignTable;
// (Ifs) int -> stmtLine, string -> variable
map<int, string> ifsTable;

vector<int> allStmtNum;
vector<int> assignNum;
vector<int> whileStmtNum;
vector<int> ifStmtNum;

void addDataToStmt();
void addToVarTable(int position, string varName, int stmtLine);
bool isContainsAssign(int stmtLine);
bool isContainsWhile(string stmtLine);

void printVarLeft();
void printVarRight();
void printWhileLoop();

VarTable::VarTable() {
}

VarTable::~VarTable() {
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

void VarTable::updateModifiesUsesTables() {

	addDataToStmt();

	std::sort(varTableLeft.begin(), varTableLeft.end());
	std::sort(varTableRight.begin(), varTableRight.end());

	VarTable::setAssign();

	std::sort(assignNum.begin(), assignNum.end());
	std::sort(whileStmtNum.begin(), whileStmtNum.end());

}

vector<int> VarTable::getAllStmt() {
	return allStmtNum;
}

vector<int> VarTable::getAllWhile() {
	return whileStmtNum;
}

vector<int> VarTable::getAllIfs() {
	return ifStmtNum;
}

// add stmtLine into stmtNum
void addDataToStmt() {
	int tempNum = PKB::getStmtNum();
	for (int i = 1; i <= tempNum; i++) {
		allStmtNum.push_back(i);
	}
}

// ---------------------- While table ---------------------------------
void VarTable::addDataToWhileTable(string variable, int stmtNum) {
	whileTable[variable].push_back(stmtNum);
	whileStmtNum.push_back(stmtNum);
}

// ---------------------- IFS table ---------------------------------
void VarTable::addDataToIfsTable(string variable, int stmtNum) {
	ifsTable.insert(pair<int, string>(stmtNum, variable));
	ifStmtNum.push_back(stmtNum);
}

//----------------------- Assign Table ---------------------------------
void VarTable::addDataToAssignTable(string variable, int stmtNum) {
	assignTable.insert(pair<int, string>(stmtNum, variable));
}

string VarTable::getAssignTable(int stmtNum) {
	string temp = "";
	std::map<int, string>::iterator it = assignTable.find(stmtNum);

	if (it != assignTable.end()) {
		// found
		temp = it->second;
	}

	return temp;
}

vector<int> VarTable::getAllAssign() {
	return assignNum;
}

// ------------------------ Modifies -----------------------------------

vector<string> VarTable::findVariableLeft(int stmtLine1, int stmtLine2) {
	// stmtLine1 = parent; stmtLine2 = the position of bracket end
	vector<string> ans;

	for (int i = 0; i < varTableLeft.size(); i++) {
		pair<int, string> tempVector = varTableLeft.at(i);

		if (tempVector.first > stmtLine1 && tempVector.first <= stmtLine2) {
			if (!ans.empty()) {
				if (std::find(ans.begin(), ans.end(), tempVector.second) != ans.end()) {
				}
				else {
					ans.push_back(tempVector.second);
				}
			}
			else {
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

vector<string> VarTable::getModifiesVariable(string firstPerimeter) {
	// firstPerimeter = stmtNum
	int temp = atoi(firstPerimeter.c_str());

	vector<string> ans;

	for (int i = 0; i < varTableLeft.size(); i++)
	{
		if (varTableLeft[i].first == temp) {
			ans.push_back(varTableLeft[i].second);
		}
	}

	return ans;
}

vector<int> VarTable::getModifiesAssign(string secondPerimeter) {
	// secondPerimeter = variable
	std::vector<int> ans = Modifies::getModifiesTable(secondPerimeter);
	vector<int> finalResult = assignNum;

	std::sort(ans.begin(), ans.end());
	std::vector<int> v_intersection;
	std::set_intersection(ans.begin(), ans.end(),
		finalResult.begin(), finalResult.end(),
		std::back_inserter(v_intersection));

	return v_intersection;
}

vector<int> VarTable::getModifiesStmt(string secondPerimeter) {
	// secondPerimeter = variable
	return Modifies::getModifiesTable(secondPerimeter);
}

vector<int> VarTable::getModifiesWhile(string secondPerimeter) {
	// secondPerimeter = variable
	vector<int> ans;
	vector<int> tempAns = Modifies::getModifiesTable(secondPerimeter);
	sort(tempAns.begin(), tempAns.end());

	set<int> intersect;
	set_intersection(tempAns.begin(), tempAns.end(), whileStmtNum.begin(), whileStmtNum.end(), back_inserter(ans));

	return ans;
}

bool VarTable::isModifiesAssign(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (isContainsAssign(numbValue)) {
		vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);

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

bool VarTable::isModifiesStmt(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
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
				break;
			}
			else {
				result = false;
			}
		}
	}

	return result;
}

bool VarTable::isModifiesWhile(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (!isContainsWhile(secondPerimeter)) {
		result = false;
	}
	else {
		vector<int> ans = whileTable.at(secondPerimeter);
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == numbValue) {
				result = true;
				break;
			}
		}
		result = false;
	}
	return result;
}

bool isContainsAssign(int stmtLine) {
	auto search = assignTable.find(stmtLine);

	if (search != assignTable.end()) {
		return true;
	}
	else {
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
	// stmtLine1 = parent; stmtLine2 = the position of bracket end
	vector<string> ans;

	for (int i = 0; i < varTableRight.size(); i++) {
		pair<int, string> tempVector = varTableRight.at(i);
		int temp = stmtLine2 - stmtLine1;

		if (temp == 1) {
			if (tempVector.first == stmtLine2) {
				ans.push_back(tempVector.second);
			}
		}
		else if (tempVector.first > stmtLine1 && tempVector.first <= stmtLine2) {
			if (std::find(ans.begin(), ans.end(), tempVector.second) != ans.end()) {

			}
			else {
				ans.push_back(tempVector.second);
			}
		}
	}

	return ans;
}

vector<string> VarTable::getUsesVariable(string firstPerimeter) {
	// firstPerimeter = stmtNum
	int stmtNum = atoi(firstPerimeter.c_str());
	vector<string> ans;
	int previous = 0;

	for (int i = 0; i < varTableRight.size(); i++)
	{
		int tempStmtLine = varTableRight[i].first;
		if (tempStmtLine == stmtNum) {
			string tempValue = varTableRight[i].second;
			if (!is_number(tempValue)) {
				ans.push_back(tempValue);
			}
		}
	}

	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	return ans;
}

vector<int> VarTable::getUsesAssig(string secondPerimeter) {
	// secondPerimeter = variable
	std::vector<int> ans = Uses::getUsesTable(secondPerimeter);
	vector<int> finalResult = assignNum;
	std::sort(ans.begin(), ans.end());
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

bool VarTable::isUsesAssign(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
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

bool VarTable::isUsesStmt(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	vector<int> tempVector = Uses::getUsesTable(secondPerimeter);

	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(firstPerimeter) >> numbValue;

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

bool VarTable::isUsesWhile(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
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
	VarTable::addDataToIfsTable(varName, stmtLine);
	Uses::addUsesTable(varName, stmtLine);
}

vector<int> VarTable::setAssign() {
	for (map<int, string>::iterator it = assignTable.begin(); it != assignTable.end(); ++it) {
		assignNum.push_back(it->first);
	}
	return assignNum;
}

// add the var to varTableLeft or varTableRight
void addToVarTable(int position, string varName, int stmtLine) {
	if (position == 1) {
		varTableLeft.push_back(make_pair(stmtLine, varName));
	}
	else if (position == 2) {
		varTableRight.push_back(make_pair(stmtLine, varName));
	}
}

// check string is a number
bool VarTable::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}

void VarTable::printTables() {
	//Modifies::printMap01();
	//Uses::printMap02();
	//printVarLeft();
	//printVarRight();
	//printWhileLoop();
}

void printVarLeft() {
	cout << "VarLeft" << endl;
	for (int i = 0; i < varTableLeft.size(); i++)
	{
		cout << varTableLeft[i].first << ", " << varTableLeft[i].second << endl;
	}
	cout << endl;
	cout << endl;
}

void printVarRight() {
	cout << "VarRight" << endl;
	for (int i = 0; i < varTableRight.size(); i++)
	{
		cout << varTableRight[i].first << ", " << varTableRight[i].second << endl;
	}
}

void printWhileLoop() {
	cout << "Table for while loop" << endl;
	for (map<string, vector<int>>::iterator ii = whileTable.begin(); ii != whileTable.end(); ++ii) {
		cout << (*ii).first << ": ";
		vector <int> inVect = (*ii).second;
		for (unsigned j = 0; j < inVect.size(); j++) {
			cout << inVect[j] << " ";
		}
		cout << endl;
	}
}