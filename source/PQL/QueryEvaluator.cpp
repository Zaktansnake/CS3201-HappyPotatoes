
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
#include "../PKB/Header/CFG.h"
#include "../PKB/Header/PatternTable.h"
#include "../PKB//Header/ProcTable.h"
#include "../PKB/Header/ConstantTable.h"
using namespace std;

QueriesAnswerStorage QAS;

vector<string> QueryEvaluator::startEvaluator(ParseResult mustPr)
{
	QAS.clear();
	cout << "Hello World! start to evaluate" << endl;
	clear();
	bool HasResults = false;
	try {

		HasResults = assessParseResult(mustPr); //add a storage check
	}
	catch (exception&e) {
		cout << e.what() << endl;
	}
	if (SelectBool == true) {
		cout << "asking for boolean" << endl;
		vector<string> BooleanResults;
		if (HasResults == true) {
			cout << "has a result for boolean" << endl;
			BooleanResults.push_back("True");
		}
		else {
			cout << "has no result for boolean" << endl;
			BooleanResults.push_back("");
		}
	}
	else {
		
		if (HasResults == true) {
			if (NoClause) {
				cout << "has no clause ans" << endl;
				return QAS.GetNoClause();
			}
		
			else {
				cout << "merge result" << endl;
				unordered_map<string, int> m = QAS.GetTable();
				for (auto it = m.begin(); it != m.end(); ++it) {
					cout << "all key 2" << endl;
					std::cout << " " << it->first << ":" << it->second << endl;;
				}
				return QAS.MergeResults();
			}
		}
		else {
			return NoResults;
		}
	}
}

vector<string> QueryEvaluator::GetAllOfTheNotStored() {
	
	vector<string> ReturnResult;
	vector<pair<string, string>> sv = QAS.GetSelectParameter();
	for (int i = 0; i < sv.size(); i++) {
		pair<string, string> pair = sv.at(i);
		string type = pair.second;
		cout << "type" << endl;
		vector<string> Result;
		if (type == "stmt") {
			cout << "is stmt" << endl;
			Result = GetAll('s');
		}
		else if (type == "while") {
			cout << "is while" << endl;
			Result = GetAll('w');
		}
		else if (type == "assign") {
			cout << "is assign" << endl;
			Result = GetAll('a');
		}
		else if (type == "if") {
			cout << "is if" << endl;
			Result = GetAll('i');
		}
		else if (type == "variable") {
			cout << "if variable" << endl;
			Result = GetAll('v');
		}
		else if (type == "constant") {
			cout << "constant" << endl;
			Result = GetAll('c');
		}
		else if (type == "procedure") {
			cout << "procedure" << endl;
			Result = GetAll('p');
		}
		else if (type == "prog_line") {
			cout << "prog_line" << endl;
			Result = GetAll('s');
		}
		else {
			cout << "nothing" << endl;
			Result = Result;
		}
		cout << Result.size() << endl;
		for (int k = 0; k < Result.size(); k++) {
			string ToBeMatch = Result.at(k);
			if (ReturnResult.size() == 0) {
				ReturnResult.push_back(ToBeMatch);
			}
			else {
				if (std::find(ReturnResult.begin(), ReturnResult.end(), ToBeMatch) == ReturnResult.end()) {
					ReturnResult.push_back(ToBeMatch);
				}
			}
		}
	}
	cout << "here haahahahahaha" << endl;
	cout << ReturnResult.size() << endl;
	return ReturnResult;
}

bool QueryEvaluator::SelectNotStored() {
	vector<pair<string, string>> sv = QAS.GetSelectParameter();
	for (int i = 0; i < sv.size(); i++) {
		string name = sv.at(i).first;
		if (!QAS.HasKey(name)) {
			return true;
		}
	}
}
bool QueryEvaluator::assessParseResult(ParseResult pr) {


	std::vector<std::string> SelectParameterVector = pr.getSelectParameter();
	std::vector<Clause> ClausesVector = pr.getClauses();
	PatternSet PatternQueryVector = pr.getPatterns();
	std::vector<With> WithClauses = pr.getWithClauses();
	cout << "assessclause result" << endl;
	return assessClauses(ClausesVector, SelectParameterVector, PatternQueryVector, WithClauses);
}

