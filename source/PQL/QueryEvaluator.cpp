
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
			if (NoClause) {
				return QAS.GetNoClause();
			}
			else {
				return QAS.MergeResults();
			}
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
	QAS.SetSelect(SelectParameterVector);
	QAS.SetWithTable(WithClauses);
	//if there is no clause and no with clause at allw
	if (ClausesVector.size() == 0 && WithClauses.size() == 0) {
		NoClause = true;
		GetResultsForNoClause(QAS.GetSelectParameter());
	}
	else {
		DoWithClause(WithClauses);
		DoNormalClause(ClausesVector);
	}
	return true;
}

bool QueryEvaluator::DoWithClause(vector<With> W) {
	
	for (int i = 0; i < W.size(); i++) {
		if (CheckWith) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool QueryEvaluator::CheckWith(With with) {
	
	if (IsSynonym(with.getLeftOfEqualSign) && IsSynonym(with.getRightOfEqualSign)) {
		return GetAnswerForBothWith(with.getLeftOfEqualSign(), with.getRightOfEqualSign());
	}
	else if (IsSynonym(with.getRightOfEqualSign)) {
		return GetAnswerForRightWith(with.getLeftOfEqualSign(), with.getRightOfEqualSign());
	}
	else if (IsSynonym(with.getLeftOfEqualSign)) {
		return GetAnswerForLeftWith(with.getLeftOfEqualSign(), with.getRightOfEqualSign());
	}
	else {
		if (with.getLeftOfEqualSign() == with.getRightOfEqualSign()) {
			return true;
		}
		else {
			return false;
		}
	}
}
bool QueryEvaluator::GetAnswerForLeftWith(string left, string right) {
	vector<vector<string>> ResultsTable = QAS.GetResultsTable();
	vector<vector<string>> NewResultsTable;
	string LeftName;
	LeftName.push_back(left.at(0));
	string LeftType = left.substr(2);
	bool HasResults = false;
	if (QAS.HasKey(LeftName)) {
		int Pos = QAS.GetResultTablePos(LeftName);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			if (Row.at(Pos) == right) {
				NewResultsTable.push_back(Row);
				HasResults = true;
			}
		}
		QAS.SetResultTable(NewResultsTable);
	}
	else {
		vector<string> leftResults = GetAllRightSideOfWithClause(LeftType);
		if (ResultsTable.size == 0) {
			for (int i = 0; i < leftResults.size(); i++) {
				if (leftResults.at(i) == right) {
					vector<string> s;
					s.push_back(leftResults.at(i));
					NewResultsTable.push_back(s);
					HasResults = false;
				}
			}
		}
		else {
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				for (int j = 0; j < leftResults.size(); j++) {
					if (leftResults.at(j) == right) {
						vector<string> copy = Row;
						copy.push_back(leftResults.at(j));
						NewResultsTable.push_back(copy);
						HasResults = true;
					}
				}
			}
		}
		QAS.SetTable(LeftName);
		QAS.SetResultTable(NewResultsTable);
	}
	return HasResults;
}

