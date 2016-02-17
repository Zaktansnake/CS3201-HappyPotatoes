#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <string>
#include <vector>

#include "./Header/Pattern.h"

using namespace std;

static string statement;

string patternAssignment(string assignment) {

	//In-order traversal is given by assignment statement
	//To understand the depth of each node, we can do a left to right reading and put a bracket around trees have a variable and or constant 
	
	//In example, we get a string assignment, we need to read it left to right, once we encounter a higher order of operation we bracket the variables aroud it
	//Once completed, method will return the updated string to PKB for storage

	statement = assignment;

	if (statement.size >= 3) {
		return statement;
	}

	for (int i = 0; i < statement.size; ++i) {
		cout << statement.size;

		char arr[statement.size];
		strcpy(arr, statement.c_str());

		char c = arr[i];

		if (c == '*') {
			if (multiplicationDetermine(statement, i)) {
				if (i == 1) {
					arr.insert(arr.begin(), '(');
					arr.insert(arr.begin() + (i + 2), ')');
				}
				else {
					arr.insert(arr.begin() + (i - 2), '(');
					arr.insert(arr.begin() + (i + 2), ')');
				}
			}
		}
		else if (c == '+') {
			if (plusDetermine(statement, i)) {
				if (i == 1) {
					arr.insert(arr.begin(), '(');
					arr.insert(arr.begin() + (i + 2), ')');
				}
				else {
					arr.insert(arr.begin() + (i - 2), '(');
					arr.insert(arr.begin() + (i + 2), ')');
				}
			}
		}

		string temp(arr);
		statement = temp;
	}

	return statement;
}

bool multiplicationDetermine(string statement, int marker) {
	
	char c1;
	char arr[statement.size];
	strcpy(arr, statement.c_str());

	if (marker == 1) {
		return true;
	}
	else {
		c1 = arr[marker - 2];
	}

	if (c1 == '+') {
		return true;
	}
	else {
		return false;
	}
}

bool plusDetermine(string statement, int marker) {

	char c1, c2;
	char arr[statement.size];
	strcpy(arr, statement.c_str());

	if (marker == 1) {
		c1 = arr[marker - 1];
	}
	else {
		c1 = arr[marker - 2];
	}

	if (marker == arr.size() - 1) {
		c2 = arr[marker + 1];
	}
	else {
		c2 = arr[marker + 2];
	}

	if (c2 == '+') {
		if (c1 == ')') {
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