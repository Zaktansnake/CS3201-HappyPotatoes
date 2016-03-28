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
const string IDENT = "(?:\\w(?:\\w|\\d|#)*)";
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

const string NAME = "(?:\\w(?:\\w|\\d)*)";
const string expr = "(?:\\(?(?:" + NAME + "|" + INTEGER + ")" + space + "(?:(?:\\+|\\*)" + space + "\\(?(?:" + NAME + "|" + INTEGER + ")\\)?" + space + ")*)";
const string expressionSpec = "(?:\"" + space + expr + space + "\"|_\"" + space + expr + space + "\"_)";

const string IF = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "_" + space +
"," + space + "_" + space + "\\))";
const string WHILE = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "_" + space + "\\))";
const string assign = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "(?:" + expressionSpec + "|" + "_)" + space + "\\))";
const string pattern = "(?:" + assign + "|" + WHILE + "|" + IF + ")";
const string patternCond = "(?:" + pattern + space + "(?:and" + space + pattern + space + ")*)";

const string withCl = "(?:with" + space + attrCond + ")";
const string suchthatCl = "(?:such that" + space + relCond + ")";
const string patternCl = "(?:pattern" + space + patternCond + ")";

const string resultCl = "(?:" + TUPLE + "|BOOLEAN)";
const string selectClause = space + "Select" + space + resultCl + space +
"(?:" + suchthatCl + "|" + withCl + "|" + patternCl + space + ")*";

const regex declarationChecking(declar);
const regex declarationParsing(IDENT);
const regex queryChecking(selectClause);
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
	vector<string> word;
	string declarationSubstr;

	while (!declaration.empty()) {
		int endIndex = declaration.find(";");
		int startIndex = endIndex + 1;
		declarationSubstr = declaration.substr(0, endIndex + 1);
		declaration = declaration.substr(startIndex, declaration.size() - startIndex);
		sregex_iterator next(declarationSubstr.begin(), declarationSubstr.end(), declarationParsing);
		sregex_iterator end;
		while (next != end) {
			smatch match = *next;
			word.push_back(match.str(0));
			next++;
		}
	}
	string type;
	for (vector<string>::iterator it = word.begin(); it != word.end(); ++it) {
		if (*it == "stmt" || *it == "assign" || *it == "while" || *it == "variable"
			|| *it == "constant" || *it == "prog_line") {
			type = *it;
		}
		else declarationTable[*it] = type;
	}
	return true;
}

ParseResult ParseResult::checkAndParseQuery(string query, unordered_map<string, string>& declarationTable) {
	smatch sm;

	if (!regex_match(query,queryChecking)) {
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
	selectPSet.push_back(selectP + "," + selectT);

	string conditionT, conditionP1, conditionP2, appendP1, appendP2;
	string patternT, patternP1, patternP2, patternP3;
	checker = sm[3];

	// "such that" comes first
	if (regex_match(query, queryChecking)) {
		conditionT = checker;
		checker = sm[4];

		if ((declarationTable[checker] == "" && !regex_match(checker, regex("\\d+"))) ||
			declarationTable[checker] == "variable") {
			signalErrorAndStop();	// the 1st param of a condition clause cannot be a variable
			return ParseResult();
		}
		else {
			conditionP1 = checker;
			if (regex_match(conditionP1, regex("\\d+"))) appendP1 = "s";
			else appendP1 = declarationTable[checker];
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
				if (regex_match(conditionP2, regex("\\d+"))) appendP2 = "s";
				else appendP2 = declarationTable[checker];
			}
		}

		// change the string according to agreed format
		conditionT += appendP1.substr(0, 1) + appendP2.substr(0, 1);
		clauseSet.push_back(Clause(conditionT, conditionP1, conditionP2));
		checker = sm[7];

		if (checker.empty()) {
			return ParseResult(selectPSet, clauseSet);
		}
		else {	// there is pattern clause following
			checker = sm[8];
			PatternType patternT = checker;
			if (declarationTable[patternT] == "") return ParseResult();
			Parameter1 patternP1 = sm[9];
			Parameter2 patternP2 = sm[10];
			patternSet.push_back(Pattern(patternT, patternP1, patternP2));
			return ParseResult(selectPSet, clauseSet, patternSet);
		}
	}
	// "pattern" comes first
	else if (regex_match(query, queryChecking)) {
		checker = sm[4];
		PatternType patternT = checker;

		if (declarationTable[patternT] == "") {
			return ParseResult();
		}

		Parameter1 patternP1 = sm[5];
		Parameter2 patternP2 = sm[6];
		patternSet.push_back(Pattern(patternT, patternP1, patternP2));
		checker = sm[8];

		// only pattern clause is present
		if (checker.empty()) {
			return ParseResult(selectPSet, patternSet);
		}
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
				if (regex_match(conditionP1, regex("\\d+"))) appendP1 = "s";
				else appendP1 = declarationTable[checker];
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
					if (regex_match(conditionP2, regex("\\d+"))) appendP2 = "s";
					else appendP2 = declarationTable[checker];
				}
			}

			conditionT += appendP1.substr(0, 1) + appendP2.substr(0, 1);
			clauseSet.push_back(Clause(conditionT, conditionP1, conditionP2));
			return ParseResult(selectPSet, clauseSet, patternSet);
		}
	}
	// has only select clause
	else {
		return ParseResult(selectPSet);
	}
}

void ParseResult::signalErrorAndStop() {
	cout << "Grammar error, query will not be evaluated" << endl;
	return;
}