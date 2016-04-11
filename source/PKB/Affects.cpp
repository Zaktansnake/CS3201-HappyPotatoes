#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>

#include "./Header/VarTable.h"
#include "./Header/ProcTable.h"
#include "./Header/Affects.h"
#include "./Header/CFG.h"
#include "./Header/PKB.h"

using namespace std;

map<int, vector<int>> AffectsTable;
map<int, vector<int>> AffectsReverseTable;
map <int, vector<int>> AffectsTransitiveTable;

Affects::Affects() {
}

Affects::~Affects() {
}

void Affects::updateAffectsTable() {
	map<string, vector<int>> allProcStmtNum = ProcTable::getProcStmtLineNum();
	vector<int> allAssign = VarTable::getAllAssign();
	vector<int>::iterator itrTemp, itrTemp2;
	for (map<string, vector<int>>::iterator ii = allProcStmtNum.begin(); ii != allProcStmtNum.end(); ++ii) {
		// return a list of integers based on procedure
		vector <int> inVect = (*ii).second;
		std::vector<int> v_intersection;
		std::set_intersection(inVect.begin(), inVect.end(),
			allAssign.begin(), allAssign.end(),
			std::back_inserter(v_intersection));
		for (itrTemp = v_intersection.begin(); itrTemp != v_intersection.end(); itrTemp++) {
			for (itrTemp2 = v_intersection.begin(); itrTemp2 != v_intersection.end(); itrTemp2++) {
				Affects::verifyAffectRelationship(*itrTemp, *itrTemp2);
			}
		}
	}
}

void Affects::verifyAffectRelationship(int aff1, int aff2) {
	string a1 = std::to_string(aff1);
	string a2 = std::to_string(aff2);

	if (CFG::isNextStar(aff1, aff2)) {
		// First, get modifies; Second, get uses
		vector<string> u1 = VarTable::getModifiesVariable(a1);
		vector<string> u2 = VarTable::getUsesVariable(a2);
		if ((!(u1.empty())) && (!(u2.empty()))) {
			for (vector<string>::iterator it = u1.begin(); it != u1.end(); ++it) {
				if (std::find(u2.begin(), u2.end(), *it) != u2.end()) {
					Affects::addToAffectsTable(a1, a2);
				}
			}
		}
	}
}

void Affects::addToAffectsTable(string aff1, string aff2) {
	int a1 = std::stoi(aff1);
	int a2 = std::stoi(aff2);
	AffectsTable[a1].push_back(a2);
	AffectsReverseTable[a2].push_back(a1);
}

std::vector<string> Affects::getAffectsLeft(string aff2) {
	int a2 = std::stoi(aff2);
	vector<int> ans = AffectsReverseTable[a2];
	return Affects::convertIntToString(ans);
}

std::vector<string> Affects::getAffectsRight(string aff1) {
	int a1 = std::stoi(aff1);
	vector<int> ans = AffectsReverseTable[a1];
	return Affects::convertIntToString(ans);
}

bool Affects::isAffects(string aff1, string aff2) {
	int a1 = std::stoi(aff1);
	int a2 = std::stoi(aff2);

	vector<int> ans = AffectsTable[a1];
	if (!ans.empty()) {
		for (vector<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
			if (a2 == *it) {
				return true;
			}
		}
		return false;
	}
	return false;
}

bool Affects::isAffectsTransitive(string aff1, string aff2) {
	int a1 = std::stoi(aff1);
	int a2 = std::stoi(aff2);

	// TO BE COMPLETED
	// 
	return false;
}

std::vector<string> Affects::convertIntToString(vector<int> temp) {
	vector<string> result;
	if (!temp.empty()) {
		for (int i = 0; i < temp.size(); i++) {
			result.push_back(to_string(temp.at(i)));
		}
	}
	return result;
}