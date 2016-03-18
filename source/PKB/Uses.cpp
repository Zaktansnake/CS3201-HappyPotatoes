#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "./Header/Uses.h"

using namespace std;

map<string, int> UsesMap; // variable name
map<int, vector<int>> UsesTable;

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

std::vector<int> Uses::getUsesTable(string varName) {
	int index = findPosition(varName);

	if (index == -1) {
		vector<int> ans;
		return ans;
	} else {
		return UsesTable[index];
	}
}

int insertToUsesMap(string varName) {
	int index = UsesMap.size();   // set the index be the size of vertor
	UsesMap.insert(pair<string, int>(varName, index));
	return index;
}



void Uses::printMap02() {
	cout << "Table for UsesMap" << endl;
	for (std::map<string, int>::iterator i = UsesMap.begin(); i != UsesMap.end(); i++)
	{
		cout << i->first << ", " << i->second << "\n";
	}

	cout << "Table for UsesTable" << endl;
	for (map<int, vector<int>>::iterator ii = UsesTable.begin(); ii != UsesTable.end(); ++ii) {
		cout << (*ii).first << ": ";
		vector <int> inVect = (*ii).second;
		for (unsigned j = 0; j<inVect.size(); j++) {
			cout << inVect[j] << " ";
		}
		cout << endl;
	}

}