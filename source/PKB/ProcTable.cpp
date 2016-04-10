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
#include <exception>

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

map<string, int> ProcMap;  // procName, index of the procName in the map
vector<string> ProcIndex;  // store the procedures
map<string, vector<int>> ProcStmtLineNum;
map<string, vector<string>> ProcWithModifies; // string -> procedure, vector<string> -> list of variables
map<string, vector<string>> ProcWithUses; // string -> procedure, vector<string> -> list of variables
map<string, vector<string>> ModifiesWithProc; // string -> variable, vector<string> -> procedure
map<string, vector<string>> UsesWithProc; // string -> variable, vector<string> -> procedure
std::vector<std::tuple<string, string, int>> tempCallsTable;  // string -> mainProcedure, string -> procedure, int -> stmtLine
std::unordered_set<std::pair<string, string>> tempCallsSet; // string -> mainProcedure, string -> procedure
std::map<string, vector<string>> CallsMap;
std::map<string, vector<string>> CallsReverseMap;
std::map<string, vector<string>> CallsTransitiveMap;
std::map<string, vector<string>> CallsReverseTransitiveMap;

vector<string> findPositionProcModifies(string variable); // return a list of procedures based on variable
vector<string> findPositionProcUses(string procName);


ProcTable::ProcTable() {
  
}

ProcTable::~ProcTable() {

}


vector<string> ProcTable::getProcWithType(string type, string value) {
	// calls (proc1, _)
	vector<string> finalResult = ProcTable::getNextProcedure(value);
	vector<int> ans, ansAll, tempAns;
	std::vector<int> v_intersection;

	if (type.compare("PROC") == 0) {
		return finalResult;
	}
	else {

		for (vector<string>::iterator it = finalResult.begin(); it != finalResult.end(); ++it) {
			ans = ProcStmtLineNum[*it];
			ansAll.insert(ansAll.end(), ans.begin(), ans.end());
		}

		if (type.compare("STMT") == 0) {
			return ProcTable::convertIntToString(ansAll);
		}
		else if (type.compare("ASSIGN") == 0) {
			tempAns = VarTable::getAllAssign();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));
			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("WHILE") == 0) {
			tempAns = VarTable::getAllWhile();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("IF") == 0) {
			tempAns = VarTable::getAllIfs();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
	}
}

vector<string> ProcTable::getParentProcWithType(string type, string value) {
	// calls (_, proc2)
	vector<string> finalResult = ProcTable::getParentProcedure(value);
	vector<int> ans, ansAll, tempAns;
	std::vector<int> v_intersection;

	if (type.compare("PROC") == 0) {
		return finalResult;
	}
	else {

		for (vector<string>::iterator it = finalResult.begin(); it != finalResult.end(); ++it) {
			ans = ProcStmtLineNum[*it];
			ansAll.insert(ansAll.end(), ans.begin(), ans.end());
		}

		if (type.compare("STMT") == 0) {
			return ProcTable::convertIntToString(ansAll);
		}
		else if (type.compare("ASSIGN") == 0) {
			tempAns = VarTable::getAllAssign();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));
			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("WHILE") == 0) {
			tempAns = VarTable::getAllWhile();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("IF") == 0) {
			tempAns = VarTable::getAllIfs();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
	}
}

vector<string> ProcTable::getProcTransitiveWithType(string type, string value) {
	// calls* (proc1, _)
	vector<string> finalResult = ProcTable::getNextProcedureTransitive(value);
	vector<int> ans, ansAll, tempAns;
	std::vector<int> v_intersection;

	if (type.compare("PROC") == 0) {
		return finalResult;
	}
	else {

		for (vector<string>::iterator it = finalResult.begin(); it != finalResult.end(); ++it) {
			ans = ProcStmtLineNum[*it];
			ansAll.insert(ansAll.end(), ans.begin(), ans.end());
		}

		if (type.compare("STMT") == 0) {
			return ProcTable::convertIntToString(ansAll);
		}
		else if (type.compare("ASSIGN") == 0) {
			tempAns = VarTable::getAllAssign();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));
			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("WHILE") == 0) {
			tempAns = VarTable::getAllWhile();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("IF") == 0) {
			tempAns = VarTable::getAllIfs();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
	}
}

