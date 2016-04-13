#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "./Header/Uses.h"

using namespace std;

map<string, int> UsesMap;
map<int, vector<int>> UsesTable;

map<int, vector<string>> varTableRight;

int insertToUsesMap(string varName);

Uses::Uses() {
}

Uses::~Uses() {
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

	varTableRight[stmtLine].push_back(varName);
	sort(varTableRight[stmtLine].begin(), varTableRight[stmtLine].end());
	varTableRight[stmtLine].erase(unique(varTableRight[stmtLine].begin(), varTableRight[stmtLine].end()), varTableRight[stmtLine].end());
}


std::vector<int> Uses::getUsesTable(string varName) {
	int index = findPosition(varName);

	if (index == -1) {
		vector<int> ans;
		return ans;
	}
	else {
		return UsesTable[index];
	}
}

vector<string> Uses::getUseVariables(string stmtLine) {
	int temp = atoi(stmtLine.c_str());
	vector<string> ans = varTableRight[temp];
	return ans;
}



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

int insertToUsesMap(string varName) {
	int index = UsesMap.size(); 
	UsesMap.insert(pair<string, int>(varName, index));
	return index;
}

