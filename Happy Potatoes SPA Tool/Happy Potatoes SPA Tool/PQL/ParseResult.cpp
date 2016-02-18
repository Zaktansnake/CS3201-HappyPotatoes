#include "../PQL/Header/ParseResult.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

// class implementations
ParameterSet ParseResult::getSelectParameter() { return selectParameter_; }
ClauseSet ParseResult::getClauses() { return condClauses_; };
PatternSet ParseResult::getPatterns() { return patterns_; }

ParseResult::ParseResult() {}
ParseResult::ParseResult(ParameterSet selectParameter) {
	selectParameter_ = selectParameter;
}
ParseResult::ParseResult(ParameterSet selectParameter, ClauseSet condClauses) {
	selectParameter_ = selectParameter;
	condClauses_ = condClauses;
}
ParseResult::ParseResult(ParameterSet selectParameter, PatternSet patterns) {
	selectParameter_ = selectParameter;
	patterns_ = patterns;
}
ParseResult::ParseResult(ParameterSet selectParameter, ClauseSet condClauses, PatternSet patterns) {
	selectParameter_ = selectParameter;
	condClauses_ = condClauses;
	patterns_ = patterns;
}

// constants for project iteration 1
const string selectClause = "Select\\s+(\\w+\\d*#*)\\s+";
const string conditionClause = "(such\\s+that\\s+(Follows|Follows\\*|Parent|Parent\\*|Modifies|Uses)\\s*\\(\\s*(\\d+|\\w+\\d*#*|_)\\s*,\\s*(\"\\w+\\d*#*\"|\\w+\\d*#*|_)\\s*\\)\\s*)?";
const string patternClause = "((pattern)\\s+(\\w+\\d*#*)\\s*\\(\\s*(\"\\w+\\d*#*\"|\\w+\\d*#*|_)\\s*,\\s*(_\"\\w+\\d*\"_|_|_\"\\d+\"_)\\s*\\)\\s*)?";

const regex declarationRegex("(\\s*(stmt|assign|while|variable|constant|prog_line)\\s+(\\w+\\d*#*\\s*,\\s*)*(\\w+\\d*#*\\s*;\\s*)+)+");
const regex queryRegex1(selectClause + conditionClause + patternClause);
const regex queryRegex2(selectClause + patternClause + conditionClause);

// hashmap for storing declarations
unordered_map<string, string> declarationTable;
// read file according to the standard required
/* vector<ParseResult> ParseResult::startQueryParsing() {
	ifstream infile;
	string filename = "test_PQL_parser.txt";
	infile.open(filename);
	vector<ParseResult> resultSet;
	while (!infile.eof()) {
		string dummy, synonym, query;
		getline(infile, dummy); // skip the comment line
		getline(infile, synonym);
		getline(infile, query);
		resultSet.push_back(generateParseResult(synonym, query));
		getline(infile, dummy); // skip the expected results line
		getline(infile, dummy); // skip the time limit line
	}
	return resultSet;
} */

ParseResult ParseResult::generateParseResult(string declarationSentence, string querySentence) {
	bool correct = checkAndParseDeclaration(declarationSentence);
	if (!correct) return ParseResult();
	return checkAndParseQuery(querySentence);
}

bool ParseResult::checkAndParseDeclaration(string declaration) {
	declarationTable.clear();
	if (!regex_match(declaration, declarationRegex)) {
		signalErrorAndStop();
		return false;	// declaration with syntax error
	}
	// store the correct declaration in a vector
	istringstream iss(declaration);
	vector<string> decWord;
	while (iss) {
		string word;
		iss >> word;
		decWord.push_back(word);
	}
	// populate the hashmap
	string synType;
	for (int i = 0; i < decWord.size()-1; i++) {
		string current = decWord.at(i);
		char lastChar = current.back();
		if (lastChar != ',' || lastChar != ';') {
			if (current=="stmt" || current=="assign" || current=="while" ||
				current=="variable" || current=="constant" || current=="prog_line") {
				synType = current;
			}
			else declarationTable[current] = synType;
		}
		else {
			current = current.substr(0, current.size() - 1);
			declarationTable[current] = synType;
		}
	}
	return true;
}