vector<string> ProcTable::getParentProcTransitiveWithType(string type, string value) {
	// calls (_, proc2)
	vector<string> finalResult = ProcTable::getParentProcedureTransitive(value);
	vector<int> ans, ansAll, tempAns;
	std::vector<int> v_intersection;

	if (type.compare("PROC") == 0) {
		return finalResult;
	}
	else {

		for (vector<string>::iterator it = finalResult.begin(); it != finalResult.end(); ++it) {
			ans = ProcStmtLineNum[*it];
			ansAll.insert(ansAll.end(), ans.begin(), ans.end());
		}

		if (type.compare("STMT") == 0) {
			return ProcTable::convertIntToString(ansAll);
		}
		else if (type.compare("ASSIGN") == 0) {
			tempAns = VarTable::getAllAssign();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));
			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("WHILE") == 0) {
			tempAns = VarTable::getAllWhile();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
		else if (type.compare("IF") == 0) {
			tempAns = VarTable::getAllIfs();
			std::set_intersection(ansAll.begin(), ansAll.end(),
				tempAns.begin(), tempAns.end(),
				std::back_inserter(v_intersection));

			return ProcTable::convertIntToString(v_intersection);
		}
	}
}



vector<string> ProcTable::getAllProcedures() {
	return ProcIndex;
}

void ProcTable::updateProcCallsTables() {
	ProcTable::updateProcWithModAndUses();
	tempCallsTable = Calls::getCallsTable();
	ProcTable::updateAllTransitiveTables();
}

void ProcTable::updateProcWithModAndUses() {
	tempCallsSet = Calls::getCallsSet();

	for (auto itr = tempCallsSet.begin(); itr != tempCallsSet.end(); ++itr) {
		pair<string, string> tempSet = *itr;
		string procA = tempSet.first; // parent
		string procB = tempSet.second; // child

		CallsMap[procA].push_back(procB);
		CallsReverseMap[procB].push_back(procA);

		if (ProcTable::isContains(procB)) {
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
		else {
			cout << "Error: procedure does not exist." << endl;
			PKB::abort();
		}
	}
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

void ProcTable::setProcStmtNum(string procName, int stmtNum) {
	ProcStmtLineNum[procName].push_back(stmtNum);
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
	vector<string> ans = ProcWithModifies[procName];
	return ans;
}

// return a list of procName based on variable
vector<string> ProcTable::getModifiesProc(string secondPerimeter) {
	// secondPerimeter = variable
	vector<string> ans = ModifiesWithProc[secondPerimeter];
	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
	}
	return ans;
}

bool ProcTable::isModifiesProc(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = procedure; secondPerimeter = variable
	bool result = false;
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
		}
	}
	return result;
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
	vector<string> ans = ProcWithUses[procName];
	return ans;
}

// return a list of procName based on variable
vector<string> ProcTable::getUsesProc(string secondPerimeter) {
	// secondPerimeter = variable
	vector<string> ans = UsesWithProc[secondPerimeter];
	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
	}
	return ans;
}

bool ProcTable::isUsesProc(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = procedure; secondPerimeter = variable
	bool result = false;
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
		}
	}

	return result;
}



vector<string> ProcTable::getNextProcedure(string proc1) {
	// (proc1, _)
	vector<string> ans = CallsMap[proc1];

	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
	}

	return ans;
}

vector<string> ProcTable::getNextProcedureTransitive(string proc1) {
	vector<string> ans = CallsTransitiveMap[proc1];
	return ans;
}