bool QueryEvaluator::assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector,
	PatternSet PS, vector<With> WithClauses) {

	cout << "I am assesssing clause" << endl;

	cout << "ClauseVector"+ClausesVector.size() << endl;
	QAS.SetSelect(SelectParameterVector);

	vector<bool> ResultsExist;
	//if there is no clause and no with clause at allw
	if ((ClausesVector.size() == 0) && ((WithClauses.size() == 0) && (PS.size() == 0))) {
		cout << "no clause 1" << endl;
		NoClause = true;
		bool has = GetResultsForNoClause(QAS.GetSelectParameter());
		if (has == false) {
			cout << "no clause has no result" << endl;
			ResultsExist.push_back(false);

		}
		else {
			ResultsExist.push_back(true);
		}
	}
	else if ((ClausesVector.size() == 0) && ((WithClauses.size() != 0) && (PS.size() != 0))) {
		ResultsExist.push_back(DoPatterns(PS));
		ResultsExist.push_back(DoWithClause(WithClauses));
		cout << "no normal clause Case 2" << endl; // patterns and with clause
	}
	else if ((PS.size() == 0) && ((WithClauses.size() != 0) && (ClausesVector.size() != 0))) {
		ResultsExist.push_back(DoWithClause(WithClauses));
		ResultsExist.push_back(DoNormalClause(ClausesVector));
		cout << "no pattern clause Case 3" << endl; // with clause and normal
	}
	else if ((WithClauses.size() == 0) && ((ClausesVector.size() != 0) && (PS.size() != 0))) {
		ResultsExist.push_back(DoPatterns(PS));
		ResultsExist.push_back(DoNormalClause(ClausesVector));
		cout << "no with clause Case 4" << endl; // pattern and normal clause
	}
	else if ((ClausesVector.size() != 0) && ((WithClauses.size() == 0) && (PS.size() == 0))) {
		cout << "no with clause and pattern clause Case 5" << endl; // normal
		ResultsExist.push_back(DoNormalClause(ClausesVector));
		
	}
	else if ((PS.size() != 0) && ((WithClauses.size() == 0) && (ClausesVector.size() == 0))) {
		ResultsExist.push_back(DoPatterns(PS));
		cout << "no with clause and normal clause Case 6" << endl; // pattern
	}
	else if ((WithClauses.size() != 0) && ((PS.size() == 0) && (ClausesVector.size() == 0))) {
		ResultsExist.push_back(DoWithClause(WithClauses));
		cout << "no pattern clause and normal clause Case 7" << endl; // with
	}
	else {
		ResultsExist.push_back(DoPatterns(PS));
		ResultsExist.push_back(DoWithClause(WithClauses));
		ResultsExist.push_back(DoNormalClause(ClausesVector));
		cout << " have every thing Case 8" << endl; // everything else
	}
	cout << "check has results" << endl;
	cout << ReturnResultsExist(ResultsExist) << endl;
	unordered_map<string, int> m = QAS.GetTable();
	for (auto it = m.begin(); it != m.end(); ++it) {
		cout << "all key 1" << endl;
		std::cout << " " << it->first << ":" << it->second<<endl;
	}
	return ReturnResultsExist(ResultsExist);
}

bool QueryEvaluator::ReturnResultsExist(vector<bool> RE) {
	for (int i = 0; i < RE.size(); i++) {
		if (RE.at(i) == false) {
			return false;
		}
	}
	return true;
}

bool QueryEvaluator::DoPatterns(PatternSet PS)
{
	vector<vector<string > > NewResultsTable;
	vector<vector<string > > ResultsTable = QAS.GetResultsTable();
	for (int i = 0; i < PS.size(); i++) {
		Pattern P = PS.at(i);
		string NamePlusType = P.getPatternOperation();
		string type = SplitString(NamePlusType).first; // reminder to check with Zhao han if type then name or name then type
		string Name = SplitString(NamePlusType).second;
		string P1 = P.getFirstParameter();
		string P2 = P.getSecondParameter();
		string P3 = P.getThirdParameter();
		vector<string> results = CheckPattern(type, Name, P1, P2, P3);
		if (results.size() == 0) {
			return false;
		}
		else {
			if (ResultsTable.size() == 0) {
				for (int i = 0; i < results.size(); i++) {
					vector<string> s;
					s.push_back(results.at(i));
					NewResultsTable.push_back(s);
				}
			}
			else {
				for (int i = 0; i < ResultsTable.size(); i++) {
					vector<string> row = ResultsTable.at(i);
					for (int j = 0; j < results.size(); j++) {
						vector<string> copy = row;
						copy.push_back(results.at(j));
						NewResultsTable.push_back(copy);
					}
				}
			}
			QAS.SetTable(Name);
			QAS.SetResultTable(NewResultsTable);
		}
	}
	return true;
}

