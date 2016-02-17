#include "Header\QueryEvaluator.h"
#include <vector>
#include "Header\Clause.h"
#include <algorithm>
#include <iterator>
#include "../PKB/Header/PKB.h"
#include "Header\ParseResult.h"
#include <string>

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
PKB pkb = new PKB();
int noTuple = 1;

//assess parseResultVector
void assessParseResult(vector<parseResult> prv) {

	for (int resultIndex = 0; resultIndex < prv.size(); resultIndex++) {
		parseResult pr = prv.at(resultIndex);
		BooleanClausesQueryResults.clear();
		//get vector of select parameter from parseResult object
		std::vector<std::string> SelectParameterVector = pr.getSelectParameter();
		//get vector of clauses object from parseResult object
		std::vector<Clause> ClausesVector = pr.getClauses();
		for (int ClausesVectorIndex = 0; ClausesVectorIndex < ClausesVector.size(); ClausesVectorIndex++) {
			Clause clauses = ClausesVector.at(ClausesVectorIndex);
			std::string clausesOperation = clauses.getClausesOperation();
			int clausesSize = clausesOperation.size();
			char firstLetter = clausesOperation.at(0);
			char firstPerimeterType = clausesOperation.at(clausesSize - 2);
			char secondPerimeterType = clausesOperation.at(clausesSize - 1);
			std::string firstSecondPerimeterType = "";
			firstSecondPerimeterType = firstSecondPerimeterType + firstPerimeterType + secondPerimeterType;
			std::string firstPerimeter = clauses.getFirstPerimeter();
			std::string secondPerimeter = clauses.getSecondPerimeter();
			if (firstLetter == 'M') {

				ModifiesResults(SelectParameterVector, firstPerimeter, secondPerimeter, firstSecondPerimeterType);
			}
			if (firstLetter == 'U') {
				UsesResults(SelectParameterVector, firstPerimeter, secondPerimeter, firstSecondPerimeterType);
				//
			}

			if (firstLetter == 'F') {
				FollowsResults(SelectParameterVector, firstPerimeter, secondPerimeter, firstSecondPerimeterType);
				//
			}

		}
	}
}




void UsesResults(std::vector<std::string> SelectParameterVector, std::string firstPerimeter,
	std::string secondPerimeter, std::string firstSecondPerimeterType) {
	//if there is no tuple	
	if (SelectParameterVector.size() == noTuple) {

		std::string SelectParameter = SelectParameterVector.at(noTuple);
		//if the selectparameter is a boolean
		if (SelectParameter == "Boolean") {
			BooleanClausesQueryResults.push_back(PKB.isUses(firstPerimeter, secondPerimeter));
		}
		//if the selectParameter is a variable and the first and second perimeter is stmt and variable 
		if ((SelectParameter == "Variable") && (firstSecondPerimeterType == "SV")) {
			VariableClausesQueryResults.push_back(PKB.isUses(firstPerimeter));
		}
		//if the selectParameter is a variable and the first and second perimeter is proc and variable
		if ((SelectParameter == "Variable") && (firstSecondPerimeterType == "PV")) {
			VariableClausesQueryResults.push_back(PKB.isUses(firstPerimeter));
		}
		//if the selectParameter is a stmt
		if ((SelectParameter == "Stmt")) {
			StmtLineClausesQueryResults.push_back(PKB.isUses(firstPerimeter));
		}
		//if the selectParameter is a proc
		if ((SelectParameter == "Proc")) {
			ProcedureClausesQueryResults.push_back(PKB.isUses(firstPerimeter));
		}
	}
	// if there are a tuple
	else {



	}

}

void FollowsResults(std::vector<std::string> SelectParameterVector, std::string firstPerimeter,
	std::string secondPerimeter, std::string firstSecondPerimeterType) {


	if (SelectParameterVector.size() == 0) {
		//if asking a stmt is following another stmt
		if (SelectParameterVector.at(0) == "Boolean") {
			StmtLineClausesQueryResults.push_back(PKB.isFollows(firstPerimeter, secondPerimeter));
		}
		//if querying for a stmt s such as for example follows(s,1);
		if ((SelectParameterVector.at(0) == "Stmt") && (firstPerimeter.find("\""))) {
			StmtLineClausesQueryResults.push_back(PKB.getFollower(secondPerimeter));
		}
		//if querying for a stmt s such as for example follows(1,s)
		if ((SelectParameterVector.at(0) == "Stmt") && (secondPerimeter.find("\""))) {
			StmtLineClausesQueryResults.push_back(PKB.getFollower(firstPerimeter));
		}
		else {
			//get the stmt that 

		}
	}
	else {

	}


}

void ModifiesResults(std::vector<std::string> SelectParameterVector, std::string firstPerimeter,
	std::string secondPerimeter, std::string firstSecondPerimeterType) {

	if (SelectParameterVector.size == 1) {

		if (SelectParameterVector.at(0) == "Boolean") {
			BooleanClausesQueryResults.push_back(PKB.isModifies(firstPerimeter, secondPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Variable") && (firstSecondPerimeterType == "PV")) {
			VariableClausesQueryResults.push_back(PKB.getModifies(firstPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Variable") && (firstSecondPerimeterType == "SV")) {
			VariableClausesQueryResults.push_back(PKB.getModifies(firstPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Procedure") && (firstSecondPerimeterType == "PV")) {
			ProcedureClausesQueryResults.push_back(PKB.getModifies(firstPerimeter));
		}
		if ((SelectParameterVector.at(0) == "Stmt") && (firstSecondPerimeterType == "SV")) {
			ProcedureClausesQueryResults.push_back(PKB.getModifies(firstPerimeter));
		}
	}
	else {

	}



}

void findingIntersection() {

}


std::vector<std::string> QueryEvaluator::startEvaluator()
{
	PQLparser PQLparser = new PQLparser();
	prv = PQLparser.startQueryParsing();
	assessParseResult(prv);
	return std::vector<std::string>();
}

QueryEvaluator::QueryEvaluator()
{


}



QueryEvaluator::~QueryEvaluator()
{
}