ParseResult ParseResult::checkAndParseQuery(string query) {
	smatch sm;
	if (!regex_match(query, sm, queryRegex1) && !regex_match(query, sm, queryRegex2)) {
		signalErrorAndStop();
		return ParseResult();
	} 
	// param required for a complete ParseResult object
	ParameterSet selectPSet;
	ClauseSet clauseSet;
	PatternSet patternSet;
	
	string checker;
	checker = sm[1];	// parameter of "Select"
	if (declarationTable[checker] == "") {
		signalErrorAndStop();
		return ParseResult();
	}
	string selectT = declarationTable[sm[1]];
	string selectP = sm[1];
	selectPSet.push_back(selectP+","+selectT);
	
	string conditionT, conditionP1, conditionP2, appendP1, appendP2;
	string patternT, patternP1, patternP2, patternP3;
	checker = sm[3];
	// "such that" comes first
	if (regex_match(query, sm, queryRegex1)) {
		conditionT = checker;
		checker = sm[4];
		if ((declarationTable[checker] == "" && !regex_match(checker, regex("\\d+"))) ||
			declarationTable[checker] == "variable") {
			signalErrorAndStop();	// the 1st param of a condition clause cannot be a variable
			return ParseResult();
		}
		else {
			conditionP1 = checker;
			appendP1 = declarationTable[checker];
		}
		checker = sm[5];
		if (conditionT == "Uses" || conditionT == "Modifies") {
			if (declarationTable[checker] != "variable" && checker.front() != '"') {
				signalErrorAndStop();	// the 2nd param of a Uses/Modifies clause must be a variable
				return ParseResult();
			}
			else {
				conditionP2 = checker;
				appendP2 = "v";
			}
		}
		else {	// case: the 2nd param is not of a Uses/Modifies clause
			if (declarationTable[checker] == "variable" || checker.front() == '"') {
				signalErrorAndStop();	// the 2nd param must not be a variable
				return ParseResult();
			}
			else {
				conditionP2 = checker;
				appendP2 = declarationTable[checker];
			}
		}
		// change the string according to agreed format
		conditionT += appendP1.substr(0, 1) + appendP2.substr(0, 1);
		clauseSet.push_back(Clause(conditionT, conditionP1, conditionP2));
		checker = sm[7];
		if (checker.empty()) return ParseResult(selectPSet, clauseSet);
		else {	// there is pattern clause following
			checker = sm[8];
			PatternType patternT = checker;
			Parameter1 patternP1 = sm[9];
			Parameter2 patternP2 = sm[10];
			patternSet.push_back(Pattern(patternT,patternP1,patternP2));
			return ParseResult(selectPSet, clauseSet, patternSet);
		}
	}
	// "pattern" comes first
	else if (regex_match(query, sm, queryRegex2)) {
		checker = sm[4];
		PatternType patternT = checker;
		Parameter1 patternP1 = sm[5];
		Parameter2 patternP2 = sm[6];
		patternSet.push_back(Pattern(patternT, patternP1, patternP2));
		checker = sm[8];
		if (checker.empty()) return ParseResult(selectPSet, patternSet);
		else {
			conditionT = checker;
			checker = sm[9];
			if ((declarationTable[checker] == "" && !regex_match(checker, regex("\\d+"))) 
				|| declarationTable[checker] == "variable") {
				signalErrorAndStop();
				return ParseResult();
			}
			else {
				conditionP1 = checker;
				appendP1 = declarationTable[checker];
			}
			checker = sm[10];
			if (conditionT == "Uses" || conditionT == "Modifies") {
				if (declarationTable[checker] != "variable" && checker.front() != '"') {
					signalErrorAndStop();
					return ParseResult();
				}
				else {
					conditionP2 = checker;
					appendP2 = "v";
				}
			}
			else {
				if (declarationTable[checker] == "variable" || checker.front() == '"') {
					signalErrorAndStop();
					return ParseResult();
				}
				else {
					conditionP2 = checker;
					appendP2 = declarationTable[checker];
				}
			}
			conditionT += appendP1.substr(0, 1) + appendP2.substr(0, 1);
			clauseSet.push_back(Clause(conditionT, conditionP1, conditionP2));
			return ParseResult(selectPSet, clauseSet, patternSet);
		}
	}
	// has only select clause
	else return ParseResult(selectPSet);
}

void ParseResult::signalErrorAndStop() {
	cout << "Grammar error, query will not be evaluated" << endl;
	return;
}