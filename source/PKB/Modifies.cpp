#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "./Header/Modifies.h"

using namespace std;

map<string, int> ModifiesMap;
map<int, vector<int>> ModifiesTable;

map<int, vector<string>> varTableLeft;

int insertToMap(string varName);

Modifies::Modifies() {
}

Modifies::~Modifies() {
}

void Modifies::addModifiesTable(string varName, int stmtLine) {
	int index;
	if (ModifiesMap.size() > 0) {
		index = findPosition(varName);

		if (index == -1) {
			index = insertToMap(varName);
		}
	} else {
		index = insertToMap(varName);
	}

	ModifiesTable[index].push_back(stmtLine);
	sort(ModifiesTable[index].begin(), ModifiesTable[index].end());
	ModifiesTable[index].erase(unique(ModifiesTable[index].begin(), ModifiesTable[index].end()), ModifiesTable[index].end());

	varTableLeft[stmtLine].push_back(varName);
	sort(varTableLeft[stmtLine].begin(), varTableLeft[stmtLine].end());
	varTableLeft[stmtLine].erase(unique(varTableLeft[stmtLine].begin(), varTableLeft[stmtLine].end()), varTableLeft[stmtLine].end());
}

std::vector<int> Modifies::getModifiesTable(string varName) {
	int index = findPosition(varName);

	if (index == -1) {
		vector<int> ans;
		return ans;
	}
	else {
		return ModifiesTable[index];
	}
}

vector<string> Modifies::getModVariables(string stmtLine) {
	int temp = atoi(stmtLine.c_str());
	vector<string> ans = varTableLeft[temp];
	return ans;
}

int Modifies::findPosition(string varName) {
	map<string, int>::iterator iter;
	iter = ModifiesMap.find(varName);

	if (iter != ModifiesMap.end()) {
		return  iter->second;
	}
	else {
		return -1;
	}
}
bool Modifies::isContains(string varName) {
	if (ModifiesMap.size() > 0) {
		if (ModifiesMap.count(varName)) {
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

int insertToMap(string varName) {
	int index = ModifiesMap.size();  
	ModifiesMap.insert(pair<string, int>(varName, index));
	return index;
}
