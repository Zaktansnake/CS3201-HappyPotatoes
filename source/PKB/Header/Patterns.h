#ifndef PATTERNS_H
#define PATTERNS_H

#pragma once

#include <stdio.h>
#include <string>

using namespace std;

class Patterns
{
public:
	// constructors
	Patterns();
	~Patterns();

	static bool compareAssignments(string assignment1, string assignment2, int stmtNum);

private:

	static vector<string> getRidOfWhiteSpaces(string line);

};

#endif