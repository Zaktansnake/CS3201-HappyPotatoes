#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>

#include "./Header/PKB.h"
#include "./Header/VarTable.h"
#include "./Header/ProcTable.h"
#include "./Header/ConstantTable.h"
#include "./Header/Modifies.h"
#include "./Header/Uses.h"

using namespace std;

// (Modifies) int -> stmtLine, string -> variable
vector<pair<int, string>> varTableLeftInPair;
// (Uses) int -> stmtLine, string -> variable
vector<pair<int, string>> varTableRightInPair;
// (While) string -> variable name, vector<int> -> stmtLine
map<string, vector<int>> whileTable;
// (Ifs) string -> variable, int -> stmtLine
map<string, vector<int>> ifsTable;
// (Assign) int -> stmtLine, string -> line
map<int, string> assignTable;

vector<string> allVariables;
vector<int> allStmtNum;
vector<int> assignNum;
vector<int> whileStmtNum;
vector<int> ifStmtNum;
vector<string> assignLines;

void addDataToStmt();
void addToVarTable(int position, string varName, int stmtLine);
bool isContainsAssign(int stmtLine);
bool isContainsWhile(string stmtLine);

void printVarLeft();
void printVarRight();
void printWhileLoop();

VarTable::VarTable() {
}

VarTable::~VarTable() {
}


vector<string> VarTable::getModifiesWithType(string type, string value) {
	// Modifies(proc, _) OR Modifies(stmt,_)
	vector<string> finalResult;

	if (type.compare("PROC") == 0) {
		finalResult = ProcTable::getProcModifiesVar(value);
	}
	else if (type.compare("VAR") == 0) {
		finalResult = VarTable::getModifiesVariable(value);
	}

	return finalResult;
}

vector<string> VarTable::getModifiedWithType(string type, string value) {
	// Modifies(_, variable)
	vector<string> finalResult;

	if (type.compare("PROC") == 0) {
		finalResult = ProcTable::getModifiesProc(value);
	}
	else if (type.compare("STMT") == 0) {
		finalResult = VarTable::getModifiesStmt(value);
	}
	else if (type.compare("ASSIGN") == 0) {
		finalResult = VarTable::getModifiesAssign(value);
	}
	else if (type.compare("WHILE") == 0) {
		finalResult = VarTable::getModifiesWhile(value);
	}
	else if (type.compare("IF") == 0) {
		finalResult = VarTable::getModifiesIfs(value);
	}

	return finalResult;
}

vector<string> VarTable::getUsesWithType(string type, string value) {
	// Uses(proc, _) OR Uses(stmt,_)
	vector<string> finalResult;

	if (type.compare("PROC") == 0) {
		finalResult = ProcTable::getProcUsesVar(value);
	}
	else if (type.compare("VAR") == 0) {
		finalResult = VarTable::getUsesVariable(value);
	}

	return finalResult;
}

vector<string> VarTable::getUsedWithType(string type, string value) {
	// Uses(_, variable)
	vector<string> finalResult;

	if (type.compare("PROC") == 0) {
		finalResult = ProcTable::getUsesProc(value);
	}
	else if (type.compare("STMT") == 0) {
		finalResult = VarTable::getUsesStmt(value);
	}
	else if (type.compare("ASSIGN") == 0) {
		finalResult = VarTable::getUsesAssig(value);
	}
	else if (type.compare("WHILE") == 0) {
		finalResult = VarTable::getUsesWhile(value);
	}
	else if (type.compare("IF") == 0) {
		finalResult = VarTable::getUsesIfs(value);
	}

	return finalResult;
}

bool VarTable::getModifiesBooleanWithType(string firstPerimeter, string secondPerimeter) {
	bool finalResult;
	if (VarTable::is_number(firstPerimeter)){
		finalResult = VarTable::isModifiesStmt(firstPerimeter, secondPerimeter);
	}
	else {
		finalResult = VarTable::isModifiesProcedure(firstPerimeter, secondPerimeter);
	}
	return finalResult;
}

