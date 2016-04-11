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

		TEST_METHOD(testParsingNormalClauses) {
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
	};
}