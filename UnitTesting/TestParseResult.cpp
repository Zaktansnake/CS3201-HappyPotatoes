#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PQL/Header/ParseResult.h"

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

	};
}