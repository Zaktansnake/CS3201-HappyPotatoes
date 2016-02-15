#include "../PQL/Header/ParseResult.h"
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

const string queryTable[4][3] = { {"Modifies", "statement | assignment | if | while | procedure | call", "variable"},
							{"Uses", "statement | assignment | if | while | procedure | call", "variable"},
							{"Follows", "statement | assignment | if | while | procedure | call", 
							"statement | assignment | if | while | procedure | call"}, 
							{"Pattern a", "variable", "expression"} };

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
		getline(infile, dummy); // skip the expected results line
		getline(infile, dummy); // skip the time limit line
	}
	return resultSet;
}

ParseResult ParseResult::generateParseResult(string declarationSentence, string querySentence) {
	istringstream iss(declarationSentence);
	vector<string> declarationWord;
	while (iss) {
		string word;
		iss >> word;
		declarationWord.push_back(word);
	}
	bool correct = checkDeclaration(declarationWord);
	if (!correct) return ParseResult();
	unordered_map<string, string> declarationTable;
	vector<string>::iterator it;
	string synType;
	for (it = declarationWord.begin(); it != declarationWord.end(); ++it) {
		string current = *it;
		char lastChar = current.back();
		if (lastChar != ',' && lastChar != ';') {
			synType = current;
		}
		string synonym = current.substr(0, current.size() - 1);
		declarationTable[synonym] = synType;
	}
	istringstream iss(querySentence);
	vector<string> queryWord;
	while (iss) {
		string word;
		iss >> word;
		queryWord.push_back(word);
	}
	return checkAndParseQuery(declarationTable,queryWord);
	/*tasks left:
	- build query table using array[][]
	- check declaration function
	- check query function
	*/
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
	return true;
}

ParseResult ParseResult::checkAndParseQuery(unordered_map<string, string> decTable, vector<string> query) {
	string selectParameter, clauseType, cparam1, cparam2, patternType, pparam1, pparam2, pparam3;
	if (query[0] != "Select") {
		signalErrorAndStop();
		return ParseResult();
	}
	for (int i = 1; i < query.size()-3; i++) {
		// if current word is not a keyword
		if (query[i]!="such" && query[i] != "that" && query[i] != "with" && query[i] != "pattern" && query[i] != "and") {
			// if current word is not a declared synonym and not a variable
			if (decTable[query[i]] == "" || (query[i].at(0)!='"' && query[i].back()!='"')) {
				signalErrorAndStop();
				return ParseResult();
			}
			// if the previous word is Select
			else if (query[i - 1] == "Select") selectParameter = query[i];
			else if (query[i - 1] == "that") {
				if (query[i] == "Modifies") {
				}
			}
		}
	}
}

void ParseResult::signalErrorAndStop() {
	cout << "Grammar error, query will not be evaluated" << endl;
	return;
}