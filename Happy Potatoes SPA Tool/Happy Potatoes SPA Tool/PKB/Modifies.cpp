#include "./Header/Modifies.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, int> ModifiesMap;
vector<vector<int>> ModifiesTable;

Modifies::Modifies()
{
}

Modifies::~Modifies()
{
}

void Modifies::addModifiesTable(string varName, int stmtLine) {
	int index;
	if (ModifiesMap.size() > 0) {
		index = findPosition(varName);
	} else {
		index = ModifiesMap.size();   // set the index be the size of vertor
		ModifiesMap.insert(pair<string, int>(varName, index));
	}
	ModifiesTable[index].push_back(stmtLine);
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

std::vector<int> Modifies::getModifiesTable(string varName)
{
	return ModifiesTable[findPosition(varName)];
}

