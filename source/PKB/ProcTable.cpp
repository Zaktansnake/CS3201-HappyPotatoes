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
#include "./Header/Calls.h"

using namespace std;

template <> struct hash<std::pair<string, string>> {
	inline size_t operator()(const std::pair<string, string> &v) const {
		std::hash<string> string_hasher;
		return string_hasher(v.first) ^ string_hasher(v.second);
	}
};

map<string, int> ProcMap;  // procName, index of the procName in the map
vector<string> ProcIndex;  // store the procedures
map<string, vector<string>> ProcWithModifies; // string -> procedure, vector<string> -> list of variables
map<string, vector<string>> ProcWithUses; // string -> procedure, vector<string> -> list of variables
map<string, vector<string>> ModifiesWithProc; // string -> variable, vector<string> -> procedure
map<string, vector<string>> UsesWithProc; // string -> variable, vector<string> -> procedure
std::vector<std::tuple<string, string, int>> tempCallsTable;  // string -> mainProcedure, string -> procedure, int -> stmtLine
std::unordered_set< std::pair<string, string>> tempCallsSet; // string -> mainProcedure, string -> procedure

static void updateModifiesUsesTables();
static void updateProcWithModAndUses();
vector<string> findPositionProcModifies(string variable); // return a list of procedures based on variable
vector<string> findPositionProcUses(string procName);

void printTable();

Calls call;


ProcTable::ProcTable() {
  
}

ProcTable::~ProcTable() {

}

vector<string> ProcTable::getAllProcedures() {
	return ProcIndex;
}

void ProcTable::updateProcCallsTables() {
	updateProcWithModAndUses();
	tempCallsTable = Calls::getCallsTable();
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

		sort(ProcWithModifies[procA].begin(), ProcWithModifies[procA].end());
		ProcWithModifies[procA].erase(unique(ProcWithModifies[procA].begin(), ProcWithModifies[procA].end()), ProcWithModifies[procA].end());

		vector<string> tempUses = ProcTable::getProcUsesVar(procB);
		for (int i = 0; i < tempUses.size(); i++) {
			ProcWithUses[procA].push_back(tempUses[i]);
		}

		sort(ProcWithUses[procA].begin(), ProcWithUses[procA].end());
		ProcWithUses[procA].erase(unique(ProcWithUses[procA].begin(), ProcWithUses[procA].end()), ProcWithUses[procA].end());
	}

	//Calls::printCallsTable();
	//printTable();
}

std::vector<std::tuple<string, string, int>> ProcTable::getCallsTable() {
	return tempCallsTable;
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

std::vector<std::tuple<string, string, int>> getCallsTable() {
	return tempCallsTable;
}

// add Modifies variables based on procName
void ProcTable::setProcModifiesVar(string procedure, string variable) {
	ProcWithModifies[procedure].push_back(variable);
	ModifiesWithProc[variable].push_back(procedure);
}

// return a list of variable based on procName
vector<string> ProcTable::getProcModifiesVar(string procName) {
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

// return a list of procName based on variable
vector<string> ProcTable::getModifiesProc(string secondPerimeter) {
	// secondPerimeter = variable
	vector<string> ans = findPositionProcModifies(secondPerimeter);
	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
	}
	return ans;
}

bool ProcTable::isModifiesProc(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = procedure; secondPerimeter = variable
	bool result;
	vector<string> tempVector = ProcTable::getProcModifiesVar(firstPerimeter);

	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i].compare(secondPerimeter) == 0) {
				result = true;
				break;
			}
			else {
				result = false;
			}
		}
	}
	return result;
}

// private method : return a list of procedures
vector<string> findPositionProcModifies(string variable) {
	map<string, vector<string>>::iterator i = ModifiesWithProc.find(variable);

	if (i == ModifiesWithProc.end()) {
		vector<string> ans;
		return ans;
	}
	else {
		return i->second;
	}
}



// add Uses variables based on procName
void ProcTable::setProcUsesVar(string procedure, string variable) {
	if (!PKB::is_number(variable)) {
		ProcWithUses[procedure].push_back(variable);
		UsesWithProc[variable].push_back(procedure);
	}
}

// return a list of variable based on procName
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

