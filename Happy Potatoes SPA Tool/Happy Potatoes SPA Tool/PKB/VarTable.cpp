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

void addToVarTable(int position, string varName, int stmtLine);

VarTable::VarTable(){
}

VarTable::~VarTable()
{
}

// stmtLine1 = parent; stmtLine2 = the position of bracket end
vector<string> VarTable::findVariableLeft(int stmtLine1, int stmtLine2) {
	vector<string> ans;

	for (int i = 0; i < varTableLeft.size(); i++) {
		pair<int, string> tempVector =  varTableLeft.at(i);

		if (tempVector.first > stmtLine1 && tempVector.first < stmtLine2) {
			ans.push_back(tempVector.second);
		}
	}

	return ans;
}

vector<string> VarTable::findVariableRight(int stmtLine1, int stmtLine2) {
	vector<string> ans;

	for (int i = 0; i < varTableRight.size(); i++) {
		pair<int, string> tempVector = varTableRight.at(i);

		if (tempVector.first > stmtLine1 && tempVector.first < stmtLine2) {
			ans.push_back(tempVector.second);
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

vector<int> VarTable::getUsesTable(string varName) {
	return Uses::getUsesTable(varName);
}

void VarTable::addDataToUses(string varName, int stmtLine) {
	addToVarTable(2, varName, stmtLine);
	Uses::addUsesTable(varName, stmtLine);
}

void addToVarTable(int position, string varName, int stmtLine) {
	if (position == 1) {
		varTableLeft.push_back(make_pair(stmtLine, varName));
	} else if (position == 2) {
		varTableRight.push_back(make_pair(stmtLine, varName));
	}
}
