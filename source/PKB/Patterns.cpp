#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "./Header/Patterns.h"

using namespace std;

bool multiplicationDetermine(string statement, int marker);
bool plusDetermine(string statement, int marker);
bool minusDetermine(string statement, int marker);

Patterns::Patterns() {	
}

Patterns::~Patterns() {
}

bool Patterns::compareAssignments(string assignment1, string assignment2) {
/*	string augmentAssignment1 = patternAssignment(assignment1);
	string augmentAssignment2 = patternAssignment(assignment2);

	//use find to use size_t for comparing

	if (augmentAssignment1.size >= augmentAssignment2.size) {
		size_t found = augmentAssignment1.find(augmentAssignment2);
		
		if (found != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		size_t found = augmentAssignment2.find(augmentAssignment1);
		
		if (found != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	*/
	return false;
}
/*
string Patterns::patternAssignment(string assignment) {
	//In-order traversal is given by assignment statement
	//To understand the depth of each node, we can do a left to right reading and put a bracket around trees have a variable and or constant 

	//For example, we get a string assignment, we need to read it left to right, once we encounter a higher order of operation we bracket the variables aroud it
	//Once completed, method will return the updated string to PKB for storage
	//Convert assignments to arrays using whitespace to determine the arrays.

	string assign = assignment;
	string statement[assign.size];
	string result;

	int i = 0;
	stringstream ssin(assign);
	
	while (ssin.good() && i < assign.size()) {
		ssin >> statement[i];
		++i;
	}

	if (sizeof(statement) / sizeof(statement[0]) <= 3) {
		string result = "";
		string temp[5];
		temp[0] = "(";
		
		for (int i = 0; i < sizeof(statement) / sizeof(statement[0]); ++i) {
			temp[i + 1] = statement[i];
		}
		
		temp[5] = ")";

		for (int j = 0; j < sizeof(temp) / sizeof(temp[0]); ++i) {
			result.append(temp[j]);
		}
		
		return result;
	}

	for (int i = 0; i < sizeof(statement) / sizeof(statement[0]); ++i) {
		string result = "";
		string c = statement[i];
		string temp[sizeof(statement) / sizeof(statement[0])];

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

	for (int j = 0; j < sizeof(statement) / sizeof(statement[0]); ++i) {
		result.append(statement[j]);
	}

	return result;
}

bool Patterns::multiplicationDetermine(string statement, int marker) {
	string c1, c2;

	if (marker == 1) {
		c2 = statement.substr(marker + 2, 1);
	}
	else if (marker == 2) {
		return false;
	}
	else if (marker == statement.size() - 1) {
		return true;
	}
	else {
		c1 = statement.substr(marker - 3, 1);
		c2 = statement.substr(marker + 2, 1);
	}

	if (c2.compare("*") == 0) {
		if (c1.compare("+") == 0) {
			return false;
		}
		else if (c1.compare("-") == 0) {
			return false;
		}
		else if (c1.compare("*") == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (c2.compare("+") == 0) {
		if (c1.compare("+") == 0) {
			return false;
		}
		else if (c1.compare("-") == 0) {
			return false;
		}
		else if (c1.compare("*") == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (c2.compare("-") == 0) {
		if (c1.compare("+") == 0) {
			return false;
		}
		else if (c1.compare("-") == 0) {
			return false;
		}
		else if (c1.compare("*") == 0) {
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

bool Patterns::plusDetermine(string statement, int marker) {
	string c1, c2;

	if (marker == 1) {
		c2 = statement.substr(marker + 2, 1);
	}
	else if (marker == 2) {
		return false;
	}
	else if (marker == statement.size() - 1) {
		return false;
	}
	else {
		c1 = statement.substr(marker - 3, 1);
		c2 = statement.substr(marker + 2, 1);
	}

	if (c2.compare("+") == 0) {
		if (c1.compare("+") == 0) {
			return false;
		}
		else if (c1.compare("-") == 0) {
			return false;
		}
		else if (c1.compare("*") == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (c2.compare("-") == 0) {
		if (c1.compare("+") == 0) {
			return false;
		}
		else if (c1.compare("-") == 0) {
			return false;
		}
		else if (c1.compare("*") == 0) {
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
		c2 = statement.substr(marker + 2, 1);
	}
	else if (marker == 2) {
		return false;
	}
	else if (marker == statement.size() - 1) {
		return false;
	}
	else {
		c1 = statement.substr(marker - 3, 1);
		c2 = statement.substr(marker + 2, 1);
	}

	if (c2.compare("+") == 0) {
		if (c1.compare("+") == 0) {
			return false;
		}
		else if (c1.compare("-") == 0) {
			return false;
		}
		else if (c1.compare("*") == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (c2.compare("-") == 0) {
		if (c1.compare("+") == 0) {
			return false;
		}
		else if (c1.compare("-") == 0) {
			return false;
		}
		else if (c1.compare("*") == 0) {
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
*/