// return a list of procName based on variable
vector<string> ProcTable::getUsesProc(string secondPerimeter) {
	// secondPerimeter = variable
	vector<string> ans = findPositionProcUses(secondPerimeter);
	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
	}
	return ans;
}

bool ProcTable::isUsesProc(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = procedure; secondPerimeter = variable
	bool result;
	vector<string> tempVector = ProcTable::getProcUsesVar(firstPerimeter);

	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i].compare(secondPerimeter) == 0) {
				result = true;
				break;
			}
			else {
				result = false;
			}
		}
	}

	return result;
}

// private method : return a list of procedures
vector<string> findPositionProcUses(string procName) {
	map<string, vector<string>>::iterator i = UsesWithProc.find(procName);

	if (i == UsesWithProc.end()) {
		vector<string> ans;
		return ans;
	}
	else {
		return i->second;
	}
}



vector<string> ProcTable::getNextProcedure(string proc1) {
	// (proc1, _)
	vector<string> ans;
	for (auto itr = tempCallsSet.begin(); itr != tempCallsSet.end(); ++itr) {
		pair<string, string> tempSet = *itr;
		string procA = tempSet.first; // parent
		string procB = tempSet.second; // child
		
		if (procA.compare(proc1) == 0) {
			ans.push_back(procB);
		}
	}

	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
	}

	return ans;
}

vector<string> ProcTable::getNextProcedureTransitive(string proc1) {
	vector<string> ans, temp;
	vector<string> caller = getNextProcedure(proc1);
	vector<string>::iterator itr, itrTemp;
	for (itr = caller.begin(); itr != caller.end(); itr++) {
		ans.push_back(*itr);
		temp = getNextProcedureTransitive(*itr);
		for (itrTemp = temp.begin(); itrTemp != temp.end(); itrTemp++) {
			ans.push_back(*itrTemp);
		}
	}

	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
	}

	return ans;
}

vector<string> ProcTable::getParentProcedure(string proc2) {
	// (_, proc2)
	vector<string> ans;
	for (auto itr = tempCallsSet.begin(); itr != tempCallsSet.end(); ++itr) {
		pair<string, string> tempSet = *itr;
		string procA = tempSet.first; // parent
		string procB = tempSet.second; // child

		if (procB.compare(proc2) == 0) {
			ans.push_back(procA);
		}
	}

	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
	}

	return ans;
}

vector<string> ProcTable::getParentProcedureTransitive(string proc2) {
	vector<string> ans, temp;
	vector<string> caller = getParentProcedure(proc2);
	vector<string>::iterator itr, itrTemp;
	for (itr = caller.begin(); itr != caller.end(); itr++) {
		ans.push_back(*itr);
		temp = getParentProcedureTransitive(*itr);
		for (itrTemp = temp.begin(); itrTemp != temp.end(); itrTemp++) {
			ans.push_back(*itrTemp);
		}
	}

	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
	}

	return ans;
}

bool ProcTable::isProcToProc(string proc1, string proc2) {
	bool result = false;
	for (auto itr = tempCallsSet.begin(); itr != tempCallsSet.end(); ++itr) {
		pair<string, string> tempSet = *itr;
		string procA = tempSet.first; // parent
		string procB = tempSet.second; // child

		if (procA.compare(proc1) == 0 && procB.compare(proc2) == 0) {
			result = true;
			break;
		}
	}
	return result;
}

bool ProcTable::isProcToProcTransitive(string proc1, string proc2) {
	vector<string> callee = getNextProcedureTransitive(proc1);
	vector<string>::iterator it;
	for (it = callee.begin(); it != callee.end(); it++) {
		if (proc2.compare(*it) == 0) { 
			return true; 
		}
	}
	return false;
}


int ProcTable::getProcTableSize() {
	return ProcMap.size();
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


void printTable(){

	for (map<string, vector<string> >::const_iterator ptr = ProcWithModifies.begin();
ptr != ProcWithModifies.end(); ptr++) {
		cout << ptr->first << ": ";
		for (vector<string>::const_iterator eptr = ptr->second.begin(); eptr != ptr->second.end(); eptr++)
			cout << *eptr << " ";
	cout << endl;
	}

}