bool VarTable::getUsesBooleanWithType(string firstPerimeter, string secondPerimeter) {
	bool finalResult;
	if (VarTable::is_number(firstPerimeter)) {
		finalResult = VarTable::isUsesStmt(firstPerimeter, secondPerimeter);
	}
	else {
		finalResult = VarTable::isUsesProcedure(firstPerimeter, secondPerimeter);
	}
	return finalResult;
}

vector<string> VarTable::getAllWithType(string type, string value) {
	vector<string> finalResult;
	if (type.compare("PROC") == 0) {
		finalResult = ProcTable::getAllProcedures();
	}
	else if (type.compare("STMT") == 0) {
		finalResult = VarTable::getAllStmtString();
	}
	else if (type.compare("ASSIGN") == 0) {
		finalResult = VarTable::getAllAssignString();
	}
	else if (type.compare("WHILE") == 0) {
		finalResult = VarTable::getAllWhileString();
	}
	else if (type.compare("IF") == 0) {
		finalResult = VarTable::getAllIfsString();
	}
	else if (type.compare("VAR") == 0) {
		finalResult = VarTable::getAllVariables();
	}
	else if (type.compare("CONSTANT") == 0) {
		finalResult = ConstantTable::getAllConstantValues();
	}
	return finalResult;
}


int VarTable::varTableLeftInPairSize() {
	return varTableLeftInPair.size();
}

int VarTable::varTableRightInPairSize() {
	return varTableRightInPair.size();
}

int VarTable::whileTableSize() {
	return whileTable.size();
}

int VarTable::assignTableSize() {
	return assignTable.size();
}



void VarTable::updateModifiesUsesTables() {
	addDataToStmt();
	VarTable::sortVarLeftAndRight();
	VarTable::setAssign();

	std::sort(assignNum.begin(), assignNum.end());
	std::sort(whileStmtNum.begin(), whileStmtNum.end());

	sort(allVariables.begin(), allVariables.end());
	allVariables.erase(unique(allVariables.begin(), allVariables.end()), allVariables.end());
}

void VarTable::sortVarLeftAndRight() {
	std::sort(varTableLeftInPair.begin(), varTableLeftInPair.end());
	varTableLeftInPair.erase(unique(varTableLeftInPair.begin(), varTableLeftInPair.end()), varTableLeftInPair.end());
	std::sort(varTableRightInPair.begin(), varTableRightInPair.end());
	varTableRightInPair.erase(unique(varTableRightInPair.begin(), varTableRightInPair.end()), varTableRightInPair.end());
}



vector<int> VarTable::getAllStmt() {
	return allStmtNum;
}

vector<int> VarTable::getAllWhile() {
	return whileStmtNum;
}

vector<int> VarTable::getAllIfs() {
	return ifStmtNum;
}

vector<string> VarTable::getAllStmtString() {
	return VarTable::convertIntToString(allStmtNum);
}

vector<string> VarTable::getAllWhileString() {
	return VarTable::convertIntToString(whileStmtNum);
}

vector<string> VarTable::getAllAssignString() {
	return VarTable::convertIntToString(assignNum);
}

vector<string> VarTable::getAllIfsString() {
	return VarTable::convertIntToString(ifStmtNum);
}

void VarTable::setAllVariables(string variable) {
	allVariables.push_back(variable);
}

vector<string> VarTable::getAllVariables() {
	return allVariables;
}



vector<pair<int, string>> VarTable::getModifiesInPair() {
	return varTableLeftInPair;
}

vector<pair<int, string>> VarTable::getUsesInPair() {
	return varTableRightInPair;
}



// add stmtLine into stmtNum
void addDataToStmt() {
	int tempNum = PKB::getStmtNum();
	for (int i = 1; i <= tempNum; i++) {
		allStmtNum.push_back(i);
	}
}

vector<int> VarTable::setAssign() {
	for (map<int, string>::iterator it = assignTable.begin(); it != assignTable.end(); ++it) {
		assignNum.push_back(it->first);
	}
	return assignNum;
}



// ---------------------- IFS table ---------------------------------
void VarTable::addDataToIfsTable(string variable, int stmtNum) {
	ifsTable[variable].push_back(stmtNum);
	ifStmtNum.push_back(stmtNum);
}

