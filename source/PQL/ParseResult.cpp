#include "./Header/ParseResult.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

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
const string IDENTWithStar = "(?:[[:alpha:]](?:[[:alpha:]]|\\d|#|\\*)*)";
const string INTEGER = "(?:\\d+)";
const string VAR = "\"" + IDENT + "\"";
const string space = "\\s*";
const string attrName = "(?:procName|varName|value|stmt#)";
const string attrRef = "(?:" + IDENT + "\\." + attrName + ")";
const string elem = "(?:" + IDENT + "|" + attrRef + ")";
const string TUPLE = "(?:" + elem + "|<" + space + elem + space + "(?:," + space + elem + space + ")*>)";
const string entRef = "(?:" + IDENT + "|_|" + "\"" + IDENT + "\"|" + INTEGER + ")";
const string entRefWithStar = "(?:" + IDENTWithStar + "|_|" + "\"" + IDENT + "\"|" + INTEGER + ")";
const string stmtRef = "(?:" + IDENT + "|_|" + INTEGER + ")";
const string lineRef = stmtRef;
const string designEntity = "(?:procedure|stmt|assign|while|if|variable|constant|prog_line)";
const string declar = "(?:" + space + designEntity + space + IDENT + space + "(?:," + space + IDENT + space + ")*" + ";)*";
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
const string patternEntRef = "(?:" + IDENT + "|\"" + IDENT + "\"|" + INTEGER + "|_|\\(|\\)|\"|\\+|-|\\*)";

const string IF = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "_" + space + "," + space + "_" + space + "\\))";
const string WHILE = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "_" + space + "\\))";
const string assign = "(?:" + IDENT + space + "\\(" + space + varRef + space + "," + space + "(?:" + expressionSpec + "|" + "_)" + space + "\\))";
const string pattern = "(?:" + assign + "|" + WHILE + "|" + IF + ")";
const string patternCond = "(?:" + pattern + space + "(?:and" + space + pattern + space + ")*)";

const string withCl = "(?:with" + space + attrCond + ")";
const string suchthatCl = "(?:such that" + space + relCond + ")";
const string patternCl = "(?:pattern" + space + patternCond + ")";
const string patternClAnother = "(?:pattern" + space + pattern + ")";

const string resultCl = "(?:BOOLEAN|" + TUPLE + ")";
const string selectOnly = space + "Select" + space + resultCl + space;
const string suchthatOnly = space + relRef + space;
const string patternOnly = space + patternClAnother + space;
const string withOnly = space + attrCompare + space;
const string selectClause = space + "Select" + space + resultCl + space + "(?:(?:" + suchthatCl + "|" + withCl + "|" + patternCl + ")" + space + ")*";

const regex declarationChecking(declar);
const regex declarationParsing(declarPar);
const regex declarationWordParsing(IDENT);
const regex queryChecking(selectClause);
const regex queryParseSelect(selectOnly);
const regex queryParseNormalClauses(suchthatOnly);
const regex queryParsePattern(patternOnly);
const regex queryParseWith(withOnly);
const regex queryWordParsingSelect(IDENT);
const regex queryWordParsingNormalClause(entRefWithStar);
const regex queryWordParsingPattern(patternEntRef);
const regex queryWordParsingWith(REF);

ParseResult ParseResult::generateParseResult(string declarationSentence, string querySentence) {
	unordered_map<string, string> declarationTable;
	bool correct = ParseResult::checkAndParseDeclaration(declarationSentence, declarationTable);

	if (!correct) {
		return ParseResult();
	}

	ParseResult result = ParseResult::checkAndParseQuery(querySentence, declarationTable);
	return result;
}

