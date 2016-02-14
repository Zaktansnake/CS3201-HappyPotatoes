#include "./Header/VarTable.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, int> VarTable::VarMap;
vector<string> VarTable::VarIndex;
vector<std::vector<string>> arrAnsForUses;
vector<std::vector<string>> arrAnsForFollows;
vector<std::vector<string>> arrAnsForModifies;
vector<std::vector<string>> arrAnsForAffects;
vector<std::vector<string>> arrAnsForParents;

struct varTable {

};

VarTable::VarTable(){
}

VarTable::~VarTable()
{
}

void VarTable::addTableData(string varName, int stmtLine) {
	VarTable pt;
	int index = pt.findPosition(varName);
	if (index = -1) {
		index = VarIndex.size();
		VarMap.insert(pair<string, int>(varName, index));
		VarIndex.push_back(varName);
	}
	else {

	}
}

// retrun the size of proc table
int VarTable::getSize() {
	return this->VarIndex.size();
}

std::vector<string> getUsesAns(int index) {
	return arrAnsForUses[index];
}

std::vector<string> getModifiesAns(int index) {
	return arrAnsForModifies[index];
}

std::vector<string> getFollowsAns(int index) {
	return arrAnsForFollows[index];
}

std::vector<string> getAffectsAns(int index) {
	return arrAnsForAffects[index];
}

std::vector<string> getParentsAns(int index) {
	return arrAnsForParents[index];
}

// return procedure index
int VarTable::getVarIndex(string key) {
	map<string, int>::iterator iter;
	iter = VarMap.find(key);
	return iter->second;
}

// get the variable name by knowing the index
string getVarName(int index);

// get the varNode 
TNode* getVarNode(int index);

// return true if procName alr in the table otherwise, false
bool VarTable::isContains(string name) {
	map<string, int>::iterator iter;
	int index;
	iter = VarMap.find(name);
	if (VarMap.size() > 0) {
		if (iter != VarMap.end()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

// return the index of the procName in the map
int VarTable::findPosition(string varName) {
	map<string, int>::iterator iter;
	iter = VarMap.find(varName);
	if (iter != VarMap.end()) {
		return  iter->second;
	}
	else {
		return -1;
	}
}


