#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Affects
{
public:

	static void updateAffectsTable();

	static std::vector<string> Affects::getAffectsRight(string aff1);
	static std::vector<string> Affects::getAffectsLeft(string aff2);

	static bool Affects::isAffects(string aff1, string aff2);
	static bool Affects::isAffectsTransitive(string aff1, string aff2);

private:

	// constructors
	Affects();
	~Affects();

	static void Affects::verifyAffectRelationship(int aff1, int aff2);
	static void Affects::addToAffectsTable(string aff1, string aff2);

	static std::vector<string> Affects::convertIntToString(vector<int> temp);


	/*std::set<STMT_NO> getAffects(STMT_NO affects);
	std::set<STMT_NO> getAffectsTransitive(STMT_NO affects);
	std::set<STMT_NO> getAffectedBy(STMT_NO affected);
	std::set<STMT_NO> getAffectedByTransitive(STMT_NO affected);*/
};