vector<int> VarTable::getAssignFromIfsTable(string variable) {
	vector<int> ans;
	if (ifsTable.count(variable)) {
		ans = ifsTable[variable];
	}
	return ans;
}

// ---------------------- While table ---------------------------------
void VarTable::addDataToWhileTable(string variable, int stmtNum) {
	whileTable[variable].push_back(stmtNum);
	whileStmtNum.push_back(stmtNum);
}

vector<int> VarTable::getAssignFromWhileTable(string variable) {
	vector<int> ans;
	if (whileTable.count(variable)) {
		ans = whileTable[variable];
	}
	return ans;
}

//----------------------- Assign Table ---------------------------------
void VarTable::addDataToAssignTable(string variable, int stmtNum) {
	assignTable.insert(pair<int, string>(stmtNum, variable));
}

string VarTable::getAssignLine(int stmtNum) {
	string temp = "";
	std::map<int, string>::iterator it = assignTable.find(stmtNum);

	if (it != assignTable.end()) {
		// found
		temp = it->second;
	}

	return temp;
}

map<int, string> VarTable::getAssignTable() {
	return assignTable;
}

vector<int> VarTable::getAllAssign() {
	return assignNum;
}



// ------------------------ Modifies -----------------------------------

void VarTable::addDataToModifies(string varName, int stmtLine) {
	addToVarTable(1, varName, stmtLine);
	Modifies::addModifiesTable(varName, stmtLine);
	VarTable::setAllVariables(varName);
}

vector<string> VarTable::findVariableLeft(int stmtLine1, int stmtLine2) {
	// stmtLine1 = parent; stmtLine2 = the position of bracket end
	vector<string> ans;

	for (int i = 0; i < varTableLeftInPair.size(); i++) {
		pair<int, string> tempVector = varTableLeftInPair.at(i);

		if (tempVector.first > stmtLine1 && tempVector.first <= stmtLine2) {
			if (!ans.empty()) {
				if (std::find(ans.begin(), ans.end(), tempVector.second) != ans.end()) {
				}
				else {
					ans.push_back(tempVector.second);
				}
			}
			else {
				ans.push_back(tempVector.second);
			}
		}
	}

	return ans;
}

vector<int> VarTable::getModifiesTable(string varName) {
	return Modifies::getModifiesTable(varName);
}

vector<string> VarTable::getModifiesVariable(string firstPerimeter) {
	// firstPerimeter = stmtNum
	vector<string> ans = Modifies::getModVariables(firstPerimeter);
	return ans;
}

vector<int> VarTable::getModifiesAssignInt(string secondPerimeter) {
	// secondPerimeter = variable
	std::vector<int> ans = Modifies::getModifiesTable(secondPerimeter);
	vector<int> finalResult = assignNum;

	if (ans.size() > 0) {
		std::sort(ans.begin(), ans.end());
		std::vector<int> v_intersection;
		std::set_intersection(ans.begin(), ans.end(),
			finalResult.begin(), finalResult.end(),
			std::back_inserter(v_intersection));
		return v_intersection;
	}

	return ans;
}

vector<string> VarTable::getModifiesAssign(string secondPerimeter) {
	// secondPerimeter = variable
	vector<string> emptyVector;
	std::vector<int> ans = Modifies::getModifiesTable(secondPerimeter);
	vector<int> finalResult = assignNum;
	if (ans.size() > 0) {
		std::sort(ans.begin(), ans.end());
		std::vector<int> v_intersection;
		std::set_intersection(ans.begin(), ans.end(),
			finalResult.begin(), finalResult.end(),
			std::back_inserter(v_intersection));
		return VarTable::convertIntToString(v_intersection);
	}
	return emptyVector;
}

vector<string> VarTable::getModifiesStmt(string secondPerimeter) {
	// secondPerimeter = variable
	return VarTable::convertIntToString(Modifies::getModifiesTable(secondPerimeter));
}