vector<string> QueryEvaluator::CheckPattern(string type, string name, string P1, string P2, string P3) {

	vector<string> results;
	if (type == "while") {
		cout << "get pattern for while" << endl;
		results = PatternTable::getPatternWhileNum(P1);
	}
	else if (type == "assign") {
		cout << "get pattern for assign" << endl;
		results = PatternTable::getPatternAssignNum(P1, P2);
	}
	else {
		cout << "get pattern for if" << endl;
		results = PatternTable::getPatternIfsNum(P1);
	}
	return results;
}

bool QueryEvaluator::DoWithClause(vector<With> W) {

	for (int i = 0; i < W.size(); i++) {
		if (CheckWith(W.at(i))) {
			cout << "have with results" << endl;
			continue;
		}
		else {
			cout << "have no with results" << endl;
			return false;
		}
	}
	return true;
}

bool QueryEvaluator::CheckWith(With with) {

	string left = with.getLeftOfEqualSign();
	string right = with.getRightOfEqualSign();
	if ((IsSynonym(left[0]) && (IsSynonym(right[0])))) {
		cout << "both is synonym for with";
		return GetAnswerForBothWith(with.getLeftOfEqualSign(), with.getRightOfEqualSign());
	}
	else if (IsSynonym(right[0])) {
		cout << "only the right is a synonym for with" << endl;
		return GetAnswerForRightWith(with.getLeftOfEqualSign(), with.getRightOfEqualSign());
	}
	else if (IsSynonym(left[0])) {
		cout << "only the left is a synonym for with" << endl;
		return GetAnswerForLeftWith(with.getLeftOfEqualSign(), with.getRightOfEqualSign());
	}
	else {
		cout << "both is not a synonym for with" << endl;
		if (with.getLeftOfEqualSign() == with.getRightOfEqualSign()) {
			return true;
		}
		else {
			return false;
		}
	}
}

