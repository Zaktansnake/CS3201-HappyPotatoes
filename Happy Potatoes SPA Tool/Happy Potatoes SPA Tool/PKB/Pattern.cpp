#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "./Header/Pattern.h"

using namespace std;

static string temp;

string patternAssignment(string assignment) {

	//In-order traversal is given by assignment statement
	//To understand the depth of each node, we can do a left to right reading and put a bracket around trees have a variable and or constant 
	
	//In example, we get a string assignment, we need to read it left to right, once we encounter a higher order of operation we bracket the variables aroud it
	//Once completed, method will return the updated string to PKB for storage

	temp = assignment;

	if (temp.size >= 3) {
		return temp;
	}

	for (char& c : temp) {
		if (c == '*') {

		}
		else if (c == '+') {

		}
	}

	return temp;
}