vector<string> VarTable::getModifiesWhile(string secondPerimeter) {
	// secondPerimeter = variable
	vector<string> emptyVector;
	vector<int> ans;
	vector<int> tempAns = Modifies::getModifiesTable(secondPerimeter);
	if (tempAns.size() > 0) {
		sort(tempAns.begin(), tempAns.end());

		set<int> intersect;
		set_intersection(tempAns.begin(), tempAns.end(), whileStmtNum.begin(), whileStmtNum.end(), back_inserter(ans));
		return VarTable::convertIntToString(ans);
	}
	return emptyVector;
}

vector<string>  VarTable::getModifiesIfs(string secondPerimeter) {
	// secondPerimeter = variable
	vector<string> emptyVector;
	vector<int> ans;
	vector<int> tempAns = Modifies::getModifiesTable(secondPerimeter);
	if (tempAns.size() > 0) {
		sort(tempAns.begin(), tempAns.end());

		set<int> intersect;
		set_intersection(tempAns.begin(), tempAns.end(), ifStmtNum.begin(), ifStmtNum.end(), back_inserter(ans));
		return VarTable::convertIntToString(ans);
	}
	return emptyVector;
}


bool VarTable::isModifiesProcedure(string firstPerimeter, string secondPerimeter) {
	return ProcTable::isModifiesProc(firstPerimeter, secondPerimeter);
}

bool VarTable::isModifiesAssign(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (isContainsAssign(numbValue)) {
		vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);

		if (tempVector.size() == 0) {
			result = false;
		}
		else {
			for (int i = 0; i < tempVector.size(); i++) {
				if (tempVector[i] == numbValue) {
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
	else {
		return false;
	}
}

bool VarTable::isModifiesStmt(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	vector<int> tempVector = Modifies::getModifiesTable(secondPerimeter);

	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(firstPerimeter) >> numbValue;

		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
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

bool VarTable::isModifiesWhile(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (!isContainsWhile(secondPerimeter)) {
		result = false;
	}
	else {
		vector<int> ans = whileTable.at(secondPerimeter);
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == numbValue) {
				result = true;
				break;
			}
		}
		result = false;
	}
	return result;
}

bool VarTable::isModifiesIfs(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result = false;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	vector<int> ans = ifsTable[secondPerimeter];
	if (!ans.empty()) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == numbValue) {
				result = true;
				break;
			}
		}
	}
	return result;
}



//-------------------------------Uses---------------------------

void VarTable::addDataToUses(string varName, int stmtLine) {
	addToVarTable(2, varName, stmtLine);
	Uses::addUsesTable(varName, stmtLine);
	VarTable::setAllVariables(varName);
}

vector<string> VarTable::findVariableRight(int stmtLine1, int stmtLine2) {
	// stmtLine1 = parent; stmtLine2 = the position of bracket end
	vector<string> ans;

	for (int i = 0; i < varTableRightInPair.size(); i++) {
		pair<int, string> tempVector = varTableRightInPair.at(i);
		int temp = stmtLine2 - stmtLine1;

		if (temp == 1) {
			if (tempVector.first == stmtLine2) {
				ans.push_back(tempVector.second);
			}
		}
		else if (tempVector.first > stmtLine1 && tempVector.first <= stmtLine2) {
			if (std::find(ans.begin(), ans.end(), tempVector.second) != ans.end()) {

			}
			else {
				ans.push_back(tempVector.second);
			}
		}
	}

	return ans;
}

vector<int> VarTable::getUsesAssigInt(string secondPerimeter) {
	// secondPerimeter = variable
	std::vector<int> ans = Uses::getUsesTable(secondPerimeter);
	vector<int> finalResult = assignNum;
	std::sort(ans.begin(), ans.end());
	std::vector<int> v_intersection;
	std::set_intersection(ans.begin(), ans.end(),
		finalResult.begin(), finalResult.end(),
		std::back_inserter(v_intersection));

	return v_intersection;
}

vector<string> VarTable::getUsesVariable(string firstPerimeter) {
	// firstPerimeter = stmtNum
	vector<string> ans = Uses::getUseVariables(firstPerimeter);
	return ans;
}

