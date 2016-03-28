#include <vector>
#include <string>
#include <unordered_map>
#include ".\Header\QueriesAnswerStorage.h"
#include "..\PKB\Header\ProcTable.h"
#include "..\PKB\Header\VarTable.h"
#include <iostream>
#include <sstream>
using namespace std;


VarTable vr;
ProcTable pr;

std::unordered_map<std::string, int> QueriesAnswerStorage::ClausesParameterPositionInTable;
vector<vector<string>> QueriesAnswerStorage::ResultsTable;
vector<pair<std::string,std::string>> QueriesAnswerStorage::SelectParameter;




void QueriesAnswerStorage::SetSelect(vector<string> sv)
{
	for (int index = 0; index < sv.size; index++) {
		string s = sv.at(index);
		stringstream ss(s);
		vector<string> result;

		while (ss.good())
		{
			string substr;
			getline(ss, substr, ',');
			result.push_back(substr);
		}
		pair<string, string> apair;
		apair.first = result.at(0);
		apair.second = result.at(1);
		SelectParameter.push_back(apair);
	}
}

void QueriesAnswerStorage::clear() {
	ResultsTable.clear();
	ClausesParameterPositionInTable.clear();
	SelectParameter.clear();
}

void QueriesAnswerStorage::SetTable(string s)
{
	if (!HasKey) {
		ClausesParameterPositionInTable[s] = ClausesParameterPositionInTable.size() - 1;
	}
	else {
		return;
	}
}

bool QueriesAnswerStorage::HasKey(string s)
{
	if (ClausesParameterPositionInTable[s] == 0) {
		return false;
	}
	else {
		true;
	}
}

void QueriesAnswerStorage::update(string s, vector<string> v, bool hasKey)
{
	bool exist = false;
	int index = ClausesParameterPositionInTable[s];
	int size = ResultsTable.size();
	if (!hasKey) {
		for (int i = 0; i != size; i++) {
			vector<string> temp = ResultsTable.at[i];
			for (int j = 0; j != v.size(); j++) {
				vector<string> copy = temp;
				copy.push_back(v.at(j));
				ResultsTable.at(i) = copy;
			}
		}
	}
	else {
		for (int i = 0; i != size; i++) {
			vector<string> temp = ResultsTable.at[i];
			string element = temp.at(index);
			for (int j = 0; j != v.size(); j++) {
				if (v.at(j) == element) {
					exist = true;
				}
			}
			if (exist == false) {
				ResultsTable.erase(ResultsTable.begin() + i);
				i = i - 1;
			}
		}
	}

}

vector<string> QueriesAnswerStorage::MergeResults()
{
	vector<string> MergeResults;
	vector<int> Position;
	for (int index = 0; index < SelectParameter.size(); index++) {
		pair<string, string> pair = SelectParameter.at(index);
		std::unordered_map<std::string, int>::const_iterator got = ClausesParameterPositionInTable.find(pair.second);

		if (got == ClausesParameterPositionInTable.end()) {
			continue;
		}
		else 
		{
			Position.push_back(ClausesParameterPositionInTable[pair.second]);
		}

	}
	for (int index = 0; index < Position.size(); index++) {
		int Col = Position.at(index);
		for (int j = 0; j < ResultsTable.size(); j++) {
			vector<string> Row = ResultsTable.at(j);
			string Ans = Row.at(Col);
			if (std::find(MergeResults.begin(), MergeResults.end(), Ans) != MergeResults.end()) {
				continue;
			}
			else
			{
				MergeResults.push_back(Ans);
			}
		}
	}
	return MergeResults;
}

QueriesAnswerStorage::QueriesAnswerStorage()
{


}

QueriesAnswerStorage::~QueriesAnswerStorage()
{

}