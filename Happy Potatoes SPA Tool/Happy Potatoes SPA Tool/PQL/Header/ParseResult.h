#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Clause.h"
#include "Pattern.h"

using namespace std;
typedef vector<string> ParameterSet;
typedef vector<Clause> ClauseSet;
typedef vector<Pattern> PatternSet;

class ParseResult {
public:
	// getters
	ParameterSet getSelectParameter(); 
	ClauseSet getClauses();
	PatternSet getPatterns();
	// constructors
	ParseResult();
	ParseResult(ParameterSet);
	ParseResult(ParameterSet, ClauseSet);
	ParseResult(ParameterSet, PatternSet);
	ParseResult(ParameterSet, ClauseSet, PatternSet);
	// for query evaluator to call
	vector<ParseResult> startQueryParsing();
private:
	// helper functions
	ParseResult generateParseResult(string, string);
	bool checkAndParseDeclaration(string);
	void signalErrorAndStop();
	ParseResult checkAndParseQuery(string);

	// attributes
	ParameterSet selectParameter_;
	ClauseSet condClauses_;
	PatternSet patterns_;
	
};