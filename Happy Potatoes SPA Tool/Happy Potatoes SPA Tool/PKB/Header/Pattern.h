#pragma once

#include <stdio.h>
#include <string>

using namespace std;

class Pattern
{
public:
	Pattern();
	~Pattern();

	string patternAssignment(string assignment);

private:
	bool multiplicationDetermine(string statement, int marker);
	bool plusDetermine(string statement, int marker);
	bool minusDetermine(string statement, int marker);
};