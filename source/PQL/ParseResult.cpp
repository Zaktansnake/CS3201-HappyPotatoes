#include "./Header/ParseResult.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

// class implementations
ParameterSet ParseResult::getSelectParameter() {
	return selectParameter_;
}
ClauseSet ParseResult::getClauses() {
	return condClauses_;
};
PatternSet ParseResult::getPatterns() {
	return patterns_;
}
WithSet ParseResult::getWithClauses() {
	return withClauses_;
}

ParseResult::ParseResult() {
}
ParseResult::ParseResult(ParameterSet selectParameter) {
	selectParameter_ = selectParameter;
}
ParseResult::ParseResult(ParameterSet selectParameter, ClauseSet condClauses) {
	selectParameter_ = selectParameter;
	condClauses_ = condClauses;
}
ParseResult::ParseResult(ParameterSet selectParameter, ClauseSet condClauses, WithSet withClauses) {
	selectParameter_ = selectParameter;
	condClauses_ = condClauses;
	withClauses_ = withClauses;
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
ParseResult::ParseResult(ParameterSet selectParameter, ClauseSet condClauses, PatternSet patterns, WithSet withClauses) {
	selectParameter_ = selectParameter;
	condClauses_ = condClauses;
	patterns_ = patterns;
	withClauses_ = withClauses;
}

// constants for project iteration 1
const string IDENT = "(?:[[:alpha:]](?:[[:alpha:]]|\\d|#)*)";
const string INTEGER = "(?:\\d+)";
const string space = "\\s*";
const string attrName = "(?:procName|varName|value|stmt#)";
const string attrRef = "(?:" + IDENT + "\\." + attrName + ")";
const string elem = "(?:" + IDENT + "|" + attrRef + ")";
const string TUPLE = "(?:" + elem + "|<" + space + elem + space + "(?:," + space + elem + space + ")*>)";
const string entRef = "(?:" + IDENT + "|_|" + "\"" + IDENT + "\"|" + INTEGER + ")";
const string stmtRef = "(?:" + IDENT + "|_|" + INTEGER + ")";
const string lineRef = stmtRef;
const string designEntity = "(?:procedure|stmt|assign|call|while|if|variable|constant|prog_line)";
const string declar = "(?:" + space + designEntity + space + IDENT + space + "(?:," + space + IDENT + space + ")*" + ";)*";
// the next single regex string is for faster parsing of declaration
const string declarPar = "(?:" + space + designEntity + space + IDENT + space + "(?:," + space + IDENT + space + ")*" + ";)";

const string REF = "(?:" + attrRef + "|" + IDENT + "|\"" + IDENT + "\"|" + INTEGER + ")";
const string attrCompare = "(?:" + REF + space + "=" + space + REF + ")";
const string attrCond = "(?:" + attrCompare + space + "(?:and" + space + attrCompare + space + ")*)";
const string varRef = "(?:" + IDENT + "|_|\"" + IDENT + "\")";

const string Modifies = "(?:Modifies" + space + "\\(" + space + entRef + space + "," + space + varRef + space + "\\))";
const string Uses = "(?:Uses" + space + "\\(" + space + entRef + space + "," + space + varRef + space + "\\))";
const string Calls = "(?:Calls" + space + "\\(" + space + entRef + space + "," + space + entRef + space + "\\))";
const string CallsT = "(?:Calls\\*" + space + "\\(" + space + entRef + space + "," + space + entRef + space + "\\))";
const string Parent = "(?:Parent" + space + "\\(" + space + stmtRef + space + "," + space + stmtRef + space + "\\))";
const string ParentT = "(?:Parent\\*" + space + "\\(" + space + stmtRef + space + "," + space + stmtRef + space + "\\))";
const string Follows = "(?:Follows" + space + "\\(" + space + stmtRef + space + "," + space + stmtRef + space + "\\))";
const string FollowsT = "(?:Follows\\*" + space + "\\(" + space + stmtRef + space + "," + space + stmtRef + space + "\\))";
const string Next = "(?:Next" + space + "\\(" + space + lineRef + space + "," + space + lineRef + space + "\\))";
const string NextT = "(?:Next\\*" + space + "\\(" + space + lineRef + space + "," + space + lineRef + space + "\\))";
const string Affects = "(?:Affects" + space + "\\(" + space + stmtRef + space + "," + space + stmtRef + space + "\\))";
const string AffectsT = "(?:Affects*" + space + "\\(" + space + stmtRef + space + "," + space + stmtRef + space + "\\))";
const string relRef = "(?:" + Modifies + "|" + Uses + "|" + Calls + "|" + CallsT + "|" + Affects + "|" + AffectsT + "|"
						+ Parent + "|" + ParentT + "|" + Follows + "|" + FollowsT + "|" + Next + "|" + NextT + ")";
const string relCond = "(?:" + relRef + space + "(?:and" + space + relRef + space + ")*)";

const string NAME = "(?:[[:alpha:]](?:[[:alpha:]]|\\d)*)";
const string expr = "(?:\\(?(?:" + NAME + "|" + INTEGER + ")" + space + "(?:(?:\\+|\\*)" + space + "\\(?(?:" + NAME + "|" + INTEGER + ")\\)?" + space + ")*)";
const string expressionSpec = "(?:\"" + space + expr + space + "\"|_\"" + space + expr + space + "\"_)";

const string IF = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "_" + space + "," + space + "_" + space + "\\))";
const string WHILE = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "_" + space + "\\))";
const string assign = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "(?:" + expressionSpec + "|" + "_)" + space + "\\))";
const string pattern = "(?:" + assign + "|" + WHILE + "|" + IF + ")";
const string patternCond = "(?:" + pattern + space + "(?:and" + space + pattern + space + ")*)";

const string withCl = "(?:with" + space + attrCond + ")";
const string suchthatCl = "(?:such that" + space + relCond + ")";
const string patternCl = "(?:pattern" + space + patternCond + ")";

const string resultCl = "(?:" + TUPLE + "|BOOLEAN)";
const string selectOnly = space + "Select" + space + resultCl + space;
const string selectClause = space + "Select" + space + resultCl + space + "(?:" + suchthatCl + "|" + withCl + "|" + patternCl + space + ")*";

const regex declarationChecking(declar);
const regex declarationParsing(declarPar);
const regex declarationWordParsing(IDENT);

const regex queryChecking(selectClause);
const regex queryParseSelect(selectOnly);
const regex queryWordParsing(entRef);
const regex queryPatternParsing(expressionSpec);

ParseResult ParseResult::generateParseResult(string declarationSentence, string querySentence) {
	unordered_map<string, string> declarationTable;
	bool correct = ParseResult::checkAndParseDeclaration(declarationSentence, declarationTable);

	if (!correct) {
		return ParseResult();
	}

	return ParseResult::checkAndParseQuery(querySentence, declarationTable);
}

bool ParseResult::checkAndParseDeclaration(string declaration, unordered_map<string, string>& declarationTable) {
	declarationTable.clear();
	if (!regex_match(declaration, declarationChecking)) {
		signalErrorAndStop();
		return false;	// declaration with syntax error
	}

	vector<string> sentence;
	string declarationSubstr;

	sregex_iterator next(declaration.begin(), declaration.end(), declarationParsing);
	sregex_iterator end;
	while (next != end) {
		smatch match = *next;
		sentence.push_back(match.str(0));
		next++;
	}

	vector<string>::iterator it;
	for (it = sentence.begin(); it != sentence.end(); ++it) {
		string current = *it;
		sregex_iterator next(current.begin(), current.end(), declarationWordParsing);
		sregex_iterator end;
		string type;
		bool typeSelected = false;
		while (next != end) {
			smatch match = *next;
			string word = match.str(0);
			if (word == "stmt" || word == "assign" || word == "while" || word == "variable"
				|| word == "constant" || word == "prog_line") {
				if (!typeSelected) {
					type = word;
					typeSelected = true;
				}
				else {
					signalErrorAndStop();
					return false;
				}
			}
			// the word being checked is not a keyword
			else {
				if (declarationTable[word] != "") {	// the synonym has already been used
					signalErrorAndStop();
					return false;
				}
				declarationTable[word] = type;
			}
			next++;
		}
		typeSelected = false;
	}

	return true;
}

ParameterSet ParseResult::parseSelect(string query, unordered_map<string, string>& declarationTable) {
	ParameterSet selectParameter;
	string selectPhrase;	// stores query words
	sregex_iterator next(query.begin(), query.end(), queryParseSelect);
	sregex_iterator end;
	smatch match = *next;
	selectPhrase = match.str(0);

	vector<string> word;
	next = sregex_iterator(selectPhrase.begin(), selectPhrase.end(), queryWordParsing);
	while (next != end) {
		smatch match = *next;
		next++;
		if (match.str(0) == "Select") continue;
		word.push_back(match.str(0));
	}
	vector<string>::iterator it;
	for (it = word.begin(); it != word.end(); ++it) {
		if ((*it == "procName" || *it == "varName" || *it == "value" || *it == "stmt#") && it != word.begin()) {
			*(prev(it)) += "." + *it;
			*it = "dummy";
		}
		else {
			// the synonym is not declared
			if (declarationTable[*it] == "") {
				signalErrorAndStop();
				return ParameterSet();
			}
			// if the current word is a synonym, check whether the next word is an attrName
			else if (it != prev(word.end()) && (*std::next(it) == "procName" || *std::next(it) == "varName" ||
				*std::next(it) == "value" || *std::next(it) == "stmt#")) {
				continue;	// the next word is an attrName then we dont append ","+type to the current synonym
			}
			else *it += "," + declarationTable[*it];
		}
	}

	for (it = word.begin(); it != word.end(); ++it) {
		if (*it == "dummy") continue;
		selectParameter.push_back(*it);
	}

	return selectParameter;
}

bool ParseResult::checkWholeQuery(string query) {
	// query with syntax error
	if (!regex_match(query, queryChecking)) return false;
	else return true;
}

ParseResult ParseResult::checkAndParseQuery(string query, unordered_map<string, string>& declarationTable) {
	ParameterSet selectParameter;
	ClauseSet clauses;
	PatternSet patterns;
	WithSet withClauses;

	bool correct = ParseResult::checkWholeQuery(query);
	if (!correct) {
		signalErrorAndStop();
		return ParseResult();
	}

	selectParameter = ParseResult::parseSelect(query, declarationTable);
	if (selectParameter.empty()) return ParseResult();
}

void ParseResult::signalErrorAndStop() {
	cout << "Grammar error, query will not be evaluated" << endl;
	return;
}