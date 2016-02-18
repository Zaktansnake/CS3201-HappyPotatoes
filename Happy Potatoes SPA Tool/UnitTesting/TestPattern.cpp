#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PKB.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/Pattern.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPattern)
	{
	public:
		TEST_METHOD(TestP) {
			Pattern p;
			string testPattern, expectedPattern, returnedPattern;

			// test for patternAssignment
			testPattern = "a+b+c+d";
			expectedPattern = "(a+b)+c+d";

			returnedPattern = p.patternAssignment(testPattern);

			Assert::AreEqual(expectedPattern, returnedPattern);

			testPattern = "a*b+c+d";
			expectedPattern = "(a*b)+c+d";

			returnedPattern = p.patternAssignment(testPattern);

			Assert::AreEqual(expectedPattern, returnedPattern);

			testPattern = "a*b+(c-d)";
			expectedPattern = "(a*b)+(c-d)";

			returnedPattern = p.patternAssignment(testPattern);

			Assert::AreEqual(expectedPattern, returnedPattern);
		}
	};
}