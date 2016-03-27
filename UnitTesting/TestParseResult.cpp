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

		TEST_METHOD(testRegex) {
			const string selectClause = "\\s*Select\\s+(\\w+\\d*#*|<\\w+\\d*#*\\s*(,\\s*\\w+\\d*#*\\s*)+>)\\s+";
			const string conditionClause = "(such\\s+that\\s+(Follows|Follows\\*|Parent|Parent\\*|Modifies|Uses)\\s*\\(\\s*(\\d+|\\w+\\d*#*|_)\\s*,\\s*(\"\\w+\\d*#*\"|\\w+\\d*#*|_)\\s*\\)\\s*)?";
			const string patternClause = "((pattern)\\s+(\\w+\\d*#*)\\s*\\(\\s*(\"\\w+\\d*#*\"|\\w+\\d*#*|_)\\s*,\\s*(_\"\\w+\\d*\"_|_|_\"\\d+\"_)\\s*\\)\\s*)?";
			
			// test selectClause regex
			regex test1(selectClause);
			Assert::IsTrue(regex_match("Select <s1, s2, v2   > ", test1));
			Assert::IsFalse(regex_match("Select <s1, s2, v2 126879  > ", test1));
		}

	};
}