bool ParseResult::checkAndParseDeclaration(string declaration, unordered_map<string, string>& declarationTable) {
	if (!regex_match(declaration, declarationChecking)) {
		signalErrorAndStop();
		return false;
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
				|| word == "constant" || word == "prog_line" || word == "procedure" || word == "if") {
				if (!typeSelected) {
					type = word;
					typeSelected = true;
				}
				else {
					signalErrorAndStop();
					return false;
				}
			}
			else {
				if (declarationTable[word] != "") {
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
	string selectPhrase;
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
			if (declarationTable[*it] == "") {
				cout << "228" << endl;
				signalErrorAndStop();
				return ParameterSet();
			}
			else if (it != prev(word.end()) && (*std::next(it) == "procName" || *std::next(it) == "varName" ||
				*std::next(it) == "value" || *std::next(it) == "stmt#")) {
				continue;
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
			else if (current.front() == '"' && current.back() == '"') {
				if (*prev(it) == "Modifies" || *prev(it) == "Uses" || *prev(it) == "Calls" || *prev(it) == "Calls*" || *prev(it) == "Parent" ||
					*prev(it) == "Parent*" || *prev(it) == "Follows" || *prev(it) == "Follows*" || *prev(it) == "Next" || *prev(it) == "Next*" ||
					*prev(it) == "Affects" || *prev(it) == "Affects*") {
					firstParam = current;
					string type = *prev(it);
					if (type == "Modifies" || type == "Uses" || type == "Calls" || type == "Calls*") {
						firstPType = "p";
						counter++;
					}
					else {
						ClauseSet c;
						c.push_back(Clause("dummy", "dummy", "dummy"));
						return c;
					}
				}
				else {
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
						ClauseSet c;
						c.push_back(Clause("dummy", "dummy", "dummy"));
						return c;
					}
				}
			}
			else {
				if (regex_match(current, regex(INTEGER))) {
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
						else {
							ClauseSet c;
							c.push_back(Clause("dummy", "dummy", "dummy"));
							return c;
						}
					}
					else {
						secondParam = current;
						string type = *prev(prev(it));
						if (type == "Modifies" || type == "Uses" || type == "Calls" || type == "Calls*") {
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
				else if (current == "_") {
					if (*prev(it) == "Modifies" || *prev(it) == "Uses" || *prev(it) == "Calls" || *prev(it) == "Calls*" || *prev(it) == "Parent" ||
						*prev(it) == "Parent*" || *prev(it) == "Follows" || *prev(it) == "Follows*" || *prev(it) == "Next" || *prev(it) == "Next*" ||
						*prev(it) == "Affects" || *prev(it) == "Affects*") {
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
						else {
							ClauseSet c;
							c.push_back(Clause("dummy", "dummy", "dummy"));
							return c;
						}
					}
					else {
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
				else {
					if (declarationTable[current] == "") {
						ClauseSet c;
						c.push_back(Clause("dummy", "dummy", "dummy"));
						return c;
					}
					else {
						if (*prev(it) == "Modifies" || *prev(it) == "Uses" || *prev(it) == "Calls" || *prev(it) == "Calls*" || *prev(it) == "Parent" ||
							*prev(it) == "Parent*" || *prev(it) == "Follows" || *prev(it) == "Follows*" || *prev(it) == "Next" || *prev(it) == "Next*" ||
							*prev(it) == "Affects" || *prev(it) == "Affects*") {
							firstParam = current;
							firstPType = declarationTable[current];
							string type = *prev(it);
							if (type == "Modifies" || type == "Uses") {
								if (firstPType == "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else if (type == "Calls" || type == "Calls*") {
								if (firstPType != "procedure") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else {
								if (firstPType == "procedure" || firstPType == "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							counter++;
							if (firstPType == "prog_line") {
								firstPType = "l";
							}
							else {
								firstPType = firstPType.substr(0, 1);
							}
						}
						else {
							secondParam = current;
							secondPType = declarationTable[current];
							string type = *prev(prev(it));
							if (type == "Modifies" || type == "Uses") {
								if (secondPType != "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else if (type == "Calls" || type == "Calls*") {
								if (secondPType != "procedure") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							else {
								if (secondPType == "procedure" || secondPType == "variable") {
									ClauseSet c;
									c.push_back(Clause("dummy", "dummy", "dummy"));
									return c;
								}
							}
							counter++;
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

			if (counter == 3) {
				clauseType += firstPType + secondPType;
				if (regex_match(firstParam, regex(INTEGER)) || regex_match(firstParam, regex(VAR))) {
					if (regex_match(secondParam, regex(INTEGER)) || regex_match(secondParam, regex(VAR))) {
						zeroSynonyms.push_back(Clause(clauseType, firstParam, secondParam));
					}
					else {
						oneSynonym.push_back(Clause(clauseType, firstParam, secondParam));
					}
				}
				else {
					if (regex_match(secondParam, regex(INTEGER)) || regex_match(secondParam, regex(VAR))) {
						oneSynonym.push_back(Clause(clauseType, firstParam, secondParam));
					}
					else {
						twoSynonyms.push_back(Clause(clauseType, firstParam, secondParam));
					}
				}
			}
		}
		word.clear();
	}

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

		word.erase(word.begin() + 2);
		word.erase(prev(word.end()));

		string patternType;
		string firstParam;
		string secondParam;
		string thirdParam;
		string current;
		string patternTypeTemp;
		vector<string>::iterator it;
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
			else {
				if (patternTypeTemp == "if") {
					firstParam = current;
					if (firstParam.front() != '"' && firstParam.back() != '"') {
						if (firstParam == "_") {}
						else if (declarationTable[firstParam] == "") {
							PatternSet p;
							p.push_back(Pattern("dummy", "dummy", "dummy"));
							return p;
						}
					}
					secondParam = "_";
					thirdParam = "_";
					ifAndWhilePattern.push_back(Pattern(patternType, firstParam, secondParam, thirdParam));
					++it; ++it;
				}
				else if (patternTypeTemp == "while") {
					firstParam = current;
					if (firstParam.front() != '"' && firstParam.back() != '"') {
						if (firstParam == "_") {}
						else if (declarationTable[firstParam] == "") {
							PatternSet p;
							p.push_back(Pattern("dummy", "dummy", "dummy"));
							return p;
						}
					}
					secondParam = "_";
					ifAndWhilePattern.push_back(Pattern(patternType, firstParam, secondParam));
					++it;
				}
				else {
					firstParam = current;
					if (firstParam.front() != '"' && firstParam.back() != '"') {
						if (firstParam == "_") {}
						else if (declarationTable[firstParam] == "") {
							PatternSet p;
							p.push_back(Pattern("dummy", "dummy", "dummy"));
							return p;
						}
					}
					++it;
					secondParam.clear();
					while (it != word.end()) {
						current = *it;
						secondParam += current;
						++it;
					}
					--it;
					assignPattern.push_back(Pattern(patternType, firstParam, secondParam));
				}
			}
		}
		word.clear();
	}
	patterns.reserve(ifAndWhilePattern.size() + assignPattern.size());
	patterns.insert(patterns.end(), ifAndWhilePattern.begin(), ifAndWhilePattern.end());
	patterns.insert(patterns.end(), assignPattern.begin(), assignPattern.end());
	return patterns;
}

WithSet ParseResult::parseWith(string query, unordered_map<string, string>& declarationTable) {
	vector<string> withPhrase;
	sregex_iterator next(query.begin(), query.end(), queryParseWith);
	sregex_iterator end;
	while (next != end) {
		smatch match = *next;
		withPhrase.push_back(match.str(0));
		next++;
	}

	vector<string> word;
	vector<string>::iterator it1;
	WithSet withClause;
	WithSet zeroAttrRefs;
	WithSet oneAttrRef;
	WithSet twoAttrRefs;

	for (it1 = withPhrase.begin(); it1 != withPhrase.end(); ++it1) {
		string currentPhrase = *it1;
		next = sregex_iterator(currentPhrase.begin(), currentPhrase.end(), queryWordParsingWith);
		while (next != end) {
			smatch match = *next;
			word.push_back(match.str(0));
			next++;
		}

		string left;
		string right;
		string current;
		vector<string>::iterator it;
		
		bool onTheLeft = true;
		int attrRefCount = 0;
		bool leftIsInt;

		for (it = word.begin(); it != word.end(); ++it) {
			current = *it;
			if (onTheLeft) {
				left = current;
				if (left.front() == '"' && left.back() == '"') {
					leftIsInt = false;
				}
				else if (regex_match(left, regex(INTEGER))) {
					leftIsInt = true;
				}
				else if (regex_match(left, regex(IDENT))) {
					if (declarationTable[left] == "" || declarationTable[left] != "prog_line") {
						WithSet w;
						w.push_back(With("dummy", "dummy"));
						return w;
					}
					leftIsInt = true;
				}
				else {
					int dotPos = left.find(".");
					string synonym = left.substr(0, dotPos);
					string attribute = left.substr(dotPos + 1, left.size() - dotPos);
					if (declarationTable[synonym] == "") {
						WithSet w;
						w.push_back(With("dummy", "dummy"));
						return w;
					}
					else if (declarationTable[synonym] == "procedure") {
						if (attribute != "procName") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						leftIsInt = false;
						attrRefCount++;
					}
					else if (declarationTable[synonym] == "variable") {
						if (attribute != "varName") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						leftIsInt = false;
						attrRefCount++;
					}
					else if (declarationTable[synonym] == "constant") {
						if (attribute != "value") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						leftIsInt = true;
						attrRefCount++;
					}
					else {
						if (attribute != "stmt#") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						leftIsInt = true;
						attrRefCount++;
					}
				}
				onTheLeft = false;
			}
			else {
				right = current;
				if (leftIsInt) {
					if (right.front() == '"' && right.back() == '"') {
						WithSet w;
						w.push_back(With("dummy", "dummy"));
						return w;
					}
					else if (regex_match(right, regex(INTEGER))) {}
					else if (regex_match(right, regex(IDENT))) {
						if (declarationTable[right] == "" || declarationTable[right] != "prog_line") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
					}
					else {
						int dotPos = right.find(".");
						string synonym = right.substr(0, dotPos);
						string attribute = right.substr(dotPos + 1, left.size() - dotPos);
						if (declarationTable[synonym] == "") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						else if (declarationTable[synonym] == "procedure") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						else if (declarationTable[synonym] == "variable") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						else if (declarationTable[synonym] == "constant") {
							if (attribute != "value") {
								WithSet w;
								w.push_back(With("dummy", "dummy"));
								return w;
							}
							else {
								attrRefCount++;
							}
						}
						else {
							if (attribute != "stmt#") {
								WithSet w;
								w.push_back(With("dummy", "dummy"));
								return w;
							}
							else {
								attrRefCount++;
							}
						}
					}
				}
				else {
					if (regex_match(right, regex(IDENT))) {
						WithSet w;
						w.push_back(With("dummy", "dummy"));
						return w;
					}
					else if (regex_match(right, regex(INTEGER))) {
						WithSet w;
						w.push_back(With("dummy", "dummy"));
						return w;
					}
					else if (right.front() == '"' && right.back() == '"') {}
					else {
						int dotPos = right.find(".");
						string synonym = right.substr(0, dotPos);
						string attribute = right.substr(dotPos + 1, right.size() - dotPos);
						if (declarationTable[synonym] == "") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						else if (declarationTable[synonym] == "procedure") {
							if (attribute != "procName") {
								WithSet w;
								w.push_back(With("dummy", "dummy"));
								return w;
							}
							else {
								attrRefCount++;
							}
						}
						else if (declarationTable[synonym] == "variable") {
							if (attribute != "varName") {
								WithSet w;
								w.push_back(With("dummy", "dummy"));
								return w;
							}
							else {
								attrRefCount++;
							}
						}
						else if (declarationTable[synonym] == "constant") {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
						else {
							WithSet w;
							w.push_back(With("dummy", "dummy"));
							return w;
						}
					}
				}
				onTheLeft = true;
			}
		}
		if (attrRefCount == 0) {
			zeroAttrRefs.push_back(With(left, right));
		}
		else if (attrRefCount == 1) {
			oneAttrRef.push_back(With(left, right));
		}
		else {
			twoAttrRefs.push_back(With(left, right));
		}
		word.clear();
	}
	withClause.reserve(zeroAttrRefs.size() + oneAttrRef.size() + twoAttrRefs.size());
	withClause.insert(withClause.end(), zeroAttrRefs.begin(), zeroAttrRefs.end());
	withClause.insert(withClause.end(), oneAttrRef.begin(), oneAttrRef.end());
	withClause.insert(withClause.end(), twoAttrRefs.begin(), twoAttrRefs.end());
	return withClause;
}

bool ParseResult::checkWholeQuery(string query) {
	if (!regex_match(query, queryChecking)) return false;
	return true;
}

ParseResult ParseResult::checkAndParseQuery(string query, unordered_map<string, string>& declarationTable) {
	ParameterSet selectParameter;
	ClauseSet clauses;
	PatternSet patterns;
	WithSet withClauses;

	cout << query << endl;
	bool correct = ParseResult::checkWholeQuery(query);

	if (!correct) {
		signalErrorAndStop();
		return ParseResult();
	}
	
	selectParameter = ParseResult::parseSelect(query, declarationTable);
	if (selectParameter.empty()) return ParseResult();
	
	clauses = ParseResult::parseNormalClauses(query, declarationTable);
	if (clauses.size() != 0) {
		if (clauses.front().getClauseOperation() == "dummy") {
			signalErrorAndStop();
			return ParseResult();
		}
	}
	
	patterns = ParseResult::parsePattern(query, declarationTable);

	if (patterns.size() != 0) {
		if (patterns.front().getPatternOperation() == "dummy") {
			signalErrorAndStop();
			return ParseResult();
		}
	}

	if (withClauses.size() != 0) {
		withClauses = ParseResult::parseWith(query, declarationTable);
		if (withClauses.front().getLeftOfEqualSign() == "dummy") {
			signalErrorAndStop();
			return ParseResult();
		}
	}
	
	return ParseResult(selectParameter, clauses, patterns, withClauses);
}

void ParseResult::signalErrorAndStop() {
	cout << "Grammar error, query will not be evaluated" << endl;
	return;
}