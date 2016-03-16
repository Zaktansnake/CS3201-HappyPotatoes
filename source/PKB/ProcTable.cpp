#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include <unordered_set>

#include "./Header/ProcTable.h"
#include "./Header/VarTable.h"
#include "./Header/Calls.h"

using namespace std;

template <> struct hash<std::pair<string, string>> {
	inline size_t operator()(const std::pair<string, string> &v) const {
		std::hash<string> string_hasher;
		return string_hasher(v.first) ^ string_hasher(v.second);
	}
};

map<string, int> ProcMap;  //procName, index of the procName in the map
vector<string> ProcIndex;  // store the index of map
map<string, vector<string>> ProcWithModifies;
map<string, vector<string>> ProcWithUses;
std::vector<std::tuple<string, string, int>> tempCallsTable;
std::unordered_set< std::pair<string, string>> tempCallsSet;

Calls call;

static void updateProcWithModAndUses();

ProcTable::ProcTable() {
  
}

ProcTable::~ProcTable() {

}

void ProcTable::updateProcCallsTables() {
	updateProcWithModAndUses();
}

static void updateProcWithModAndUses() {
	tempCallsSet = Calls::getCallsSet();

	for (auto itr = tempCallsSet.begin(); itr != tempCallsSet.end(); ++itr) {
		pair<string, string> tempSet = *itr;
		string procA = tempSet.first; // parent
		string procB = tempSet.second; // child

		vector<string> tempMod = ProcTable::getProcModifiesVar(procB);
		for (int i = 0; i < tempMod.size(); i++) {
			ProcWithModifies[procA].push_back(tempMod[i]);
		}

		vector<string> tempUses = ProcTable::getProcUsesVar(procB);
		for (int i = 0; i < tempUses.size(); i++) {
			ProcWithUses[procA].push_back(tempUses[i]);
		}
	}
}

void ProcTable::addTableData(string procName) {
   ProcTable pt;
   int index = pt.findPosition(procName);

   // index = -1 means there is no same proc name in the table
   if (index == -1) {
	   index = ProcIndex.size();   // set the index be the size of vertor
	   ProcMap.insert(pair<string, int>(procName, index)); 
	   ProcIndex.push_back(procName);
   }
}

void ProcTable::setCallsTable(string proc1, string proc2, int stmtLine) {
	Calls::setCallProcedure(proc1, proc2, stmtLine);
}

// add Modifies variables based on procName
void ProcTable::addProcModifiesVar(string procName, string variable) {
	ProcWithModifies[procName].push_back(variable);
}

vector<string> ProcTable::getProcModifiesVar(string procName) {
	//Calls::printCallsTable();
	vector<string> ans;
	auto it = ProcWithModifies.find(procName);

	if (it != ProcWithModifies.end())
	{
		auto& vIt = it->second;

		for (auto elem : vIt)
		{
			ans.push_back(elem);
		}
	}

	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
	}

	return ans;
}



// add Uses variables based on procName
void ProcTable::addProcUsesVar(string procName, string variable) {
	ProcWithUses[procName].push_back(variable);
}

vector<string> ProcTable::getProcUsesVar(string procName) {
	vector<string> ans;
	auto it = ProcWithUses.find(procName);

	if (it != ProcWithUses.end())
	{
		auto& vIt = it->second;

		for (auto elem : vIt)
		{
			ans.push_back(elem);
		}
	}

	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		auto it = unique(ans.begin(), ans.end());
		ans.erase(it, ans.end());
	}

	return ans;


}




// return the index of the procName in the map
int ProcTable::findPosition(string procName) {
	map<string, int>::iterator iter;
	iter = ProcMap.find(procName);

	if (iter != ProcMap.end()) {
		return  iter->second;
	}
	else {
		return -1;
	}
}

// return true if procName alr in the table otherwise, false
bool ProcTable::isContains(string name) {
	map<string, int>::iterator iter;
	int index;
	iter = ProcMap.find(name);

	if (ProcMap.size() > 0) {
		if (iter != ProcMap.end()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
