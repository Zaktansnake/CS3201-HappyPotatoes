#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "Header/Pattern.h"

using namespace std;

static string statement;

string patternAssignment(string assignment);
bool multiplicationDetermine(string statement, int marker);
bool plusDetermine(string statement, int marker);

string patternAssignment(string assignment) {

	//In-order traversal is given by assignment statement
	//To understand the depth of each node, we can do a left to right reading and put a bracket around trees have a variable and or constant 
	
	//In example, we get a string assignment, we need to read it left to right, once we encounter a higher order of operation we bracket the variables aroud it
	//Once completed, method will return the updated string to PKB for storage

	statement = assignment;

	if (statement.size() >= 3) {
		return statement;
	}

	for (int i = 0; i < statement.size(); ++i) {
		//cout << statement.size();

		string temp = statement;
		string c = statement.substr(i);

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

		statement = temp;
	}

	return statement;
}

bool multiplicationDetermine(string statement, int marker) {

	string c1, c2;

	if (marker == 1) {
		return true;
	}
	else {
		c1 = statement.substr(marker - 2);
	}

	if (c1.compare("+")) {
		return true;
	}
	else {
		return false;
	}
}

bool plusDetermine(string statement, int marker) {

	string c1, c2;

	if (marker == 1) {
		c1 = statement.substr(marker - 1);
	}
	else {
		c1 = statement.substr(marker - 2);
	}

	if (marker == statement.size() - 1) {
		c2 = statement.substr(marker + 1);
	}
	else {
		c2 = statement.substr(marker + 2);
	}

	if (c2.compare("+")) {
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