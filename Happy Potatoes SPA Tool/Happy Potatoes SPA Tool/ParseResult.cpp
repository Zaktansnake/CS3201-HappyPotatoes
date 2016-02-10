#include "ParseResult.h"
#include <iostream>
#include <fstream>
#include <sstream>

ParameterSet ParseResult::getSelectParameter() { return selectParameter_; }
ClauseSet ParseResult::getClauses() { return condClauses_; };
PatternSet ParseResult::getPatterns() { return patterns_; }
	
ParseResult::ParseResult() {}
ParseResult::ParseResult(ParameterSet selectParameter, ClauseSet condClauses, PatternSet patterns) {
	selectParameter_ = selectParameter;
	condClauses_ = condClauses;
	patterns_ = patterns;
}

vector<ParseResult> ParseResult::startQueryParsing() {
	ifstream infile;
	string filename = "test_PQL_parser.txt";
	infile.open(filename);
	vector<ParseResult> resultSet;
	while (!infile.eof) {
		string dummy, synonym, query;
		getline(infile, dummy); // skip the comment line
		getline(infile, synonym);
		getline(infile, query);
		resultSet.push_back(generateParseResult(synonym, query));
		getline(infile, dummy);
		getline(infile, dummy);
	}
	return resultSet;
}

ParseResult ParseResult::generateParseResult(string synonym, string query) {
	istringstream iss(synonym);
	vector<string> declaration;
	while (iss) {
		string word;
		iss >> word;
		declaration.push_back(word);
	}
	bool correct = checkDeclaration(declaration);
	if (!correct) return ParseResult();
	
}

bool ParseResult::checkDeclaration(vector<string> declaration) {
	for (int i = 0; i < declaration.size(); i++) {
		string current = declaration.at(i);
		char lastChar = current.back();
		if (lastChar != ',' || lastChar != ';') {
			if (current.compare("stmt") != 0 && current.compare("assign") != 0 && current.compare("while") != 0
				&& current.compare("variable") != 0 && current.compare("constant") != 0 
				&& current.compare("prog_line") != 0) {
				signalErrorAndStop();
				return false;
			}
		}
		// there must be another ',' or ';' at the back of next word if this word has a ',' at the back
		if (lastChar == ',') {
			string nextWord = declaration.at(i + 1);
			char nextLastChar = nextWord.back();
			if (nextLastChar != ',' || nextLastChar != ';') {
				signalErrorAndStop();
				return false;
			}
			nextWord = nextWord.substr(0, nextWord.size() - 1);
			if (nextWord.compare("stmt") == 0 || nextWord.compare("assign") == 0 || nextWord.compare("while") == 0
				|| nextWord.compare("variable") == 0 || nextWord.compare("constant") == 0
				|| nextWord.compare("prog_line") == 0 || nextWord.empty()) {
				signalErrorAndStop();
				return false;
			}

		}
	}
}

void ParseResult::signalErrorAndStop() {
	cout << "Syntax error, query will not be evaluated" << endl;
	return;
}