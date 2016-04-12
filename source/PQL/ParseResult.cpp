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

const string IDENT = "(?:[[:alpha:]](?:[[:alpha:]]|\\d|#)*)";
// IDENTWithStar is used to parse normal clauses because of Calls*, Parent*, Follows*, etc.
const string IDENTWithStar = "(?:[[:alpha:]](?:[[:alpha:]]|\\d|#|\\*)*)";
const string INTEGER = "(?:\\d+)";
// VAR is used during clause object construction
const string VAR = "\"" + IDENT + "\"";
const string space = "\\s*";
const string attrName = "(?:procName|varName|value|stmt#)";
const string attrRef = "(?:" + IDENT + "\\." + attrName + ")";
const string elem = "(?:" + IDENT + "|" + attrRef + ")";
const string TUPLE = "(?:" + elem + "|<" + space + elem + space + "(?:," + space + elem + space + ")*>)";
const string entRef = "(?:" + IDENT + "|_|" + "\"" + IDENT + "\"|" + INTEGER + ")";
// entRefWithStar is used to parse normal clauses because of Calls*, Parent*, Follows*, etc.
const string entRefWithStar = "(?:" + IDENTWithStar + "|_|" + "\"" + IDENT + "\"|" + INTEGER + ")";
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
const string AffectsT = "(?:Affects\\*" + space + "\\(" + space + stmtRef + space + "," + space + stmtRef + space + "\\))";
const string relRef = "(?:" + Modifies + "|" + Uses + "|" + Calls + "|" + CallsT + "|" + Affects + "|" + AffectsT + "|"
						+ Parent + "|" + ParentT + "|" + Follows + "|" + FollowsT + "|" + Next + "|" + NextT + ")";
const string relCond = "(?:" + relRef + space + "(?:and" + space + relRef + space + ")*)";

const string NAME = "(?:[[:alpha:]](?:[[:alpha:]]|\\d)*)";
const string expr = "(?:\\(?(?:" + NAME + "|" + INTEGER + ")" + space + "(?:(?:\\+|\\*)" + space + "\\(?(?:" + NAME + "|" + INTEGER + ")\\)?" + space + ")*)";
const string expressionSpec = "(?:\"" + space + expr + space + "\"|_\"" + space + expr + space + "\"_)";
// this regex string is used to cater to assign pattern parsing on top of normal word parsing
const string patternEntRef = "(?:" + IDENT + "|_|\\(|\\)|\"|\\+|-|\\*|" + "\"" + IDENT + "\"|" + INTEGER + ")";

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
const string suchthatOnly = space + relRef + space;
const string patternOnly = space + patternCl + space;
const string selectClause = space + "Select" + space + resultCl + space + "(?:" + suchthatCl + "|" + withCl + "|" + patternCl + space + ")*";

const regex declarationChecking(declar);
const regex declarationParsing(declarPar);
const regex declarationWordParsing(IDENT);

const regex queryChecking(selectClause);
const regex queryParseSelect(selectOnly);
const regex queryParseNormalClauses(suchthatOnly);
const regex queryParsePattern(patternOnly);

const regex queryWordParsingSelect(IDENT);
const regex queryWordParsingNormalClause(entRefWithStar);
const regex queryWordParsingPattern(patternEntRef);

