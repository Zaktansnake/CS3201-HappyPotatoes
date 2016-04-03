#include <iostream>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PQL/Header/QueryEvaluator.h"
#include "../source/PQL/Header/QueriesAnswerStorage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryEvaluator)
	{
	public:
		TEST_METHOD(TestQE) {

			string fileName = "..\Release\Sample-Source02.txt";

			Parser::parse(fileName);

			/*
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
			*/
		}
	};
}