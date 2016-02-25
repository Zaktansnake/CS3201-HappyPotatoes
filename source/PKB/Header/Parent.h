#pragma once

#include <string>
#include <map>
#include "PKB.h";

using namespace std;

class Parent
{
public:
	// constructors
	Parent();
	~Parent();

	void setParent(string stmtLine, int stmtNo, int nestLevel, bool loopFlag, int endLopp);
	std::vector<int> getParent(int stmtNo);
	std::vector<int> getChild(int stmtNo);

	bool isParent(int stmt1, int stmt2);

	static std::map<int, int> AnsMap;

	// print out the call answer table
	void PrintProcTable();
};