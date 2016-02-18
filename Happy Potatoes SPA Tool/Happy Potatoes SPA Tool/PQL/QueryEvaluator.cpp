#include "Header\QueryEvaluator.h"
#include <vector>
#include "Header\Clause.h"
#include <algorithm>
#include <iterator>
#include "../PKB/Header/PKB.h"
#include "Header\ParseResult.h"
#include <string>
#include <sstream>
#include "../PKB/Header/VarTable.h"
#include "../PKB/Header/StmtTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
vector<ParseResult> prv;
std::vector<std::string> resultVector;
std::string resultString;
//all the boolean results for all conditions in a single query will be stored here
std::vector<bool> BooleanClausesQueryResults;
//all the variable results for all conditions in a single query will be stored here
std::vector<std::vector<std::string>> VariableClausesQueryResults;
//all the procedure results for all conditions in a single query will be stored here
std::vector<std::vector<std::string>> ProcedureClausesQueryResults;
//all the stmtline results for all conditions in a single query will be stored here
std::vector<std::vector<int>> StmtLineClausesQueryResults;
//all the assignment results for all patterns
std::vector<std::vector<int>> PatternClausesQueryResults;
//the final string that is suppose to be printed
std::vector<std::string> finalStringVector;
void Intersection();
int noTuple = 1;

//function prototype makes code works dont ask me why =)
void PatternResults(std::vector<std::string>, Parameter1, Parameter2);
void UsesResults(std::vector<std::string>, Parameter1, Parameter2, std::string);
void FollowsResults(std::vector<std::string>, Parameter1, Parameter2, std::string);
void ModifiesResults(std::vector<std::string>, Parameter1, Parameter2, std::string);
std::string changeIntToString(int);
void StmtIntersection();
void ProcIntersection();
void VarIntersection();
void findBoolean();
std::string MakeFinalString(std::vector<std::string> SelectParameter);
//assess parseResultVector
void assessParseResult(vector<ParseResult> prv) {

	for (int resultIndex = 0; resultIndex < prv.size(); resultIndex++) {
		ParseResult pr = prv.at(resultIndex);
		BooleanClausesQueryResults.clear();
		//get vector of select parameter from parseResult object
		std::vector<std::string> SelectParameterVector = pr.getSelectParameter();
		//get vector of clauses object from parseResult object
		std::vector<Clause> ClausesVector = pr.getClauses();
		//get the vector of pattern queries
		std::vector<Pattern> PatternQueryVector = pr.getPatterns();

		for (int ClausesVectorIndex = 0; ClausesVectorIndex < ClausesVector.size(); ClausesVectorIndex++) {
			Clause clauses = ClausesVector.at(ClausesVectorIndex);
			std::string clausesOperation = clauses.getClauseOperation();
			int clausesSize = clausesOperation.size();
			char firstParameterType = clausesOperation.at(clausesSize - 2);
			char secondParameterType = clausesOperation.at(clausesSize - 1);
			std::string firstSecondParameterType = "";
			firstSecondParameterType = firstSecondParameterType + firstParameterType + secondParameterType;
			Parameter1 firstParameter = clauses.getFirstParameter();
			Parameter2 secondParameter = clauses.getSecondParameter();

			if (clausesOperation == "ModifiesS") {

				ModifiesResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
			}

			if (clausesOperation == "Uses") {
				UsesResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
				//
			}

			if (clausesOperation == "Follows") {

				FollowsResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
				//
			}

			if (clausesOperation == "Parent*") {

				ParentStarResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
			}

			if (clausesOperation == "Parent") {

				ParentResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
			}

			if (clausesOperation == "Follows*") {

			}

		}

		for (int index2 = 0; index2 < PatternQueryVector.size(); index2++) {
			std::string firstPatternParameter = PatternQueryVector.at(index2).getFirstParameter();
			std::string secondPatternParameter = PatternQueryVector.at(index2).getSecondParameter();
			std::string thridPatternParameter = PatternQueryVector.at(index2).getThirdParameter();
			PatternResults(SelectParameterVector, firstPatternParameter, secondPatternParameter);
		}
	}
}

void ParentStarResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {

	if (SelectParameterVector.at(0) == "Boolean") {

	}

}

void ParentResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {

	int firstPerimeterInt;
	int secondPerimeterInt;

	if (SelectParameterVector.at(0) == "boolean") {

		if ((!is_number(firstPerimeter)) && (!is_number(secondPerimeter))) {

		}
		if ((!is_number(firstPerimeter)) && (is_number(secondPerimeter))) {

		}
		if ((is_number(firstPerimeter)) && (!is_number(secondPerimeter))) {

		}
	}
	else {
		if ((is_number(firstPerimeter))) {
			StmtLineClausesQueryResults.push_back(getChild(changeStringToInt(firstPerimeter)));
		}

		if ((is_number(secondPerimeter))) {
			StmtLineClausesQueryResults.push_back(getParent(changeStringToInt(secondPerimeter)));
		}
	}
}

void PatternResults(std::vector<std::string> SelectParameterVector, std::string firstPerimeter,
	std::string secondPerimeter) {


	std::string SelectParameter = SelectParameterVector.at(noTuple);
	//if the selectparameter is a boolean
	if (SelectParameter == "Assignment") {
		StmtLineClausesQueryResults.push_back(getPattern(firstPerimeter, secondPerimeter));
	}
}

void UsesResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {
	//if there is no tuple	
	if (SelectParameterVector.size() == noTuple) {

		std::string SelectParameter = SelectParameterVector.at(noTuple);
		//if the selectparameter is a boolean
		if (SelectParameter == "Boolean") {
			BooleanClausesQueryResults.push_back(VarTable::isUsesBoolean(firstPerimeter, secondPerimeter));
		}
		//if the selectParameter is a variable and the first and second perimeter is stmt and variable 
		if ((SelectParameter == "Variable") && (firstSecondPerimeterType == "SV")) {
			VariableClausesQueryResults.push_back(VarTable::isUsesVariable(firstPerimeter));
		}
		//if the selectParameter is a variable and the first and second perimeter is proc and variable
		if ((SelectParameter == "Variable") && (firstSecondPerimeterType == "PV")) {
			VariableClausesQueryResults.push_back(VarTable::isUsesProcTable(firstPerimeter));
		}
		//if the selectParameter is a stmt
		if ((SelectParameter == "Stmt")) {
			StmtLineClausesQueryResults.push_back(VarTable::getUsesStmt(firstPerimeter));
		}
		if ((SelectParameter == "Assignment")) {
			StmtLineClausesQueryResults.push_back(VarTable::getUsesAssg(firstPerimeter));
		}
		//if the selectParameter is a proc
		if ((SelectParameter == "Proc")) {
			ProcedureClausesQueryResults.push_back(VarTable::getUsesProc(firstPerimeter));
		}
	}
	// if there are a tuple
	else {



	}

}


void FollowsResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {

	//if asking a stmt is following another stmt
	if (SelectParameterVector.at(0) == "Boolean") {
		StmtLineClausesQueryResults.push_back(isFollows(firstPerimeter, secondPerimeter));
	}
	//if querying for a stmt s such as for example follows(s,1),need to change
	if ((SelectParameterVector.at(0) == "Stmt") && (firstPerimeter.find("\""))) {
		StmtLineClausesQueryResults.push_back(getFollows(secondPerimeter));
	}
	//if querying for a stmt s such as for example follows(1,s),need to change
	if ((SelectParameterVector.at(0) == "Stmt") && (secondPerimeter.find("\""))) {
		StmtLineClausesQueryResults.push_back(getFollower(firstPerimeter));
	}
}


void ModifiesResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {

	if (SelectParameterVector.size() == 1) {

		if (SelectParameterVector.at(0) == "Boolean") {
			BooleanClausesQueryResults.push_back(VarTable::isModifiesBoolean(firstPerimeter, secondPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Variable") && (firstSecondPerimeterType == "PV")) {
			VariableClausesQueryResults.push_back(VarTable::getModifiesPV(firstPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Variable") && (firstSecondPerimeterType == "SV")) {
			VariableClausesQueryResults.push_back(VarTable::getModifiesVariable(firstPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Procedure")) {
			ProcedureClausesQueryResults.push_back(VarTable::getModifiesProc(firstPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Stmt")) {
			StmtLineClausesQueryResults.push_back(VarTable::getModifiesStmt(firstPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Assignment")) {
			StmtLineClausesQueryResults.push_back(VarTable::getModifiesAssg(firstPerimeter));
		}
	}
	else {

	}

}


bool is_number(std::string s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int changeStringToInt(std::string s) {

	int value = atoi(s.c_str());
}

void Intersection() {
	for (int index = 0; index < 4; index++) {
		if (index == 0) {
			StmtIntersection();
		}
		if (index == 1) {
			ProcIntersection();
		}
		if (index == 2) {
			VarIntersection();
		}
		if (index == 3) {
			findBoolean();
		}
	}
}

//find the intersection of all the list of stmtlist
void StmtIntersection() {

	if ((StmtLineClausesQueryResults.size() == 1) || (StmtLineClausesQueryResults.size() == 0)) {
		return;
	}
	vector<int> store;
	vector<int> toBeIntersect;
	vector<int> toBeIntersect2;
	for (int index = 1; index < StmtLineClausesQueryResults.size(); index++) {
		vector<int> toStore = vector<int>();
		if (index == 1) {
			toBeIntersect = StmtLineClausesQueryResults.at(0);
			toBeIntersect2 = StmtLineClausesQueryResults.at(1);
		}
		else {
			toBeIntersect = store;
			toBeIntersect2 = StmtLineClausesQueryResults.at(index);
		}
		if ((toBeIntersect.size() == 0) || (toBeIntersect2.size() == 0)) {
			StmtLineClausesQueryResults.clear();
			return;
		}
		vector<int> combineSize(toBeIntersect.size() + toBeIntersect2.size());
		vector<int>::iterator it;
		std::sort(toBeIntersect.begin(), toBeIntersect.begin() + toBeIntersect.size());
		std::sort(toBeIntersect2.begin(), toBeIntersect2.begin() + toBeIntersect2.size());
		it = std::set_intersection(toBeIntersect.begin(), toBeIntersect.begin() + toBeIntersect.size(),
			toBeIntersect2.begin(), toBeIntersect2.begin() + toBeIntersect2.size(), combineSize.begin());
		combineSize.resize(it - combineSize.begin());
		store = combineSize;
	}
	StmtLineClausesQueryResults.clear();
	StmtLineClausesQueryResults.push_back(store);
}

//find the intersection between the list of procedure list
void ProcIntersection() {

	if ((ProcedureClausesQueryResults.size() == 1) || (ProcedureClausesQueryResults.size() == 0)) {
		return;
	}
	vector<std::string> store;
	vector<std::string> toBeIntersect;
	vector<std::string> toBeIntersect2;
	for (int index = 1; index < ProcedureClausesQueryResults.size(); index++) {
		vector<int> toStore = vector<int>();
		if (index == 1) {
			toBeIntersect = ProcedureClausesQueryResults.at(0);
			toBeIntersect2 = ProcedureClausesQueryResults.at(1);
		}
		else {
			toBeIntersect = store;
			toBeIntersect2 = ProcedureClausesQueryResults.at(index);
		}
		if ((toBeIntersect.size() == 0) || (toBeIntersect2.size() == 0)) {
			ProcedureClausesQueryResults.clear();
			return;
		}
		vector<std::string> combineSize(toBeIntersect.size() + toBeIntersect2.size());
		vector<std::string>::iterator it;
		std::sort(toBeIntersect.begin(), toBeIntersect.begin() + toBeIntersect.size());
		std::sort(toBeIntersect2.begin(), toBeIntersect2.begin() + toBeIntersect2.size());
		it = std::set_intersection(toBeIntersect.begin(), toBeIntersect.begin() + toBeIntersect.size(),
			toBeIntersect2.begin(), toBeIntersect2.begin() + toBeIntersect2.size(), combineSize.begin());
		combineSize.resize(it - combineSize.begin());
		store = combineSize;
	}
	ProcedureClausesQueryResults.clear();
	ProcedureClausesQueryResults.push_back(store);
}

//find the intersection of the variable list
void VarIntersection() {

	if ((VariableClausesQueryResults.size() == 1) || (VariableClausesQueryResults.size() == 0)) {
		return;
	}
	vector<std::string> store;
	vector<std::string> toBeIntersect;
	vector<std::string> toBeIntersect2;
	for (int index = 1; index < VariableClausesQueryResults.size(); index++) {
		vector<int> toStore = vector<int>();
		if (index == 1) {
			toBeIntersect = VariableClausesQueryResults.at(0);
			toBeIntersect2 = VariableClausesQueryResults.at(1);
		}
		else {
			toBeIntersect = store;
			toBeIntersect2 = VariableClausesQueryResults.at(index);
		}
		if ((toBeIntersect.size() == 0) || (toBeIntersect2.size() == 0)) {
			VariableClausesQueryResults.clear();
			return;
		}
		vector<std::string> combineSize(toBeIntersect.size() + toBeIntersect2.size());
		vector<std::string>::iterator it;
		std::sort(toBeIntersect.begin(), toBeIntersect.begin() + toBeIntersect.size());
		std::sort(toBeIntersect2.begin(), toBeIntersect2.begin() + toBeIntersect2.size());
		it = std::set_intersection(toBeIntersect.begin(), toBeIntersect.begin() + toBeIntersect.size(),
			toBeIntersect2.begin(), toBeIntersect2.begin() + toBeIntersect2.size(), combineSize.begin());
		combineSize.resize(it - combineSize.begin());
		store = combineSize;
	}
	VariableClausesQueryResults.clear();
	VariableClausesQueryResults.push_back(store);
}

void findBoolean() {

	bool finalResults;
	for (int index = 0; index < BooleanClausesQueryResults.size(); index++) {
		finalResults = BooleanClausesQueryResults.at(index);
	}
	BooleanClausesQueryResults.clear();
	BooleanClausesQueryResults.push_back(finalResults);
}

//convert int to strint
std::string changeIntToString(int StmtList) {

	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << StmtList;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	return Result;
}

std::string MakeFinalString(std::vector<std::string> SelectParameter) {

	std::string stmtLine = "";
	std::string variables = "";
	std::vector<char> scat;
	if (SelectParameter.at(0) == "Boolean") {
		if (BooleanClausesQueryResults.at(0)) {
			return "true";
		}
		else {
			return "false";
		}
	}
	if (SelectParameter.at(0) == "Stmt") {
		for (int i = 0; i < StmtLineClausesQueryResults.at(0).size(); i++) {
			stmtLine = changeIntToString(StmtLineClausesQueryResults.at(0).at(i)) + " , ";
		}
		return stmtLine;
	}
	if (SelectParameter.at(0) == "Variable") {
		for (int j = 0; j < VariableClausesQueryResults.at(0).size(); j++) {
			variables = VariableClausesQueryResults.at(0).at(j) + " , ";
		}
		return variables;
	}


}


std::vector<std::string> QueryEvaluator::startEvaluator()
{
	ParseResult pr;
	prv = pr.startQueryParsing();
	assessParseResult(prv);
	return std::vector<std::string>();
}

QueryEvaluator::QueryEvaluator()
{


}



QueryEvaluator::~QueryEvaluator()
{
}





