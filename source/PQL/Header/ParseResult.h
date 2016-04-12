#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Clause.h"
#include "Pattern.h"
#include "With.h"

using namespace std;
typedef vector<string> ParameterSet;
typedef vector<Clause> ClauseSet;
typedef vector<Pattern> PatternSet;
typedef vector<With> WithSet;

class ParseResult {
public:
	// getters
	ParameterSet getSelectParameter(); 
	ClauseSet getClauses();
	PatternSet getPatterns();
	WithSet getWithClauses();

	// constructors
	ParseResult();
	ParseResult(ParameterSet);
	ParseResult(ParameterSet, ClauseSet);
	ParseResult(ParameterSet, ClauseSet, WithSet);
	ParseResult(ParameterSet, PatternSet);
	ParseResult(ParameterSet, ClauseSet, PatternSet);
	ParseResult(ParameterSet, ClauseSet, PatternSet, WithSet);

	// originally private but made public for unit test
	static bool checkAndParseDeclaration(string, unordered_map<string, string>&);
	static ParseResult checkAndParseQuery(string, unordered_map<string, string>&);
	static bool checkWholeQuery(string query);
	static ParameterSet parseSelect(string, unordered_map<string, string>&);
	static ClauseSet parseNormalClauses(string, unordered_map<string, string>&);
	static PatternSet parsePattern(string, unordered_map<string, string>&);
	static WithSet parseWith(string, unordered_map<string, string>&);

	// constructs the parsing result for query evaluator
	static ParseResult generateParseResult(string, string);

private:
	// helper functions
	static void signalErrorAndStop();
	
	// attributes
	ParameterSet selectParameter_;
	ClauseSet condClauses_;
	PatternSet patterns_;
	WithSet withClauses_;
};