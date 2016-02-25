#pragma once
#include <string>

using namespace std;
typedef string ClauseType;
typedef string Parameter1;
typedef string Parameter2;

class Clause {
public:
	// getters
	ClauseType getClauseOperation();
	Parameter1 getFirstParameter(); 
	Parameter2 getSecondParameter();

	// constructors
	Clause();
	Clause(ClauseType,Parameter1,Parameter2);

private:
	ClauseType clauseType_;
	Parameter1 parameter1_;
	Parameter2 parameter2_;
};