//this is the case for e.g v.varname = "x"
bool QueryEvaluator::GetAnswerForLeftWith(string left, string right) {
	vector<vector<string > > ResultsTable = QAS.GetResultsTable();
	vector<vector<string > > NewResultsTable;
	//get the left synonym and the corresponding type
	string LeftName = SplitString(left).second;
	string LeftType = SplitString(right).first;
	bool HasResults = false;
	//if the left is actually stored in the storage before
	if (QAS.HasKey(LeftName)) {
		int Pos = QAS.GetResultTablePos(LeftName);
		//check if the collumn that contains all the results for the left fits the withclause
		//if fits, take the row where the colelement is at and store them in the new storage
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			if (Row.at(Pos) == right) { //check whether right has quotation marks, if have then remove, and don't have return the same
				NewResultsTable.push_back(Row);
				HasResults = true;
			}
		}
		QAS.SetResultTable(NewResultsTable);
	}
	else {
		//if left is not stored in the resutls before
		vector<string> leftResults = GetAllOfWithClause(LeftType);
		//if resultstable has nothing inside just store the whole column
		if (ResultsTable.size() == 0) {
			for (int i = 0; i < leftResults.size(); i++) {
				if (leftResults.at(i) == right) { //check whether right has quotation marks, if have then remove, and don't have return the same
					vector<string> s;
					s.push_back(leftResults.at(i));
					NewResultsTable.push_back(s);
					HasResults = true;
				}
			}
		}
		else {
			//else do catesian product with the withclause results
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				for (int j = 0; j < leftResults.size(); j++) {
					if (leftResults.at(j) == right) { //check whether right has quotation marks, if have then remove, and don't have return the same
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

//the same thing as left with
bool QueryEvaluator::GetAnswerForRightWith(string left, string right) {
	vector<vector<string > > ResultsTable = QAS.GetResultsTable();
	vector<vector<string > > NewResultsTable;
	string RightName = SplitString(right).second;
	string RightType = SplitString(right).first;
	bool HasResults = false;
	if (QAS.HasKey(RightName)) {
		int Pos = QAS.GetResultTablePos(RightName);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			if (Row.at(Pos) == left) { //check whether left has quotation marks, if have then remove, and don't have return the same
				NewResultsTable.push_back(Row);
				HasResults = true;
			}
		}
		QAS.SetResultTable(NewResultsTable);
	}
	else {
		vector<string> RightResults = GetAllOfWithClause(RightType);
		if (ResultsTable.size() == 0) {
			for (int i = 0; i < RightResults.size(); i++) {
				if (RightResults.at(i) == right) { //check whether left has quotation marks, if have then remove, and don't have return the same
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
					if (RightResults.at(j) == right) { //check whether left has quotation marks, if have then remove, and don't have return the same
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

//this is a case for s.#stmt = c.constant
bool QueryEvaluator::GetAnswerForBothWith(string left, string right) {
	vector<vector<string > > ResultsTable = QAS.GetResultsTable();
	vector<vector<string > > NewResultsTable;
	pair<string, string> Left = SplitString(left);
	pair<string, string> Right = SplitString(right);
	string LeftName = Left.second;
	string LeftType = Left.first;
	string RightName = Right.second;
	string RightType = Right.first;
	bool HasResults = false;
	//when both of the results is stored just check whether the v and the c in each row 
	//fulfils the condition
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
	//if only the left is stored
	else if (QAS.HasKey(LeftName)) {
		//get all of the right first depending on the type
		vector<string> RightResults = GetAllOfWithClause(RightType);
		int pos1 = QAS.GetResultTablePos(LeftName);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			string ColElement = Row.at(pos1);
			//loop throught the rightresults vector
			for (int j = 0; j < RightResults.size(); j++) {
				//if the colelement is equal to any of the right results 
				//push back colelement, since the right have to be equal to the colelement
				//then push the entire row into the new results vector
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
		vector<string> LeftResults = GetAllOfWithClause(LeftType);
		int pos1 = QAS.GetResultTablePos(RightName);
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
		vector<string> RightResults = GetAllOfWithClause(RightType);
		int pos1 = QAS.GetResultTablePos(RightName);
		vector<string> LeftResults = GetAllOfWithClause(LeftType);
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
			for (int i = 0; i < ToBePushed.size(); i++) {
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

bool QueryEvaluator::CheckSynonym(string firstParameter, string secondParameter,
	char firstParameterType, char secondParameterType, string clauseType) {
	bool HasResults = false;
	if ((IsSynonym(firstParameter[0])) && (IsSynonym(secondParameter[0]))) {
		cout << "normal clause when both is synonym" << endl;
		HasResults = GetResultsForBothSynonym(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
	else if (IsSynonym(firstParameter[0])) {
		cout << "normal clause when only one is synonym" << endl;
		HasResults = GetResultsForFirstSynonym(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
	else if (IsSynonym(secondParameter[0])) {
		cout << "normal clause when only the second is snynonym" << endl;
		HasResults = GetResultsForSecondSynonym(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
	else {
		cout << "normal clause when both is not a snynonym" << endl;
		HasResults = CheckTrueOrFalse(firstParameter, secondParameter,
			firstParameterType, secondParameterType, clauseType);
	}
	return HasResults;
}

bool QueryEvaluator::GetResultsForBothSynonym(string P1, string P2, char P1Type
	, char P2Type, string ClauseType)
{
	bool HasResults = false;
	vector<vector<string > > NewResultsTable;
	vector<vector<string > > ResultsTable = QAS.GetResultsTable();
	if (P1 == P2) {

	}
	if (QAS.HasKey(P1) && QAS.HasKey(P2)) {
		int Pos1 = QAS.GetResultTablePos(P1);
		int Pos2 = QAS.GetResultTablePos(P2);
		for (int i = 0; i < ResultsTable.size(); i++) {
			vector<string> Row = ResultsTable.at(i);
			string ColElement1 = Row.at(Pos1);
			string ColElement2 = Row.at(Pos2);
			if (CheckIsResultsFromPkb(ColElement1, ColElement2, P1Type, P2Type, ClauseType)) {
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
		cout << "both synonym has key" << endl;
		vector<string> P1Results = GetAll(P1Type);
		cout << "P1Results" << endl;
		cout << P1Results.size() << endl;
		if (ResultsTable.size() == 0) {
			for (int i = 0; i < P1Results.size(); i++) {
				string P1Col = P1Results.at(i);
				HasResults = true;
				vector<string> P2Results = GetAllSecondSynonymFromPKB(P1Col, P2, P1Type, P2Type, ClauseType);
				cout << "P2Results" <<endl;
				cout << P2Results.size() << endl;
				if (P2Results.size() != 0) {
					for (int j = 0; j < P2Results.size(); j++) {
						string P2Col = P2Results.at(j);
						vector<string> row;
						row.push_back(P1Col);
						row.push_back(P2Col);
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
	cout << "i reach here already" << endl;
	bool HasResults = false;
	vector<vector<string > > NewResultsTable;
	vector<vector<string > > ResultsTable = QAS.GetResultsTable();
	vector<string> Results;
	cout << "P2" + P2 << endl;
	//if is for example follows(s,"_")
	if (P2 == "_") {
		vector<string> Everything = GetP2Blank(ClauseType);
		//if p1 has is stored
		//check if the each of the colelement of p1 and the each of the results for 
		//"_" matches
		if (QAS.HasKey(P1)) {
			cout << "haskey but p2 is blank" << endl;
			cout << Everything.size() << endl;
			int Pos1 = QAS.GetResultTablePos(P1);
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				string ColElement = Row.at(Pos1);
				for (int j = 0; j < Everything.size(); j++) {
					string ToMatch = Everything.at(j);
					if (CheckIsResultsFromPkb(ColElement, ToMatch, P1Type, P2Type, ClauseType)) {
						cout << "ResultsTable.size()" << endl;
						cout << ResultsTable.size() << endl;
						cout << "string to match for p1" << endl;
						cout << ToMatch << endl;
						cout << "colelement" << endl;
						cout << ColElement << endl;
						HasResults = true;
						NewResultsTable.push_back(Row);
					}
				}
			}
			QAS.SetResultTable(NewResultsTable);
			return HasResults;
		}
		else {

			//if p1 is not stored
			vector<string> Results;
			cout << "everything" + Everything.size() << endl;
			//check loop through all of everything to find all possible ans for p1 and store them in a array
			for (int i = 0; i < Everything.size(); i++) {
				string Blank = Everything.at(i);
				vector<string> ToBeAppend = GetAllFirstSynonymFromPKB(P1, Blank, P1Type, P2Type, ClauseType);
				for (int j = 0; j < ToBeAppend.size(); j++) {
					//check for duplicates
					if ((std::find(Results.begin(), Results.end(), ToBeAppend.at(j)) == Results.end())) {
						Results.push_back(ToBeAppend.at(j));
					}
				}
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
		cout << P1 << endl;
		cout << "haskey" << endl;
		cout << QAS.HasKey(P1) << endl;
		if (QAS.HasKey(P1)==true) {
			cout << "P1 is stored before" << endl;
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
				cout << "no results" << endl;
				return false;
			}
			cout << "haskey" << endl;
			cout << QAS.HasKey(P1);
			cout << "size" << endl;
			cout << Results.size() << endl;
			if (ResultsTable.size() == 0) {
				for (int i = 0; i < Results.size(); i++) {
					vector<string> row;
					row.push_back(Results.at(i));
					cout << "pushing into new results" << endl;
					NewResultsTable.push_back(row);
				}
				cout << "already set results" << endl;
				QAS.SetTable(P1);
				QAS.SetResultTable(NewResultsTable);
				return true;
			}
			else {
				cout << "there is something in resultstable" << endl;
				for (int i = 0; i < Results.size(); i++) {
					string s = Results.at(i);
					for (int j = 0; j < ResultsTable.size(); j++) {
						cout << "ResultsTable.size" << endl;
						cout << ResultsTable.size() << endl;
						vector<string > Row = ResultsTable.at(j);
						cout << Row.size() << endl;
						Row.push_back(s);
						cout << "Row push back ans" << endl;
						NewResultsTable.push_back(Row);
						cout << "new table push back row" << endl;
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
	vector<vector<string > > NewResultsTable;
	vector<vector<string > > ResultsTable = QAS.GetResultsTable();
	vector<string> Results;
	if (P1 == "_") {
		cout << "if p1 is a blank" << endl;
		vector<string> Everything = GetP1Blank(ClauseType);
		if (QAS.HasKey(P2)) {
			cout << "if p1 is stored" << endl;
			int Pos2 = QAS.GetResultTablePos(P1);
			for (int i = 0; i < ResultsTable.size(); i++) {
				vector<string> Row = ResultsTable.at(i);
				string ColElement = Row.at(Pos2);
				for (int j = 0; j < Everything.size(); j++) {
					string ToMatch = Everything.at(j);
					if (CheckIsResultsFromPkb(ColElement, ToMatch, P1Type, P2Type, ClauseType)) {
						HasResults = true;
						NewResultsTable.push_back(Row);
						break;
					}
				}
			}
			QAS.SetResultTable(NewResultsTable);
			return HasResults;
		}
		else {
			cout << "if p1 has no key" << endl;
			vector<string> Results;
			for (int i = 0; i < Everything.size(); i++) {
				string Blank = Everything.at(i);
				vector<string> ToBeAppend = GetAllSecondSynonymFromPKB(Blank, P2, P1Type, P2Type, ClauseType);
				for (int j = 0; j < ToBeAppend.size(); j++) {
					if ((std::find(Results.begin(), Results.end(), ToBeAppend.at(j)) == Results.end())) {
						Results.push_back(ToBeAppend.at(j));
					}
				}
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
			cout << "finding second" << endl;
			Results = GetAllSecondSynonymFromPKB(P1, P2, P1Type, P2Type, ClauseType);
			if (Results.size() == 0) {
				return false;
			}
			else {
				cout << "has results in second" << endl;
				if (ResultsTable.size() == 0) {
					cout << "synonym is not inside" << endl;
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
					for (int i = 0; i < Results.size(); i++) {
						string s = Results.at(i);
						for (int j = 0; j < ResultsTable.size(); j++) {
							vector<string> Row = ResultsTable.at(j);
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
	return CheckIsResultsFromPkb(P1, P2, P1Type, P2Type, ClauseType);
}

vector<string> QueryEvaluator::GetAll(char Type) {
	vector<string> Results;

	if (Type == 'p') {
		cout << "get all procedure" << endl;
		return ProcTable::getAllProcedures();
	}
	else if (Type == 'v') {
		cout << "get all variable" << endl;
		return VarTable::getAllWithType(GetStringType(Type), "");

	}
	else if (Type == 's') {
		cout << "get all stmt" << endl;
		cout << GetStringType(Type) << endl;
		cout << VarTable::getAllWithType(GetStringType(Type), "").size() << endl;
		return VarTable::getAllWithType(GetStringType(Type), "");
	}
	else if (Type == 'i') {
		cout << "get all if" << endl;
		return VarTable::getAllWithType(GetStringType(Type), "");
	}
	else if (Type == 'w') {
		cout << "get all while" << endl;
		return VarTable::getAllWithType(GetStringType(Type), "");
		//return VarTable::getAllWhile();
	}
	else if (Type == 'a') {
		cout << "get all assign" << endl;
		return VarTable::getAllWithType(GetStringType(Type), "");
		//return VarTable::getAllAssign();
	}
	else if (Type == 'c') {
		cout << "get all constant" << endl;
		return ConstantTable::getAllConstantValues();
		//return ConstantTable::getAllConstantValues();
	}
	else if (Type == 'l') {
		cout << "get all progline" << endl;
		return VarTable::getAllWithType(GetStringType(Type), "");
		//return VarTable::getAllStmt();
	}
	else {
		return Results;
	}
}

vector<string> QueryEvaluator::GetAllSecondSynonymFromPKB(string P1, string P2, char P1Type,
	char P2Type, string clausesType) { // check if there is a quotation mark, if there is will need to remove
	vector<string> results;
	cout << "getallsecondsynonymfrompkb" << endl;
	if (clausesType == "Follows") {
		cout << "follows" << endl;
		cout << P2Type << endl;
		results = stmtTable::getFollowWithType(GetStringType(P2Type), P1);
		cout << results.size() << endl;
	}
	else if (clausesType == "Follows*") {
		results = stmtTable::getFollowStarWithType(GetStringType(P2Type), P1);
	}
	else if (clausesType == "Uses") {
		results = VarTable::getUsesWithType(GetStringType(P2Type), RemoveQuotations(P1));
	}
	else if (clausesType == "Calls") {
		results = ProcTable::getProcWithType("PROC", RemoveQuotations(P1));
	}
	else if (clausesType == "Modifies") {
		results = VarTable::getModifiesWithType(GetStringType(P2Type), RemoveQuotations(P1));
	}
	else if (clausesType == "Parent") {
		results = stmtTable::getChildWithType(GetStringType(P2Type), P1);
	}
	else if (clausesType == "Parent*") {
		cout << "parents*" << endl;
		results = stmtTable::getChildStarWithType(GetStringType(P2Type), P1);
	}
	else if (clausesType == "Next") {
		results = CFG::getNextString(ChangeStringToInt(P1));
	}
	else if (clausesType == "Next*") {
		results = CFG::getNextStarString(ChangeStringToInt(P1));
	}
	else if (clausesType == "Affects") {
		return results;
	}
	else if (clausesType == "Affects*") {
		return results;
	}
	else {
		return results;
	}
	return results;
}

vector<string> QueryEvaluator::GetAllFirstSynonymFromPKB(string P1, string P2, char P1Type,
	char P2Type, string clausesType) { // check if there is a quotation mark, if there is will need to remove
	cout << "getting all synonym in pkb" << endl;
	cout << clausesType << endl;
	vector<string> results;
	if (clausesType == "Follows") {
		cout << "follows" << endl;
		cout << P1Type << endl;
		cout << results.size() << endl;
		return results = stmtTable::getFollowFanWithType(GetStringType(P1Type), P2);
		
	}
	else if (clausesType == "Follows*") {
		results = stmtTable::getFollowFanStarWithType(GetStringType(P1Type), P2);
	}
	else if (clausesType == "Uses") {
		results = VarTable::getUsedWithType(GetStringType(P1Type), RemoveQuotations(P2));
	}
	else if (clausesType == "Calls") {
		results = ProcTable::getParentProcWithType(GetStringType(P1Type), RemoveQuotations(P2));
	}
	else if (clausesType == "Modifies") {
		results = VarTable::getModifiedWithType(GetStringType(P1Type), RemoveQuotations(P2));
	}
	else if (clausesType == "Parent") {
		results = stmtTable::getParentWithType(GetStringType(P1Type), P2);
		cout << results.size() << endl;
	}
	else if (clausesType == "Parent*") {
		results = stmtTable::getParentStarWithType(GetStringType(P1Type), P2);
	}
	else if (clausesType == "Next") {
		results = CFG::getNextString(ChangeStringToInt(P2));
	}
	else if (clausesType == "Next*") {
		results = CFG::getNextStarString(ChangeStringToInt(P2));
	}
	else if (clausesType == "Affects") {
		return results;
	}
	else if (clausesType == "Affects*") {
		return results;
	}
	else {
		return results;
	}
	return results;
}

bool QueryEvaluator::CheckIsResultsFromPkb(string P1, string P2, char P1Type,
	char P2Type, string clausesType) { // check if there is a quotation mark, if there is will need to remove

	bool results;
	if (clausesType == "Follows") {
		cout << "check is results for follows" << endl;
		results = stmtTable::isFollow(ChangeStringToInt(P1), ChangeStringToInt(P2));
		//cout << "results for follows" << endl;
		//cout << results << endl;
	
	}
	else if (clausesType == "Follows*") {
		cout << "check is results for follows*" << endl;
		results = stmtTable::isFollowStar(ChangeStringToInt(P1), ChangeStringToInt(P2));
	}
	else if (clausesType == "Uses") {
		cout << "check is results for Uses" << endl;
		results = VarTable::getUsesBooleanWithType(P1, P2);
	}
	else if (clausesType == "Calls") {
		cout << "check is results for Calls" << endl;
		results = ProcTable::isProcToProc(P1, P2);
	}
	else if (clausesType == "Modifies") {
		cout << "check is results for Modifies" << endl;
		results = VarTable::getModifiesBooleanWithType(P1, P2);
	}
	else if (clausesType == "Parent") {
		cout << "check is results for Parents" << endl;
		results = stmtTable::isParent(ChangeStringToInt(P1), ChangeStringToInt(P2));
	}
	else if (clausesType == "Parent*") {
		cout << "check is results for Parents*" << endl;
		results = stmtTable::isParentStar(ChangeStringToInt(P1), ChangeStringToInt(P2));
	}
	else if (clausesType == "Next") {
		cout << "check is results for next" << endl;
		results = CFG::isNext(ChangeStringToInt(P1), ChangeStringToInt(P2));
	}
	else if (clausesType == "Next*") {
		results = CFG::isNext(ChangeStringToInt(P1), ChangeStringToInt(P2));
	}
	else if (clausesType == "Affects") {
		return results;
	}
	else if (clausesType == "Affects*") {
		return results;
	}
	else {
		return results;
	}
	return results;
}

string QueryEvaluator::GetStringType(char c) {
	cout << c << endl;
	if (c == 'c') {
		cout << "cont" << endl;
		return "CONSTANT";
	}
	else if (c == 'v') {
		cout << "getstringtype var" << endl;
		return "VAR";
	}
	else if (c == 'a') {
		cout << "getstringtype assignment" << endl;
		return "ASSIGN";
	}
	else if (c == 'p') {
		cout << "getstringtype proc" << endl;
		return "PROC";
	}
	else if (c == 'i') {
		cout << "getstringtype if" << endl;
		return "IF";
	}
	else if (c == 'w') {
		cout << "getstringtype while" << endl;
		return "WHILE";
	}
	else if (c == 'l') {
		cout << "getstringtype prog" << endl;
		return "STMT";
	}
	else if (c == 's') {
		cout << "getstringtype stmt" << endl;
		return "STMT";
	}
	else {
		return "";
	}
}
bool QueryEvaluator::CheckTempResultSize(vector<string> v) {
	if (v.size() == 0) {
		return false;
	}
	return true;
}

bool QueryEvaluator::GetResultsForNoClause(vector<pair<string, string> > SP)
{
	for (int i = 0; i < SP.size(); i++) {
		pair<string, string> pair = SP.at(i);
		string type = pair.second;
		cout << "type" << endl;
		vector<string> Result;
		if (type == "stmt") {
			cout << "is stmt" << endl;
			Result = GetAll('S');
		}
		else if (type == "while") {
			cout << "is while" << endl;
			Result = GetAll('W');
		}
		else if (type == "assign") {
			cout << "is assign" << endl;
			Result = GetAll('A');
		}
		else if (type == "if") {
			cout << "is if" << endl;
			Result = GetAll('I');
		}
		else if (type == "variable") {
			cout << "if variable" << endl;
			Result = GetAll('V');
		}
		else if (type == "constant") {
			cout << "constant" << endl;
			Result = GetAll('C');
		}
		else if (type == "procedure") {
			cout << "procedure" << endl;
			Result = GetAll('P');
		}
		else if (type == "prog_line") {
			cout << "prog_line" << endl;
			Result = GetAll('S');
		}
		else {
			cout << "nothing" << endl;
			Result = Result;
		}
		if (Result.size() == 0) {
			cout << "no answer for get select" << endl;
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

vector<string> QueryEvaluator::GetP2Blank(string clausesType) {
	vector<string> results;
	if (clausesType == "Follows") {
		return VarTable::getAllWithType("STMT", "");
		//return allstmt
	}
	else if (clausesType == "Follows*") {
		
		return VarTable::getAllWithType("STMT", "");
		//return allstmt
	}
	else if (clausesType == "Uses") {
		return VarTable::getAllWithType("VAR", "");
		//return variable
	}
	else if (clausesType == "Calls") {
		return ProcTable::getAllProcedures();
		//return all procedure
	}
	else if (clausesType == "Modifies") {
		return VarTable::getAllWithType("VAR", "");
		//return all procedure
	}
	else if (clausesType == "Parent") {
		return VarTable::getAllWithType("STMT", "");
		//return all stmt
	}
	else if (clausesType == "Parent*") {
		return VarTable::getAllWithType("STMT", "");
		//return all stmt
	}
	else if (clausesType == "Next") {
		return VarTable::getAllWithType("STMT", "");
		//return all prog_line
	}
	else if (clausesType == "Next*") {
		return VarTable::getAllWithType("STMT", "");
		//return all prog_line
	}
	else if (clausesType == "Affects") {
		return results;
		//return all assign
	}
	else if (clausesType == "Affects*") {
		return results;
		//return all assing
	}
	else {
		return results;
		//return nothing
	}
}

vector<string> QueryEvaluator::GetP1Blank(string clausesType) {
	vector<string> results;
	if (clausesType == "Follows") {
		return VarTable::getAllWithType("STMT", "");
		//return allstmt
	}
	else if (clausesType == "Follows*") {
		return VarTable::getAllWithType("STMT", "");
		//return allstmt
	}
	else if (clausesType == "Uses") {
		return VarTable::getAllWithType("VAR", "");
		//return variable
	}
	else if (clausesType == "Calls") {
		return ProcTable::getAllProcedures();
		//return all procedure
	}
	else if (clausesType == "Modifies") {
		return VarTable::getAllWithType("VAR", "");
		//return all procedure
	}
	else if (clausesType == "Parent") {
		return VarTable::getAllWithType("STMT", "");
		//return all stmt
	}
	else if (clausesType == "Parent*") {
		return VarTable::getAllWithType("STMT", "");
		//return all stmt
	}
	else if (clausesType == "Next") {
		return VarTable::getAllWithType("STMT", "");
		//return all prog_line
	}
	else if (clausesType == "Next*") {
		return VarTable::getAllWithType("STMT", "");
		//return all prog_line
	}
	else if (clausesType == "Affects") {
		return results;
		//return all assign
	}
	else if (clausesType == "Affects*") {
		return results;
		//return all assing
	}
	else {
		return results;
		//return nothing
	}
}
vector<string> QueryEvaluator::GetAllOfWithClause(string s) {

	vector<string> results;
	string type = QAS.GetSelectType(s);
	if (type == "procName") {
		cout << "get all procedure" << endl;
		return ProcTable::getAllProcedures();
	}
	else if (type == "varName") {
		cout << "get all variable" << endl;
		return VarTable::getAllWithType("VAR", "");

	}
	else if (type == "stmt#") {
		cout << "get all stmt" << endl;
		return VarTable::getAllWithType("STMT", "");
	}
	else if (type == "value") {
		cout << "get all constant" << endl;
		return ConstantTable::getAllConstantValues();
		//return ConstantTable::getAllConstantValues();
	}
	else {
		return results;
	}
}

void QueryEvaluator::clear()
{
	NoClause = false;
	SelectBool = false;
}

string QueryEvaluator::RemoveQuotations(string s) {

	size_t found = s.find("\"");
	if (found == string::npos) {
		return s;
	}
	else {
		s.erase(remove(s.begin(), s.end(), '\"'), s.end());
		return s;
	}
	return s;
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

pair<string, string> QueryEvaluator::SplitString(string s) {

	int pos = s.find(".");
	string name = s.substr(0, pos);
	string type = s.substr(pos + 1);
	return make_pair(type, name);
}

QueryEvaluator::QueryEvaluator()
{


}

QueryEvaluator::~QueryEvaluator()
{
}




