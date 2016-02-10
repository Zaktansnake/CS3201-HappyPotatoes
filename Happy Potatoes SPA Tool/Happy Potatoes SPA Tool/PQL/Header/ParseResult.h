#pragma once
#include <string>
#include <vector>
#include "Clause.h"
#include "PatternClause.h"

using namespace std;
typedef vector<string> ParameterSet;
typedef vector<Clause> ClauseSet;
typedef vector<PatternClause> PatternSet;

class ParseResult {
public:
	// getters
	ParameterSet getSelectParameter(); 
	ClauseSet getClauses();
	PatternSet getPatterns();
	// constructors
	ParseResult();
	ParseResult(ParameterSet selectParameter, ClauseSet condClauses, PatternSet patterns);
	// for query evaluator to call
	vector<ParseResult> startQueryParsing();
	// helper functions
	ParseResult generateParseResult(string assignment, string query);
	bool checkDeclaration(vector<string> declaration);
	void signalErrorAndStop();
private:
	ParameterSet selectParameter_;
	ClauseSet condClauses_;
	PatternSet patterns_;
};