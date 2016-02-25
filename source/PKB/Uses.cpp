#include "./Header/Uses.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, int> UsesMap; // variable name
map<int, vector<int>> UsesTable;
map<string, vector<string>> UsesProcedureTable;

int insertToUsesMap(string varName);
vector<string> findPositionProcUses(string procName);

Uses::Uses()
{
}

Uses::~Uses()
{
}

void Uses::addUsesTable(string varName, int stmtLine) {
	int index;
	if (UsesMap.size() > 0) {
		index = findPosition(varName);
		if (index == -1) {
			index = insertToUsesMap(varName);
		}
	}
	else {
		index = insertToUsesMap(varName);
	}

	UsesTable[index].push_back(stmtLine);
	sort(UsesTable[index].begin(), UsesTable[index].end());
	UsesTable[index].erase(unique(UsesTable[index].begin(), UsesTable[index].end()), UsesTable[index].end());
}

void Uses::addUsesProcedureTable(string procedure, string varName) {
	if (UsesProcedureTable.size() > 0) {
		vector<string> ans = findPositionProcUses(procedure);
		if (ans.size() > 0) {
			UsesProcedureTable[procedure].push_back(varName);
		}
	} else {
		UsesProcedureTable[procedure].push_back(varName);
	}
}

// return the index of the varName in the map
int Uses::findPosition(string varName) {
	map<string, int>::iterator iter;
	iter = UsesMap.find(varName);
	if (iter != UsesMap.end()) {
		return  iter->second;
	}
	else {
		return -1;
	}
}

// return vector<string> of the varName in the map
vector<string> findPositionProcUses(string procName) {
	map<string, vector<string>>::iterator i = UsesProcedureTable.find(procName);
	if (i == UsesProcedureTable.end()) {
		vector<string> ans;
		return ans;
	}
	else {
		return i->second;
	}
}

bool Uses::isContains(string varName) {
	if (UsesMap.size() > 0) {
		if (UsesMap.count(varName)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

std::vector<int> Uses::getUsesTable(string varName)
{
	int index = findPosition(varName);
	if (index == -1) {
		vector<int> ans;
		return ans;
	} else {
		return UsesTable[index];
	}
}

std::vector<string> Uses::getUsesProcTable(string procName)
{
	return findPositionProcUses(procName);
}

int insertToUsesMap(string varName) {
	int index = UsesMap.size();   // set the index be the size of vertor
	UsesMap.insert(pair<string, int>(varName, index));
	return index;
}


