
#include "./Header/Pattern.h"
#include "./Header/QueryEvaluator.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Header\Clause.h"
#include "Header\QueriesAnswerStorage.h"
#include <iostream>
#include "../PKB/Header/VarTable.h"
#include "../PKB/Header/StmtTable.h"
using namespace std;

QueriesAnswerStorage QAS;

bool SelectBool = false;

vector<string> QueryEvaluator::startEvaluator(ParseResult mustPr)
{

	bool HasResults = assessParseResult(mustPr);
	if (SelectBool == true) {
		vector<string> BooleanResults;
		if (HasResults == true) {
			BooleanResults.push_back("True");
		}
		else {
			BooleanResults.push_back("False");
		}
	}
	else {
		if (HasResults == true) {
			return QAS.MergeResults();
		}
		else {
			return NoResults;
		}
	}
}

bool QueryEvaluator::assessParseResult(ParseResult pr) {

	std::vector<std::string> SelectParameterVector = pr.getSelectParameter();
	std::vector<Clause> ClausesVector = pr.getClauses();
	PatternSet PatternQueryVector = pr.getPatterns();
	std::vector<With> WithClauses = pr.getWithClauses();
	return assessClauses(ClausesVector, SelectParameterVector, PatternQueryVector, WithClauses);
}

bool QueryEvaluator::assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector,
	PatternSet PS, vector<With> WithClauses) {


	string CheckBool = SelectParameterVector.at(0);
	if (CheckBool == "Boolean") {
		SelectBool = true;
	}

	for (int i = 0; i < ClausesVector.size(); i++) {

		bool ResultsExist;
		Clause clauses = ClausesVector.at(i);
		std::string clausesOperation = clauses.getClauseOperation();
		int clausesSize = clausesOperation.size();
		char firstParameterType = clausesOperation.at(clausesSize - 2);
		char secondParameterType = clausesOperation.at(clausesSize - 1);
		string clauseType = clausesOperation.substr(0,clausesSize-2);
		std::string firstSecondParameterType = "";
		firstSecondParameterType = firstSecondParameterType + firstParameterType + secondParameterType;
		Parameter1 firstParameter = clauses.getFirstParameter();
		Parameter2 secondParameter = clauses.getSecondParameter();
		char firstLetter = clausesOperation.at(0);
		ResultsExist = CheckSynonym(firstParameter,secondParameter,firstParameterType,
			secondParameterType,clauseType);
		if (ResultsExist = true) {
			
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool QueryEvaluator::CheckSynonym(string firstParameter,string secondParameter,
	char firstParameterType,char secondParameterType,string clauseType) {
	if ((IsSynonym(firstParameter[0])) && (IsSynonym(secondParameter[0]))) {
		GetResultsForBothSynonym(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
	else if (IsSynonym(firstParameter[0])) {
		GetResultsForFirstSynonym(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
	else if (IsSynonym(secondParameter[0])) {
		GetResultsForSecondSynonym(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
	else {
		CheckTrueOrFalse(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
}

bool QueryEvaluator::GetResultsForBothSynonym(string P1, string P2, char P1Type
	, char P2Type, string ClauseType)
{
	vector<string> Results;
	vector<string> temp;
	if (QAS.HasKey(P1) && QAS.HasKey(P2)) {
		vector<string> Col1 = QAS.GetColFromResultsTable(P1);
		vector<string> Col2 = QAS.GetColFromResultsTable(P2);
	}
	// if only P1 is stored before
	else if ((QAS.HasKey(P1)) && (!QAS.HasKey(P2))) {
		vector<string> Col1 = QAS.GetColFromResultsTable(P1);
		for (int i = 0; i < Col1.size(); i++) {
			
		}
		QAS.update(P2, Results);
	}
	//if only P2 is stored before
	else if (!(QAS.HasKey(P1)) && (QAS.HasKey(P2))) {
		vector<string> Col2 = QAS.GetColFromResultsTable(P2);
		for (int i = 0; i < Col2.size(); i++) {
		
		}
		QAS.update(P1, Results);
	}
	//if both is not stored before
	else {
		vector<string> AllVector = GetAll(P1Type);
		for (int i = 0; AllVector.size(); i++) {
			Results.push_back(AllVector.at(i));
		}
		QAS.update(P1, Results);
		Results.clear();
		for (int i = 0; i < AllVector.size(); i++) {
			temp = GetAllSecondSynonymFromPKB(AllVector.at(i), P2, P1Type, P2Type, ClauseType);
			for (int j = 0; j < temp.size(); j++) {
				Results.push_back(temp.at(j));
			}
		}
		QAS.update(P2, Results);
	}
	return CheckTempResultSize(Results);
}

bool QueryEvaluator::GetResultsForFirstSynonym(string P1, string P2, char P1Type
	, char P2Type, string ClauseType)
{
	vector<string> Results;	
	if (QAS.HasKey(P1)) {
		vector<string> Col = QAS.GetColFromResultsTable(P1);
		for (int i = 0; i < Col.size(); i++) {
			if (CheckIsResultsFromPkb(Col.at(i), P2, P1Type, P2Type, ClauseType)) {
				Results.push_back(Col.at(i));
			}
		}
	}
	else {
		Results = GetAllFirstSynonymFromPKB(P1,P2,P1Type,P2Type,ClauseType);
	}
	//check if there is actually an results. If no results return false, if there is return true
	return CheckTempResultSize(Results);
}

bool QueryEvaluator::GetResultsForSecondSynonym(string P1, string P2, char P1Type
	, char P2Type, string ClauseType)
{
	vector<string> Results;
	if (QAS.HasKey(P2)) {
		vector<string> Col = QAS.GetColFromResultsTable(P1);
		for (int i = 0; i < Col.size(); i++) {
			if (CheckIsResultsFromPkb(P1, Col.at(i), P1Type, P2Type, ClauseType)) {
				Results.push_back(Col.at(i));
			}
		}
	}
	else {
		Results = GetAllSecondSynonymFromPKB(P1, P2, P1Type, P2Type, ClauseType);
	}
	//check if there is actually an results. If no results return false, if there is return true
	return CheckTempResultSize(Results);
}

bool QueryEvaluator::CheckTrueOrFalse(string P1, string P2, char P1Type
	, char P2Type, string ClauseType) {
	return CheckIsResultsFromPkb(P1,P2,P1Type,P2Type,ClauseType);
}

vector<string> QueryEvaluator::GetAll(char Type) {
	if (Type == 'P') {
		//getallprocedure
	}
	else if (Type == 'V') {
		//getallvariable
	}
	else if (Type == 'S') {
		//getallstmt
	}
	else if (Type == 'I') {
		//getallif
	}
	else if (Type == 'W') {
		//getallwhile
	}
	else if (Type == 'A') {
		//getallassign
	}
	else if (Type == 'C') {
		//getallconstant
	}
	else {
		
	}
}

vector<string> QueryEvaluator::GetAllSecondSynonymFromPKB(string P1, string P2, char P1Type,
	char P2Type, string clausesType) {

	if (clausesType == "Follows") {

	}
	else if (clausesType == "Follows*") {

	}
	else if (clausesType == "Uses") {

	}
	else if (clausesType == "Calls") {

	}
	else if (clausesType == "Modifies") {

	}
	else if (clausesType == "Parent") {

	}
	else if (clausesType == "Parent*") {

	}
	else if (clausesType == "Next") {

	}
	else if (clausesType == "Next*") {

	}
	else if (clausesType == "Affects") {

	}
	else if (clausesType == "Affects*") {

	}
}

vector<string> QueryEvaluator::GetAllFirstSynonymFromPKB(string P1, string P2, char P1Type,
	char P2Type, string clausesType) {

	if (clausesType == "Follows") {

	}
	else if (clausesType == "Follows*") {

	}
	else if (clausesType == "Uses") {

	}
	else if (clausesType == "Calls") {

	}
	else if (clausesType == "Modifies") {

	}
	else if (clausesType == "Parent") {

	}
	else if (clausesType == "Parent*") {

	}
	else if (clausesType == "Next") {

	}
	else if (clausesType == "Next*") {

	}
	else if (clausesType == "Affects") {

	}
	else if (clausesType == "Affects*") {

	}
}

bool QueryEvaluator::CheckIsResultsFromPkb(string P1,string P2,char P1Type,
	char P2Type,string clausesType) {

	if (clausesType == "Follows") {

	}
	else if (clausesType == "Follows*") {

	}
	else if (clausesType == "Uses") {

	}
	else if (clausesType == "Calls") {

	}
	else if (clausesType == "Modifies") {

	}
	else if (clausesType == "Parent") {

	}
	else if (clausesType == "Parent*") {

	}
	else if (clausesType == "Next") {

	}
	else if (clausesType == "Next*") {

	}
	else if (clausesType == "Affects") {

	}
	else if (clausesType == "Affects*") {

	}
}

bool QueryEvaluator::CheckTempResultSize(vector<string> v) {
	if (v.size() == 0) {
		return false;
	}
	return true;
}

vector<string> splitComma(string line) {
	std::istringstream ss(line);
	std::string token;
	vector<string> result;

	while (std::getline(ss, token, ',')) {
		result.push_back(token);
	}
	return result;
}

bool QueryEvaluator::IsSynonym(char c) {
	if (isalpha(c)) {
		return true;
	}
	return false;
}

int QueryEvaluator::ChangeStringToInt(string s)
{
	int value = atoi(s.c_str());
	return value;
}

string QueryEvaluator::ChangeIntToString(int i)
{
	ostringstream temp;
	temp << i;
	return temp.str();
}

bool QueryEvaluator::HaveQuotation(string s)
{
	size_t found;
	found = s.find("\"");
	if (found == string::npos) {
		return false;
	}
	return true;
}

bool QueryEvaluator::IsNumber(string s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

QueryEvaluator::QueryEvaluator()
{


}

QueryEvaluator::~QueryEvaluator()
{
}





