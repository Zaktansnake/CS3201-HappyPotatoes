#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Follows
{
public:
	// constructors
	Follows();
	~Follows();
	
	void setFollow(string stmtLine, int stmtNo, int nestLvl, bool loopFlag, int endLoopNo, int condition);
	std::vector<int> Follows::getFollow(int stmtNo);
	std::vector<int> Follows::getFollowFan(int stmtNo);
	std::vector<int> Follows::getFollowStar(int stmtNo);
	std::vector<int> Follows::getFollowFanStar(int stmtNo);
	bool isFollows(int s1, int s2);


	std::vector<int> Follows::getFollowForWhile(int stmtNo);
	std::vector<int> Follows::getFollowFanForWhile(int stmtNo);
	std::vector<int> Follows::getFollowForAssign(int stmtNo);
	std::vector<int> Follows::getFollowFanForAssign(int stmtNo);
	std::vector<int> Follows::getFollowForIf(int stmtNo);
	std::vector<int> Follows::getFollowFanForIf(int stmtNo);

	std::vector<int> Follows::getFollowStarForWhile(int stmtNo);
	std::vector<int> Follows::getFollowFanStarForWhile(int stmtNo);
	std::vector<int> Follows::getFollowStarForAssign(int stmtNo);
	std::vector<int> Follows::getFollowFanStarForAssign(int stmtNo);
	std::vector<int> Follows::getFollowStarForIf(int stmtNo);
	std::vector<int> Follows::getFollowFanStarForIf(int stmtNo);

	void Follows::PrintProcTable();
};