bool QueryEvaluator::GetAnswerForRightWith(string left, string right) {
	vector<vector<string>> ResultsTable = QAS.GetResultsTable();
	vector<vector<string>> NewResultsTable;
	string RightName;
	RightName.push_back(right.at(0));
	string RightType = right.substr(2);
	bool HasResults = false;
	if (QAS.HasKey(RightName)) {
		int Pos = QAS.GetResultTablePos(RightName);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			if (Row.at(Pos) == left) {
				NewResultsTable.push_back(Row);
				HasResults = true;
			}
		}
		QAS.SetResultTable(NewResultsTable);
	}
	else {
		vector<string> RightResults = GetAllRightSideOfWithClause(RightType);
		if (ResultsTable.size == 0) {
			for (int i = 0; i < RightResults.size(); i++) {
				if (RightResults.at(i) == right) {
					vector<string> s;
					s.push_back(RightResults.at(i));
					NewResultsTable.push_back(s);
					HasResults = false;
				}
			}
		}
		else {
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				for (int j = 0; j < RightResults.size(); j++) {
					if (RightResults.at(j) == right) {
						vector<string> copy = Row;
						copy.push_back(RightResults.at(j));
						NewResultsTable.push_back(copy);
						HasResults = true;
					}
				}
			}
		}
		QAS.SetTable(RightName);
		QAS.SetResultTable(NewResultsTable);
	}
	return HasResults;
}
bool QueryEvaluator::GetAnswerForBothWith(string left,string right) {
	vector<vector<string>> ResultsTable = QAS.GetResultsTable();
	vector<vector<string>> NewResultsTable;
	string LeftName;
	string RightName;
	LeftName.push_back(left.at(0));
	RightName.push_back(right.at(0));
	string LeftType = left.substr(2);
	string RightType = right.substr(2);
	bool HasResults = false;
	if (QAS.HasKey(LeftName) && QAS.HasKey(RightName)) {
		int pos1 = QAS.GetResultTablePos(LeftName);
		int pos2 = QAS.GetResultTablePos(RightName);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> row = ResultsTable.at(i);
			string ColElement1 = row.at(pos1);
			string ColElement2 = row.at(pos2);
			if (ColElement1 == ColElement2) {
				NewResultsTable.push_back(row);
				HasResults = true;
			}
		}
		QAS.SetResultTable(NewResultsTable);
	}
	else if (QAS.HasKey(LeftName)) {
		vector<string> RightResults = GetAllRightSideOfWithClause(RightType);
		int pos1 = QAS.GetResultTablePos(LeftName);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			string ColElement = Row.at(pos1);
			for (int j = 0; j < RightResults.size(); j++) {
				if (ColElement == RightResults.at(j)) {
					Row.push_back(ColElement);
					NewResultsTable.push_back(Row);
					HasResults = true;
					break;
				}
			}
		}
		QAS.SetTable(RightName);
		return HasResults;
	}
	else if (QAS.HasKey(RightName)) {
		vector<string> LeftResults = GetAllRightSideOfWithClause(LeftType);
		int pos1 = QAS.GetResultTablePos(LeftName);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			string ColElement = Row.at(pos1);
			for (int j = 0; j < LeftResults.size(); j++) {
				if (ColElement == LeftResults.at(j)) {
					Row.push_back(ColElement);
					NewResultsTable.push_back(Row);
					HasResults = true;
					break;
				}
			}
		}
		QAS.SetTable(LeftName);
		return HasResults;
	}
	else {
		vector<string> RightResults = GetAllRightSideOfWithClause(RightType);
		int pos1 = QAS.GetResultTablePos(RightName);
		vector<string> LeftResults = GetAllRightSideOfWithClause(LeftType);
		int pos2 = QAS.GetResultTablePos(LeftName);
		vector<string> ToBePushed;
		for (int i = 0; i < RightResults.size(); i++) {
			for (int j = 0; j < LeftResults.size(); j++) {
				if (RightResults.at(i) == LeftResults.at(j)) {
					ToBePushed.push_back(RightResults.at(i));
					HasResults = true;
				}
			}
		}
		if (ResultsTable.size() == 0) {
			for(int i = 0; i < ToBePushed.size(); i++) {
				vector<string> v;
				v.push_back(ToBePushed.at(i));
				v.push_back(ToBePushed.at(i));
				NewResultsTable.push_back(v);
			}
		}
		else {
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				for (int j = 0; j < ToBePushed.size(); j++) {
					vector<string> copy = Row;
					copy.push_back(ToBePushed.at(j));
					copy.push_back(ToBePushed.at(j));
					NewResultsTable.push_back(copy);
				}
			}
		}
		QAS.SetTable(RightName);
		QAS.SetTable(LeftName);
		QAS.SetResultTable(NewResultsTable);
		return HasResults;
	}
	return HasResults;
}
bool QueryEvaluator::DoNormalClause(vector<Clause> ClausesVector) {
	for (int i = 0; i < ClausesVector.size(); i++) {

		bool ResultsExist;
		Clause clauses = ClausesVector.at(i);
		std::string clausesOperation = clauses.getClauseOperation();
		int clausesSize = clausesOperation.size();
		char firstParameterType = clausesOperation.at(clausesSize - 2);
		char secondParameterType = clausesOperation.at(clausesSize - 1);
		string clauseType = clausesOperation.substr(0, clausesSize - 2);
		std::string firstSecondParameterType = "";
		firstSecondParameterType = firstSecondParameterType + firstParameterType + secondParameterType;
		Parameter1 firstParameter = clauses.getFirstParameter();
		Parameter2 secondParameter = clauses.getSecondParameter();
		char firstLetter = clausesOperation.at(0);
		ResultsExist = CheckSynonym(firstParameter, secondParameter, firstParameterType,
			secondParameterType, clauseType);
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
	bool HasResults = false;
	vector<vector<string>> NewResultsTable;
	vector<vector<string>> ResultsTable = QAS.GetResultsTable();
	if (QAS.HasKey(P1)&&QAS.HasKey(P2)) {
		int Pos1 = QAS.GetResultTablePos(P1);
		int Pos2 = QAS.GetResultTablePos(P2);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			string ColElement1 = Row.at(Pos1);
			string ColElement2 = Row.at(Pos2);
			if (CheckIsResultsFromPkb(ColElement1,ColElement2 , P1Type, P2Type, ClauseType)) {
				NewResultsTable.push_back(Row);
				HasResults = true;
			}
		}
		return HasResults;
	}
	else if (QAS.HasKey(P1)) {
		int Pos1 = QAS.GetResultTablePos(P1);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			string ColElement = Row.at(Pos1);
			if (ResultsTable.size() != 0) {
				vector<string> temp = GetAllSecondSynonymFromPKB(ColElement, P2, P1Type, P2Type, ClauseType);
				for (int j = 0; j < temp.size(); j++) {
					vector<string> Copy = Row;
					Copy.push_back(temp.at(j));
					NewResultsTable.push_back(Copy);

				}
				HasResults = true;
			}
		}
		QAS.SetTable(P2);
		QAS.SetResultTable(NewResultsTable);
		return HasResults;
	}
	else if (QAS.HasKey(P2)) {
		int Pos2 = QAS.GetResultTablePos(P2);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			string ColElement = Row.at(Pos2);
			if (ResultsTable.size() != 0) {
				vector<string> temp = GetAllFirstSynonymFromPKB(P1, ColElement, P1Type, P2Type, ClauseType);
				for (int j = 0; j < temp.size(); j++) {
					vector<string> Copy = Row;
					Copy.push_back(temp.at(j));
					NewResultsTable.push_back(Copy);
				}
			}
		}
		return HasResults;
		QAS.SetTable(P1);
		QAS.SetResultTable(NewResultsTable);
	}
	else {
		vector<string> P1Results = GetAll(P1Type);
		if(ResultsTable.size()==0){
			for (int i = 0; i < P1Results.size(); i++) {
				string P1Col = P1Results.at(i);
				HasResults = true;
				vector<string> P2Results = GetAllSecondSynonymFromPKB(P1Col, P2, P1Type, P2Type, ClauseType);
				if (P2Results.size() != 0) {
					for (int j = 0; j < P2Results.size(); j++) {
						vector<string> row;
						row.push_back(P1Col);
						row.push_back(P1Col);
						NewResultsTable.push_back(row);
					}
				}
			}
			QAS.SetTable(P1);
			QAS.SetTable(P2);
			QAS.SetResultTable(NewResultsTable);
			return HasResults;
		}
		else {
			for (int j = 0; j < P1Results.size(); j++) {
				string P1Col = P1Results.at(j);
				vector<string> P2Results = GetAllSecondSynonymFromPKB(P1Col, P2, P1Type, P2Type, ClauseType);
				if (P2Results.size() != 0) {
					for (int k = 0; k < P2Results.size(); k++) {
						HasResults = true;
						string P2Col = P2Results.at(k);
						for (int i = 0; i < ResultsTable.size(); i++) {
							vector<string> row = ResultsTable.at(i);
							row.push_back(P1);
							row.push_back(P2);
							NewResultsTable.push_back(row);
						}
					}
				}
			}
		}
		QAS.SetTable(P1);
		QAS.SetTable(P2);
		QAS.SetResultTable(NewResultsTable);
		return HasResults;
	}
	return HasResults;
}

