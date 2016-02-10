#pragma once
#include <string>
#include "Pattern.h"

using namespace std;
typedef string PatternType;
typedef string Parameter1;
typedef Pattern Parameter2;
typedef string Parameter3;

class PatternClause {
public:
	// getters
	PatternType getPatternOperation();
	Parameter1 getFirstParameter();
	Parameter2 getSecondParameter();
	Parameter3 getThirdParameter();

	// constructors
	PatternClause();
	PatternClause(Parameter1 p1, Parameter2 p2, Parameter3 p3);
private:
	PatternType patternType_;
	Parameter1 parameter1_;
	Parameter2 parameter2_;
	Parameter3 parameter3_;
};