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

int insertToMap(string varName);

Modifies::Modifies() {
}

Modifies::~Modifies() {
}

// refStmtLine -> when update Modifies Table
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
}

// return the index of the varName in the map
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

// return true if procName alr in the table otherwise, false
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

std::vector<int> Modifies::getModifiesTable(string varName) {
	int index = findPosition(varName);

	if (index == -1) {
		vector<int> ans;
		return ans;
	} else {
		return ModifiesTable[index];
	}
}

int insertToMap(string varName) {
	int index = ModifiesMap.size();   // set the index be the size of vertor
	ModifiesMap.insert(pair<string, int>(varName, index));
	return index;
}




void Modifies::printMap01() {
	cout << "Table for ModifiesMap" << endl;
	for (std::map<string, int>::iterator i = ModifiesMap.begin(); i != ModifiesMap.end(); i++)
	{
		cout << i->first << ", " << i->second << "\n";
	}

	cout << "Table for ModifiesTable" << endl;
	for (map<int, vector<int>>::iterator ii = ModifiesTable.begin(); ii != ModifiesTable.end(); ++ii) {
		cout << (*ii).first << ": ";
		vector <int> inVect = (*ii).second;
		for (unsigned j = 0; j<inVect.size(); j++) {
			cout << inVect[j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}