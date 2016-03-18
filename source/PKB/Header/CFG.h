#pragma once
#include <string>
#include <vector>
#include <map>

class CFG
{
public:
	// constructors
	CFG();
	~CFG();

	static void addRoot (std::string root);
	static void addNextNode (int stmtNo, std::string stmt);

	static int getChildNode (int stmtNo);
	static int getParentNode (int stmtNo);
	static int getLeftNode (int stmtNo);
	static int getRightNode (int stmtNo);
};