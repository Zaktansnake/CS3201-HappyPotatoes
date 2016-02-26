#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

#include "./Header/QueryEvaluator.h"
#include "./Header/Pattern.h"
#include "./Header/Clause.h"
#include "./Header/ParseResult.h"
#include "../PKB/Header/PKB.h"
#include "../PKB/Header/VarTable.h"
#include "../PKB/Header/StmtTable.h"

using namespace std;

ParseResult pr;

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

//stmtTable st;
//VarTable vt;
PKB pkb;
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
void MakeFinalString(std::vector<std::string> SelectParameter);
std::string removeDoubleQuote(std::string s);
void ParentStarResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType);
bool is_number(std::string s);
int changeStringToInt(std::string s);
std::vector<int> getAllInFront(std::string firstPerimeter, std::string secondPerimeter);
bool checkIfFollowStar(std::string first, std::string second);
std::vector<int> combineList(std::vector<std::vector<int>> toCombine);
std::vector<std::vector<int>> findAllListOfChild(std::vector<int> v, std::vector<std::vector<int>> combine);
std::vector<int> getAllFollowers(std::string firstPerimeter, std::string secondPerimeter);
std::vector<int> getAllParent(std::vector<int> v);
void ParentResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType);
void FollowStarResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeter);
void assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector);
void setResultsPattern(PatternSet PatternQueryVector, std::vector<std::string> SelectParameterVector);
void stmtFinalString();
void ProcedureFinalString();
void variableFinalString();
//assess parseResultVector

vector<string> splitComma(string line);

void assessParseResult(ParseResult pr) {
	ProcedureClausesQueryResults.clear();
	BooleanClausesQueryResults.clear();
	VariableClausesQueryResults.clear();
	PatternClausesQueryResults.clear();
	StmtLineClausesQueryResults.clear();
	finalStringVector.clear();

	//get vector of select parameter from parseResult object
	std::vector<std::string> SelectParameterVector = pr.getSelectParameter();
	//get vector of clauses object from parseResult object
	std::vector<Clause> ClausesVector = pr.getClauses();
	//get the vector of pattern queries
	PatternSet PatternQueryVector = pr.getPatterns();
	assessClauses(ClausesVector, SelectParameterVector);
	setResultsPattern(PatternQueryVector, SelectParameterVector);
	MakeFinalString(SelectParameterVector);
}

void setResultsPattern(PatternSet PatternQueryVector, std::vector<std::string> SelectParameterVector) {
	std::string firstPatternParameter;
	std::string secondPatternParameter;
	std::string thridPatternParameter;

	if (PatternQueryVector.size() > 0) {
		firstPatternParameter = PatternQueryVector.at(0).getFirstParameter();
		secondPatternParameter = PatternQueryVector.at(0).getSecondParameter();
		thridPatternParameter = PatternQueryVector.at(0).getThirdParameter();
	}
	else {
		firstPatternParameter = "";
		secondPatternParameter = "";
		thridPatternParameter = "";
	}

	PatternResults(SelectParameterVector, firstPatternParameter, secondPatternParameter);
}

void assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector) {
	Clause clauses = ClausesVector.at(0);
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
			ParentStarResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
		}
		if (firstLetter == 'F') {
			FollowStarResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
		}
	}
	else {
		if (firstLetter == 'M') {
			ModifiesResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
		}
		if (firstLetter == 'F') {
			FollowsResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
		}
		if (firstLetter = 'U') {
			UsesResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
		}
		if (firstLetter = 'P') {
			ParentResults(SelectParameterVector, firstParameter, secondParameter, firstSecondParameterType);
		}
	}
}

void ParentStarResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {
	int firstPerimeterInt;
	int secondPerimeterInt;
	vector<int> temp;

	if (SelectParameterVector.at(0) == "BOOLEAN") {
		if ((!is_number(firstPerimeter)) && (!is_number(secondPerimeter))) {
			for (int index = 1; index < pkb.getStmtNum(); index++) {
				if (stmtTable::getParent(index).size() != 0) {
					BooleanClausesQueryResults.push_back(true);
					break;
				}
			}
			BooleanClausesQueryResults.push_back(false);
		}

		if ((!is_number(firstPerimeter)) && (is_number(secondPerimeter))) {
			if (stmtTable::getParent(changeStringToInt(secondPerimeter)).size() != 0) {
				BooleanClausesQueryResults.push_back(true);
			}
			else {
				BooleanClausesQueryResults.push_back(false);
			}
		}

		if ((is_number(firstPerimeter)) && (!is_number(secondPerimeter))) {
			if (stmtTable::getChild(changeStringToInt(firstPerimeter)).size() != 0) {
				BooleanClausesQueryResults.push_back(true);
			}
			else {
				BooleanClausesQueryResults.push_back(false);
			}
		}

		if ((is_number(firstPerimeter)) && (is_number(secondPerimeter))) {
		}
	}
	else {
		if ((is_number(firstPerimeter))) {
			std::vector<int> child = stmtTable::getChild(changeStringToInt(firstPerimeter));

			if (stmtTable::getChild(changeStringToInt(firstPerimeter)).size() == 0) {
				StmtLineClausesQueryResults.push_back(child);
			}
			else {
				std::vector<std::vector<int>> temp;
				std::vector<std::vector<int>> overAll = findAllListOfChild(child, temp);
				StmtLineClausesQueryResults.push_back(combineList(overAll));
			}
		}
		else {
			StmtLineClausesQueryResults.push_back(getAllParent(stmtTable::getParent(
				changeStringToInt(secondPerimeter))));
		}
	}
}

