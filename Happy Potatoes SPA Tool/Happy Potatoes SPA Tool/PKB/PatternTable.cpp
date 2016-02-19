#pragma once
#include<string>
#include<vector>
#include <algorithm>
#include <string>
#include <vector>
#include "Header\PatternTable.h"
#include "Header\VarTable.h"


using namespace std;
std::vector<int>lineThatModifiedV;
string stmtLine;

// -----------------isPattern--------------------------
std::vector<int> getVariable(string variable) {
    return VarTable::getModifiesTable(variable);
}
string getStatementLine(int stmtNo) {
}
bool PatternTable::isPattern(string variable, string key) {
    lineThatModifiedV = getVariable(variable);
	for (int i = 0; i < lineThatModifiedV.size(); i++) {
	     stmtLine = getStatementLine(lineThatModifiedV.at(i));

	}

}
