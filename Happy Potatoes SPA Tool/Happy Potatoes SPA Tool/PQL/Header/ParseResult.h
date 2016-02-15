#pragma once
#include <string>
#include <vector>
#include <unordered_map>
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
	ParseResult(ParameterSet, ClauseSet, PatternSet);
	// for query evaluator to call
	vector<ParseResult> startQueryParsing();
private:
	// helper functions
	ParseResult generateParseResult(string, string);
	bool checkDeclaration(vector<string>);
	void signalErrorAndStop();
	ParseResult checkAndParseQuery(unordered_map<string, string>, vector<string>);

	// attributes
	ParameterSet selectParameter_;
	ClauseSet condClauses_;
	PatternSet patterns_;
	
};