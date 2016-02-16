#pragma once
#include <string>
#include <map>
#include "PKB.h";

using namespace std;

class Parent
{
public:
	Parent();
	~Parent();
	void setParent(string stmtLine, int stmtNo, int nestLevel, bool loopFlag, int endLopp);
	std::vector<int> getAns(int stmtNo);

	static std::map<int, int> AnsMap;

	// print out the call answer table
	void PrintProcTable();
};

