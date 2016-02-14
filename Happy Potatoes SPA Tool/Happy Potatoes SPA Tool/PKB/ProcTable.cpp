#include "./Header/ProcTable.h"
#include "./Header/Call.h"
#include "./Header/Calls.h"

using namespace std;

map<string, int> ProcTable::ProcMap;
vector<string> ProcTable::ProcIndex;
std::vector<std::vector<string>> arrAnsForCall;
std::vector<int> stmtPosition;
Call call;

ProcTable::ProcTable()
{
  
}

ProcTable::~ProcTable()
{
/*	if (!ProcString.empty()) {
		for (map<string, int>::iterator iter = ProcString.begin(); iter != ProcString.end(); iter++) {
			ProcString.erase(iter);
		}
		ProcString.clear();
	}

	if (!M)
*/
}

void ProcTable::addTableData(string procName, int stmtLine) {
   ProcTable pt;
   int index = pt.findPosition(procName);
   if (index = -1) {
	   index = ProcIndex.size();
	   std::vector<string> callAns;
	   ProcMap.insert(pair<string, int>(procName, index));
	   ProcIndex.push_back(procName);
	   //stmtPosition[index] = stmtLine;
	   //arrAnsForCall[index] = call.getCall(procName);
   } else {

   }
}

// return the index of the procName in the map
int ProcTable::findPosition(string procName) {
	map<string, int>::iterator iter;
	iter = ProcMap.find(procName);
	if (iter != ProcMap.end()) {
		return  iter->second;
	}
	else {
	return -1;
	}
}

// retrun the size of proc table
int ProcTable::getSize(){ 
   return this->ProcIndex.size(); 
}

// return call answer
std::vector<string> ProcTable::getCallAns(int index) {
   return arrAnsForCall[index];
}

// return the program line for the procedure
int ProcTable::getProgLine(string procName) {
    int index = findPosition(procName);
	return stmtPosition[index];
}

// return procedure index
int ProcTable::getProcIndex(string key) {
	int index = findPosition(key);
	return index;
}

// get the procedure name by knowing the index
string getProcName(int index);

// get the procNode 
TNode* getProcNode(int index);

// return true if procName alr in the table otherwise, false
bool ProcTable::isContains(string name) {
	map<string, int>::iterator iter;
	int index;
	iter = ProcMap.find(name);
	if (ProcMap.size() > 0) {
		if (iter != ProcMap.end()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

// print out the proceTable
void PrintProcTable() {
	for (int i = 0; i < arrAnsForCall.size(); i++) {
		for (int j = 0; j < arrAnsForCall[i].size(); j++) {
			std::cout << arrAnsForCall[i].at(j) <<" ";
		}
		cout <<endl;
	}
}



