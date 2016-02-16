#pragma once
#include <string>

using namespace std;
typedef string PatternType;
typedef string Parameter1;
typedef string Parameter2;
typedef string Parameter3;

class PatternNode;

class PatternNode;

class Pattern {
public:
	// getters
	PatternType getPatternOperation();
	Parameter1 getFirstParameter();
	Parameter2 getSecondParameter();
	Parameter3 getThirdParameter();

	// constructors
	Pattern();
	Pattern(PatternType, Parameter1, Parameter2, Parameter3);
private:
	PatternType patternType_;
	Parameter1 parameter1_;
	Parameter2 parameter2_;
	Parameter3 parameter3_;
};
