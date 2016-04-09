
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <set>

#include "./Header/VarTable.h"
#include "./Header/Affects.h"
#include "./Header/CFG.h"
#include "./Header/PKB.h"

using namespace std;

map<int, vector<int>> AffectsTable;
map<int, vector<int>> AffectsReverseTable;

Affects::Affects() {
}

Affects::~Affects() {
}

// TO HAVE A CAHCE TO STORE FREQUENTLY CALLED ASSIGNNUM
void Affects::verifyAffectRelationship(int aff1) {
	string a1 = std::to_string(aff1);

	// Check whether a1 & a2 are assignType
	if ((VarTable::getAssignLine(aff1).compare("") != 0)) {
		// getUses
		vector<string> u1 = VarTable::getUsesVariable(a1);
		if (!(u1.empty())) {
			// getPreviousNodes
			vector<int> prevNodes = CFG::getPrev(aff1);
			if (!prevNodes.empty()) {
				while (true) {
					if (VarTable::getAssignLine(prevNodes[0]).compare("") != 0) {
						break;
					}
					else {
						prevNodes = CFG::getPrev(prevNodes[0]);
					}
				}
			}
		
			for (vector<string>::iterator it = u1.begin(); it != u1.end(); ++it) {
				if (VarTable::isModifiesAssign(std::to_string(prevNodes[0]), *it) == true) {
					Affects::addToAffectsTable(std::to_string(prevNodes[0]), a1);
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