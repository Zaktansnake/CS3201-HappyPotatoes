
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


using namespace std;

QueriesAnswerStorage QAS;

bool assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector,
	PatternSet PS, vector<With> WithClauses) {
	
	//---- do the with clauses first-------

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
	if (HasResults == true) {
		return QAS.MergeResults();
	}
	else {
		return NoResults;
	}
}

bool QueryEvaluator::Follows(string, string, string, string, bool, string, string)
{
	return false;
}

bool QueryEvaluator::Modifies(string, string, string, string, bool, string, string)
{
	return false;
}

bool QueryEvaluator::FollowsStar(string, string, string, string, bool, string, string)
{
	return false;
}

bool QueryEvaluator::Next(string, string, string, string, bool, string, string)
{
	return false;
}

bool QueryEvaluator::NextStar(string, string, string, string, bool, string, string)
{
	return false;
}

bool QueryEvaluator::Parents(string, string, string, string, bool, string, string)
{
	return false;
}

bool QueryEvaluator::ParentsStar(string, string, string, string, bool, string, string)
{
	return false;
}

bool QueryEvaluator::Uses(string, string, string, string, bool, string, string)
{
	return false;
}

QueryEvaluator::QueryEvaluator()
{


}



QueryEvaluator::~QueryEvaluator()
{
}





