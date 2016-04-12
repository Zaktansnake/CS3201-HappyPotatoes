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
map<int, vector<int>> AffectsTransitiveTable;
map<int, vector<int>> AffectsTransitiveReverseTable;

bool boolResult = true;

Affects::Affects() {
}

Affects::~Affects() {
}

void Affects::updateAffectsTable() {
	try {
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
					if (boolResult) {
						if (!Affects::verifyAffectRelationship(*itrTemp, *itrTemp2)) {
							boolResult = false;
						}
					}
				}
				boolResult = true;
			}
		}
	}
	catch (exception &e) {
		cout << "Standard exception (for affects): " << e.what() << endl;
	}

}

bool Affects::verifyAffectRelationship(int aff1, int aff2) {

	bool result = false;
	string a1 = std::to_string(aff1);
	string a2 = std::to_string(aff2);

	if (CFG::isNextStar(aff1, aff2)) {
		// First, get modifies; Second, get uses
		vector<string> u1 = VarTable::getModifiesVariable(a1);
		vector<string> u2 = VarTable::getUsesVariable(a1);
		vector<string> u3 = VarTable::getUsesVariable(a2);
		vector<string> u4 = VarTable::getModifiesVariable(a2);
		if (aff1 == aff2) {
			if ((!(u1.empty())) && (!(u2.empty()))) {
				for (vector<string>::iterator it = u1.begin(); it != u1.end(); ++it) {
					if (std::find(u2.begin(), u2.end(), *it) != u2.end()) {
						Affects::addToAffectsTable(aff1, aff2);
					}
				}
			}
		}
		else {
			if ((!(u1.empty())) && (!(u3.empty()) && (!(u4.empty())))) {
				for (vector<string>::iterator it = u1.begin(); it != u1.end(); ++it) {
					if ((std::find(u4.begin(), u4.end(), *it) != u4.end())) {
						if (std::find(u2.begin(), u2.end(), *it) != u2.end()) {
							return false;
						}
						else {
							if (std::find(u3.begin(), u3.end(), *it) != u3.end()) {
								Affects::addToAffectsTable(aff1, aff2);
								return result;
							}
							else {
								return result;
							}
						}
					}
					else {
						if (std::find(u3.begin(), u3.end(), *it) != u3.end()) {
							Affects::addToAffectsTable(aff1, aff2);
							return true;
						}
					}
				}
			}
		}
	}
}

void Affects::updateAffectsTransitiveTable(int assign1) {
	int key;
	set<int> newSetValue;
	vector<int> newValue;
	vector<string>::iterator itrTemp;
	try {
		if (AffectsTable.size() > 0) {
			for (map<int, vector<int>>::iterator ii = AffectsTable.begin(); ii != AffectsTable.end(); ++ii) {
				key = (*ii).first;
				vector<int> inVect = (*ii).second;
				for (unsigned j = 0; j < inVect.size(); j++) {
					newSetValue.insert(inVect[j]);
					vector<int> temp1 = AffectsTable[inVect[j]];
					for (unsigned z = 0; z < temp1.size(); z++) {
						newSetValue.insert(temp1[z]);
					}
				}

				std::copy(newSetValue.begin(), newSetValue.end(), std::back_inserter(newValue));
				AffectsTransitiveTable[key] = newValue;

				set<int>::iterator it;
				for (it = newSetValue.begin(); it != newSetValue.end(); it++) {
					AffectsTransitiveReverseTable[*it].push_back(key);
				}

				newValue.clear();
				newSetValue.clear();
			}
		}
	}
	catch (exception &e) {
		cout << "Standard exception (updateAffectsTransitiveTable): " << e.what() << endl;
	}

}

void Affects::addToAffectsTable(int a1, int a2) {
	AffectsTable[a1].push_back(a2);
	AffectsReverseTable[a2].push_back(a1);
}

std::vector<string> Affects::getAffectsLeft(string aff2) {
	vector<int> ans;
	int a2 = atoi(aff2.c_str());
	map<int, vector<int>>::iterator it;
	it = AffectsReverseTable.find(a2);
	if (it != AffectsReverseTable.end()) {
		ans = it->second;
	}
	return Affects::convertIntToString(ans);
}

