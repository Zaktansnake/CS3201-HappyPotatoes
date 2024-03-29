#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PQL/Header/ParseResult.h"
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(testParseResult)
	{
	public:

		TEST_METHOD(testCheckAndParseDeclaration)
		{
			// TODO: Your test code here
			unordered_map<string, string> declarationTable;
			string declarationSentence = "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3;";
			bool correct = ParseResult::checkAndParseDeclaration(declarationSentence, declarationTable);
			Assert::AreEqual(correct, true);
			Assert::AreEqual(declarationTable["a1"], string("assign"));
			Assert::AreEqual(declarationTable["a2"], string("assign"));
			Assert::AreEqual(declarationTable["a3"], string("assign"));
			Assert::AreEqual(declarationTable["s1"], string("stmt"));
			Assert::AreEqual(declarationTable["s2"], string("stmt"));
			Assert::AreEqual(declarationTable["s3"], string("stmt"));
			Assert::AreEqual(declarationTable["v1"], string("variable"));
			Assert::AreEqual(declarationTable["v2"], string("variable"));
			Assert::AreEqual(declarationTable["v3"], string("variable"));
			return;
		}

		TEST_METHOD(testCheckAndParseDeclarationDuplicateSynonym) {
			unordered_map<string, string> declarationTable;
			string declarationSentence = "assign a1, a2, a3; stmt a1;";
			bool correct = ParseResult::checkAndParseDeclaration(declarationSentence, declarationTable);
			Assert::IsFalse(correct);
		}

		TEST_METHOD(testCheckAndParseDeclarationSynonymSameAsKeyword) {
			unordered_map<string, string> declarationTable;
			string declarationSentence = "assign a1, a2, a3; stmt stmt;";
			bool correct = ParseResult::checkAndParseDeclaration(declarationSentence, declarationTable);
			Assert::IsFalse(correct);
		}

		TEST_METHOD(testParsingSelectWithoutAttrCompare) {
			unordered_map<string, string> declarationTable{ { "s1","stmt" },{ "s2","stmt" },{ "v2","variable" } };
			string querySentence = "Select <s1, s2, v2> such that Uses (5, \"y\") and Follows (3, 4)";
			ParameterSet selectParameter = ParseResult::parseSelect(querySentence, declarationTable);
			vector<string>::iterator it;
			string result;
			for (it = selectParameter.begin(); it != selectParameter.end(); ++it) {
				result += "[" + *it + "]";
			}
			Assert::AreEqual(result, string("[s1,stmt][s2,stmt][v2,variable]"));
		}

		TEST_METHOD(testParsingSelectWithAttrCompare) {
			unordered_map<string, string> declarationTable{ { "s1","stmt" },{ "s2","stmt" },{ "v2","variable" } };
			string querySentence = "Select <s1.stmt#,   v2.varName,s2   > such that Uses (5, \"y\") and Follows (3, 4)";
			ParameterSet selectParameter = ParseResult::parseSelect(querySentence, declarationTable);
			vector<string>::iterator it;
			string result;
			for (it = selectParameter.begin(); it != selectParameter.end(); ++it) {
				result += "[" + *it + "]";
			}
			Assert::AreEqual(result, string("[s1.stmt#][v2.varName][s2,stmt]"));
		}

		TEST_METHOD(testParsingNormalClauses1) {
			unordered_map<string, string> declarationTable{ { "s1","stmt" },{ "s2","stmt" },{ "v2","variable" } };
			string querySentence = "Select <s1.stmt#,   v2.varName,s2   > such that Uses (5, \"y\") and Follows (3, 4) such that Modifies (s1,v2) and Affects* (2,s2)";
			ClauseSet normalClauses = ParseResult::parseNormalClauses(querySentence, declarationTable);
			Clause resultClause = normalClauses[0];
			string clauseType = resultClause.getClauseOperation();
			string firstParam = resultClause.getFirstParameter();
			string secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(clauseType, string("Usessv"));
			Assert::AreEqual(firstParam, string("5"));
			Assert::AreEqual(secondParam, string("\"y\""));
			resultClause = normalClauses[1];
			clauseType = resultClause.getClauseOperation();
			firstParam = resultClause.getFirstParameter();
			secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(clauseType, string("Followsss"));
			Assert::AreEqual(firstParam, string("3"));
			Assert::AreEqual(secondParam, string("4"));
			resultClause = normalClauses[2];
			clauseType = resultClause.getClauseOperation();
			firstParam = resultClause.getFirstParameter();
			secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(clauseType, string("Affects*ss"));
			Assert::AreEqual(firstParam, string("2"));
			Assert::AreEqual(secondParam, string("s2"));
			resultClause = normalClauses[3];
			clauseType = resultClause.getClauseOperation();
			firstParam = resultClause.getFirstParameter();
			secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(clauseType, string("Modifiessv"));
			Assert::AreEqual(firstParam, string("s1"));
			Assert::AreEqual(secondParam, string("v2"));
		}

		TEST_METHOD(testParsingNormalClauses2) {
			unordered_map<string, string> declarationTable{ { "lol","procedure" },{ "jack","procedure" },{ "joke","procedure" } };
			string querySentence = "Select BOOLEAN such that Calls (\"bread\", \"butter\") and Calls* (lol, \"haha\") such that Calls (jack,joke)";
			ClauseSet normalClauses = ParseResult::parseNormalClauses(querySentence, declarationTable);
			Clause resultClause = normalClauses[0];
			string clauseType = resultClause.getClauseOperation();
			string firstParam = resultClause.getFirstParameter();
			string secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(clauseType, string("Callspp"));
			Assert::AreEqual(firstParam, string("\"bread\""));
			Assert::AreEqual(secondParam, string("\"butter\""));
			resultClause = normalClauses[1];
			clauseType = resultClause.getClauseOperation();
			firstParam = resultClause.getFirstParameter();
			secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(clauseType, string("Calls*pp"));
			Assert::AreEqual(firstParam, string("lol"));
			Assert::AreEqual(secondParam, string("\"haha\""));
			resultClause = normalClauses[2];
			clauseType = resultClause.getClauseOperation();
			firstParam = resultClause.getFirstParameter();
			secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(clauseType, string("Callspp"));
			Assert::AreEqual(firstParam, string("jack"));
			Assert::AreEqual(secondParam, string("joke"));
		}

		TEST_METHOD(testParsingPattern) {
			unordered_map<string, string> declarationTable{ { "RoMeo###","assign" },{ "Ju1i3t#","assign" },{ "v2","variable" } };
			string querySentence = "Select BOOLEAN such that Uses (5, \"y\") pattern RoMeo### (v2,_\"x+y\"_) with Ju1i3t#.stmt# = 20 pattern Ju1i3t#(\"z\" , _)";
			PatternSet patternClauses = ParseResult::parsePattern(querySentence, declarationTable);
			Pattern resultClause = patternClauses[0];
			string patternType = resultClause.getPatternOperation();
			string firstParam = resultClause.getFirstParameter();
			string secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(patternType, string("RoMeo###,assign"));
			Assert::AreEqual(firstParam, string("v2"));
			Assert::AreEqual(secondParam, string("_\"x+y\"_"));
			resultClause = patternClauses[1];
			patternType = resultClause.getPatternOperation();
			firstParam = resultClause.getFirstParameter();
			secondParam = resultClause.getSecondParameter();
			Assert::AreEqual(patternType, string("Ju1i3t#,assign"));
			Assert::AreEqual(firstParam, string("\"z\""));
			Assert::AreEqual(secondParam, string("_"));
		}

		TEST_METHOD(testParsingWith) {
			unordered_map<string, string> declarationTable{ { "RoMeo###","prog_line" },{ "Ju1i3t#","procedure" },{ "v2","variable" } };
			string querySentence = "Select BOOLEAN such that Uses (5, \"y\") with RoMeo### = 2 and with \"Apple\" =Ju1i3t#.procName  and with v2.varName = \"xii\"";
			WithSet withClauses = ParseResult::parseWith(querySentence, declarationTable);
			With resultClause = withClauses[0];
			string leftSide = resultClause.getLeftOfEqualSign();
			string rightSide = resultClause.getRightOfEqualSign();
			Assert::AreEqual(string("RoMeo###"), leftSide);
			Assert::AreEqual(string("2"), rightSide);
			resultClause = withClauses[1];
			leftSide = resultClause.getLeftOfEqualSign();
			rightSide = resultClause.getRightOfEqualSign();
			Assert::AreEqual(string("\"Apple\""), leftSide);
			Assert::AreEqual(string("Ju1i3t#.procName"), rightSide);
			resultClause = withClauses[2];
			leftSide = resultClause.getLeftOfEqualSign();
			rightSide = resultClause.getRightOfEqualSign();
			Assert::AreEqual(string("v2.varName"), leftSide);
			Assert::AreEqual(string("\"xii\""), rightSide);
		}
	};
}