bool QueryEvaluator::GetResultsForFirstSynonym(string P1, string P2, char P1Type
	, char P2Type, string ClauseType)
{	 
	bool HasResults = false;
	vector<vector<string>> NewResultsTable;
	vector<vector<string>> ResultsTable = QAS.GetResultsTable();
	vector<string> Results;	
	if (P2.find('_')) {
		vector<string> Everything = GetP2Blank(ClauseType);
		if (QAS.HasKey(P1)) {
			int Pos1 = QAS.GetResultTablePos(P1);
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				string ColElement = Row.at(Pos1);
				for (int j = 0; j < Everything.size(); j++) {
					string ToMatch = Everything.at(j);
					if (CheckIsResultsFromPkb(ColElement, ToMatch, P1Type, P2Type, ClauseType)) {
						HasResults = true;
						NewResultsTable.push_back(Row);
					}
					break;
				}
			}
			QAS.SetResultTable(NewResultsTable);
			return HasResults;
		}
		else {
			vector<string> Results;
			for (int i = 0; i < Everything.size(); i++) {
				string Blank = Everything.at(i);
				vector<string> ToBeAppend = GetAllFirstSynonymFromPKB(P1, Blank, P1Type, P2Type, ClauseType);
				Results.insert(Results.end(), ToBeAppend.begin(), ToBeAppend.end());
			}
			if (Results.size() == 0) {
				return false;
			}
			else {
				if (ResultsTable.size() == 0) {
					for (int i = 0; i < Results.size(); i++) {
						vector<string> row;
						row.push_back(Results.at(i));
						NewResultsTable.push_back(row);
					}
					QAS.SetTable(P1);
					QAS.SetResultTable(NewResultsTable);
					return true;
				}
				else {
					for (int i = 0; i < ResultsTable.size(); i++) {
						vector<string> row = ResultsTable.at(i);
						for (int j = 0; j < Results.size(); j++) {
							vector<string> Copy = row;
							Copy.push_back(Results.at(j));
							NewResultsTable.push_back(Copy);
						}
					}
					QAS.SetTable(P1);
					QAS.SetResultTable(NewResultsTable);
					return true;
				}
			}
		}
	}
	else {
		if (QAS.HasKey(P1)) {
			int Pos1 = QAS.GetResultTablePos(P1);
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				string ColElement = Row.at(Pos1);
				if (CheckIsResultsFromPkb(ColElement, P2, P1Type, P2Type, ClauseType)) {
					HasResults = true;
					NewResultsTable.push_back(Row);
				}
			}
			QAS.SetResultTable(NewResultsTable);
			return HasResults;
		}
		else {
			Results = GetAllFirstSynonymFromPKB(P1, P2, P1Type, P2Type, ClauseType);
			if (Results.size() == 0) {
				return false;
			}
			if (ResultsTable.size() == 0) {
				for (int i = 0; i < Results.size(); i++) {
					vector<string> row;
					row.push_back(Results.at(i));
					NewResultsTable.push_back(row);
				}
				QAS.SetTable(P1);
				QAS.SetResultTable(NewResultsTable);
				return true;
			}
			else {
				for (int i = 0; i < Results.size(); i++) {
					string s = Results.at(i);
					for (int j = 0; j < ResultsTable.size(); j++) {
						vector<string> Row = ResultsTable.at(i);
						Row.push_back(s);
						NewResultsTable.push_back(Row);
					}
				}
				//same as below
				QAS.SetTable(P1);
				QAS.SetResultTable(NewResultsTable);
				return true;
			}
		}
	}
	//check if there is actually an results. If no results return false, if there is return true
	return false;
}

