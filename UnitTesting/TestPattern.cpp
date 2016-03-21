#include <iostream>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/Patterns.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPattern)
	{
	public:
		TEST_METHOD(TestP) {
			Patterns p;
			string testPattern, expectedPattern, returnedPattern;

			// test for patternAssignment
			testPattern = "a+(b+c)+d";
			expectedPattern = "a+(b+c)+d";
			returnedPattern = p.patternAssignment(testPattern);

			Assert::AreEqual(expectedPattern, returnedPattern);

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

			testPattern = "_\"a*b+(c-d)\"_";
			expectedPattern = "_\"(a*b)+(c-d)\"_";
			returnedPattern = p.patternAssignment(testPattern);

			Assert::AreEqual(expectedPattern, returnedPattern);
		}
	};
}