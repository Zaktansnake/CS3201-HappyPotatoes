#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <regex>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
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


	TEST_CLASS(testRegex)
	{
	public:

		TEST_METHOD(testDeclaration) {
			regex test(declar);
			Assert::IsTrue(regex_match("assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3;", test));
			// wrong type
			Assert::IsFalse(regex_match("ASSIGN a1, a2;",test));
			// wrong synonym syntax
			Assert::IsFalse(regex_match("stmt 9999;", test));
			// duplicated synonym
			Assert::IsFalse(regex_match("stmt s1,s1;", test));
			// redundant punctuation
			Assert::IsFalse(regex_match("stmt s1,,s2;", test));
			Assert::IsFalse(regex_match("stmt s1,s2;;", test));
		}

	};
}