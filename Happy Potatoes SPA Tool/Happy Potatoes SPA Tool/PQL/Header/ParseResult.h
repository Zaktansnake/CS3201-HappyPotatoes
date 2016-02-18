#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Clause.h"
#include "../Header/Pattern.h";

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
	// originally private but made public for unit test
	bool checkAndParseDeclaration(string);
	ParseResult checkAndParseQuery(string);
	ParseResult generateParseResult(string, string);
	void signalErrorAndStop();
private:
	// helper functions
	
	
	// attributes
	ParameterSet selectParameter_;
	ClauseSet condClauses_;
	PatternSet patterns_;
};