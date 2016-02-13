#pragma once
#include <string>
#include "PKB.h";

using namespace std;
class Call
{
public:
	Call();
	~Call();

	std::vector<string> getCall(string procname);
};

