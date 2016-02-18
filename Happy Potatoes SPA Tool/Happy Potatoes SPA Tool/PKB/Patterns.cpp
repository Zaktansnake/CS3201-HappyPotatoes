#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "Header/Patterns.h"

using namespace std;

string patternAssignment(string assignment);
bool multiplicationDetermine(string statement, int marker);
bool plusDetermine(string statement, int marker);
bool minusDetermine(string statement, int marker);

Patterns::Patterns()
{	
}

Patterns::~Patterns()
{
}

string Patterns::patternAssignment(string assignment) {

	//In-order traversal is given by assignment statement
	//To understand the depth of each node, we can do a left to right reading and put a bracket around trees have a variable and or constant 

	//In example, we get a string assignment, we need to read it left to right, once we encounter a higher order of operation we bracket the variables aroud it
	//Once completed, method will return the updated string to PKB for storage

	string statement = assignment;

	if (statement.size() >= 3) {
		return statement;
	}

	for (int i = 0; i < statement.size(); ++i) {
		//cout << statement.size();

		string temp = statement;
		string c = statement.substr(i, i + 1);

		if (c.compare("*")) {
			if (multiplicationDetermine(statement, i)) {
				if (i == 1) {
					temp.insert(0, "(");
					temp.insert(i + 2, ")");
				}
				else {
					temp.insert(i - 2, "(");
					temp.insert(i + 2, ")");
				}
			}
		}
		else if (c.compare("+")) {
			if (plusDetermine(statement, i)) {
				if (i == 1) {
					temp.insert(0, "(");
					temp.insert(i + 2, ")");
				}
				else {
					temp.insert(i - 2, "(");
					temp.insert(i + 2, ")");
				}
			}
		}
		else if (c.compare("-")) {
			if (minusDetermine(statement, i)) {
				if (i == 1) {
					temp.insert(0, "(");
					temp.insert(i + 2, ")");
				}
				else {
					temp.insert(i - 2, "(");
					temp.insert(i + 2, ")");
				}
			}
		}

		statement = temp;
	}

	return statement;
}

bool Patterns::multiplicationDetermine(string statement, int marker) {

	string c1, c2;

	if (marker == 1) {
		return true;
	}
	else {
		c1 = statement.substr(marker - 2, marker - 1);
	}

	if (c1.compare("+")) {
		return true;
	}
	else if (c1.compare("-")) {
		return true;
	}
	else {
		return false;
	}
}

bool Patterns::plusDetermine(string statement, int marker) {

	string c1, c2;

	if (marker == 1) {
		c1 = statement.substr(marker - 1, marker);
	}
	else {
		c1 = statement.substr(marker - 2, marker - 1);
	}

	if (marker == statement.size() - 1) {
		c2 = statement.substr(marker, marker + 1);
	}
	else {
		c2 = statement.substr(marker + 2, marker + 3);
	}

	if (c2.compare("+")) {
		if (c1.compare(")")) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (c2.compare("-")) {
		if (c1.compare(")")) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

bool Patterns::minusDetermine(string statement, int marker) {

	string c1, c2;

	if (marker == 1) {
		c1 = statement.substr(marker - 1, marker);
	}
	else {
		c1 = statement.substr(marker - 2, marker - 1);
	}

	if (marker == statement.size() - 1) {
		c2 = statement.substr(marker, marker + 1);
	}
	else {
		c2 = statement.substr(marker + 2, marker + 3);
	}

	if (c2.compare("+")) {
		if (c1.compare(")")) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (c2.compare("-")) {
		if (c1.compare(")")) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}