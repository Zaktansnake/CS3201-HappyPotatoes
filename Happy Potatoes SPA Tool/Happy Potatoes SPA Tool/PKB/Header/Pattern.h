#ifndef PATTERN_H
#define PATTERN_H

#pragma once

#include <stdio.h>
#include <string>

using namespace std;

class Pattern
{
public:
	Pattern();
	~Pattern();

	static string patternAssignment(string assignment);

private:
	static bool multiplicationDetermine(string statement, int marker);
	static bool plusDetermine(string statement, int marker);
	static bool minusDetermine(string statement, int marker);
};

#endif