ParseResult ParseResult::generateParseResult(string declarationSentence, string querySentence) {
	unordered_map<string, string> declarationTable;
	bool correct = ParseResult::checkAndParseDeclaration(declarationSentence, declarationTable);
	cout << "I am here" << endl;
	if (!correct) {
		cout << "I am here 1" << endl;
		return ParseResult();
	}
	cout << "I am here 2" << endl;
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
	next = sregex_iterator(selectPhrase.begin(), selectPhrase.end(), queryWordParsingSelect);
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

ClauseSet ParseResult::parseNormalClauses(string query, unordered_map<string, string>& declarationTable) {
	vector<string> normalClausePhrase;
	sregex_iterator next(query.begin(), query.end(), queryParseNormalClauses);
	sregex_iterator end;
	while (next != end) {
		smatch match = *next;
		normalClausePhrase.push_back(match.str(0));
		next++;
	}

	vector<string> word;
	vector<string>::iterator it1;
	ClauseSet normalClauses;
	ClauseSet zeroSynonyms;
	ClauseSet oneSynonym;
	ClauseSet twoSynonyms;

	for (it1 = normalClausePhrase.begin(); it1 != normalClausePhrase.end(); ++it1) {
		string currentPhrase = *it1;
		next = sregex_iterator(currentPhrase.begin(), currentPhrase.end(), queryWordParsingNormalClause);
		while (next != end) {
			smatch match = *next;
			word.push_back(match.str(0));
			next++;
		}

		string clauseType;
		string firstParam;
		string secondParam;
		string current;
		string firstPType;
		string secondPType;
		vector<string>::iterator it;
		int counter = 0;

		for (it = word.begin(); it != word.end(); it++) {
			current = *it;
			if (*it == "Modifies" || *it == "Uses" || *it == "Calls" || *it == "Calls*" || *it == "Parent" ||
				*it == "Parent*" || *it == "Follows" || *it == "Follows*" || *it == "Next" || *it == "Next*" ||
				*it == "Affects" || *it == "Affects*") {
				clauseType = current;
				counter++;
			}
			// current iterator points to a variable
			else if (current.front() == '"' && current.back() == '"') {
				// the variable is the first parameter
				if (*prev(it) == "Modifies" || *prev(it) == "Uses" || *prev(it) == "Calls" || *prev(it) == "Calls*" || *prev(it) == "Parent" ||
					*prev(it) == "Parent*" || *prev(it) == "Follows" || *prev(it) == "Follows*" || *prev(it) == "Next" || *prev(it) == "Next*" ||
					*prev(it) == "Affects" || *prev(it) == "Affects*") {
					firstParam = current;
					string type = *prev(it);
					if (type == "Modifies" || type == "Uses" || type == "Calls" || type == "Calls*") {
						firstPType = "p";
						counter++;
					}
					else {	//grammar error as Parent|Follows|Next|Affects cannot have variable
						ClauseSet c;
						c.push_back(Clause("dummy", "dummy", "dummy"));
						return c;
					}
				}
				else {	// the variable is the second parameter
					secondParam = current;
					string type = *prev(prev(it));
					if (type == "Modifies" || type == "Uses") {
						secondPType = "v";
						counter++;
					}
					else if (type == "Calls" || type == "Calls*") {
						secondPType = "p";
						counter++;
					}
					else {	//grammar error
						ClauseSet c;
						c.push_back(Clause("dummy", "dummy", "dummy"));
						return c;
					}
				}
			}
			// current iterator points to a non-variable
			else {
				// the non-variable is a constant
				if (regex_match(current, regex(INTEGER))) {
					// the constant is the first parameter
					if (*prev(it) == "Modifies" || *prev(it) == "Uses" || *prev(it) == "Calls" || *prev(it) == "Calls*" || *prev(it) == "Parent" ||
						*prev(it) == "Parent*" || *prev(it) == "Follows" || *prev(it) == "Follows*" || *prev(it) == "Next" || *prev(it) == "Next*" ||
						*prev(it) == "Affects" || *prev(it) == "Affects*") {
						firstParam = current;
						string type = *prev(it);
						if (type == "Modifies" || type == "Uses" || type == "Parent" || type == "Parent*" || type == "Follows" ||
							type == "Follows*" || type == "Next" || type == "Next*" || type == "Affects" || type == "Affects*") {
							firstPType = "s";
							counter++;
						}
						else {	// grammar error as Calls cannot have integer as parameter
							ClauseSet c;
							c.push_back(Clause("dummy", "dummy", "dummy"));
							return c;
						}
					}
					else {	// the digit is the second parameter
						secondParam = current;
						string type = *prev(prev(it));
						if (type == "Modifies" || type == "Uses" || type == "Calls" || type == "Calls*") {
							// grammar error as Modifies|Uses|Calls cannot have second parameter as integer
							ClauseSet c;
							c.push_back(Clause("dummy", "dummy", "dummy"));
							return c;
						}
						else {
							secondPType = "s";
							counter++;
						}
					}
				}
				// the non-variable is a underscore
				else if (current == "_") {
					if (*prev(it) == "Modifies" || *prev(it) == "Uses" || *prev(it) == "Calls" || *prev(it) == "Calls*" || *prev(it) == "Parent" ||
						*prev(it) == "Parent*" || *prev(it) == "Follows" || *prev(it) == "Follows*" || *prev(it) == "Next" || *prev(it) == "Next*" ||
						*prev(it) == "Affects" || *prev(it) == "Affects*") {
						// the underscore is the first parameter
						firstParam = current;
						string type = *prev(it);
						if (type == "Calls" || type == "Calls*") {
							firstPType = "p";
							counter++;
						}
						else if (type == "Parent" || type == "Parent*" || type == "Follows" || type == "Follows*" || type == "Next" ||
							type == "Next*" || type == "Affects" || type == "Affects*") {
							firstPType = "s";
							counter++;
						}
						else {	// grammar error due to ambiguity
							ClauseSet c;
							c.push_back(Clause("dummy", "dummy", "dummy"));
							return c;
						}
					}
					else {	// the underscore is the second parameter
						secondParam = current;
						string type = *prev(prev(it));
						if (type == "Modifies" || type == "Uses") {
							secondPType = "v";
							counter++;
						}
						else if (type == "Calls" || type == "Calls*") {
							secondPType = "p";
							counter++;
						}
						else {
							secondPType = "s";
							counter++;
						}
					}
				}
				// the non-variable is a synonym
				else {
					// the synonym was not declared
					if (declarationTable[current] == "") {
						ClauseSet c;
						c.push_back(Clause("dummy", "dummy", "dummy"));
						return c;
					}
					else {	// the synonym was declared
						if (*prev(it) == "Modifies" || *prev(it) == "Uses" || *prev(it) == "Calls" || *prev(it) == "Calls*" || *prev(it) == "Parent" ||
							*prev(it) == "Parent*" || *prev(it) == "Follows" || *prev(it) == "Follows*" || *prev(it) == "Next" || *prev(it) == "Next*" ||
							*prev(it) == "Affects" || *prev(it) == "Affects*") {
							// the synonym is the first parameter
							firstParam = current;
							firstPType = declarationTable[current];
							string type = *prev(it);
							if (type == "Modifies" || type == "Uses") {
								// type error because first parameter of Modifies|Uses cannot be a variable type
								if (firstPType == "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else if (type == "Calls" || type == "Calls*") {
								// type error because first parameter of Calls can only be a procedure
								if (firstPType != "procedure") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else {
								// type error because for relationships between statements synonym type cannot be procedure or variable
								if (firstPType == "procedure" || firstPType == "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							counter++;
							// shortening firstPType for abbr
							if (firstPType == "prog_line") {
								firstPType = "l";
							}
							else {
								firstPType = firstPType.substr(0, 1);
							}
						}
						else {
							// the synonym is the second parameter
							secondParam = current;
							secondPType = declarationTable[current];
							string type = *prev(prev(it));
							if (type == "Modifies" || type == "Uses") {
								// type error because second parameter of Modifies|Uses can only be a variable type
								if (secondPType != "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else if (type == "Calls" || type == "Calls*") {
								// type error because second parameter of Calls can only be a procedure
								if (secondPType != "procedure") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else {
								// type error because for relationships between statements, synonym type cannot be procedure or variable
								if (secondPType == "procedure" || secondPType == "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							counter++;
							// shortening secondPType for abbr
							if (secondPType == "prog_line") {
								secondPType = "l";
							}
							else {
								secondPType = secondPType.substr(0, 1);
							}
						}
					}
				}
			}

			// a clause object is ready to be constructed
			if (counter == 3) {
				// append abbr to clauseType
				clauseType += firstPType + secondPType;
				if (regex_match(firstParam, regex(INTEGER)) || regex_match(firstParam, regex(VAR))) {
					// both the first and second parameter are non-synonyms
					if (regex_match(secondParam, regex(INTEGER)) || regex_match(secondParam, regex(VAR))) {
						zeroSynonyms.push_back(Clause(clauseType, firstParam, secondParam));
					}
					else {	// only the first parameter is not a synonym
						oneSynonym.push_back(Clause(clauseType, firstParam, secondParam));
					}
				}
				else {
					// only the second parameter is not a synonym
					if (regex_match(secondParam, regex(INTEGER)) || regex_match(secondParam, regex(VAR))) {
						oneSynonym.push_back(Clause(clauseType, firstParam, secondParam));
					}
					else {	// both parameters are synonyms
						twoSynonyms.push_back(Clause(clauseType, firstParam, secondParam));
					}
				}
			}
		}
		word.clear();
	}

	// concat all ClauseSets into one ClauseSet
	normalClauses.reserve(zeroSynonyms.size() + oneSynonym.size() + twoSynonyms.size());
	normalClauses.insert(normalClauses.end(), zeroSynonyms.begin(), zeroSynonyms.end());
	normalClauses.insert(normalClauses.end(), oneSynonym.begin(), oneSynonym.end());
	normalClauses.insert(normalClauses.end(), twoSynonyms.begin(), twoSynonyms.end());
	return normalClauses;
}

PatternSet ParseResult::parsePattern(string query, unordered_map<string, string>& declarationTable) {
	vector<string> patternClausePhrase;
	sregex_iterator next(query.begin(), query.end(), queryParsePattern);
	sregex_iterator end;
	while (next != end) {
		smatch match = *next;
		patternClausePhrase.push_back(match.str(0));
		next++;
	}

	vector<string> word;
	vector<string>::iterator it1;
	PatternSet patterns;
	PatternSet ifAndWhilePattern;
	PatternSet assignPattern;

	for (it1 = patternClausePhrase.begin(); it1 != patternClausePhrase.end(); ++it1) {
		string currentPhrase = *it1;
		next = sregex_iterator(currentPhrase.begin(), currentPhrase.end(), queryWordParsingPattern);
		while (next != end) {
			smatch match = *next;
			word.push_back(match.str(0));
			next++;
		}

		string patternType;
		string firstParam;
		string secondParam;
		string thirdParam;
		string current;
		string patternTypeTemp;
		vector<string>::iterator it;
		// due to the special pattern clause syntax, this bool is used to make sure that hashmap is used only when needed
		bool needCheckType = false;

		for (it = word.begin(); it != word.end(); ++it) {
			current = *it;
			if (current == "pattern") {
				needCheckType = true;
				continue;
			}
			if (needCheckType) {
				string underCheck = declarationTable[current];
				if (underCheck != "assign" && underCheck != "while" && underCheck != "if") {
					// synonym type is wrong according to PQL grammar
					PatternSet p;
					p.push_back(Pattern("dummy", "dummy", "dummy"));
					return p;
				}
				else {
					patternType = current + "," + underCheck;
					patternTypeTemp = underCheck;
					needCheckType = false;
					continue;
				}
			}
			else {	// current string is inside bracket
				if (patternTypeTemp == "if") {
					firstParam = current;
					// the first parameter is a synonym
					if (firstParam.front() != '"' && firstParam.back() != '"') {
						// the synonym is not declared
						if (declarationTable[firstParam] == "") {
							PatternSet p;
							p.push_back(Pattern("dummy", "dummy", "dummy"));
							return p;
						}
					}
					secondParam = "_";
					thirdParam = "_";
					ifAndWhilePattern.push_back(Pattern(patternType, firstParam, secondParam, thirdParam));
					++it; ++it;	// advance the iterator to the next pattern clause
				}
				else if (patternTypeTemp == "while") {
					firstParam = current;
					// the first parameter is a synonym
					if (firstParam.front() != '"' && firstParam.back() != '"') {
						// the synonym is not declared
						if (declarationTable[firstParam] == "") {
							PatternSet p;
							p.push_back(Pattern("dummy", "dummy", "dummy"));
							return p;
						}
					}
					secondParam = "_";
					ifAndWhilePattern.push_back(Pattern(patternType, firstParam, secondParam));
					++it;	// advance the iterator to the next pattern clause
				}
				else { // the pattern is of type assign
					firstParam = current;
					// the first parameter is a synonym
					if (firstParam.front() != '"' && firstParam.back() != '"') {
						// the synonym is not declared
						if (declarationTable[firstParam] == "") {
							PatternSet p;
							p.push_back(Pattern("dummy", "dummy", "dummy"));
							return p;
						}
					}
					++it;
					secondParam.clear();
					while (*it != "pattern") {
						current = *it;
						secondParam += current;
						++it;
					}
					--it;	// reverse one time so that the for loop that uses it will not be affected
					assignPattern.push_back(Pattern(patternType, firstParam, secondParam));
				}
			}
		}
	}
	// concat all PatternSets into one PatternSet
	patterns.reserve(ifAndWhilePattern.size() + assignPattern.size());
	patterns.insert(patterns.end(), ifAndWhilePattern.begin(), ifAndWhilePattern.end());
	patterns.insert(patterns.end(), assignPattern.begin(), assignPattern.end());
	return patterns;
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
		cout << "signal" << endl;

		return ParseResult();
	}

	selectParameter = ParseResult::parseSelect(query, declarationTable);
	if (selectParameter.empty()) return ParseResult();
	cout << "line662" << endl;
	clauses = ParseResult::parseNormalClauses(query, declarationTable);
	cout << "line664" << endl;
	// if normal clauses contain grammar error, return empty ParseResult
	if (clauses.front().getClauseOperation() == "dummy") {
		signalErrorAndStop();
		cout << "signal2" << endl;
		return ParseResult();
	}



	/* withClauses = ParseResult::parseWith(query, declarationTable);
	if (withClauses.front().getLeftOfEqualSign == "dummy") {
		signalErrorAndStop();
		return ParseResult();
	} */
	cout << "I am here 3" << endl;
	// if every component in ParseResult object is syntactically and grammatically correct
	return ParseResult(selectParameter, clauses, patterns, withClauses);
}

void ParseResult::signalErrorAndStop() {
	cout << "Grammar error, query will not be evaluated" << endl;
	return;
}