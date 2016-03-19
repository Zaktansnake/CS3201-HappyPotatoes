#include <string>
#include <tuple>
#include <unordered_set>

#include "./Header/Calls.h"
#include "./Header/PKB.h"

using namespace std;

template <> struct hash<std::pair<string, string>> {
	inline size_t operator()(const std::pair<string, string> &v) const {
		std::hash<string> string_hasher;
		return string_hasher(v.first) ^ string_hasher(v.second);
	}
};

std::vector<std::tuple<string, string, int>> CallsTable;
std::unordered_set< std::pair<string, string>> CallsSet;

void Calls::setCallProcedure(string mainProcedure, string procedure, int stmtLine) {
	if (CallsTable.size() > 0) {
		// check whether there is a recrusive call
		for (int i = 0; i < CallsTable.size(); i++) {
			string procA = get<0>(CallsTable[i]);
			string procB = get<1>(CallsTable[i]);
			
			if (procA.compare(procedure) == 0 && procB.compare(mainProcedure) == 0) {
				PKB::abort();
			}
		}
		CallsTable.push_back(make_tuple(mainProcedure, procedure,stmtLine));
		CallsSet.insert(make_pair(mainProcedure, procedure));
	}
	else {
		CallsTable.push_back(make_tuple(mainProcedure, procedure, stmtLine));
		CallsSet.insert(make_pair(mainProcedure, procedure));
	}

}

std::vector<std::tuple<string, string, int>> Calls::getCallsTable() {
	return CallsTable;
}

std::unordered_set< std::pair<string, string>> Calls::getCallsSet() {
	return CallsSet;
}

bool Calls::isCalls(string proc1, string proc2) {
    return true;
}


void Calls::printCallsTable() {
	/*for (int i = 0; i < CallsTable.size(); i++) {
		cout << "procA :: " << get<0>(CallsTable[i]) << "  procB :: " << get<1>(CallsTable[i]) << "  stmtLine :: " << get<2>(CallsTable[i]) << endl;
	}

	for (auto itr = CallsSet.begin(); itr != CallsSet.end(); ++itr) {
		pair<string, string> tempVector = *itr;
		cout << tempVector.first << "  , " << tempVector.second << endl;
	}*/

}