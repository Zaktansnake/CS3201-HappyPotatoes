
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "./Header/ConstantTable.h"

map<int, int> ConstantMap;
map<int, vector<int>> ConstantTables;
vector<int> ConstantList;

int insertToConstantMap(string constantValue);

ConstantTable::ConstantTable()
{
}

ConstantTable::~ConstantTable()
{
}

vector<int> ConstantTable::getAllConstantValues() {
	return ConstantList;
}

// refStmtLine -> when update Modifies Table
void ConstantTable::setConstantValue(string constantValue, int stmtLine) {

	int temp = atoi(constantValue.c_str());

	int index;
	if (ConstantMap.size() > 0) {
		index = findPosition(temp);

		if (index == -1) {
			index = insertToConstantMap(constantValue);
		}
	}
	else {
		index = insertToConstantMap(constantValue);
	}

	ConstantTables[index].push_back(stmtLine);
	sort(ConstantTables[index].begin(), ConstantTables[index].end());
	ConstantTables[index].erase(unique(ConstantTables[index].begin(), ConstantTables[index].end()), ConstantTables[index].end());

	ConstantList.push_back(temp);
	sort(ConstantList.begin(), ConstantList.end());
	ConstantList.erase(unique(ConstantList.begin(), ConstantList.end()), ConstantList.end());
}

// return the index of the varName in the map
int ConstantTable::findPosition(int constantValue) {
	map<int, int>::iterator iter;
	iter = ConstantMap.find(constantValue);
	if (iter != ConstantMap.end()) {
		return  iter->second;
	}
	else {
		return -1;
	}
}

// return true if procName alr in the table otherwise, false
bool ConstantTable::isContains(int constantValue) {
	if (ConstantMap.size() > 0) {
		if (ConstantMap.count(constantValue)) {
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

std::vector<int> ConstantTable::getConstantValue(string constantValue) {
	int temp = atoi(constantValue.c_str());
	int index = findPosition(temp);

	if (index == -1) {
		vector<int> ans;
		return ans;
	}
	else {
		return ConstantTables[index];
	}
}

int insertToConstantMap(string constantValue) {
	int temp = atoi(constantValue.c_str());
	int index = ConstantMap.size();   // set the index be the size of vertor
	ConstantMap.insert(pair<int, int>(temp, index));
	return index;
}



void ConstantTable::printMap03() {
	cout << "Table for ConstantMap" << endl;
	for (std::map<int, int>::iterator i = ConstantMap.begin(); i != ConstantMap.end(); i++)
	{
		cout << i->first << ", " << i->second << "\n";
	}

	cout << "Table for ConstantTables" << endl;
	for (map<int, vector<int>>::iterator ii = ConstantTables.begin(); ii != ConstantTables.end(); ++ii) {
		cout << (*ii).first << ": ";
		vector <int> inVect = (*ii).second;
		for (unsigned j = 0; j<inVect.size(); j++) {
			cout << inVect[j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}