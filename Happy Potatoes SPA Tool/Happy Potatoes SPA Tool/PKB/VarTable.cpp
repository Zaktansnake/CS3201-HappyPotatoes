#include "./Header/VarTable.h"
#include "./Header/Modifies.h"
#include "./Header/Uses.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

//vector<std::vector<string>> arrAnsForParents;

VarTable::VarTable(){
}

VarTable::~VarTable()
{
}

vector<int> VarTable::getModifiesTable(string varName) {
	return Modifies::getModifiesTable(varName);
}

void VarTable::addDataToModifies(string varName, int stmtLine) {
	Modifies::addModifiesTable(varName, stmtLine);
}

vector<int> getUsesTable(string varName) {
	return Uses::getUsesTable(varName);
}

void addDataToUses(string varName, int stmtLine) {
	Uses::addUsesTable(varName, stmtLine);
}

