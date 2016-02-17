#ifndef PATTERN_H
#define PATTERN_H

#pragma once

#include <stdio.h>
#include <string>

using namespace std;

class Pattern
{
	struct node
	{
		string key_value;
		int stmtNo;
		node *left;
		node *right;
	};

public:
	Pattern();
	~Pattern();

	void insert (string node, int stmtNo);
	int  search (string key);
	void destroy_tree();

private:
    void insert (string key, node *leaf);
	node *search (string key, node *leaf);


	node *root;

};

#endif

