#include "./Header/ProcTable.h"
#include "./Header/Call.h"
#include "./Header/Calls.h"

using namespace std;
std::vector<std::vector<string>> arrAnsForCall;
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

void ProcTable::addTableData(string procName) {
   map<string,int>::iterator iter;
   int index;
   iter = ProcMap.find(procName);
   if (iter != ProcMap.end()) {
	   index = iter->second;
   }
   else {
       index = -1;
   }
   if (index = -1) {
	   index = ProcIndex.size();
	   std::vector<string> callAns;
	   ProcMap.insert(pair<string, int>(procName, index));
	   ProcIndex.push_back(procName);
	   arrAnsForCall[index] = call.getCall(procName);
   }
   else {

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

// return procedure index
int ProcTable::getProcIndex(string key) {
	map<string, int>::iterator iter;
	iter = ProcMap.find(key);
	return iter->second;
}

// get the procedure name by knowing the index
string getProcName(int index);

// get the procNode 
TNode* getProcNode(int index);

// print out the proceTable
void PrintProcTable() {
	for (int i = 0; i < arrAnsForCall.size(); i++) {
		for (int j = 0; j < arrAnsForCall[i].size(); j++) {
			std::cout << arrAnsForCall[i].at(j) <<" ";
		}
		cout <<endl;
	}
}