bool checkIfParentStar(std::string first, std::string second) {
	int firstInt = changeStringToInt(first);
	int secondInt = changeStringToInt(second);
	std::vector<int> temp = stmtTable::getParent(secondInt);

	if (temp.size() != 0) {
		if (temp.at(0) == firstInt) {
			return true;
		}
		else {
			while (temp.size() != 0) {
				if (temp.at(0) != firstInt) {
					temp = stmtTable::getParent(temp.at(0));
				}
				else {
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<int> getAllParent(std::vector<int> v) {
	vector<int> toReturn;

	while (v.size() != 0) {
		toReturn.push_back(v.at(0));
		v = stmtTable::getParent(v.at(0));
	}

	return toReturn;
}

std::vector<int> combineList(std::vector<std::vector<int>> toCombine) {
	std::vector<int> toReturn;

	for (int index = 0; index < toCombine.size(); index++) {
		for (int index2 = 0; index2 < toCombine.at(index).size(); index++) {
			toReturn.push_back(toCombine.at(index).at(index2));
		}
	}

	return toReturn;
}

std::vector<std::vector<int>> findAllListOfChild(std::vector<int> v, std::vector<std::vector<int>> combine) {
	if (v.size() == 0) {
		return combine;
	}
	else {
		for (int index = 0; index < v.size(); index++) {
			std::vector<std::vector<int>> temp = findAllListOfChild(stmtTable::getChild(v.at(index)), combine);

			for (int index2 = 0; index2 < temp.size(); index2++) {
				combine.push_back(temp.at(index2));
			}

			return combine;
		}
	}
}

void ParentResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {
	int firstPerimeterInt;
	int secondPerimeterInt;
	vector<int> temp;

	if (SelectParameterVector.at(0) == "BOOLEAN") {
		if ((!is_number(firstPerimeter)) && (!is_number(secondPerimeter))) {
			for (int index = 1; index < pkb.getStmtNum(); index++) {
				if (stmtTable::getParent(index).size() != 0) {
					BooleanClausesQueryResults.push_back(true);
					break;
				}
			}

			BooleanClausesQueryResults.push_back(false);
		}

		if ((!is_number(firstPerimeter)) && (is_number(secondPerimeter))) {
			if (stmtTable::getParent(changeStringToInt(secondPerimeter)).size() != 0) {
				BooleanClausesQueryResults.push_back(true);
			}
			else {
				BooleanClausesQueryResults.push_back(false);
			}
		}

		if ((is_number(firstPerimeter)) && (!is_number(secondPerimeter))) {
			if (stmtTable::getChild(changeStringToInt(firstPerimeter)).size() != 0) {
				BooleanClausesQueryResults.push_back(true);
			}
			else {
				BooleanClausesQueryResults.push_back(false);
			}
		}
	}
	else {
		if ((is_number(firstPerimeter))) {
			StmtLineClausesQueryResults.push_back(stmtTable::getChild(changeStringToInt(firstPerimeter)));
		}

		if ((is_number(secondPerimeter))) {
			StmtLineClausesQueryResults.push_back(stmtTable::getParent(changeStringToInt(secondPerimeter)));
		}
	}
}

void PatternResults(std::vector<std::string> SelectParameterVector, std::string firstPerimeter,
	std::string secondPerimeter) {
	vector<string> parameter = splitComma(SelectParameterVector.at(0));
	std::string SelectParameter = parameter.at(noTuple);

	//if the selectparameter is a boolean
	if (SelectParameter == "assign") {
		//StmtLineClausesQueryResults.push_back(Pattern::getPattern(firstPerimeter, secondPerimeter));
	}
	if (SelectParameter == "BOOLEAN") {
		//BooleanClausesQueryResults.push_back(Pattern::isttern(firstPerimeter, secondPerimeter));
	}
}

void UsesResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {
	vector<string> parameter = splitComma(SelectParameterVector.at(0));

	if (parameter.at(1) == "variable") {
		VariableClausesQueryResults.push_back(VarTable::getUsesVariable(removeDoubleQuote(firstPerimeter)));
	}
	if (parameter.at(1) == "proc") {
		ProcedureClausesQueryResults.push_back(VarTable::getUsesProc(removeDoubleQuote(secondPerimeter)));
	}
	if (parameter.at(1) == "assign") {
		StmtLineClausesQueryResults.push_back(VarTable::getUsesAssig(removeDoubleQuote(secondPerimeter)));
	}
	if (parameter.at(1) == "stmt") {
		StmtLineClausesQueryResults.push_back(VarTable::getUsesStmt(removeDoubleQuote(secondPerimeter)));
	}
	if (parameter.at(1) == "while") {
		StmtLineClausesQueryResults.push_back(VarTable::getUsesWhile(removeDoubleQuote(secondPerimeter)));
	}
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "pv")) {
		BooleanClausesQueryResults.push_back(VarTable::isUsesProc(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "av")) {
		BooleanClausesQueryResults.push_back(VarTable::isUsesAssign(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "sv")) {
		BooleanClausesQueryResults.push_back(VarTable::isUsesStmt(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "wv")) {
		BooleanClausesQueryResults.push_back(VarTable::isUsesWhile(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
}

void FollowsResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {
	vector<string> parameter = splitComma(SelectParameterVector.at(0));
	std::vector<int> temp;

	//if asking a stmt is following another stmt
	if (parameter.at(1) == "BOOLEAN") {
		BooleanClausesQueryResults.push_back(stmtTable::isFollow(changeStringToInt(firstPerimeter),
			changeStringToInt(secondPerimeter)));
	}

	//if querying for a stmt s such as for example follows(s,1),need to change
	if ((parameter.at(1) == "stmt") && (is_number(secondPerimeter))) {
		temp = stmtTable::getFollowFan(changeStringToInt(secondPerimeter));
		StmtLineClausesQueryResults.push_back(temp);
	}

	//if querying for a stmt s such as for example follows(1,s),need to change
	if ((parameter.at(1) == "stmt") && (is_number(firstPerimeter))) {
		temp = stmtTable::getFollow(changeStringToInt(firstPerimeter));
		StmtLineClausesQueryResults.push_back(temp);
	}

	if ((parameter.at(1) == "while") && (is_number(secondPerimeter))) {
		temp = stmtTable::getFollow(changeStringToInt(secondPerimeter));
		StmtLineClausesQueryResults.push_back(temp);
	}

	//if querying for a stmt s such as for example follows(1,s),need to change
	if ((parameter.at(1) == "while") && (is_number(firstPerimeter))) {
		temp = stmtTable::getFollowFan(changeStringToInt(firstPerimeter));
		StmtLineClausesQueryResults.push_back(temp);
	}

	if ((parameter.at(1) == "assign") && (is_number(secondPerimeter))) {
		temp = stmtTable::getFollow(changeStringToInt(secondPerimeter));
		StmtLineClausesQueryResults.push_back(temp);
	}

	//if querying for a stmt s such as for example follows(1,s),need to change
	if ((parameter.at(1) == "assign") && (is_number(firstPerimeter))) {
		temp = stmtTable::getFollowFan(changeStringToInt(firstPerimeter));
		StmtLineClausesQueryResults.push_back(temp);
	}
}

void FollowStarResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeter) {

	if (SelectParameterVector.at(0) == "BOOLEAN") {
		checkIfFollowStar(firstPerimeter, secondPerimeter);
	}

	if ((SelectParameterVector.at(0) == "stmt") && (is_number(firstPerimeter))) {
		getAllFollowers(firstPerimeter, secondPerimeter);
	}

	if ((SelectParameterVector.at(0) == "stmt") && (is_number(secondPerimeter))) {
		getAllInFront(firstPerimeter, secondPerimeter);
	}
}

std::vector<int> getAllInFront(std::string firstPerimeter, std::string secondPerimeter) {
	int firstInt = changeStringToInt(firstPerimeter);
	int secondInt = changeStringToInt(secondPerimeter);
	vector<int> temp;
	vector<int> getFollowFan = stmtTable::getFollowFan(secondInt);

	while (getFollowFan.size() != 0) {
		temp.push_back(getFollowFan.at(0));
		getFollowFan = stmtTable::getFollowFan(getFollowFan.at(0));
	}

	return temp;
}

std::vector<int> getAllFollowers(std::string firstPerimeter, std::string secondPerimeter) {
	int firstInt = changeStringToInt(firstPerimeter);
	int secondInt = changeStringToInt(secondPerimeter);
	vector<int> temp;
	vector<int> getFollow = stmtTable::getFollow(firstInt);

	while (getFollow.size() != 0) {
		temp.push_back(getFollow.at(0));
		getFollow = stmtTable::getFollow(getFollow.at(0));
	}

	return temp;
}

bool checkIfFollowStar(std::string first, std::string second) {
	int firstInt = changeStringToInt(first);
	int secondInt = changeStringToInt(second);
	std::vector<int> temp = stmtTable::getFollow(firstInt);

	if (temp.size() != 0) {
		if (temp.at(0) == secondInt) {
			return true;
		}
		else {
			while (temp.size() != 0) {
				if (temp.at(0) != secondInt) {
					temp = stmtTable::getFollow(temp.at(0));
				}
				else {
					return true;
				}
			}
		}
	}
	return false;
}

void ModifiesResults(std::vector<std::string> SelectParameterVector, Parameter1 firstPerimeter,
	Parameter2 secondPerimeter, std::string firstSecondPerimeterType) {
	vector<string> parameter = splitComma(SelectParameterVector.at(0));
	
	if (parameter.at(1) == "variable") {
		VariableClausesQueryResults.push_back(VarTable::getModifiesVariable(removeDoubleQuote(firstPerimeter)));
	}
	
	if (parameter.at(1) == "proc") {
		ProcedureClausesQueryResults.push_back(VarTable::getModifiesProc(removeDoubleQuote(secondPerimeter)));
	}
	
	if (parameter.at(1) == "assign") {
		StmtLineClausesQueryResults.push_back(VarTable::getModifiesAssign(removeDoubleQuote(secondPerimeter)));
	}
	
	if (parameter.at(1) == "stmt") {
		StmtLineClausesQueryResults.push_back(VarTable::getModifiesStmt(removeDoubleQuote(secondPerimeter)));
	}
	
	if (parameter.at(1) == "while") {
		StmtLineClausesQueryResults.push_back(VarTable::getModifiesWhile(removeDoubleQuote(secondPerimeter)));
	}
	
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "pv")) {
		BooleanClausesQueryResults.push_back(VarTable::isModifiesProc(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
	
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "av")) {
		BooleanClausesQueryResults.push_back(VarTable::isModifiesAssign(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
	
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "sv")) {
		BooleanClausesQueryResults.push_back(VarTable::isModifiesStmt(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
	
	if ((parameter.at(1) == "BOOLEAN") && (firstSecondPerimeterType == "wv")) {
		BooleanClausesQueryResults.push_back(VarTable::isModifiesWhile(removeDoubleQuote(firstPerimeter),
			removeDoubleQuote(secondPerimeter)));
	}
}

std::string removeDoubleQuote(std::string s) {
	/*if (!s.find("\"")) {
	return s;
	}
	else {
	return s.substr(1, s.size() - 2);
	}*/

	if (s.front() == '"') {
		s.erase(0, 1); // erase the first character
		s.erase(s.size() - 1); // erase the last character
		return s;
	}
	else {
		return s;
	}
}

bool is_number(std::string s) {
	std::string::const_iterator it = s.begin();

	while (it != s.end() && isdigit(*it)) {
		++it;
	}

	return !s.empty() && it == s.end();
}

int changeStringToInt(std::string s) {
	int value = atoi(s.c_str());
	return value;
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

		if (index != 1) {
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

		if (index != 1) {
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

		if (index != 1) {
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

void MakeFinalString(std::vector<std::string> SelectParameter) {
	vector<string> parameter = splitComma(SelectParameter.at(0));

	if (parameter.at(1) == "stmt") {
		stmtFinalString();
	}

	if (parameter.at(1) == "proc") {
		ProcedureFinalString();
	}

	if (parameter.at(1) == "while") {
		stmtFinalString();
	}

	if (parameter.at(1) == "assign") {
		stmtFinalString();
	}

	if (parameter.at(1) == "variable") {
		variableFinalString();
	}
}

void stmtFinalString() {
	if (StmtLineClausesQueryResults.size() == 0) {
		finalStringVector.clear();
		return;
	}
	else {
		vector<int> v = StmtLineClausesQueryResults.at(0);

		for (int i = 0; i < v.size(); i++) {
			finalStringVector.push_back(changeIntToString(v.at(i)));
		}
	}
}

void variableFinalString() {
	if (VariableClausesQueryResults.size() == 0) {
		finalStringVector.clear();
		return;
	}
	else {
		vector<std::string> v = VariableClausesQueryResults.at(0);

		for (int i = 0; i < v.size(); i++) {
			finalStringVector.push_back(v.at(i));
		}
	}
}

void ProcedureFinalString() {
	if (ProcedureClausesQueryResults.size() == 0) {
		finalStringVector.clear();
		return;
	}
	else {
		vector<std::string> v = ProcedureClausesQueryResults.at(0);

		for (int i = 0; i < v.size(); i++) {
			finalStringVector.push_back(v.at(i));
		}
	}
}

vector<string> QueryEvaluator::startEvaluator(ParseResult mustPr) {
	assessParseResult(mustPr);
	return finalStringVector;
}

QueryEvaluator::QueryEvaluator(){
}

QueryEvaluator::~QueryEvaluator() {
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