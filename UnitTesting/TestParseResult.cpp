#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "../source/PQL/Header/ParseResult.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestParseResult)
	{
	public:
		TEST_METHOD(TestP) {
			string testDeclaration, testQuery;

			// test for generateParseResult
			testDeclaration = "";
			testQuery = "";
			ParseResult expectedResult = ParseResult(); // should construct a object with the expected query tested, need to insert in correct formatted query
			ParseResult p = ParseResult();
			ParseResult result = p.generateParseResult(testDeclaration, testQuery);

			Assert::AreEqual(result, expectedResult);
		}
	};
}