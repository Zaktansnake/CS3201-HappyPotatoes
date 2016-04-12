#include <vector>
#include <string>
#include <unordered_map>
#include ".\Header\QueriesAnswerStorage.h"
#include "..\PKB\Header\ProcTable.h"
#include "..\PKB\Header\VarTable.h"
#include <iostream>
#include <sstream>
using namespace std;




std::unordered_map<std::string, int> QueriesAnswerStorage::ClausesParameterPositionInTable;
vector<vector<string > > QueriesAnswerStorage::ResultsTable;
vector<pair<std::string,std::string > > QueriesAnswerStorage::SelectParameter;
vector<string> QueriesAnswerStorage::NoClause;



void QueriesAnswerStorage::SetSelect(vector<string> sv)
{
	cout << "I am setting select" << endl;
	for (int index = 0; index < sv.size(); index++) {
		string s = sv.at(index);
		stringstream ss(s);
		vector<string> result;

		while (ss.good())
		{
			string substr;
			getline(ss, substr, ',');
			result.push_back(substr);
		} //the first is a name, second is a type
		pair<string, string> apair;
		apair.first = result.at(0);
		apair.second = result.at(1);
		SelectParameter.push_back(apair);
		cout << "i finish setting select" << endl;
	}
}

void QueriesAnswerStorage::clear() {
	ResultsTable.clear();
	ClausesParameterPositionInTable.clear();
	SelectParameter.clear();
}

void QueriesAnswerStorage::SetNoClause(vector<string> v)
{
	for (int i = 0; i < v.size(); i++) {
		string s = v.at(i);
		if (std::find(NoClause.begin(), NoClause.end(), s) == NoClause.end()) {
			return;
		}
		else
		{
			NoClause.push_back(s);
		}
	}
}

vector<string> QueriesAnswerStorage::GetNoClause()
{
	return NoClause;
}

vector<pair<std::string, std::string>> QueriesAnswerStorage::GetSelectParameter()
{
	return SelectParameter;
}


void QueriesAnswerStorage::SetTable(string s)
{
	if (HasKey(s) != true) {
		ClausesParameterPositionInTable[s] = ClausesParameterPositionInTable.size() - 1;
	}
	else {
		return;
	}
}

bool QueriesAnswerStorage::HasKey(string s)
{
	
	if (ClausesParameterPositionInTable.find(s)== ClausesParameterPositionInTable.end()) {
		return false;
	}
	else {
		true;
	}
}
//Merge The result table. Result, remove duplicate 
vector<string> QueriesAnswerStorage::MergeResults()
{
	vector<string> MergeResults;
	vector<int> Position;
	//find the col that has the answer for the select
	for (int index = 0; index < SelectParameter.size(); index++) {
		pair<string, string> pair = SelectParameter.at(index);
		std::unordered_map<std::string, int>::const_iterator got = ClausesParameterPositionInTable.find(pair.first);

		if (got == ClausesParameterPositionInTable.end()) {
			continue;
		}
		else 
		{
			Position.push_back(ClausesParameterPositionInTable[pair.first]);
		}

	}
	for (int index = 0; index < Position.size(); index++) {
		int Col = Position.at(index);
		for (int j = 0; j < ResultsTable.size(); j++) {
			vector<string> Row = ResultsTable.at(j);
			string Ans = Row.at(Col);
			if (std::find(MergeResults.begin(), MergeResults.end(), Ans) == MergeResults.end()) {
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

string QueriesAnswerStorage::GetSelectType(string s) {
	for (int i = 0; i < SelectParameter.size(); i++) {
		if (SelectParameter.at(i).second == s) {
			return SelectParameter.at(i).first;
		}
	}
}

void QueriesAnswerStorage::SetResultTable(vector<vector<string > > v)
{
	ResultsTable = v;
}

int QueriesAnswerStorage::GetResultTablePos(string s)
{
	return ClausesParameterPositionInTable[s];
}

vector<vector<string > > QueriesAnswerStorage::GetResultsTable() {
	return ResultsTable;
}

QueriesAnswerStorage::QueriesAnswerStorage()
{


}

QueriesAnswerStorage::~QueriesAnswerStorage()
{

}