vector<string> ProcTable::getParentProcedure(string proc2) {
	// (_, proc2)
	vector<string> ans = CallsReverseMap[proc2];
	
	if (!ans.empty()) {
		sort(ans.begin(), ans.end());
	}

	return ans;
}

vector<string> ProcTable::getParentProcedureTransitive(string proc2) {
	vector<string> ans = CallsReverseTransitiveMap[proc2];
	return ans;
}

bool ProcTable::isProcToProc(string proc1, string proc2) {
	bool result = false;

	vector<string> ans = ProcTable::getNextProcedure(proc1);

	if (ans.size() > 0) {
		for (auto itr = ans.begin(); itr != ans.end(); ++itr) {
			string tempSet = *itr;

			if (tempSet.compare(proc2) == 0) {
				result = true;
				break;
			}
		}
	}

	return result;
}

bool ProcTable::isProcToProcTransitive(string proc1, string proc2) {

	bool result = false;
	vector<string>::iterator it;
	vector<string> callee = getNextProcedureTransitive(proc1);

	if (callee.size() > 0) {
		for (it = callee.begin(); it != callee.end(); it++) {
			string tempSet = *it;

			if (tempSet.compare(proc2) == 0) {
				result = true;
				break;
			}
		}
	}

	return result;
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

void ProcTable::updateAllTransitiveTables() {
	ProcTable::updateCallsTransitive();
	ProcTable::updateParentProcTransitive();
}

void ProcTable::updateCallsTransitive() {
	vector<string> ans1, ans2, ansAll;
	vector<string>::reverse_iterator itrTemp;
	try {
		if (ProcIndex.size() > 0) {
			for (itrTemp = ProcIndex.rbegin(); itrTemp != ProcIndex.rend(); itrTemp++) {
				ans1 = ProcTable::getNextProcedure(*itrTemp);
				for (vector<string>::iterator it = ans1.begin(); it != ans1.end(); ++it) {
					ansAll.push_back(*it);
					ans2 = ProcTable::getNextProcedure(*it);
					ansAll.insert(ansAll.end(), ans2.begin(), ans2.end());
					if (!ansAll.empty()) {
						sort(ansAll.begin(), ansAll.end());
						ansAll.erase(unique(ansAll.begin(), ansAll.end()), ansAll.end());
					}
					CallsTransitiveMap[*itrTemp] = ansAll;
				}
				ansAll.clear();
			}
		}
	}
	catch (exception &e) {
		cout << "Standard exception: " << e.what() << endl;
	}
}

void ProcTable::updateParentProcTransitive() {
	vector<string> ans1, ans2, ansAll;
	vector<string>::reverse_iterator itrTemp;
	try {
		if (ProcIndex.size() > 0) {
			for (itrTemp = ProcIndex.rbegin(); itrTemp != ProcIndex.rend(); itrTemp++) {
				ans1 = ProcTable::getParentProcedure(*itrTemp);
				for (vector<string>::iterator it = ans1.begin(); it != ans1.end(); ++it) {
					ansAll.push_back(*it);
					ans2 = ProcTable::getParentProcedure(*it);
					ansAll.insert(ansAll.end(), ans2.begin(), ans2.end());
					if (!ansAll.empty()) {
						sort(ansAll.begin(), ansAll.end());
						ansAll.erase(unique(ansAll.begin(), ansAll.end()), ansAll.end());
					}
					CallsReverseTransitiveMap[*itrTemp] = ansAll;
				}
				ansAll.clear();
			}
		}
	}
	catch (exception &e) {
		cout << "Standard exception: " << e.what() << endl;
	}
}


// Convert vector<int> to vector<string>
vector<string> ProcTable::convertIntToString(vector<int> temp) {
	vector<string> result;
	if (!temp.empty()) {
		for (int i = 0; i < temp.size(); i++) {
			result.push_back(to_string(temp.at(i)));
		}
	}
	return result;
}