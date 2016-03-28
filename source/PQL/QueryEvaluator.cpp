
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

void assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector,
	PatternSet PS, vector<With> WithClauses) {
	for (int i = 0; i < ClausesVector.size(); i++) {

		vector<int> temp;
		vector<char> tempString;
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
void assessParseResult(ParseResult pr) {

	std::vector<std::string> SelectParameterVector = pr.getSelectParameter();
	std::vector<Clause> ClausesVector = pr.getClauses();
	PatternSet PatternQueryVector = pr.getPatterns();
	std::vector<With> WithClauses = pr.getWithClauses();
	assessClauses(ClausesVector, SelectParameterVector,PatternQueryVector,WithClauses);
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

	assessParseResult(mustPr);
	return QAS.MergeResults();

}

QueryEvaluator::QueryEvaluator()
{


}



QueryEvaluator::~QueryEvaluator()
{
}