vector<string> VarTable::getUsesAssig(string secondPerimeter) {
	// secondPerimeter = variable
	std::vector<int> ans = Uses::getUsesTable(secondPerimeter);
	vector<int> finalResult = assignNum;
	std::sort(ans.begin(), ans.end());
	std::vector<int> v_intersection;
	std::set_intersection(ans.begin(), ans.end(),
		finalResult.begin(), finalResult.end(),
		std::back_inserter(v_intersection));

	return VarTable::convertIntToString(v_intersection);
}

vector<string> VarTable::getUsesStmt(string secondPerimeter) {
	// secondPerimeter -> variable
	return VarTable::convertIntToString(Uses::getUsesTable(secondPerimeter));
}

vector<string> VarTable::getUsesWhile(string secondPerimeter) {
	// secondPerimeter -> variable
	vector<int> ans = whileTable[secondPerimeter];
	return VarTable::convertIntToString(ans);
}

vector<string> VarTable::getUsesIfs(string secondPerimeter) {
	// secondPerimeter -> variable
	vector<int> ans = ifsTable[secondPerimeter];
	return VarTable::convertIntToString(ans);
}


bool VarTable::isUsesProcedure(string firstPerimeter, string secondPerimeter) {
	return ProcTable::isUsesProc(firstPerimeter, secondPerimeter);
}

bool VarTable::isUsesAssign(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;

	if (isContainsAssign(numbValue)) {
		vector<int> tempVector = Uses::getUsesTable(secondPerimeter);

		if (tempVector.size() == 0) {
			result = false;
		}
		else {
			for (int i = 0; i < tempVector.size(); i++) {
				if (tempVector[i] == numbValue) {
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
	else {
		return false;
	}
}

bool VarTable::isUsesStmt(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result;
	vector<int> tempVector = Uses::getUsesTable(secondPerimeter);

	if (tempVector.size() == 0) {
		result = false;
	}
	else {
		int numbValue;
		istringstream(firstPerimeter) >> numbValue;

		for (int i = 0; i < tempVector.size(); i++) {
			if (tempVector[i] == numbValue) {
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

bool VarTable::isUsesWhile(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result = false;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;
	vector<int> ans = whileTable.at(secondPerimeter);
	if (ans.size() > 0) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == numbValue) {
				result = true;
				break;
			}
		}
	}
	return result;
}

bool VarTable::isUsesIfs(string firstPerimeter, string secondPerimeter) {
	// firstPerimeter = statementNumber; secondPerimeter = variable
	bool result = false;
	int numbValue;
	istringstream(firstPerimeter) >> numbValue;
	vector<int> ans =ifsTable.at(secondPerimeter);
	if (ans.size() > 0) {
		for (int i = 0; i < ans.size(); i++) {
			if (ans.at(i) == numbValue) {
				result = true;
				break;
			}
		}
	}
	return result;
}


vector<int> VarTable::getUsesTable(string varName) {
	return Uses::getUsesTable(varName);
}


// add the var to varTableLeftInPair or varTableRightInPair
void addToVarTable(int position, string varName, int stmtLine) {
	if (position == 1) {
		varTableLeftInPair.push_back(make_pair(stmtLine, varName));
	}
	else if (position == 2) {
		varTableRightInPair.push_back(make_pair(stmtLine, varName));
	}
}



bool isContainsAssign(int stmtLine) {
	auto search = assignTable.find(stmtLine);

	if (search != assignTable.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool isContainsWhile(string variable) {
	auto search = whileTable.find(variable);

	if (search != whileTable.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool isContainsIfs(string variable) {
	auto search = ifsTable.find(variable);

	if (search != ifsTable.end()) {
		return true;
	}
	else {
		return false;
	}
}



bool VarTable::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !::isdigit(c); }) == s.end();
}


// Convert vector<int> to vector<string>
vector<string> VarTable::convertIntToString(vector<int> temp) {
	vector<string> result;
	if (!temp.empty()) {
		for(int i = 0; i < temp.size(); i++) {
			result.push_back(to_string(temp.at(i)));
		}
	}
	return result;
}
