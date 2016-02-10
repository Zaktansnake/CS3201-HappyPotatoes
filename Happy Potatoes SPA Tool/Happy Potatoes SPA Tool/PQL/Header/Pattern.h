#pragma once
#include <string>

using namespace std;

class Pattern {
public:
	PatternNode getRoot();

	// constructors
	Pattern();
	Pattern(string content);

private:
	PatternNode root_;
};