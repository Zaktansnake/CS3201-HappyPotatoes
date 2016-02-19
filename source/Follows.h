#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Follows
{
public:
	Follows();
	~Follows();
	
	void setFollow(string stmtLine, int stmtNo, int nestLvl, bool loopFlag, int endLoopNo);
	std::vector<int> Follows::getFollow(int stmtNo);
	std::vector<int> Follows::getFollowFan(int stmtNo);
	bool isFollows(int s1, int s2);
};

