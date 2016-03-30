
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

bool assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector,
	PatternSet PS, vector<With> WithClauses) {
	
	//---- do the with clauses first-------
	string CheckBool = SelectParameterVector.at(0);
	if (CheckBool == "Boolean") {
		SelectBool = true;
	}

	for (int i = 0; i < WithClauses.size(); i++) {
		
		With w = WithClauses.at(i);
		Clause clause = w.getNormalClause();
		string LeftSide = w.getLeftOfEqualSign();
		string RightSide = w.getRightOfEqualSign();
		string clauseOperation = clause.getClauseOperation();
		int clausesSize = clauseOperation.size();
		char firstParameterType = clauseOperation.at(clausesSize - 2);
		char secondParameterType = clauseOperation.at(clausesSize - 1);
		std::string firstSecondParameterType = "";
		firstSecondParameterType = firstSecondParameterType + firstParameterType + secondParameterType;
		Parameter1 firstParameter = clause.getFirstParameter();
		Parameter2 secondParameter = clause.getSecondParameter();
		char firstLetter = clauseOperation.at(0);
		std::size_t found = clauseOperation.find("*");


		if (found != std::string::npos) {
			if (firstLetter == 'P') {

			}
			if (firstLetter == 'F') {

			}
		}
		else {
			if (firstLetter == 'M') {

			}
			else if (firstLetter == 'U') {

			}
			else if (firstLetter == 'P') {

			}
			else if (firstLetter == 'F') {

			}
			else {

			}
		}
	}
	
	
	
	
	
	//----------- then do normal clauses-----------
	for (int i = 0; i < ClausesVector.size(); i++) {

		Clause clauses = ClausesVector.at(i);
		std::string clausesOperation = clauses.getClauseOperation();
		int clausesSize = clausesOperation.size();
		char firstParameterType = clausesOperation.at(clausesSize - 2);
		char secondParameterType = clausesOperation.at(clausesSize - 1);
		std::string firstSecondParameterType = "";
		firstSecondParameterType = firstSecondParameterType + firstParameterType + secondParameterType;
		Parameter1 firstParameter = clauses.getFirstParameter();
		Parameter2 secondParameter = clauses.getSecondParameter();
		char firstLetter = clausesOperation.at(0);
		std::size_t found = clausesOperation.find("*");


		if (found != std::string::npos) {
			if (firstLetter == 'P') {

			}
			if (firstLetter == 'F') {

			}
		}
		else {
			if (firstLetter == 'M') {

			}
			else if (firstLetter == 'U') {

			}
			else if (firstLetter == 'P') {

			}
			else if (firstLetter == 'F') {
							
			}
			else {

			}
		}
	}
}
bool assessParseResult(ParseResult pr) {

	std::vector<std::string> SelectParameterVector = pr.getSelectParameter();
	std::vector<Clause> ClausesVector = pr.getClauses();
	PatternSet PatternQueryVector = pr.getPatterns();
	std::vector<With> WithClauses = pr.getWithClauses();
	return assessClauses(ClausesVector, SelectParameterVector,PatternQueryVector,WithClauses);
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

bool QueryEvaluator::Follows(string P1, string P2, string P1Type, string P2Type, 
	bool IsWith, string Left, string Right)
{
	vector<string> temp;
	//if is case like Follows(1,1)
	if (IsNumber(P1) && IsNumber(P2)) {
		return stmtTable::isFollow(ChangeStringToInt(P1),ChangeStringToInt(P2));
	}
	//if is case like Follows(1,s)
	else if ((IsNumber(P1))&&(!IsNumber(P2))) {
		//if P2 has been stored in the Results table before
		if (QAS.HasKey(P2)) {
			vector<string> Col = QAS.GetColFromResultsTable(P2);
			for (int i = 0; i < Col.size(); i++) {
				//check if the stored results follows P1 or not
				if (stmtTable::isFollow(ChangeStringToInt(P1), ChangeStringToInt(Col.at(i)))) {
					temp.push_back(Col.at(i));
				}
			}
		}
		else {
			vector<int> Results = stmtTable::getFollow(ChangeStringToInt(P1));
			for (int i = 0; i < Results.size(); i++) {
				temp.push_back(ChangeIntToString(Results.at(i)));
			}
		}
		//check if there is actually an results. If no results return false, if there is return true
		if (temp.size() == 0) {
			return false;
		}
		else {
			QAS.update(P2,temp);
		}
	}
	// if is case like Follows(s,1)
	else if ((IsNumber(P2))&&(!IsNumber(P1))) {
		if (QAS.HasKey(P1)) {
			vector<string> Col = QAS.GetColFromResultsTable(P1);
			for (int i = 0; i < Col.size(); i++) {
				//check if the all the p1 stored follows p2
				if (stmtTable::isFollow(ChangeStringToInt(Col.at(i)), ChangeStringToInt(P2))) {
					temp.push_back(Col.at(i));
				}
			}
		}
		else {
			vector<int> Results = stmtTable::getFollowFan(ChangeStringToInt(P2));
			for (int i = 0; i < Results.size(); i++) {
				temp.push_back(ChangeIntToString(Results.at(i)));
			}
		}
		//check if there is actually an results. If no results return false, if there is return true
		if (temp.size() == 0) {
			return false;
		}
		else {
			QAS.update(P2, temp);
		}
	}
	//if is case like follows(s,s1)
	else {
		// if both P1 and P2 is stored before
		if (QAS.HasKey(P1) && QAS.HasKey(P2)) {
			vector<string> Col1 = QAS.GetColFromResultsTable(P1);
			vector<string> Col2 = QAS.GetColFromResultsTable(P2);
		}
		// if only P1 is stored before
		else if ((QAS.HasKey(P1)) && (!QAS.HasKey(P2))) {
			vector<string> Col1 = QAS.GetColFromResultsTable(P1);
			for (int i = 0; i < Col1.size(); i++) {
				vector<int> Results = stmtTable::getFollow(ChangeStringToInt(Col1.at(i)));
				for (int j = 0; j < Results.size(); j++) {
					temp.push_back(ChangeIntToString(Results.at(j)));
				}
			}
			QAS.update(P2,temp);
		}
		//if only P2 is stored before
		else if (!(QAS.HasKey(P1)) && (QAS.HasKey(P2))) {
			vector<string> Col2 = QAS.GetColFromResultsTable(P2);
			for (int i = 0; i < Col2.size(); i++) {
				vector<int> Results = stmtTable::getFollowFan(ChangeStringToInt(Col2.at(i)));
				for (int j = 0; j < Results.size(); j++) {
					temp.push_back(ChangeIntToString(Results.at(j)));
				}
			}
			QAS.update(P1, temp);
		}
		//if both is not stored before
		else {
			vector<int> allStmt = VarTable::getAllStmt();
			for (int i = 0; allStmt.size(); i++) {
				temp.push_back(ChangeIntToString(allStmt.at(i)));
			}
			QAS.update(P1, temp);
			temp.clear();
			for (int i = 0; i < allStmt.size(); i++) {
				vector<int> Results = stmtTable::getFollow(ChangeStringToInt(Col1.at(i)));
				for (int j = 0; j < Results.size(); j++) {
					temp.push_back(ChangeIntToString(Results.at(j)));
				}
			}
			QAS.update(P2, temp);
		}
		if (temp.size() == 0) {
			return false;
		}
	}
	return true;
}

bool QueryEvaluator::Modifies(string P1, string P2, string P1Type, string P2Type,
	bool IsWith, string Left, string Right)
{
	return true;
}

bool QueryEvaluator::FollowsStar(string P1, string P2, string P1Type, string P2Type,
	bool IsWith, string Left, string Right)
{
	return true;
}

bool QueryEvaluator::Next(string P1, string P2, string P1Type, string P2Type,
	bool IsWith, string Left, string Right)
{
	return true;
}

bool QueryEvaluator::NextStar(string P1, string P2, string P1Type, string P2Type,
	bool IsWith, string Left, string Right)
{
	return true;
}

bool QueryEvaluator::Parents(string P1, string P2, string P1Type, string P2Type,
	bool IsWith, string Left, string Right)
{
	return true;
}

bool QueryEvaluator::ParentsStar(string P1, string P2, string P1Type, string P2Type,
	bool IsWith, string Left, string Right)
{
	return true;
}

bool QueryEvaluator::Uses(string P1, string P2, string P1Type, string P2Type,
	bool IsWith, string Left, string Right)
{
	return true;
}

int QueryEvaluator::ChangeStringToInt(string s)
{
	int value = atoi(s.c_str());
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





