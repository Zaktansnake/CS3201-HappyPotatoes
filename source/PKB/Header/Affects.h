#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Affects
{
public:

	static void Affects::verifyAffectRelationship(int aff1);

	static std::vector<string> Affects::getAffectsLeft(string aff2);
	static std::vector<string> Affects::getAffectsRight(string aff1);

	static bool Affects::isAffects(string aff1, string aff2);
	static bool Affects::isAffectsTransitive(string aff1, string aff2);

private:

	// constructors
	Affects();
	~Affects();

	static std::vector<string> Affects::convertIntToString(vector<int> temp);

	static void Affects::addToAffectsTable(string aff1, string aff2);

};