bool QueryEvaluator::GetResultsForSecondSynonym(string P1, string P2, char P1Type
	, char P2Type, string ClauseType)
{

	bool HasResults = false;
	vector<vector<string>> NewResultsTable;
	vector<vector<string>> ResultsTable = QAS.GetResultsTable();
	vector<string> Results;
	bool HasResults = false;
	vector<vector<string>> NewResultsTable;
	vector<vector<string>> ResultsTable = QAS.GetResultsTable();
	vector<string> Results;
	if (P1.find('_')) {
		vector<string> Everything = GetP1Blank(ClauseType);
		if (QAS.HasKey(P1)) {
			int Pos2 = QAS.GetResultTablePos(P1);
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				string ColElement = Row.at(Pos2);
				for (int j = 0; j < Everything.size(); j++) {
					string ToMatch = Everything.at(j);
					if (CheckIsResultsFromPkb(ColElement, ToMatch, P1Type, P2Type, ClauseType)) {
						HasResults = true;
						NewResultsTable.push_back(Row);
					}
					break;
				}
			}
			QAS.SetResultTable(NewResultsTable);
			return HasResults;
		}
		else {
			vector<string> Results;
			for (int i = 0; i < Everything.size(); i++) {
				string Blank = Everything.at(i);
				vector<string> ToBeAppend = GetAllSecondSynonymFromPKB(Blank, P2, P1Type, P2Type, ClauseType);
				Results.insert(Results.end(), ToBeAppend.begin(), ToBeAppend.end());
			}
			if (Results.size() == 0) {
				return false;
			}
			else {
				if (ResultsTable.size() == 0) {
					for (int i = 0; i < Results.size(); i++) {
						vector<string> row;
						row.push_back(Results.at(i));
						NewResultsTable.push_back(row);
					}
					QAS.SetTable(P2);
					QAS.SetResultTable(NewResultsTable);
					return true;
				}
				else {
					for (int i = 0; i < ResultsTable.size(); i++) {
						vector<string> row = ResultsTable.at(i);
						for (int j = 0; j < Results.size(); j++) {
							vector<string> Copy = row;
							Copy.push_back(Results.at(j));
							NewResultsTable.push_back(Copy);
						}
					}
					QAS.SetTable(P2);
					QAS.SetResultTable(NewResultsTable);
					return true;
				}
			}
		}
	}
	else {
		if (QAS.HasKey(P2)) {
			int Pos2 = QAS.GetResultTablePos(P1);
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				string ColElement = Row.at(Pos2);
				if (CheckIsResultsFromPkb(P1, ColElement, P1Type, P2Type, ClauseType)) {
					HasResults = true;
					NewResultsTable.push_back(Row);
				}
			}
			QAS.SetResultTable(NewResultsTable);
			return HasResults;
		}
		else {
			Results = GetAllSecondSynonymFromPKB(P1, P2, P1Type, P2Type, ClauseType);
			if (Results.size() == 0) {
				return false;
			}
			else {
				if (ResultsTable.size()) {
					if (ResultsTable.size() == 0) {
						for (int i = 0; i < Results.size(); i++) {
							vector<string> row;
							row.push_back(Results.at(i));
							NewResultsTable.push_back(row);
						}
						QAS.SetTable(P2);
						QAS.SetResultTable(NewResultsTable);
						return true;
					}
				}
				else {
					for (int i = 0; i < Results.size(); i++) {
						string s = Results.at(i);
						for (int j = 0; j < ResultsTable.size(); j++) {
							vector<string> Row = ResultsTable.at(i);
							Row.push_back(s);
							NewResultsTable.push_back(Row);
						}
					}
					//same as below
					QAS.SetTable(P2);
					QAS.SetResultTable(NewResultsTable);
					return true;
				}
			}
		}
	}
	//check if there is actually an results. If no results return false, if there is return true
	return false;
}

