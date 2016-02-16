#include "./Header/Call.h"
#include "Header\PKB.h"
#include <string>

using namespace std;

std::vector<std::vector<string> > arrAnsForCall;

bool isContains(string procName, int index);

Call::Call()
{
}


Call::~Call()
{
}
std::vector<string> Call::getCall(int index) {
	if (index > arrAnsForCall.size()) {
		throw exception ();
	}
	return arrAnsForCall.at(index);
}

void setCall(string procName, int index) {

     // check the size of vector and compare with index
	 // if index > size, create a new vector otherwise, add the procName at the back of the ans
	 // check whter the proc name already in the vector of call ans
	 // if yes, do nothing
	 // if no, push_back
	if (arrAnsForCall.size() < index) {
		if (!isContains(procName, index)) {
		   arrAnsForCall.at(index).push_back(procName);
		}
	}
	else {
	std::vector<string> temp;
	temp.push_back(procName);
	arrAnsForCall.push_back(temp);
	   
	}
}

bool isContains(string procName, int index) {
	std::vector<string>temp = arrAnsForCall.at(index);
	if (std::find(temp.begin(), temp.end(), procName) != temp.end()) {
		return false;
	}
	else {
		return true;
	}
}

// print out the proceTable
void PrintProcTable() {
	for (int i = 0; i < arrAnsForCall.size(); i++) {
		for (int j = 0; j < arrAnsForCall[i].size(); j++) {
			std::cout << arrAnsForCall[i].at(j) << " ";
		}
		cout << endl;
	}
}

