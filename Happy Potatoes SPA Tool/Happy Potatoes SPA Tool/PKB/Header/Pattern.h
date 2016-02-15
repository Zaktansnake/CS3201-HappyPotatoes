#pragma once

class Pattern
{
public:
	Pattern();
	~Pattern();

	struct node
	{
	   string key_value;
	   int stmtNo;
	   node *left;
	   node *right;
	};
	void insert (string node, int stmtNo);
	int  search (string key);
	void destroy_tree();

private:
    void insert (string key, node *leaf);
	node *search (string key, node *leaf);


	node *root;



};

