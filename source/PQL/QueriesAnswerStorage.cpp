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
vector<vector<string>> QueriesAnswerStorage::ResultsTable;
vector<pair<std::string,std::string>> QueriesAnswerStorage::SelectParameter;




void QueriesAnswerStorage::SetSelect(vector<string> sv)
{
	for (int index = 0; index < sv.size(); index++) {
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

string QueriesAnswerStorage::GetWithTableElement(string s)
{
	if (WithTable.find(s) == WithTable.end()) {
		return "none";
	}
	return WithTable[s];
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

//to store a results for 2 synonym and both are not stored before
void QueriesAnswerStorage::UpdatePairBothNotStore(vector<pair<string, string>> V, string P1, string P2)
{
	vector<vector<string>> NewResultsTable;
	int pos1 = ClausesParameterPositionInTable[P1];
	int pos2 = ClausesParameterPositionInTable[P2];
	for (int i = 0; i < ResultsTable.size(); i++) {
		vector<string> rol = ResultsTable.at(i);
		string e1 = rol.at(pos1);
		string e2 = rol.at(pos2);
		if (CheckPairMatch(e1, e2, V)) {
			rol.push_back(e1);
			rol.push_back(e2);
			NewResultsTable.push_back(rol);
		}
	}
	SetTable(P1);
	SetTable(P2);
	ResultsTable = NewResultsTable;
}

void QueriesAnswerStorage::UpdatePairOneStore(vector<string> s,
	unordered_map<string, vector<string>> m, string known, string notknown)
{
	vector<vector<string>> NewResultTable;
	int pos = ClausesParameterPositionInTable[known];
	for (int i = 0; i < ResultsTable.size; i++) {
		vector<string> row = ResultsTable.at(i);
		string ColElement = row.at(pos);
		if (std::find(s.begin(), s.end(), ColElement)
			== s.end()) {
			vector<string> v = m[ColElement];
			for (int j = 0; j < v.size; j++) {
				vector<string> copy = row;
				copy.push_back(v.at(j));
				NewResultTable.push_back(copy);
			}
		}
	}
	SetTable(notknown);
	ResultsTable = NewResultTable;
}

//update case such as modifies(s1,s2) where by both is stored before
void QueriesAnswerStorage::UpdatePair(vector<pair<string, string>> v, string P1, string P2)
{
	vector<vector<string>> NewResultsTable;
	int pos1 = ClausesParameterPositionInTable[P1];
	int pos2 = ClausesParameterPositionInTable[P2];
	for (int i = 0; i < ResultsTable.size(); i++) {
		vector<string> rol = ResultsTable.at(i);
		string e1 = rol.at(pos1);
		string e2 = rol.at(pos2);
		if (CheckPairMatch(e1, e2, v)) {
			NewResultsTable.push_back(rol);
		}
	}
	ResultsTable = NewResultsTable;
}

bool CheckPairMatch(string e1,string e2,vector<pair<string,string>> v) {
	for (int j = 0; j < v.size(); j++) {
		pair<string, string> p = v.at(j);
		string p1 = p.first;
		string p2 = p.second;
		if ((e1 == p1) && (e2 == p2)) {
			return true;
		}
	}
	return false;
}
bool QueriesAnswerStorage::HasKeyInWithMap(string s) {
	if (WithMap.find(s) == WithMap.end()) {
		return false;
	}
	else {
		true;
	}
}
//update the result table for clauses such as modifies(s1,"x")
void QueriesAnswerStorage::update(string s, vector<string> v)
{
	bool exist = false;
	vector<int> MightHaveToDelete;
	//find the synonym that remove 
	if (HasKeyInWithMap(s)) {
		vector<string> AllLeftSide = WithMap[s];
		for (int i = 0; i < AllLeftSide.size(); i++) {
			MightHaveToDelete.push_back
				(ClausesParameterPositionInTable[AllLeftSide.at(i)]);
		}
	}
	MightHaveToDelete.push_back(ClausesParameterPositionInTable[s]);
	int size = ResultsTable.size();
	bool hasKey = HasKey(s);
	vector<vector<string >> NewResultTable;
	if (!hasKey) {
		for (int i = 0; i != size; i++) {
			vector<string> temp = ResultsTable.at(i);
			for (int j = 0; j != v.size(); j++) {
				vector<string> copy = temp;
				copy.push_back(v.at(j));
				NewResultTable.push_back(copy);
			}
		}
		ResultsTable = NewResultTable;
		SetTable(s);
	}
	else {
		bool exist = true;
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> row = ResultsTable.at(i);
			for (int j = 0; j < MightHaveToDelete.size(); j++) {
				int pos = MightHaveToDelete.at(j);
				string ColElement = row.at(pos);
				if (std::find(v.begin(), v.end(),ColElement ) == v.end()) {
					exist = false;
					break;
				}
			}
			if (exist = true) {
				NewResultTable.push_back(row);
			}
			else {
				exist = true;
			}
		}
		ResultsTable = NewResultTable;
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

//remove a key in WithTable
void QueriesAnswerStorage::RemoveWithTable (string s) {
	WithTable.erase(s);
}

//set up with map. with map is use to store the right side of with clause is used by 
//how many left. e.g v.var = c.constant, s.stmt = c.constant store c is map with v and s
void QueriesAnswerStorage::SetWithMap(string right,string left) {
	
	//if we right side of with clause is not set as key yet
	if (WithMap.find(right) == WithMap.end()) {
		vector<string> v = WithMap[right];
		v.push_back(left);
		WithMap[right] = v;
	}
	else {
		vector<string> v;
		v.push_back(left);
		WithMap[right] = v;
	}
}
//get all the col of result table. each col is the answer of a synonym
vector<string> QueriesAnswerStorage::GetColFromResultsTable(string s)
{
	int ColIndex = ClausesParameterPositionInTable[s];
	vector<string> temp;
	for (int index = 0; index < ResultsTable.size(); index++) {
		vector<string> Row = ResultsTable.at(index);
		string ColElement = Row.at(ColIndex);
		temp.push_back(ColElement);
	}
	return temp;
}

//set all the with clause e.g with v.var = c.constant , store v.var as key and c.constant as element
void QueriesAnswerStorage::SetWithTable(vector<With> WV)
{
	for (int i = 0; i < WV.size(); i++) {
		WithTable[WV.at(i).getLeftOfEqualSign()] = WV.at(i).getRightOfEqualSign();
	}

}

void QueriesAnswerStorage::SetResultTable(vector<vector<string>> v)
{
	ResultsTable = v;
}

int QueriesAnswerStorage::GetResultTablePos(string s)
{
	return ClausesParameterPositionInTable[s];
}

vector<vector<string>> QueriesAnswerStorage::GetResultsTable() {
	return ResultsTable;
}

QueriesAnswerStorage::QueriesAnswerStorage()
{


}

QueriesAnswerStorage::~QueriesAnswerStorage()
{

}