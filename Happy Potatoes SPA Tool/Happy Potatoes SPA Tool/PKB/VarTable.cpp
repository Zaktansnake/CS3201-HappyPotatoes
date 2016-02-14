#include "./Header/VarTable.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

std::vector<std::vector<string>> arrAnsForUses;
std::vector<std::vector<string>> arrAnsForFollows;
std::vector<std::vector<string>> arrAnsForModifies;
std::vector<std::vector<string>> arrAnsForAffects;
std::vector<std::vector<string>> arrAnsForParents;

struct varTable {
	

};


VarTable::VarTable(){
}

VarTable::~VarTable()
{
}

void VarTable::addTableData(string varName) {
	map<string, int>::iterator iter;
	int index;
	iter = VarMap.find(varName);
	if (iter != VarMap.end()) {
		index = iter->second;
	}
	else {
		index = -1;
	}
	if (index = -1) {
		index = VarIndex.size();
		std::vector<string> callAns;
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


