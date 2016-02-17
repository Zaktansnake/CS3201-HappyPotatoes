#include "./Header/Uses.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, int> UsesMap;
map<int, vector<int>> UsesTable;

int insertToUsesMap(string varName);

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

// return true if procName alr in the table otherwise, false
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
	return UsesTable[findPosition(varName)];
}

int insertToUsesMap(string varName) {
	int index = UsesMap.size();   // set the index be the size of vertor
	UsesMap.insert(pair<string, int>(varName, index));
	return index;
}