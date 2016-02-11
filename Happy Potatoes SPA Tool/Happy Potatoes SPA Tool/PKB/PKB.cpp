#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <fstream>
#include <sstream>

#include "./Header/PKB.h"
#include "./Header/TNode.h"

using namespace std;

static int setProcToAST(PROC p, TNode* r);
static TNode* getRootAST(PROC p);
static int setProcToCFG(PROC p, GNode* g);


std::vector<int> PKB::getModifies(VAR var)
{
	return std::vector<int>();
}

int PKB::setProcToAST(PROC p, TNode* r) {
	return NULL;
}

TNode* PKB::getRootAST (PROC p){
	return NULL;
}

int PKB::setProcToCFG(PROC p, GNode* r) {
	return NULL;
}