std::vector<string> Affects::getAffectsRight(string aff1) {
	vector<int> ans;
	int a1 = atoi(aff1.c_str());
	map<int, vector<int>>::iterator it;
	it = AffectsTable.find(a1);
	if (it != AffectsTable.end()) {
		ans = it->second;
	}
	return Affects::convertIntToString(ans);
}


std::vector<string> Affects::getAffectsTransitiveRight(string aff1) {
	int a1 = std::stoi(aff1);
	vector<int> finalResult, ans;
	map<int, vector<int>>::iterator it;
	it = AffectsTable.find(a1);
	if (it != AffectsTable.end()) {
		ans = it->second;
	}
	if (ans.size() > 0) {
		if (AffectsTransitiveTable.size() > 0) {
			it = AffectsTransitiveTable.find(a1);
			if (it != AffectsTransitiveTable.end()) {
				finalResult = it->second;
			}
			else {
				Affects::updateAffectsTransitiveTable(a1);
				it = AffectsTransitiveTable.find(a1);
				if (it != AffectsTransitiveTable.end()) {
					finalResult = it->second;
				}
			}
		}
		else {
			Affects::updateAffectsTransitiveTable(a1);
			it = AffectsTransitiveTable.find(a1);
			if (it != AffectsTransitiveTable.end()) {
				finalResult = it->second;
			}
		}
	}
	return Affects::convertIntToString(finalResult);
}

std::vector<string> Affects::getAffectsTransitiveLeft(string aff2) {
	int a2 = std::stoi(aff2);
	vector<int> finalResult, ans;
	map<int, vector<int>>::iterator it;
	it = AffectsReverseTable.find(a2);
	if (it != AffectsReverseTable.end()) {
		ans = it->second;
	}
	if (ans.size() > 0) {
		if (AffectsTransitiveReverseTable.size() > 0) {
			it = AffectsTransitiveReverseTable.find(a2);
			if (it != AffectsTransitiveReverseTable.end()) {
				finalResult = it->second;
			}
			else {
				Affects::updateAffectsTransitiveTable(a2);
				it = AffectsTransitiveReverseTable.find(a2);
				if (it != AffectsTransitiveReverseTable.end()) {
					finalResult = it->second;
				}
			}
		}
		else {
			Affects::updateAffectsTransitiveTable(a2);
			it = AffectsTransitiveReverseTable.find(a2);
			if (it != AffectsTransitiveReverseTable.end()) {
				finalResult = it->second;
			}
		}
	}


	cout << "Table for AffectsTransitiveTable" << endl;
	for (map<int, vector<int>>::iterator ii = AffectsTransitiveTable.begin(); ii != AffectsTransitiveTable.end(); ++ii) {
		cout << (*ii).first << ": ";
		vector <int> inVect = (*ii).second;
		for (unsigned j = 0; j<inVect.size(); j++) {
			cout << inVect[j] << " ";
		}
		cout << endl;
	}


	cout << "Table for AffectsTransitiveReverseTable" << endl;
	for (map<int, vector<int>>::iterator ii = AffectsTransitiveReverseTable.begin(); ii != AffectsTransitiveReverseTable.end(); ++ii) {
		cout << (*ii).first << ": ";
		vector <int> inVect = (*ii).second;
		for (unsigned j = 0; j<inVect.size(); j++) {
			cout << inVect[j] << " ";
		}
		cout << endl;
	}



	return Affects::convertIntToString(finalResult);
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

	vector<int> ans = AffectsTransitiveTable[a1];
	if (!ans.empty()) {
		for (vector<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
			if (a2 == *it) {
				return true;
			}
		}
	}
	else {
		Affects::updateAffectsTransitiveTable(a1);
		ans = AffectsTransitiveTable[a1];
		if (!ans.empty()) {
			for (vector<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
				if (a2 == *it) {
					return true;
				}
			}
		}

	}
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