bool QueryEvaluator::CheckTrueOrFalse(string P1, string P2, char P1Type
	, char P2Type, string ClauseType) {
	return CheckIsResultsFromPkb(P1,P2,P1Type,P2Type,ClauseType);
}

vector<string> QueryEvaluator::GetAll(char Type) {
	vector<string> Results;
	if (Type == 'p') {
		//getallprocedure
	}
	else if (Type == 'v') {
		//getallvariable
	}
	else if (Type == 's') {
		//getallstmt
	}
	else if (Type == 'i') {
		//getallif
	}
	else if (Type == 'w') {
		//getallwhile
	}
	else if (Type == 'a') {
		//getallassign
	}
	else if (Type == 'c') {
		//getallconstant
	}
	else {
		return Results;
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

bool QueryEvaluator::GetResultsForNoClause(vector<pair<string, string>> SP)
{	
	for (int i = 0; i < SP.size(); i++) {
		pair<string, string> pair = SP.at(i);
		string type = pair.first;
		vector<string> Result;
		if (type == "stmt") {
			Result = GetAll('s');
		}
		else if (type == "while") {
			Result = GetAll('w');
		}
		else if (type == "assign") {
			Result = GetAll('a');
		}
		else if (type == "if") {
			Result = GetAll('i');
		}
		else if (type == "variable") {
			Result = GetAll('v');
		}
		else if (type == "constant") {
			Result = GetAll('c');
		}
		else if(type == "procedure") {
			Result = GetAll('p');
		}
		else {
			return false;
		}
		if (Result.size() == 0) {
			return false;
		}
		QAS.SetNoClause(Result);
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

string QueryEvaluator::MatchWithClause(string ToBeMatch,char type)
{
	string Results;
	string WTK = WithTableKey(ToBeMatch,type);
	string WithClause = QAS.GetWithTableElement(WTK);
	if (WithClause == "none") {
		return Results;
	}
	else {
		return WithClause;
	}
}

vector<string> QueryEvaluator::CheckWithClauseVector(vector<string> v, vector<string> w) {
	
	vector<string> Results;
	for (int i = 0; i < v.size(); i++) {
		if (CheckIfMatchWithClause(v.at(i), w)) {
			//if true push-back
			Results.push_back(v.at(i));
		}
	}
	return Results;
}
pair<string, string>QueryEvaluator::SplitWithClause(string s ) {
	string ClauseName = s.substr(0,1);
	string type = s.substr(2);
	return make_pair(ClauseName,type);
}

vector<string> QueryEvaluator::GetP2Blank(string clausesType) {
	
	if (clausesType == "Follows") {
		//return allstmt
	}
	else if (clausesType == "Follows*") {
		//return allstmt
	}
	else if (clausesType == "Uses") {
		//return variable
	}
	else if (clausesType == "Calls") {
		//return all procedure
	}
	else if (clausesType == "Modifies") {
		//return all procedure
	}
	else if (clausesType == "Parent") {
		//return all stmt
	}
	else if (clausesType == "Parent*") {
		//return all stmt
	}
	else if (clausesType == "Next") {
		//return all prog_line
	}
	else if (clausesType == "Next*") {
		//return all prog_line
	}
	else if (clausesType == "Affects") {
		//return all assign
	}
	else if (clausesType == "Affects*") {
		//return all assing
	}
	else {
		//return nothing
	}
}

vector<string> QueryEvaluator::GetP1Blank(string clausesType) {

	if (clausesType == "Follows") {
		//return allstmt
	}
	else if (clausesType == "Follows*") {
		//return allstmt
	}
	else if (clausesType == "Uses") {
		//return variable
	}
	else if (clausesType == "Calls") {
		//return all procedure
	}
	else if (clausesType == "Modifies") {
		//return all procedure
	}
	else if (clausesType == "Parent") {
		//return all stmt
	}
	else if (clausesType == "Parent*") {
		//return all stmt
	}
	else if (clausesType == "Next") {
		//return all prog_line
	}
	else if (clausesType == "Next*") {
		//return all prog_line
	}
	else if (clausesType == "Affects") {
		//return all assign
	}
	else if (clausesType == "Affects*") {
		//return all assing
	}
	else {
		//return nothing
	}
}
vector<string> QueryEvaluator::GetAllRightSideOfWithClause(string s) {
	
	if (QAS.HasKey(s)) {
		return QAS.GetColFromResultsTable(s);
	}
	else {
		string type = QAS.GetSelectType(s);
		if (type == "stmt") {
			//return all stmt
		}
		else if (type == "assignment") {
			//return all assignment
		}
		else if (type == "procedure") {
			//return all procedure
		}
		else if (type == "while") {
			//return all while
		}
		else if (type == "assign") {
			//return all assign
		}
		else if (type == "constant") {
			//return all constant
		}
		else {
			//return empty
		}
	}
}

string QueryEvaluator::WithTableKey(string ToBeMatch,char type) {
	
	if (type = 'C') {
		return ToBeMatch+".value";
	}
	else if (type = 'V') {
		return ToBeMatch + ".varName";
	}
	else if (type = 'A') {
		//---not sure
	}
	else if (type = 'W') {
		//----not sure
	}
	else if (type = 'I') {
		//---not sure
	}
	else if (type = 'S') {
		return ToBeMatch + ".stmt#";
	}
	else if(type = 'P'){
		return ToBeMatch + ".procName";
	}
	else {
		//--not sure
	}
}


void QueryEvaluator::clear()
{
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
//check with the withresult , and see whether the string matches any one of them
bool QueryEvaluator::CheckIfMatchWithClause(string s,vector<string> v) {
	for (int i = 0; i < v.size; i++) {
		if (v.at(i) == s) {
			return true;
		}
	}
	return false;
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





