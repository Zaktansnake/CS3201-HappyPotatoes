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

	if (statement.size() <= 3) {
		return statement;
	}

	for (int i = 0; i < statement.size(); ++i) {
		//cout << statement.size();

		string temp = statement;
		string c = statement.substr(i, i);

		if (c.compare("*") == 0) {
			if (multiplicationDetermine(statement, i)) {
				if (i == 1) {
					temp.insert(0, "(");
					temp.insert(i + 3, ")");
				}
				else {
					temp.insert(i - 2, "(");
					temp.insert(i + 3, ")");
				}
			}
		}
		else if (c.compare("+") == 0) {
			if (plusDetermine(statement, i)) {
				if (i == 1) {
					temp.insert(0, "(");
					temp.insert(i + 3, ")");
				}
				else {
					temp.insert(i - 2, "(");
					temp.insert(i + 3, ")");
				}
			}
		}
		else if (c.compare("-") == 0) {
			if (minusDetermine(statement, i)) {
				if (i == 1) {
					temp.insert(0, "(");
					temp.insert(i + 3, ")");
				}
				else {
					temp.insert(i - 2, "(");
					temp.insert(i + 3, ")");
				}
			}
		}

		statement = temp;
	}

	return statement;
}

bool Patterns::multiplicationDetermine(string statement, int marker) {

	string c;

	if (marker == 1) {
		return true;
	}
	else if (marker == statement.size() - 1) {
		return true;
	}
	else {
		c = statement.substr(marker + 2, marker + 2);
	}

	if (c.compare("*") == 0) {
		return true;
	}
	else if (c.compare("+") == 0) {
		return true;
	}
	else if (c.compare("-") == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Patterns::plusDetermine(string statement, int marker) {

	string c;

	if (marker == 1) {
		return true;
	}
	else if (marker == statement.size() - 1) {
		return false;
	}
	else {
		c = statement.substr(marker + 2, marker + 2);
	}

	if (c.compare("+") == 0) {
		return true;
	}
	else if (c.compare("-") == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Patterns::minusDetermine(string statement, int marker) {

	string c;

	if (marker == 1) {
		return true;
	} 
	else if (marker == statement.size() - 1) {
		return false;
	}
	else {
		c = statement.substr(marker + 2, marker + 2);
	}

	if (c.compare("+") == 0) {
		return true;
	}
	else if (c.compare("-") == 0) {
		return true;
	}
	else {
		return false;
	}
}