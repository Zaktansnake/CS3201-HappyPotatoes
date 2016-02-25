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
map<int, vector<int>> ModifiesTable;
map<string, vector<string>> ModifiesProcedureTable;

int insertToMap(string varName);
vector<string> findPositionProc(string varName);

Modifies::Modifies()
{
}

Modifies::~Modifies()
{
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

// return vector<string> of the varName in the map
vector<string> findPositionProc(string procName) {

	map<string, vector<string>>::iterator i = ModifiesProcedureTable.find(procName);

	if (i == ModifiesProcedureTable.end()) { 
		vector<string> ans;
		return ans;
	} else { 
		return i->second;
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
	int index = findPosition(varName);
	if (index == -1) {
		vector<int> ans;
		return ans;
	} else {
		return ModifiesTable[index];
	}
}

void Modifies::addModifiesProcedureTable(string procedure, string varName ) {
	if (ModifiesProcedureTable.size() > 0) {
		vector<string> ans = findPositionProc(procedure);
		if (ans.size() > 0) {
			ModifiesProcedureTable[procedure].push_back(varName);
		}
	} else {
		ModifiesProcedureTable[procedure].push_back(varName);
	}
}

std::vector<string> Modifies::getModifiesProcTable(string procName)
{
	return findPositionProc(procName);
}

int insertToMap(string varName) {
	int index = ModifiesMap.size();   // set the index be the size of vertor
	ModifiesMap.insert(pair<string, int>(varName, index));
	return index;
}

